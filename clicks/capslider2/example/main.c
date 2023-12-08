/*!
 * \file 
 * \brief CapSlider2 Click example
 * 
 * # Description
 * This application could be used for controlling various devices.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface, performs the device reset and configurations
 * and sets the desired threshold value which determines sensor sensitivity.
 * 
 * ## Application Task  
 * Checks for data ready and then read capacitance from all channels.
 * There are two sliders on the clik board (X and Y).
 * X slider selects which LEDs are being activated, 
 * while Y slider increases/decreases the LEDs intensity.
 * 
 * ## NOTE 
 * In some cases, the user will need to wait several seconds after the click initialization
 * for the sensor to be stabilized.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capslider2.h"

// ------------------------------------------------------------------ VARIABLES

static capslider2_t capslider2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

uint32_t wheel_avrg1;
uint32_t wheel_avrg2;
uint16_t out_val;
uint8_t out_mode;
uint8_t cnt;

void horizontal_check(  )
{
    out_val = ((wheel_avrg1 / cnt) / 142.1) - 5;
    out_mode = CAPSLDR2_LED_NUMBER;
}

void vertical_check(  )
{
    out_val = (2047 - (wheel_avrg1 / cnt)) / 147.4;
    out_mode = CAPSLDR2_LED_INTENSITY;
}


void application_init ( void )
{
    log_cfg_t log_cfg;
    capslider2_cfg_t cfg;

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

    capslider2_cfg_setup( &cfg );
    CAPSLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capslider2_init( &capslider2, &cfg );

    Delay_ms( 500 );

    cnt = 0;
    wheel_avrg1 = 0;
    wheel_avrg2 = 0;
    
    capsldr2_reset( &capslider2 );
    Delay_ms( 500 );
    
    capsldr2_enable_chann( &capslider2, CAPSLDR2_CH0_PROX_EN | CAPSLDR2_CH1_EN | CAPSLDR2_CH2_EN | CAPSLDR2_CH3_EN | CAPSLDR2_CH4_EN | CAPSLDR2_CH5_EN | CAPSLDR2_CH6_EN | CAPSLDR2_CH7_EN | CAPSLDR2_CH8_EN | CAPSLDR2_CH9_EN );
    capsldr2_config( &capslider2 );
    capsldr2_set_threshold( &capslider2, 0x04 );
    Delay_ms( 2000 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "CAP Slider 2 is initialized\r\n" );

}

void application_task ( void )
{
    uint16_t data_wheel1;
    uint16_t data_wheel2;
    uint8_t ready_check;

    ready_check = capsldr2_check_data_ready( &capslider2 );
    
    if (ready_check == CAPSLDR2_DATA_READY)
    {
        capsldr2_get_data( &capslider2, &data_wheel1, &data_wheel2 );
        
        wheel_avrg1 += data_wheel1;
        wheel_avrg2 += data_wheel2;
        cnt++;
    }
    
    if (cnt == 1)
    {
        if ((wheel_avrg2 / cnt) > 1800)
        {
            horizontal_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        else if (((wheel_avrg2 / cnt) < 1650) && ((wheel_avrg2 / cnt) > 1000))
        {
            vertical_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        
        wheel_avrg1 = 0;
        wheel_avrg2 = 0;
        cnt = 0;
    }
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
