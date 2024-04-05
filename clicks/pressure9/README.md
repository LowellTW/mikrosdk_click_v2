\mainpage Main Page
 
---
# Pressure 9 click

> Pressure 9 click is a digital barometric air pressure sensor Click board™. It is equipped with the DPS422, barometric air pressure sensor, based on a capacitive sensor element.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure9_click.png" height=300px>
</p>

> - [click Product page](https://www.mikroe.com/pressure-9-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure9 Click driver.

#### Standard key functions :

- `pressure9_cfg_setup` Config Object Initialization function.
```c
void pressure9_cfg_setup ( pressure9_cfg_t *cfg ); 
```

- `pressure9_init` Initialization function.
```c
err_t pressure9_init ( pressure9_t *ctx, pressure9_cfg_t *cfg );
```

- `pressure9_default_cfg` Click Default Configuration function.
```c
void pressure9_default_cfg ( pressure9_t *ctx );
```

#### Example key functions :

- `pressure9_get_pressure_data` Get Pressure data in mBar
```c
float pressure9_get_pressure_data ( pressure9_t *ctx );
```

- `pressure9_get_temperature_data` Get Temperature data in C
```c
float pressure9_get_temperature_data ( pressure9_t *ctx );
```

- `pressure9_configuration` Writing data to the configuration registers
```c
void pressure9_configuration ( pressure9_t *ctx, uint8_t reg_adr, uint8_t data_in );
```

## Examples Description

> The demo application displays the pressure and temperature measurement using Pressure 9 click.

**The demo application is composed of two sections :**

### Application Init 

> Initialization the driver, test comunication, and performs the click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure9_cfg_t cfg;

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

    //  Click initialization.
    pressure9_cfg_setup( &cfg );
    PRESSURE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure9_init( &pressure9, &cfg );
    Delay_ms ( 100 );

    // Test comunication
    uint8_t product_id = 0;
    pressure9_generic_read( &pressure9, PRESSURE9_REG_PRODUCT_ID, &product_id, 1 );
    if ( PRESSURE9_PRODUCT_ID != product_id )
    {
        log_error( &logger, "Read product ID." );
        for ( ; ; );
    }

    pressure9_default_cfg( &pressure9 );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Reads Temperature data in [C] and Pressure data in [mBar] and this data logs to the USB UART every 2 sec.

```c
void application_task ( void )
{
    pressure = pressure9_get_pressure_data( &pressure9 );
    log_printf( &logger, " Pressure: %.2f mBar\r\n", pressure );

    temperature = pressure9_get_temperature_data( &pressure9 );
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure9

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
