/*!
 * \file 
 * \brief Line Follower Click example
 * 
 * # Description
 * Line Follower Click carries an array of five QRE1113 
 * miniature reflective object sensors,
 * reading staus of AN, RST, PWM, TX and RX pins and reading tracking data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs logger and Click Initialization.
 * 
 * ## Application Task  
 * Application Task shows the functionality of the Line Follower Click.
 * Each one of the QRE1113 sensors consist of an
 * infrared transmitter and infrared receiver. 
 * By default the sensor output a Logic Level 1, until they encounter a 
 * white surface which changes the output signal to 0.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "linefollower.h"

// ------------------------------------------------------------------ VARIABLES

static linefollower_t linefollower;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    linefollower_cfg_t cfg;

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
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " - Application Init -\r\n" );

    //  Click initialization.
    linefollower_cfg_setup( &cfg );
    LINEFOLLOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linefollower_init( &linefollower, &cfg );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Line Follower  Click \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}

void application_task ( void )
{
    linefollower_direction_t data_track;
    
    linefollower_data_track ( &linefollower, &data_track );
    
    log_printf( &logger, " %u\t%u\t%u\t%u\t%u\r\n", 
                (uint16_t) data_track.u1, 
                (uint16_t) data_track.u2, 
                (uint16_t) data_track.u3, 
                (uint16_t) data_track.u4, 
                (uint16_t) data_track.u5);
    
    Delay_ms ( 100 );
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
