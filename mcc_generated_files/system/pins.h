/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA1 aliases
#define LED_STANDBY_TRIS                 TRISAbits.TRISA1
#define LED_STANDBY_LAT                  LATAbits.LATA1
#define LED_STANDBY_PORT                 PORTAbits.RA1
#define LED_STANDBY_WPU                  WPUAbits.WPUA1
#define LED_STANDBY_OD                   ODCONAbits.ODCA1
#define LED_STANDBY_ANS                  ANSELAbits.ANSA1
#define LED_STANDBY_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_STANDBY_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_STANDBY_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_STANDBY_GetValue()           PORTAbits.RA1
#define LED_STANDBY_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_STANDBY_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_STANDBY_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED_STANDBY_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED_STANDBY_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED_STANDBY_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED_STANDBY_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_STANDBY_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define Y_LED_TRIS                 TRISAbits.TRISA2
#define Y_LED_LAT                  LATAbits.LATA2
#define Y_LED_PORT                 PORTAbits.RA2
#define Y_LED_WPU                  WPUAbits.WPUA2
#define Y_LED_OD                   ODCONAbits.ODCA2
#define Y_LED_ANS                  ANSELAbits.ANSA2
#define Y_LED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Y_LED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Y_LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Y_LED_GetValue()           PORTAbits.RA2
#define Y_LED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Y_LED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Y_LED_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Y_LED_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Y_LED_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define Y_LED_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define Y_LED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Y_LED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define LED_POWER_TRIS                 TRISAbits.TRISA4
#define LED_POWER_LAT                  LATAbits.LATA4
#define LED_POWER_PORT                 PORTAbits.RA4
#define LED_POWER_WPU                  WPUAbits.WPUA4
#define LED_POWER_OD                   ODCONAbits.ODCA4
#define LED_POWER_ANS                  ANSELAbits.ANSA4
#define LED_POWER_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LED_POWER_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LED_POWER_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LED_POWER_GetValue()           PORTAbits.RA4
#define LED_POWER_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LED_POWER_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LED_POWER_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define LED_POWER_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define LED_POWER_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define LED_POWER_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define LED_POWER_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define LED_POWER_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_OD                   ODCONBbits.ODCB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_OD                   ODCONBbits.ODCB6
#define IO_RB6_ANS                  ANSELBbits.ANSB6
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)
// get/set IO_RC2 aliases
#define SW0_TRIS                 TRISCbits.TRISC2
#define SW0_LAT                  LATCbits.LATC2
#define SW0_PORT                 PORTCbits.RC2
#define SW0_WPU                  WPUCbits.WPUC2
#define SW0_OD                   ODCONCbits.ODCC2
#define SW0_ANS                  ANSELCbits.ANSC2
#define SW0_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SW0_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SW0_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SW0_GetValue()           PORTCbits.RC2
#define SW0_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SW0_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SW0_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SW0_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SW0_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SW0_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SW0_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define SW0_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC3 aliases
#define POWER_SWITCH_TRIS                 TRISCbits.TRISC3
#define POWER_SWITCH_LAT                  LATCbits.LATC3
#define POWER_SWITCH_PORT                 PORTCbits.RC3
#define POWER_SWITCH_WPU                  WPUCbits.WPUC3
#define POWER_SWITCH_OD                   ODCONCbits.ODCC3
#define POWER_SWITCH_ANS                  ANSELCbits.ANSC3
#define POWER_SWITCH_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define POWER_SWITCH_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define POWER_SWITCH_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define POWER_SWITCH_GetValue()           PORTCbits.RC3
#define POWER_SWITCH_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define POWER_SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define POWER_SWITCH_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define POWER_SWITCH_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define POWER_SWITCH_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define POWER_SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define POWER_SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define POWER_SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
#define RC3_SetInterruptHandler  POWER_SWITCH_SetInterruptHandler
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the POWER_SWITCH pin functionality
 * @param none
 * @return none
 */
void POWER_SWITCH_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for POWER_SWITCH pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for POWER_SWITCH at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void POWER_SWITCH_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for POWER_SWITCH pin.
 *        This is a dynamic interrupt handler to be used together with the POWER_SWITCH_SetInterruptHandler() method.
 *        This handler is called every time the POWER_SWITCH ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*POWER_SWITCH_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for POWER_SWITCH pin. 
 *        This is a predefined interrupt handler to be used together with the POWER_SWITCH_SetInterruptHandler() method.
 *        This handler is called every time the POWER_SWITCH ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void POWER_SWITCH_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/