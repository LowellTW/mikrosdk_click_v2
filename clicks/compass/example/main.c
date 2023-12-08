/*!
 * \file 
 * \brief Compass Click example
 * 
 * # Description
 * This application measures magnetic and accelerometer axes data and shows them over USBUART
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and init chip
 * 
 * ## Application Task  
 * Read magnet axis data and accel axis data and logs data on USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "compass.h"

// ------------------------------------------------------------------ VARIABLES

static compass_t compass;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass_cfg_t cfg;

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

    compass_cfg_setup( &cfg );
    COMPASS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass_init( &compass, &cfg );
    compass_default_config( &compass );
}

void application_task ( void )
{
    int16_t accel_axis[ 3 ];
    int16_t magnet_axis[ 3 ];
    
    compass_read_magnet_axis( &compass, &magnet_axis[ 0 ], &magnet_axis[ 1 ], &magnet_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", magnet_axis[ 0 ], magnet_axis[ 1 ], magnet_axis[ 2 ] );
  
    compass_read_accel_axis ( &compass, &accel_axis[ 0 ], &accel_axis[ 1 ], &accel_axis[ 2 ] );
    log_printf( &logger, "Magnet axis -- X: %d Y: %d  Z: %d \r\n", accel_axis[ 0 ], accel_axis[ 1 ], accel_axis[ 2 ] );
   
    log_printf( &logger, " \r\n");
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
