/*!
 * \file 
 * \brief TouchKey Click example
 * 
 * # Description
 * This application has four capacitive pads powered by TTP224, a touchpad detector IC. 
 * Capacitive buttons like these can be toggled even when placed under a layer of glass or paper.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also starts write log.
 * 
 * ## Application Task  
 * This example demonstrates the use of TouchKey Click board.
 * Detects whether any of the keys is pressed. Results are being sent to the Usart Terminal, 
 * where you can track changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchkey.h"

// ------------------------------------------------------------------ VARIABLES

static touchkey_t touchkey;
static log_t logger;

static uint8_t key_state = 0;
static uint8_t key_state_old = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey_cfg_t cfg;

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

    touchkey_cfg_setup( &cfg );
    TOUCHKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey_init( &touchkey, &cfg );
    log_printf( &logger, "Press key\r\n" );
}

void application_task ( void )
{

    key_state = touchkey_a( &touchkey ) | touchkey_b( &touchkey ) | touchkey_c( &touchkey ) | touchkey_d( &touchkey );

    if( key_state == 1 && key_state_old == 0  )
    {
        log_printf( &logger,"Pressed : " );

        if( touchkey_a( &touchkey ) )
        {
            log_printf( &logger, "A\r\n " );
        }
        if( touchkey_b( &touchkey) )
        {
            log_printf( &logger, "B\r\n " );
        }
        if( touchkey_c( &touchkey ) )
        {
            log_printf( &logger, "C\r\n " );;
        }
        if( touchkey_d( &touchkey ) )
        {
            log_printf( &logger, "D\r\n " );
        }
        key_state_old = 1;
    }
    if ( key_state == 0 && key_state_old == 1 )
    {
        key_state_old = 0;
    }

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
