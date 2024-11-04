
---
# Ammeter Click

Ammeter Click is a mikroBUS add-on board with circuitry for measuring electric current (both AC and DC).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ammeter_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ammeter-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Ammeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ammeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ammeter_cfg_setup ( ammeter_cfg_t *cfg ); 
 
- Initialization function.
> AMMETER_RETVAL ammeter_init ( ammeter_t *ctx, ammeter_cfg_t *cfg );


#### Example key functions :

- Function is used to measure amperage of a power consumer connected to the Click board.
> float ammeter_amperage ( ammeter_t *ctx );

## Examples Description

> 
> Demo app measures and displays current by using Ammeter Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes SPI, LOG and Click drivers.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ammeter_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    ammeter_cfg_setup( &cfg );
    AMMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ammeter_init( &ammeter, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Ammeter  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
  
```

### Application Task

>
> This is an example that shows the capabilities of the Ammeter Click by 
  measuring amperage in miliampers. Ammeter Click board can be used to saftly 
  measure current up to 1A both AC and DC, in the case of AC, for peak to peak value.
> 

```c

void application_task ( void )
{
    amperage = ammeter_amperage( &ammeter );
    log_printf( &logger, " Current: %.2f mA \r\n", amperage );
    
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}  

```

## Note

> 
> It is important to notice that this Click board has its' own electronic 
  circuit, and may not be powered from the same source which we are measuring.
  Result will not be correct in that case.
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ammeter

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
