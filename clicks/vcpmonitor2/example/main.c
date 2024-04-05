/*!
 * \file 
 * \brief Vcpmonitor2 Click example
 * 
 * # Description
 * VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication 
 * function ensuring the intended application works within desired operating conditions.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initiaizes the driver, and checks the communication by reading the manufacture device ID.
 * After that, performs the device default configuration.
 * 
 * ## Application Task  
 * Displays the voltage, current, and power detected from channel 1 on the USB UART every 2 seconds.
 * It also displays the status of alert indicators.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vcpmonitor2.h"

// ------------------------------------------------------------------ VARIABLES

static vcpmonitor2_t vcpmonitor2;
static log_t logger;

static uint16_t check_id;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void display_alert_status ( )
{
    uint8_t status;
    
    status = vcpmonitor2_get_alert_status( &vcpmonitor2 );

    if ( ( status & VCPMONITOR2_ALERT_PVALID ) != 0 )
    {
        log_printf( &logger, ">> Alert status: [ PVALID ]\r\n" );
    }
    if ( ( status & VCPMONITOR2_ALERT_WRNG ) != 0 )
    {
        log_printf( &logger, ">> Alert status: [ WRNG ]\r\n" );
    }
    if ( ( status & VCPMONITOR2_ALERT_CRTCL ) != 0 )
    {
        log_printf( &logger, ">> Alert status: [ CRTCL ]\r\n" );
    }
    if ( ( status & VCPMONITOR2_ALERT_TCTRL ) != 0 )
    {
        log_printf( &logger, ">> Alert status: [ TCTRL ]\r\n" );
    }
}

void display_channel_data ( uint8_t channel )
{
    float shunt_volt;
    float bus_volt;
    float current;
    float power;
    
    shunt_volt = vcpmonitor2_get_shunt_voltage( &vcpmonitor2, channel );
    log_printf( &logger, ">> Shunt voltage: %.2f mV\r\n", shunt_volt );

    bus_volt = vcpmonitor2_get_bus_voltage( &vcpmonitor2, channel );
    log_printf( &logger, ">> BUS voltage: %.2f mV\r\n", bus_volt );

    current = vcpmonitor2_get_current( &vcpmonitor2, channel );
    log_printf( &logger, ">> Current: %.2f mV\r\n", current );

    power = vcpmonitor2_get_power( &vcpmonitor2, channel );
    log_printf( &logger, ">> Power: %.2f mV\r\n", power );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor2_cfg_t cfg;

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

    vcpmonitor2_cfg_setup( &cfg );
    VCPMONITOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor2_init( &vcpmonitor2, &cfg );

    check_id = vcpmonitor2_get_manifacture_id( &vcpmonitor2 );
    if ( check_id == VCPMONITOR2_DEF_MANUFACTURE_ID )
    {
        log_printf( &logger, ">> Manufacture ID: 0x%.4X\r\n", check_id );
    }
    else
    {
        log_error( &logger, " WRONG ID READ! " );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }

    vcpmonitor2_default_cfg( &vcpmonitor2 );
}

void application_task ( void )
{
    log_printf( &logger, ">> CHANNEL 1 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_1 );

    display_alert_status( );
    log_printf( &logger, "--------------------------\r\n" );
    
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
