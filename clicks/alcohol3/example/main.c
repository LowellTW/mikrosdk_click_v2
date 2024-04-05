/*!
 * \file 
 * \brief Alcohol3 Click example
 * 
 * # Description
 * Code of this sensor reacts to the presence of deoxidizing and reducing gases,
 * such as ethanol (also known as alcohol).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Reads percentage of alcohol in the blood (BAC) 
 * and this data logs to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "alcohol3.h"

// ------------------------------------------------------------------ VARIABLES

static alcohol3_t alcohol3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol3_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    alcohol3_cfg_setup( &cfg );
    ALCOHOL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol3_init( &alcohol3, &cfg );

    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ---- Alcohol 3 Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    uint16_t co_ppm;
    uint16_t p_bac;
    float temp_bac;

    //  Task implementation.

    log_printf( &logger, " --- Alcohol diagnostics ---- \r\n" );

    co_ppm = alcohol3_get_co_in_ppm ( &alcohol3 );
    log_printf( &logger, " co in ppm  %d    | \r\n", co_ppm );

    temp_bac = alcohol3_get_percentage_bac( &alcohol3 );
    p_bac = ( uint16_t )( temp_bac * 1000 );

    if ( 10 > p_bac && p_bac < 100 )
    {
        log_printf( &logger, " BAC      | 0.00%d\r\n", p_bac );
    }
    else if ( 100 <= p_bac && 1000 > p_bac )
    {
        log_printf( &logger, " BAC      | 0.0%d\r\n", p_bac );
    }
    else if ( p_bac >= 1000 )
    {
        log_printf( &logger, " BAC      | 0.%d\r\n", p_bac );
    }
    else
    {
        log_printf( &logger, " BAC  | 0.0000\r\n" );
    }
    log_printf( &logger, " ---------------------------- \r\n" );

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
