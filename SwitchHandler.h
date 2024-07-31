#ifndef SWITCHHANDLER_H
#define	SWITCHHANDLER_H


//	Create a typedef for an Unsigned Type the Same Width as the SFRs for this Architecture.
typedef uint8_t SFR_T;

//	#defines for Voltage Regulator Setting.  1 -> LowPower, SlowWake.  Not used for LF parts.
#define SwitchVrSfr		VREGCONbits	// VoltageRegulator SFR.  Use: "SwitchVrSfr.
#define SwitchVrBit		VREGPM		// VoltageRegulator Bit.        SwitchVrBit =
#define SwitchVrVal		1			// VoltageRegulator Value.      SwitchVrVal;


//	#defines for IOC Interrupt Control.  Use IOCIE if Available, otherwise use GIE.
#define SwitchIoceSfr	PIE0bits	// Interrupt Enable SFR.  Use: "SwitchIoceSFR.
#define SwitchIoceBit	IOCIE		// Interrupt Enable Bit.        SwitchIoceBit = 0/1;"


//	#defines for SFR Names to Allow use of Different Ports.
#define	SwitchPort		PORTC		// Port (Input).
#define	SwitchIocf		IOCCF		// Changed Flags.
#define	SwitchIocp		IOCCP		// Enable Bits for Rising Edge Detector.
#define	SwitchIocn		IOCCN		// Enable Bits for Falling Edge Detector.


#define PIN_TRIGGER ((SFR_T) 0b0100) // Switch on Port C RC2
#define PIN_POWER   ((SFR_T) 0b1000) // Switch on Port C RC3

//	#defines for Switch Mask and Count.
#define	SwitchMask		((SFR_T) (PIN_TRIGGER+PIN_POWER))   //((SFR_T) 0b1100)	
#define SwitchCount		2				// Must Match Count of '1' Bits in Mask.


//	Assumed Initial Switch Bit Values.
#define SwitchesAtStartup	((SFR_T) 0b1111) // SwitchMask	// ALL Switches Open (1 == Open).


//	#define for Switch Debounce Period.
//	Smallest Value that Reliably exceeds the Switches' longest Bounce Time is best.
#define	SwitchDebounceMicroseconds	15000	// 15 ms.


//	Functions _Implemented_ by the SwitchHandler.c and referenced in other source files.
void Switch_IOC_InterruptHandler(void);
void SwitchInitialize(void);
void SwitchChanged(SFR_T intrSwitchMask, SFR_T intrSwitchValue);
void SwitchDebounceEnd(SFR_T switchMask); // Do NOT Inline.

#endif	/* SWITCHHANDLER_H */