/*!
 * \file 
 * \brief AudioMUX Click example
 * 
 * # Description
 * The following demo shows basic click functionality:
 * Initializes AudioMUX device to work with the desired configurations and
 * shows a message on uart when playing is started.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click and logger.
 * 
 * ## Application Task  
 * Every 4 seconds shows a message on uart until 5 messages has been
 * shown or device stops playing.
 * 
 * *note:* 
 * Device initialization will be performed only once and after that 
 * AudioMUX will work with the same desired configurations.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audiomux.h"

// ------------------------------------------------------------------ VARIABLES

static audiomux_t audiomux;
static log_t logger;

uint8_t init_check;
uint8_t mess_cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audiomux_cfg_t cfg;

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

    audiomux_cfg_setup( &cfg );
    AUDIOMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audiomux_init( &audiomux, &cfg );

    init_check = 0;
    mess_cnt   = 0;

    log_info( &logger, "** AudioMUX initialized **\r\n" );
}

void application_task ( void )
{
    if (init_check == 0)
    {
        audiomux_default_cfg ( &audiomux );
        init_check = 1;

        log_printf( &logger, "Playing from IN1 " );
        Delay_ms ( 1000 );
    }

    if (mess_cnt < 5)
    {
        log_printf( &logger, ". " );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        mess_cnt++;
    }
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
