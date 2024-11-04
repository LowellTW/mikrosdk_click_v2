
---
# Accel Click

Accel Click is an accessory board in mikroBUS form factor. It features ADXL345 3-axis accelerometer module with ultra-low power and high resolution (13-bit) measurement.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/accel-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel Click driver.

#### Standard key functions :

- `accel_cfg_setup` Config Object Initialization function.
```c
void accel_cfg_setup ( accel_cfg_t *cfg );
```

- `accel_init` Initialization function.
```c
err_t accel_init ( accel_t *ctx, accel_cfg_t *cfg );
```

- `accel_default_cfg` Click Default Configuration function.
```c
void accel_default_cfg ( accel_t *ctx );
```

#### Example key functions :

- `accel_read_x_axis` Function reads X axis value from Accel.
```c
int16_t accel_read_x_axis ( accel_t *ctx );
```
 
- `accel_read_y_axis` Function reads Y axis value from Accel.
```c
int16_t accel_read_y_axis ( accel_t *ctx );
```

- `accel_read_z_axis` Function reads Z axis value from Accel.
```c
int16_t accel_read_z_axis ( accel_t *ctx );
```

## Examples Description

> This example demonstrates the use of Accel Click board by reading and displaying the accelerometer data (X, Y, and Z axis).

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI/I2C driver and settings data read format, power mode, FIFO control and baud rate ( 100Hz default ).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel_cfg_t cfg;

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

    accel_cfg_setup( &cfg );
    ACCEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel_init( &accel, &cfg );

    accel_generic_read( &accel, ACCEL_REG_DEVID, &tmp, 1 );

    if ( tmp == ACCEL_DEVID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        for ( ; ; );
    }
    accel_default_cfg ( &accel );
}
```

### Application Task

> Reads X, Y and Z axis and logs on usbuart every 100 ms.

```c
void application_task ( void )
{
    val_x = accel_read_x_axis( &accel );
    log_printf( &logger, "Axis X : %.3f g\r\n", val_x / ACCEL_DATA_RES_LSB_PER_G );

    val_y = accel_read_y_axis( &accel );
    log_printf( &logger, "Axis Y : %.3f g\r\n", val_y / ACCEL_DATA_RES_LSB_PER_G );

    val_z = accel_read_z_axis( &accel );
    log_printf( &logger, "Axis Z : %.3f g\r\n", val_z / ACCEL_DATA_RES_LSB_PER_G );

    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
