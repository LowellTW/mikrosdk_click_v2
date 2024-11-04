/*!
 * \file 
 * \brief I2Cisolator Click example
 * 
 * # Description
 * This is an example which demonstrates the use of I2C Isolator Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * sets configuration of TMP007 sensor on IrThermo 2 Click and start to write log.
 * 
 * ## Application Task  
 * In this example we use IrThermo 2 Click, measures the temperature with,
 * and calculate the temperature in degrees Celsius [ C ].
 * Results are being sent to the USART Terminal where you can track their changes.
 * All data logs on usb uart each second.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cisolator.h"

/* Register Address */
#define I2CISOLATOR_IRTHERMO2_CONFIGURATION                       0x02
#define I2CISOLATOR_IRTHERMO2_OBJECT_TEMPERATURE              0x03
#define I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE       0x05

/* Commands */       
#define I2CISOLATOR_IRTHERMO2_CFG_MODEON                           0x1000
#define I2CISOLATOR_IRTHERMO2_CFG_ALERTEN                           0x0100
#define I2CISOLATOR_IRTHERMO2_CFG_TRANSC                            0x0040
#define I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE                         0x0800
#define I2CISOLATOR_IRTHERMO2_STAT_ALERTEN                         0x8000
#define I2CISOLATOR_IRTHERMO2_STAT_CRTEN                            0x4000

// ------------------------------------------------------------------ VARIABLES

static i2cisolator_t i2cisolator;
static log_t logger;
static float temperature;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void i2cisolator_get_temperature ( void )
{
    uint8_t temp_data[ 2 ];
    uint16_t temp;
    
    i2cisolator_generic_read( &i2cisolator, I2CISOLATOR_IRTHERMO2_OBJECT_TEMPERATURE, temp_data, 2 );
    
    temp = temp_data[ 0 ];
    temp <<= 8;
    temp |= temp_data[ 1 ];
    temp >>= 2;
    temperature = ( float ) temp;
    temperature *= 0.03125;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator_cfg_t cfg;
    uint8_t tmp;

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

    i2cisolator_cfg_setup( &cfg );
    I2CISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator_init( &i2cisolator, &cfg );

    log_printf( &logger, "    Driver  Initialized\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
    tmp =    I2CISOLATOR_IRTHERMO2_CFG_MODEON |
                I2CISOLATOR_IRTHERMO2_CFG_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_CFG_TRANSC | 
                I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_CONFIGURATION, &tmp, 1 );

    tmp =    I2CISOLATOR_IRTHERMO2_STAT_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_STAT_CRTEN;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE, &tmp, 1 );    
    
    log_printf( &logger, "       Configuration\r\n" );
    log_printf( &logger, "      IrThermo 2 Click\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    i2cisolator_get_temperature( );   
    
    log_printf( &logger, " Temperature : %0.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );
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
