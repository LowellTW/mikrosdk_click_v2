/*!
 * \file 
 * \brief LinHall Click example
 * 
 * # Description
 * This is a example which demonstrates the use of Lin Hall Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI and LOG structures, initialization driver enable's 
 * - SPI and start write log.
 * 
 * ## Application Task  
 * Read 12-bit ADC value from the MCP3201 chip.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 100 ms when the ADC value changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "linhall.h"

// ------------------------------------------------------------------ VARIABLES

static linhall_t linhall;
static log_t logger;

static uint16_t value_adc;
static uint16_t value_adc_old;
static uint16_t sensitivity;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    linhall_cfg_t cfg;

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

    linhall_cfg_setup( &cfg );
    LINHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linhall_init( &linhall, &cfg );
    
    log_printf( &logger, "  Lin Hall Click  \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 100 );
    
    value_adc_old = 0;
    sensitivity = 30;
}

void application_task ( void )
{
    value_adc = linhall_read_data( &linhall );

    if ( ( ( value_adc - value_adc_old ) > sensitivity ) && ( ( value_adc_old - value_adc ) > sensitivity ) )
    {
        log_printf( &logger, "  ADC Value : %d \r\n", value_adc );
        log_printf( &logger, "------------------\r\n" );

        value_adc_old = value_adc;
        Delay_ms ( 100 );
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
