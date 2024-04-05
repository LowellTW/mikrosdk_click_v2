/*!
 * \file 
 * \brief MRAM Click example
 * 
 * # Description
 * This example writes and reads from the Mram Click and displays it on the terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Writes 10 bytes of buffer data in memory with start address 0x0001. Then reads
 * 10 bytes from memory with start address 0x0001 and shows result on USB UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mram.h"

// ------------------------------------------------------------------ VARIABLES

static mram_t mram;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram_cfg_t cfg;

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

    mram_cfg_setup( &cfg );
    MRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram_init( &mram, &cfg );
    mram_default_cfg( &mram );
    
}

void application_task ( void )
{
    uint8_t number_bytes_write;
    uint8_t number_bytes_read;
    uint16_t i;
    uint8_t data_write[ 10 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint8_t data_read[ 20 ] = { 0 };
    
    number_bytes_write = 10;
    number_bytes_read = 10;

    log_printf( &logger, " Data written!\r\n" );
    mram_write_data_bytes ( &mram, 0x0001, data_write, number_bytes_write );
    
    log_printf( &logger, " Read data:\r\n" );
    mram_read_data_bytes ( &mram, 0x0001, data_read, number_bytes_read );
    
    for ( i = 0; i < number_bytes_read; i++ )
    {
        log_printf( &logger, "%d ", ( uint16_t )data_read[ i ] );
    }
    
    log_printf( &logger, "\n" );

    Delay_ms ( 1000 );
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
