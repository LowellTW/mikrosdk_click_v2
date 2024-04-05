/*!
 * \file 
 * \brief 3dHall7 Click example
 * 
 * # Description
 * Read the position of magnetic
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, test communication and configuration device for measurement.
 * 
 * ## Application Task  
 * Reads 3 Axis of the magnetic sensor and logs this data to USBUART every 500ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall7.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall7_t c3dhall7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init (  )
{
    c3dhall7_dev_info_t info;
    uint8_t red_data;

    log_cfg_t log_cfg;
    c3dhall7_cfg_t cfg;

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

    c3dhall7_cfg_setup( &cfg );
    C3DHALL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall7_init( &c3dhall7, &cfg );
    
    c3dhall7_device_reset( &c3dhall7 );

    // Test communication 
    c3dhall7_device_info( &c3dhall7, &info );
    if ( info.device_id == C3DHALL7_DEVICE_ID )
    {
        log_printf( &logger, "---- Communication [ OK ]!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Communication [ ERROR ]!!! ----\r\n" );

        for ( ; ; );
    }

    // Configuration 
    c3dhall7_default_cfg ( &c3dhall7 );
}

void application_task ( void )
{
    c3dhall7_axis_t axis;

    c3dhall7_get_axis_data( &c3dhall7, &axis );
    
    log_printf( &logger, "---- Measurement data of magnetic sensor ----\r\n" );
    
    log_printf( &logger, "X axis: %d \r\n", axis.x );

    log_printf( &logger, "Y axis: %d \r\n", axis.y );

    log_printf( &logger, "Z axis: %d \r\n", axis.z );
    
    log_printf( &logger, "---------------------------------------------\r\n");
    Delay_ms ( 500 );
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
