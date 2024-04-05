/*!
 * \file 
 * \brief Ecg Click example
 * 
 * # Description
 * This example demonstrates the use of ECG Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click board.
 * 
 * ## Application Task  
 * Reads ADC sends results on serial plotter.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ecg.h"

// ------------------------------------------------------------------ VARIABLES

static ecg_t ecg;
static log_t logger;

static uint16_t read_adc;
static uint32_t time_read;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void plot_res ( uint16_t plot_data, uint32_t plot_time )
{
    log_printf( &logger, "%u,%u \r\n", plot_data, plot_time);
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg_cfg_t cfg;

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

    ecg_cfg_setup( &cfg );
    Delay_ms ( 200 );
    ECG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg_init( &ecg, &cfg );
    Delay_ms ( 200 );

    time_read = 0;
}

void application_task ( void )
{
    time_read++;
    read_adc = ecg_generic_read( &ecg );
    plot_res( read_adc , time_read);

    Delay_ms ( 5 );
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
