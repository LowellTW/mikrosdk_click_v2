/*!
 * \file 
 * \brief Tmrmixsens Click example
 * 
 * # Description
 * The TMR mix-sens Click has three types of magnetic field sensors: Two digital and one analog sensor. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger and makes an initial log.
 * 
 * ## Application Task  
 * Displays the ADC value of linear output and the states of bipolar and omnipolar indicators
 * on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tmrmixsens.h"

// ------------------------------------------------------------------ VARIABLES

static tmrmixsens_t tmrmixsens;
static log_t logger;

static uint16_t adc_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrmixsens_cfg_t cfg;

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

    tmrmixsens_cfg_setup( &cfg );
    TMRMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrmixsens_init( &tmrmixsens, &cfg );
}

void application_task ( void )
{
    tmrmixsens_data_t tmp;
    
    tmp = tmrmixsens_generic_read ( &tmrmixsens );
    log_printf( &logger, " ADC value of linear output : %d \r\n", tmp );

    log_printf( &logger, " Bipolar response: " );
    if ( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_NORTH_POLE )
    {
        log_printf( &logger, " North pole is detected!\r\n" );
    }
    else if( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_SOUTH_POLE )
    {
        log_printf( &logger, " South pole is detected!\r\n" );
    }
    
    if ( tmrmixsens_get_omnipolar ( &tmrmixsens ) == 0 )
    {
        log_printf( &logger, " Omnipolar response: Either South or North pole is detected!\r\n" );
    }
    
    log_printf( &logger, "--------------------------------------\r\n" );
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
