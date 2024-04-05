 
---
# Temp Hum 11 click

Temp-hum 11 click is a temperature and humidity sensing Click board™, equipped with the HDC1080, a high accuracy digital humidity, and temperature sensor. Its key features are its low power consumption, and the measurement accuracy achieved with that much energy.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum11_cfg_setup ( temphum11_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM11_RETVAL temphum11_init ( temphum11_t *ctx, temphum11_cfg_t *cfg );

- Click Default Configuration function.
> void temphum11_default_cfg ( temphum11_t *ctx );


#### Example key functions :

- This function reads temperature data in desired unit.
> float temphum11_get_temperature ( temphum11_t *ctx, uint8_t temp_in );
 
- This function reads relative huminidy data
> float temphum11_get_humidity ( temphum11_t *ctx );

- This function reads data from the desired register.
> uint16_t temphum11_read_data ( temphum11_t *ctx, uint8_t reg );

## Examples Description

> This click has two sensors which can be set to sample measurements with the resolution 
> of 8, 11 or 14 bits, based on the measurement time. Calibration coefficients that are applied 
> to the measured value and the results are stored in the MSB/LSB format, on the output registers. 
> These values are then used in formulas so that the final temperature or relative humidity data can be calculated.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, test comunication and configuration chip for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum11_cfg_t cfg;

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

    temphum11_cfg_setup( &cfg );
    TEMPHUM11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum11_init( &temphum11, &cfg );

    // Test comunication

    if ( temphum11_read_data( &temphum11, TEMPHUM11_REG_DEVICE_ID ) == TEMPHUM11_DEVICE_ID )
    {
        log_printf( &logger, "--- Comunication OK!!! ---\r\n" );
    }
    else
    {
        log_printf( &logger, "--- Comunication ERROR!!! ---\r\n" );
        for ( ; ; );
    }

    temphum11_default_cfg( &temphum11 );
    log_printf( &logger, "--- Start measurement --- \r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads Temperature and Humidity data. This data logs to USBUART every 1500ms.

```c

void application_task ( void )
{
    temperature = temphum11_get_temperature( &temphum11, TEMPHUM11_TEMP_IN_CELSIUS );
    
    log_printf( &logger, " Temperature : %.2f\r\n", temperature );
    
    humidity = temphum11_get_humidity( &temphum11 );
    
    log_printf( &logger, " Humidity :  %.2f\r\n", humidity );
    
    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum11

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
