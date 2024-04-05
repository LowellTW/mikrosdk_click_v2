/*!
 * @file main.c
 * @brief nvSRAM3 Click example
 *
 * # Description
 * The demo application shows how to write/read data to/from nvSRAM memory.
 * It also sets RTC date and time, then reads it in an infinite loop and displays results on USB UART each second. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes device, reads the device ID, writes desired message to memory and sets RTC date and time.
 *
 * ## Application Task
 * Reads current date and time and then reads the message that we have previusly stored in the memory.
 * All data is being logged on USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nvsram3.h"

static nvsram3_t nvsram3;
static log_t logger;

static char demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char rx_data[ 9 ];
static uint32_t memory_addr;
static uint8_t new_sec = 255;
static uint16_t c_year = 2020;

static nvsram3_rtc_time_t time;
static nvsram3_rtc_date_t date;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nvsram3_cfg_t nvsram3_cfg;  /**< Click config object. */

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

    nvsram3_cfg_setup( &nvsram3_cfg );
    NVSRAM3_MAP_MIKROBUS( nvsram3_cfg, MIKROBUS_1 );
    err_t init_flag = nvsram3_init( &nvsram3, &nvsram3_cfg );
    
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     nvSRAM 3 click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    nvsram3_default_cfg ( &nvsram3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " DEVICE ID: 0x%.8LX\r\n", nvsram3_get_device_id( &nvsram3 ) );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
    
    memory_addr = 0x10000;
    
    log_printf( &logger, "  Write data : %s", demo_data );
    nvsram3_memory_write( &nvsram3, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    date.day_of_week = 4;
    date.day = 31;
    date.month = 12;
    date.year = 2020;
    nvsram3_set_rtc_date( &nvsram3, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    nvsram3_set_rtc_time( &nvsram3, time );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    nvsram3_get_rtc_time( &nvsram3, &time );
    nvsram3_get_rtc_date( &nvsram3, &date );
    
    if ( time.sec != new_sec ) 
    {
        log_printf( &logger, "  Date      : %.2d-%.2d-%.4d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        
        if ( date.year != c_year ) 
        {
            log_printf( &logger, "     Happy New Year    \r\n" );
            c_year = date.year;
        } 
        else 
        {
            nvsram3_memory_read( &nvsram3, memory_addr, &rx_data[ 0 ], 9 );
            log_printf( &logger, "  Read data : %s", rx_data );    
        }
               
        log_printf( &logger, "-----------------------\r\n" );
    } 
    else 
    {
        Delay_ms ( 500 );    
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
