/*!
 * \file 
 * \brief LSM303AGR Click example
 * 
 * # Description
 * This example returns accel and magnet values from the LSM303AGR sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * I2C Driver initaliation and setting operating modes of accelerometer and
 * magnetometer 
 * 
 * ## Application Task  
 * Reading accelerometer and magnetometer axis X,Y,Z and displaying via UART
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lsm303agr.h"

// ------------------------------------------------------------------ VARIABLES

static lsm303agr_t lsm303agr;
static log_t logger;
static float read_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm303agr_cfg_t cfg;

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

    lsm303agr_cfg_setup( &cfg );
    LSM303AGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm303agr_init( &lsm303agr, &cfg );
    
    lsm303agr_default_cfg ( &lsm303agr );
   
}

void application_task ( void )
{
    //  Task implementation.

    log_printf(&logger, "======== Accelerometer data ========\r\n");
    
    read_data = lsm303agr_get_acc_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %.2f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %.2f\r\n", read_data);

    read_data = lsm303agr_get_acc_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %.2f\r\n", read_data);
    
    log_printf(&logger, "======== Mangetometer data ========\r\n");
    
    read_data = lsm303agr_get_mag_axis_x ( &lsm303agr );
    log_printf(&logger, "X Axis : %.2f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_y ( &lsm303agr );
    log_printf(&logger, "Y Axis : %.2f\r\n", read_data);

    read_data = lsm303agr_get_mag_axis_z ( &lsm303agr );
    log_printf(&logger, "Z Axis : %.2f\r\n", read_data);

    Delay_ms ( 1000 );
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
