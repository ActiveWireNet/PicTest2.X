#ifndef APPLICATION_H
#define	APPLICATION_H

#include	"SwitchHandler.h"		// Needed for SFR_T typedef.


//	Function Definitions for Functions referenced OUTSIDE of Application.c

//	Called by MCC's interrupt_manager.c (as modified for this project).
void Timer0_InterruptHandler(void);

//	Called (back) by SwitchHandler.c
void AppSwitchChanged(SFR_T oldValue, SFR_T newValue);
void AppSwitchChangeEnqueue(SFR_T mask, SFR_T value);
void AppDebounceTimerEnqueue(SFR_T mask);

//	Called by MCC's main.c (as modified for this project)
void ApplicationMain(void);


#endif	/* APPLICATION_H */