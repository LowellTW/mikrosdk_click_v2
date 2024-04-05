/*!
 * @file main.c
 * @brief Volume Click example
 *
 * # Description
 * This example sets up the device and performs volume turn up and down.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes drivers and powers up the device.
 *
 * ## Application Task
 * Circles the volume from -40 [dB] to 10 [dB] back and forth.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "volume.h"

float left_speaker_gain;
float right_speaker_gain;
uint8_t one_circle;

static volume_t volume;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    volume_cfg_t volume_cfg;  /**< Click config object. */

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

    volume_cfg_setup( &volume_cfg );
    VOLUME_MAP_MIKROBUS( volume_cfg, MIKROBUS_1 );
    err_t init_flag  = volume_init( &volume, &volume_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    volume_default_cfg ( &volume );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    left_speaker_gain  = -40;
    right_speaker_gain = -40;
    one_circle = 0;
    
    log_printf( &logger, " Turning volume up.\r\n" );
    while ( one_circle < 2 ) {
        if ( one_circle == 0 ) {
            if ( left_speaker_gain <= 10 || right_speaker_gain <= 10 ) {
                volume_set_vol_gain( &volume, left_speaker_gain, right_speaker_gain );
                left_speaker_gain += 0.5;
                right_speaker_gain += 0.5;
                Delay_ms ( 50 );
            } else {
                one_circle++;
                log_printf( &logger, " Turning volume down.\r\n" );
            }
        } else if ( left_speaker_gain >= -40 || right_speaker_gain >= -40 ) {
            volume_set_vol_gain( &volume, left_speaker_gain, right_speaker_gain );
            left_speaker_gain -= 0.5;
            right_speaker_gain -= 0.5;
            Delay_ms ( 50 );
        } else one_circle++;
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
