/*!
 * \file
 * \brief Pedometer3 Click example
 *
 * # Description
 * The demo application displays measuring 2 accelerometers (normal accel and high pass accel),
 * counting steps and displaying tilt positions.
 * The sensor includes additional feature and setups that you can look up in the library.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * Settings the Click in the default configuration.
 *
 * ## Application Task
 * Reads Accel and High Pass Accel X/Y/Z axis and detect Tilt Position.
 * All data logs on the USBUART every 400 ms.
 *
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pedometer3.h"

// ------------------------------------------------------------------ VARIABLES

static pedometer3_t pedometer3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer3_cfg_t cfg;
    uint8_t tmp;

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
    pedometer3_cfg_setup( &cfg );
    PEDOMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pedometer3_init( &pedometer3, &cfg );

    // Default Click configurations
    pedometer3_default_cfg( &pedometer3 );

    tmp = PEDOMETER3_CNTL1_MODE_LOW_POWER | PEDOMETER3_CNTL1_MODE_LOW_POWER |
          PEDOMETER3_CNTL1_RES_MODE_LOWER_NOISE | PEDOMETER3_CNTL1_DATA_READY_DISABLE |
          PEDOMETER3_CNTL1_G_RANGE_2g | PEDOMETER3_CNTL1_TAP_ENABLE |
          PEDOMETER3_CNTL1_PEDOMETER_ENABLE | PEDOMETER3_CNTL1_TILT_ENABLE;

    pedometer3_generic_write( &pedometer3, PEDOMETER3_REG_CONTROL_1, &tmp, 1 );
}

void application_task ( void )
{
    static uint16_t ped_step = 0;
    pedometer3_axis_t accel_axis;
    pedometer3_axis_t highpass_axis;
    pedometer3_tilt_position_t tilt;

    pedometer3_get_accel_axis( &pedometer3, &accel_axis );
    pedometer3_get_hp_accel_axis( &pedometer3, &highpass_axis );
    ped_step += pedometer3_get_step_counter( &pedometer3 );

    log_printf( &logger, "___________ Pedometer 3 Click _____________\r\n");

    log_printf( &logger, "--  Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                accel_axis.x, accel_axis.y, accel_axis.z );
    log_printf( &logger, "--  HP Accel : [ X ]: %d / [ Y ]: %d / [ Z ]: %d \r\n", 
                highpass_axis.x, highpass_axis.y, highpass_axis.z );

    log_printf( &logger, "--  Step counter : [ STEP ]: %d \r\n", ped_step );

    pedometer3_get_tilt_position( &pedometer3, &tilt);

    switch ( tilt.current_pos )
    {
        case PEDOMETER3_TILT_POSITION_LEFT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ LEFT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_RIGHT:
        {
            log_printf( &logger, "--  Current Tilt Position: [ RIGHT ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ UP ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_DOWN:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE DOWN ] \r\n" );
            break;
        }
        case PEDOMETER3_TILT_POSITION_FACE_UP:
        {
            log_printf( &logger, "--  Current Tilt Position: [ FACE UP ] \r\n" );
            break;
        }
    }

    Delay_ms ( 400 );
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
