/*!
 * \file 
 * \brief Joystick Click example
 * 
 * # Description
 * This application configures and enables use of the joystick.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - device,
 *  sets default configuration and starts write log.
 * 
 * ## Application Task  
 * (code snippet) This is a example which demonstrates the use of Joystick Click board.
 * Joystick Click communicates with register via I2C by write and read from register,
 * read joystick position and press button state.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when the sensor is triggered.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "joystick.h"

// ------------------------------------------------------------------ VARIABLES

static joystick_t joystick;
static log_t logger;

uint8_t position;
uint8_t button_state;
uint8_t position_old = 1;
uint8_t button_state_old = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    joystick_cfg_t cfg;

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

    joystick_cfg_setup( &cfg );
    JOYSTCIK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    joystick_init( &joystick, &cfg );

    Delay_ms( 100 );

    joystick_default_cfg( &joystick );

    log_printf( &logger,  "*********************\r\n" );
    log_printf( &logger,  "    Configuration    \r\n" );
    log_printf( &logger,  "*********************\r\n" );
    log_printf( &logger,  "    Joystick Click   \r\n" );
    log_printf( &logger,  "*********************\r\n" );

    Delay_ms( 100 );
}

void application_task ( void ) 
{
    //  Task implementation.

    button_state = joystick_press_button( &joystick );

    position = joystick_get_position( &joystick );

    Delay_ms( 10 );

    if ( ( button_state == 1 ) && ( button_state_old == 0 ) )
    {
        button_state_old = 1;

        log_printf( &logger, "  Button is pressed \r\n" );
        log_printf( &logger, "*********************\r\n" );
    }

    if ( ( button_state == 0 ) && ( button_state_old == 1 ) )
    {
        button_state_old = 0;
    }

    if ( position_old != position )
    {
        switch ( position )
        {
            case 0 :
            {
                log_printf( &logger,"    Start position    \r\n" );
                break;
            }
            case 1 :
            {
                log_printf( &logger, "         Top    \r\n" );
                break;
            }
            case 2 :
            {
                log_printf( &logger, "      Top-Right    \r\n" );
                break;
            }
            case 3 :
            {
                log_printf( &logger, "        Right    \r\n" );
                break;
            }
            case 4 :
            {
                log_printf( &logger, "     Bottom-Right    \r\n" );
                break;
            }
            case 5 :
            {
                log_printf( &logger, "        Bottom    \r\n" );
                break;
            }
            case 6 :
            {
                log_printf( &logger, "     Bottom-Left    \r\n" );
                break;
            }
            case 7 :
            {
                log_printf( &logger, "         Left    \r\n" );
                break;
            }
            case 8 :
            {
                log_printf( &logger, "       Top-Left    \r\n" );
                break;
            }
        }

        log_printf( &logger, "*********************\r\n" );

        position_old = position;

        Delay_ms( 100 );
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
