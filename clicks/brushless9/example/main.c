/*!
 * @file main.c
 * @brief Brushlesss9 Click example
 *
 * # Description
 * This application is a schowcase of controlling speed and direction of brushless motor with hall sesnor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of LOG, PWM module and additional pins for controlling motor.
 *
 * ## Application Task
 * In span of 2 seconds changes duty cycle from 0 to 100% and then back to 0, at the end changes direction of motor.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless9.h"
#include "math.h"

#define DUTY_CHANGE_DELAY   2000
#define BREAK_DELAY         5000

static brushless9_t brushless9;
static log_t logger;

static uint8_t direction = 0;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless9_cfg_t brushless9_cfg;  /**< Click config object. */

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
    brushless9_cfg_setup( &brushless9_cfg );
    BRUSHLESS9_MAP_MIKROBUS( brushless9_cfg, MIKROBUS_1 );
    err_t init_flag  = brushless9_init( &brushless9, &brushless9_cfg );
    if ( init_flag == PWM_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    brushless9_set_dir( &brushless9, direction );
    brushless9_set_brk( &brushless9, 1 );

    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_pwm_start( &brushless9 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_info( &logger, " Starting... " );
    brushless9_set_brk( &brushless9, 0 );
    for ( float duty = 0.1; duty < 1; duty += 0.1 )
    {
        Delay_ms( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, duty );
        log_printf( &logger, "Duty: %u%%\r\n", ( uint16_t )ceil( duty * 100 ) );
    }

    for ( float duty = 0.9; duty >= 0; duty -= 0.1 )
    {
        Delay_ms( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, duty );
        log_printf( &logger, "Duty: %u%%\r\n", ( uint16_t )ceil( duty * 100 ) );
    }

    Delay_ms( DUTY_CHANGE_DELAY );
    log_info( &logger, " Stopping... " );
    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_set_brk( &brushless9, 1 );
    Delay_ms( BREAK_DELAY );
    log_info( &logger, " Changing direction... " );
    direction = !direction;
    brushless9_set_dir( &brushless9, direction );
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
