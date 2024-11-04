
---
# LPS22HB Click

LPS22HB Click is an easy solution for adding a digital barometer to your design. It carries the LPS22HB MEMS nano pressure sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lps22hb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lps22hb-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Lps22hb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Lps22hb Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lps22hb_cfg_setup ( lps22hb_cfg_t *cfg ); 
 
- Initialization function.
> LPS22HB_RETVAL lps22hb_init ( lps22hb_t *ctx, lps22hb_cfg_t *cfg );

- Click Default Configuration function.
> void lps22hb_default_cfg ( lps22hb_t *ctx );


#### Example key functions :

- Click Default Configuration function.
> void lps22hb_default_cfg ( lps22hb_t *ctx );
 
- Function gets pressure data, calculates and returns pressure.
> float lps22hb_get_pressure ( lps22hb_t *ctx );
 
- Function gets temperature returns value in degrees Celsius.
> float lps22hb_get_temp ( lps22hb_t *ctx );

## Examples Description

> 
> The demo application measures temperature and pressure.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes Click driver, resets the device, applies default settings
> and makes an initial log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lps22hb_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    lps22hb_cfg_setup( &cfg );
    LPS22HB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lps22hb_init( &lps22hb, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ------ LPS22HB Click ------\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    lps22hb_default_cfg ( &lps22hb, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> This is a example which demonstrates the use of LPS22HB Click board. By 
> measuring temperature and pressure. The results are being sent to the USART 
> terminal where you can track their changes.
> 

```c

void application_task ( void )
{
    pressure = lps22hb_get_pressure( &lps22hb );
    temperature = lps22hb_get_temp( &lps22hb );
    
    log_printf( &logger, "** Pressure is %.2f mBar\r\n", pressure );
    log_printf( &logger, "** Temperature is %.2f C \r\n", temperature );
    
    log_printf( &logger, "----------------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Lps22hb

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
