/*!
 * \file 
 * \brief Grideye Click example
 * 
 * # Description
 * 64 individual thermal sensors build an image on a display. The detecting distance is 5m.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings, and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Grid-EYE click board by reading full grid and displaying values via USART terminal
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "grideye.h"

#define GRIDEYE_TEMP_COEF  0.25

// ------------------------------------------------------------------ VARIABLES

static grideye_t grideye;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    grideye_cfg_t cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    grideye_cfg_setup( &cfg );
    GRIDEYE_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( grideye_init( &grideye, &cfg ) == GRIDEYE_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );

    grideye_default_cfg ( &grideye );

    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    uint8_t i;
    uint8_t j;
    int16_t grid_array[ 64 ];
    int16_t grid_array_tmp;

    grideye_read_grid( &grideye, grid_array );

    for( i = 1; i < 9; i++ )
    {
        for( j = 1; j < 9; j++ )
        {
            log_printf( &logger, "| " );
            grid_array_tmp = grid_array[ i * j - 1 ];

            log_printf( &logger, "%d ", (int16_t)( grid_array_tmp * GRIDEYE_TEMP_COEF ) );
        }
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "-------------------------------------- \r\n" );
    }

    Delay_ms ( 1000 );
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
