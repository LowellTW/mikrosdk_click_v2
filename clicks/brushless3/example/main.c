/*!
 * \file 
 * \brief Brushless3 Click example
 * 
 * # Description
 * This Click has three-phase sensorless motor driver and 
 * with an external power supply it drives a brushless DC motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, set default parameter value.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Brushless 3 Click board.
 * Read and display float motor frequency value from the DRV10983 sensorless 
 * BLDC motor driver on Brushless 3 Click board. Results are being sent to 
 * the Usart Terminal where you can track their changes. 
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless3.h"

// ------------------------------------------------------------------ VARIABLES

static brushless3_t brushless3;
static log_t logger;

static float velocity = 0; 
static int16_t speed = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless3_cfg_t cfg;

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
    brushless3_cfg_setup( &cfg );
    BRUSHLESS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless3_init( &brushless3, &cfg );
    
    if ( BRUSHLESS3_ERROR == brushless3_default_cfg ( &brushless3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
}

void application_task ( void )
{
    log_printf( &logger, "    acceleration      \r\n" );
    
    for ( speed = 100; speed <= BRUSHLESS3_MAX_SPEED; speed += 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, "    slowing down     \r\n" );
    
    for ( speed = BRUSHLESS3_MAX_SPEED; speed >= 50; speed -= 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
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
