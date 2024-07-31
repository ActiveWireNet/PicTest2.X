#include <xc.h>							// xcXX and Processor-Dependent Definitions.
#include "SwitchHandler.h"				// Public Symbols for this Code.
#include "Application.h"				// Needed for Callback Function Prototypes.


//   SFR_T PhysSwitchVal = SwitchesAtStartup;	// Physical Switch Value.
volatile SFR_T IntrSwitchVal = SwitchesAtStartup; // Interrupt's Switch Value.
SFR_T ApplSwitchVal = SwitchesAtStartup; // Application's Switch Value.


//	Switch IOC Interrupt Handler.  Handles ONLY 'SwitchMask' IOCs.  Other IOCs (if any)
//	must be handled separately.  Clears P, N, and F Bits for Changed Switches.  Computes
//	the Switch State.  Queues a SwitchChange Notice.

void Switch_IOC_InterruptHandler(void) {
    SFR_T switchIocf = SwitchIocf & SwitchMask; // IOCx Flags for Switch Bits ONLY.

    if (switchIocf) { // If ANY Switch-Specific IOCxF Flags are set:
        //printf("Switch_IOC_InterruptHandler r\n");
        SFR_T switchIocfInv = ~switchIocf; // Invert for clearing Flags being handled here.
        SwitchIocp &= switchIocfInv; // Disable Changed Switch's 'P' Edge Detector.
        SwitchIocn &= switchIocfInv; // Disable Changed Switch's 'N' Edge Detector.
        SwitchIocf &= switchIocfInv; // Clear any Set Switch's Flags.  After Edge Off.

        IntrSwitchVal ^= switchIocf; // Compute Switch Values as known to this Code.

        AppSwitchChangeEnqueue(switchIocf, IntrSwitchVal); // Queue Notification to Appl.
    } else {
        printf("Switch_IOC_InterruptHandler NOOOOOO \r\n");        
    }
}


//	Initialize Switch States at Power-ON.  ALL Switch Bits are tested against the #define
//	'SwitchesAtStartup' from SwitchHandler.h.  Any Switches NOT as expected have their
//	respective Flag bits set for processing when Interrupts are Enabled.  Enables the Edge
//	Detectors for Each Switch Bit.  Once Interrupts are enabled, the Interrupt Handler will
//	Queue a SwitchChange Event for Non-Matching Switches (if any) for the Application.
//	Called by Application.c at Startup BEFORE Interrupts Enabled, so runs at Task-Level.

void SwitchInitialize(void) {
    SwitchDebounceEnd(SwitchMask); // Use DebounceEnd to Enable Edges and Find Non-Defaults.
}


//	Process a (Set of) Pin Change(s).  Called by MainLoop in Application.c at Task Level.
//	Given a Mask and Value: Start a Debounce Timer, Notify Application, Save Switch Value.

void SwitchChanged(SFR_T intrSwitchMask, SFR_T intrSwitchValue) {
    AppDebounceTimerEnqueue(intrSwitchMask); // Start Debounce Timer.
    AppSwitchChanged(ApplSwitchVal, intrSwitchValue); // Notify the Application (old, new).
    ApplSwitchVal = intrSwitchValue; // ApplicationSwitchValue = newValue.
}


//	A Debounce Timer has expired OR Initializing Switches.
//	For each Switch specified by 'switchMask': Enable the Edge Detectors.
//	For Changed Switches: Set IOCxF Bits.  Subsequent Interrupt will process the change.
//	Called by Application.c from Task Loop at Task Level and SwitchInitialize (Above).

void SwitchDebounceEnd(SFR_T switchMask) {
    //	Turn IOC Interrupts OFF while manipulating IOC P/N Edge Detectors and Flag Settings.
    SwitchIoceSfr.SwitchIoceBit = 0; // IOC Interrupts Disabled.

    //	Enable the IOC Edge Detectors for each of the Switches Specified by 'switchMask'.
    SwitchIocp |= switchMask; // Turn On P Edge Detector(s).
    SwitchIocn |= switchMask; // Turn On N Edge Detector(s).

    //	Turn ON IOCxF Bits for the Specified Switches changed during Debouncing (or Initially).
    //	These MAY have been set by the Hardware after one of the two lines above Set IOCxP/N.
    //	This is the Subtle part of the Algorithm.  Changes cannot get by this line.
    SwitchIocf |= (IntrSwitchVal ^ SwitchPort) & switchMask;

    //	Turn IOC Interrupts ON as ALL Switch-Related IOC Bits are now Set.
    SwitchIoceSfr.SwitchIoceBit = 1; // IOC Interrupts Enabled.
}
