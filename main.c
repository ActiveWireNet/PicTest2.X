/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
 */


#include "mcc_generated_files/system/system.h"

#include "Application.h"

/*
    Main application
 */
void main(void) {
    SYSTEM_Initialize(); // Initialize the Device

    ApplicationMain(); // Run the Application.
}

/* End of File */