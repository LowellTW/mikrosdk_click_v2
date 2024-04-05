
---
# Pressure 8 click

> Pressure 8 Click is an accurate and fully calibrated pressure sensor, equipped with the MPR series integrated piezoresistive silicon pressure sensor IC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure8 Click driver.

#### Standard key functions :

- `pressure8_cfg_setup` Config Object Initialization function.
```c
void pressure8_cfg_setup ( pressure8_cfg_t *cfg ); 
```

- `pressure8_init` Initialization function.
```c
err_t pressure8_init ( pressure8_t *ctx, pressure8_cfg_t *cfg );
```

#### Example key functions :

- `pressure8_get_pressure` Functions for get Pressure data
```c
float pressure8_get_pressure ( pressure8_t *ctx, uint8_t press_format );
```

- `pressure8_get_device_status` Functions for get device status
```c
uint8_t pressure8_get_device_status ( pressure8_t *ctx );
```

- `pressure8_set_psi_range` Functions for set PSI range
```c
void pressure8_set_psi_range ( pressure8_t *ctx, float psi_min, float psi_max );
```

## Examples Description

> This application reads pressure data.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device and logger module, reset device and set PSI range.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure8_cfg_t cfg;

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
    pressure8_cfg_setup( &cfg );
    PRESSURE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure8_init( &pressure8, &cfg );

    pressure8_device_reset( &pressure8 );
    pressure8_set_psi_range( &pressure8, 0, 25 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads pressure data in mBar and logs it on the USB UART once per second.

```c
void application_task ( void )
{
    float pressure = 0;
    
    pressure = pressure8_get_pressure( &pressure8, PRESSURE8_DATA_IN_MBAR );
    log_printf( &logger, " Pressure: %.1f mBar\r\n", pressure );

    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure8

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
