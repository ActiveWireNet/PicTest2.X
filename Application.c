//	The Main Logic for Fast Switch Debounce DEMO.  This includes Initialization and a Main
//	Loop, a Queue Handler for Switch Changes, a "Debounce Expiration" Queue, a Single Byte
//	for Task Management (SwitchChange Queue and Timer0 Tick), and a very simple Switch
//	Change Handler that turns LEDs On and Off.

//	A more detailed explanation of SOME of this code can be found in SwitchHandler.md.

//	The Main Loop checks the Task Mask.  SwitchChanges (if any) in the SwitchChange Queue
//	are handled first.  Then a Timer Tick will be processed if one is Pending.  In this Demo
//	the Timer Tick is used only to time the Debounce Expiration Queue.

//	All Changes are Serialized by using the Event Queue which is processed here.
//	Interrupts only ADD to the EventQueue.  They DO NOT change State.  All
//	Manipulation of State and Peripherals (except IOC) is Done at the Task
//	(Non-Interrupt) Level to Avoid Concurrency Issues in the Code.

//	The "Debounce Expiration" Queue is a very simplified time-based event queue.  Only
//	one event type (Debounce Expiration) with a fixed timeout is supported.  Insertions and
//	Expirations are the only supported actions.  Entries are simply a Mask of Switches
//	being Debounced.  The DebounceQueue manages the expiration times as Deltas.

//	SwitchHandler.c Calls Back to this code (AppSwitchChanged) which turns three (3) LEDs
//	On and Off.  This indirection allows SwitchHandler to be Independent of the Application.

//	MCC System Register Setup is used to Power Down ALL Peripherals except the IOC module.

//	NOTE that an actual, useful version of this code will support more tasks.

//	Resources (see MCC):
//	1.	Timer0.
//	2.	PortC (Switches) and PortA (LEDs)


#include <xc.h>

#include "Application.h"
#include "SwitchHandler.h"

#include "mcc_generated_files/system/system.h"


#pragma		warning disable 520			// function XYZ is never called


//	#define for Debounce _Ticks_.  Note: Tick = 2 ms. (Set via MCC).
//	Round Up for safety.  The extra "1" is needed as the next tick could be immediate.
//	The smallest value consistent with the Switches and the problem is best.
//	'SwitchDebounceMicroseconds' is #defined in SwitchHandler.h.  Modify there.
#define AppDebounceTicks	((SwitchDebounceMicroseconds + 1999) / 2000 + 1)


//	Tasking Control Structure: Union of a Byte and a Bit-Mask.

typedef union {
    uint8_t AllBits; // For testing ALL tasks at once.

    struct {
        unsigned int SwitchChange : 1; // Switch Changed.
        unsigned int DebounceTick : 1; // Debounce Tick.
    };
} TaskMaskBits_t;

volatile TaskMaskBits_t TaskMask; // Controls Main-Loop (Sub-) Tasking.


//	Timer0 Interrupts Every 2 ms. when Running.  Sets TaskMask.DebounceTick.
//		Deferring Activity to MainLoop Prevents Debounce Queue from Being Volatile.
//		TaskMask is Volatile.  [As is the SwitchChangeQueue.]

void Timer0_InterruptHandler(void) {
    TaskMask.DebounceTick = 1; // Trigger Tick Processing Task.
}


//	Declare an SwitchChange Queue with Eight (8) Entries (16 Bytes).
//	Each Entry is a Pair: the Switch Change Mask and Switch States.
//	The EntryCount Must be >= Switch Count.
#define				SwitchChangeQueueLength		(1 << 4)	// MUST BE 2^N: Wrap using Mask.
#define				SwitchChangeQueueLengthMask	(SwitchChangeQueueLength - 1)
volatile SFR_T SwitchChanges[SwitchChangeQueueLength];
volatile uint8_t SwitchChangeNext = 0;
uint8_t SwitchChangeLast = 0;

#if (SwitchChangeQueueLength < (SwitchCount*2))
#error "Switch Queue Too Small."
#endif

//	Enqueue a SwitchChange.  Called from Interrupt Handler ONLY.

void AppSwitchChangeEnqueue(SFR_T mask, SFR_T value) {
    SwitchChanges[SwitchChangeNext++ & SwitchChangeQueueLengthMask] = mask;
    SwitchChanges[SwitchChangeNext++ & SwitchChangeQueueLengthMask] = value;
    TaskMask.SwitchChange = 1; // Inform MainLoop Queue Occupied.
}

//	Dequeue a SwitchChange SFR.  Called by MainLoop ONLY.  Always Called Twice.

SFR_T SwitchChangeDequeue(void) {
    return SwitchChanges[SwitchChangeLast++ & SwitchChangeQueueLengthMask];
}

//	Inform Caller if the SwitchChange Queue is Occupied.  Called by MainLoop ONLY.

uint8_t SwitchChangeQueueOccupied(void) {
    return (SwitchChangeNext - SwitchChangeLast);
}


//	Declare a DebounceTiming Queue with Eight (8) Entries.  Entry Count >= Switch Count.
//	Uses Two (2) Separate Arrays to Speed Indexing and Avoid a Struct.
//	The 'TimerTotal' is the SUM of the Active Elements Delays which are DELTAs.
//	The Count (or Delay) for Each Entry is FIXED.  The Code ASSUMES This.
//	This IS NOT a General Purpose Time Queue.
#define		DebounceTimerQueueLength		(1 << 3)	// MUST BE 2^N: Wrap Using Mask.
#define		DebounceTimerQueueLengthMask	(DebounceTimerQueueLength - 1)
uint8_t DebounceTimerCounts[DebounceTimerQueueLength];
SFR_T DebounceTimerMasks [DebounceTimerQueueLength];
uint8_t DebounceTimerNext = 0; // Index of NEXT Element to Add to Queue.
uint8_t DebounceTimerLast = 0; // Index of LAST Unprocessed Element in the Queue.
uint8_t DebounceTimerTotal = 0; // Total of Counts in Debounce Queue.

#if (DebounceTimerQueueLength < SwitchCount)
#error "Debounce Timer Queue Too Small."
#endif

//	Enqueue a Debounce Timer.  Called by MainLoop (Indirectly) ONLY.

void AppDebounceTimerEnqueue(SFR_T mask) {
    //	Turn Timer0 ON if Currently Off.
    if (PMD1bits.TMR0MD) {
        PMD1bits.TMR0MD = 0; // Timer0 - Turn Power ON.
        TMR0_Initialize(); // (Re-)Initialize.  Power was OFF.
        TMR0_Start(); // Start Timer0.
        CPUDOZEbits.IDLEN = 1; // Idle ENable, SLEEP is IDLE (Clocks Run, CPU No).
    }

    //	Add Entry to End of Queue.  Compute its TimeDelta.  Set Total Time to the Fixed Count.
    DebounceTimerMasks [DebounceTimerNext & DebounceTimerQueueLengthMask] = mask;
    DebounceTimerCounts[DebounceTimerNext & DebounceTimerQueueLengthMask] =
            AppDebounceTicks - DebounceTimerTotal;
    DebounceTimerTotal = AppDebounceTicks;
    DebounceTimerNext++;
}

//	Dequeue a Debounce Timer Mask.  Count NOT Used.  Called by MainLoop ONLY.

SFR_T DebounceTimerDequeue(void) {
    return DebounceTimerMasks[DebounceTimerLast++ & DebounceTimerQueueLengthMask];
}

//	Inform Caller if the Debounce Queue is Occupied.  Called by MainLoop ONLY.

uint8_t DebounceTimerQueueOccupied(void) {
    return (DebounceTimerNext - DebounceTimerLast);
}


//	Called by Main when a DebounceTick is Noted in the TaskMask.

void AppDebounceTick(void) {
    //	Check Switch Debounce Queue.
    if (DebounceTimerQueueOccupied()) {
        DebounceTimerTotal--;
        DebounceTimerCounts[DebounceTimerLast & DebounceTimerQueueLengthMask]--;
        while (DebounceTimerQueueOccupied() &&
                DebounceTimerCounts[DebounceTimerLast & DebounceTimerQueueLengthMask] == 0) {
            SwitchDebounceEnd(DebounceTimerDequeue()); // Top Queue Entry 'Expired'.
        }
    }

    //	If Queue Now Empty, Turn Timer0 OFF and Turn DOZE OFF (Turn ON Full SLEEP).
    if (!DebounceTimerQueueOccupied()) {
        PMD1bits.TMR0MD = 1; // Disable Timer0 - Save Power.
        CPUDOZEbits.IDLEN = 0; // Idle DISable, Full SLEEP.  Timer0 ONLY Clock User.
    }
}

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 


//	Maps Raw Switch Changes to Application-Specific use of Switches.
//	Handle Switches in N (= 3) On/Off Pairs for the N LEDs Supported.
//	This is just for Demonstration purposes.
//	Note 1: Assumes Switch Bits: In Pairs, Dense, Right-Justified.
//	Note 2: This simple example does not use 'oldSwitches'.

void AppSwitchChanged(SFR_T oldSwitches, SFR_T newSwitches) {
__delay_ms(2);
printf("\r\n-----------\r\n");
SFR_T delta = (oldSwitches ^ newSwitches) & SwitchMask;
printf("delta      "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(delta));
printf("\r\n");
if (0==delta) return; // nothing changed
    //	Change to Positive Logic.
    newSwitches = ~newSwitches;
    if (delta & PIN_TRIGGER) {
        if (newSwitches & PIN_TRIGGER) {
            printf("Trigger on\r\n");
            LED_POWER_SetLow();
        } else {
            printf("Trigger off\r\n");
            LED_POWER_SetHigh();
        }
    }
    if (delta & PIN_POWER) {
        if (newSwitches & PIN_POWER) {
            printf("PowerSw on\r\n");
            LED_STANDBY_SetLow();
        } else {
            printf("PowerSw off\r\n");
            LED_STANDBY_SetHigh();
        }
    }
}


//	Initialize CPUDOZE, VREGPM, SwitchHandler and Interrupts.
//	Main Loop (Forever):
//		Each Pass: Process ActionQueue and New DebounceTick (If Any).
//		When No Tasks Ready: Sleep Until Interrupt (Timer0 or IOC) is Serviced.
//		JUST A DEMO Program.  Real Code would handle more tasks.

void ApplicationMain(void) {
//    printf(" \r\nhello world \r\n");
//    printf("startVal "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(PORTC));
    
    //	Clear TaskMask.
    TaskMask.AllBits = 0;

    //	Timer0 is Initially Idle, so Clocks can Stop when Sleeping.  Timer0 is only Clock User.
    CPUDOZEbits.IDLEN = 0; // Idle DISable, Full SLEEP w/ Clocks OFF.

    //	Set VoltageRegulator PowerMode per SwitchHandler.h #defines.
#ifdef SwitchVrVal
    SwitchVrSfr.SwitchVrBit = SwitchVrVal; // 0: Normal, 1: LowPwr, Slower Wakeup.
#endif

    //	Initialize Switch Handler.  Can set GIE for some PICs, so place just before GIE = 1.
    SwitchInitialize(); // Initialize Switch Logic. May Set IOC Flags.

    //	Enable Peripheral and Global Interrupts.
    INTERRUPT_PeripheralInterruptEnable(); // PIE = 1.
    INTERRUPT_GlobalInterruptEnable(); // GIE = 1.

    //	Loop Forever Handling Tasks put in ActionQueue by IOC Interrupts AND TimerTicks.
    while (true) { // Loop Forever.

        //	Process Ready Tasks: Switch Changes and Clock Ticks.
        while (TaskMask.AllBits) {
            //	Drain SwitchChange Queue.
            while (TaskMask.SwitchChange) { // Switch Change in Action Queue.
                SFR_T swMask = SwitchChangeDequeue();
                SFR_T swValue = SwitchChangeDequeue();
                SwitchChanged(swMask, swValue);
                TaskMask.SwitchChange = 0; // Assume Empty, but Check Next.
                if (SwitchChangeQueueOccupied()) TaskMask.SwitchChange = 1;
            }

            //	If DebounceTick: Clear and Process.  Can Queue SwitchChanges.
            if (TaskMask.DebounceTick) { // 2 ms. Time Tick Occurred
                TaskMask.DebounceTick = 0;
                AppDebounceTick();
            }
        } // While TaskMask.AllBits.

        //	See if ANY Tasks Ready with Interrupts OFF.  If NOT, Sleep.
        //	There is a SMALL but Real Chance an Interrupt Occurred After While Test Above.
        INTERRUPT_GlobalInterruptDisable(); // GIE = 0.
        if (TaskMask.AllBits == 0) {
//            printf("Sleep \r\n");
            //	Clocks Run Per CPUDOZEbits.IDLEN Bit - Changed by Timer0 Start and Stop.
           SLEEP(); // Interrupts Wake CPU, but GIE still = 0.
        }
        INTERRUPT_GlobalInterruptEnable(); // GIE = 1.

    } // while (true)

}
