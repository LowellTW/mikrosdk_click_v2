/*!
 * \file 
 * \brief Magneto8 Click example
 * 
 * # Description
 * This example demonstrates the use of Magneto 8 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and applies the click default configuration.
 * 
 * ## Application Task  
 * Reads angle and magnitude data and displays it on the USB UART every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto8.h"

// ------------------------------------------------------------------ VARIABLES

static magneto8_t magneto8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    magneto8_cfg_setup( &cfg );
    MAGNETO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto8_init( &magneto8, &cfg );

    magneto8_default_cfg( &magneto8 );
    log_printf( &logger, "--- Configuration done ---- \r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    float angle;
    uint16_t mag;

    mag  = magneto8_get_magnitude( &magneto8 );
    log_printf( &logger, "Magnitude: %d \r\n", mag );
    
    angle = magneto8_get_angle_data( &magneto8 );
    log_printf( &logger, "Angle : %.1f deg\r\n", angle );

    log_printf( &logger, "---------------------- \r\n" );
    Delay_ms( 500 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
