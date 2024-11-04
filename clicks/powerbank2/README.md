\mainpage Main Page
 
---
# PowerBank 2 Click

The PowerBank 2 Click is a Click board™ equipped with the RT9480, highly integrated and easy to use power solution for Li-ion power bank and other powered handheld applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powerbank2_click.png">
</p>

[Click Product page](https://www.mikroe.com/powerbank-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Powerbank2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Powerbank2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void powerbank2_cfg_setup ( powerbank2_cfg_t *cfg ); 
 
- Initialization function.
> POWERBANK2_RETVAL powerbank2_init ( powerbank2_t *ctx, powerbank2_cfg_t *cfg );

#### Example key functions :

- Read function.
> void powerbank2_read ( powerbank2_t *ctx, uint16_t *result );
 
- Read voltage function.
> uint16_t powerbank2_read_voltage ( powerbank2_t *ctx, uint16_t v_ref );

## Examples Description

> This single chip includes a linear charger, a synchronous Boost with dual output load management and a torch function support. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank2_cfg_t cfg;

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

    powerbank2_cfg_setup( &cfg );
    POWERBANK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank2_init( &powerbank2, &cfg );
}
  
```

### Application Task

> This example shows the capabilities of the Power Bank 2 Click
> by measuring voltage of the connected battery. In order to get correct calculations 
> the user should change "v_ref" value to his own power supply voltage.

```c

void application_task ( void )
{
    voltage = powerbank2_read_voltage( &powerbank2, v_ref );

    log_printf( &logger, "Battery voltage: %u mV\r\n", voltage );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Powerbank2

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
