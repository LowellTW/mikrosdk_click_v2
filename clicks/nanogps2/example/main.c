/*!
 * \file 
 * \brief NanoGps2 Click example
 * 
 * # Description
 * This example reads and processes data from Nano GPS 2 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - nanogps2_process ( ) - The general process of collecting data the module sends.
 * 
 * @note
 * Depending on the environmental conditions and the satellites availability
 * it may take some time for the module to receive the position fix.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanogps2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 600
#define PROCESS_PARSER_BUFFER_SIZE 600

// ------------------------------------------------------------------ VARIABLES

static nanogps2_t nanogps2;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void nanogps2_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = nanogps2_generic_read( &nanogps2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n" ); 
    nanogps2_generic_parser( rsp, NANOGPS2_NEMA_GNGGA, NANOGPS2_GNGGA_LATITUDE, element_buf );
    if ( strlen( element_buf ) > 0 )
    {
        log_printf( &logger, "Latitude:  %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
        nanogps2_generic_parser( rsp, NANOGPS2_NEMA_GNGGA, NANOGPS2_GNGGA_LONGITUDE, element_buf );
        log_printf( &logger, "Longitude:  %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
        memset( element_buf, 0, sizeof( element_buf ) );
        nanogps2_generic_parser( rsp, NANOGPS2_NEMA_GNGGA, NANOGPS2_GNGGA_ALTITUDE, element_buf );
        log_printf( &logger, "Altitude: %s m", element_buf );  
    }
    else
    {
        log_printf( &logger, "Waiting for the position fix..." );
    } 
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanogps2_cfg_t cfg;

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

    nanogps2_cfg_setup( &cfg );
    NANOGPS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanogps2_init( &nanogps2, &cfg );
    
    nanogps2_module_wakeup ( &nanogps2 );
}

void application_task ( void )
{
    nanogps2_process( );
    parser_application( current_parser_buf );
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
