/*!
 * @file main.c
 * @brief Opto 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of Opto 5 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of UART LOG and GPIO pin drivers.
 * The output of PWM is set to high so the optocoupler
 * is not triggered by default.
 *
 * ## Application Task
 * The output pin is toggled every 5 seconds. 
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "opto5.h"

static opto5_t opto5;               /**< Opto 5 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    opto5_cfg_t opto5_cfg;          /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    opto5_cfg_setup( &opto5_cfg );
    OPTO5_MAP_MIKROBUS( opto5_cfg, MIKROBUS_1 );
    if ( opto5_init( &opto5, &opto5_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    opto5_default_cfg ( &opto5 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Pin toggling...\r\n" );
    opto5_pin_toggle( &opto5 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
