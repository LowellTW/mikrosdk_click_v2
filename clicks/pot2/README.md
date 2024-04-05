\mainpage Main Page
 
 

---
# POT 2 click

POT 2 click is a Click board™ with the accurate selectable reference voltage output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pot-2-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Pot2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pot2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pot2_cfg_setup ( pot2_cfg_t *cfg ); 
 
- Initialization function.
> POT2_RETVAL pot2_init ( pot2_t *ctx, pot2_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> pot2_data_t pot2_generic_read ( pot2_t *ctx );

## Examples Description

> This demo-app shows the ADC values using POT 2 click board.

**The demo application is composed of two sections :**

### Application Init 

> Configures clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pot2_cfg_t cfg;

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

    pot2_cfg_setup( &cfg );
    POT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pot2_init( &pot2, &cfg );
}
```

### Application Task

> Demo app reads ADC data and displays them as dec and hex values every second.

```c
void application_task ( void )
{
    pot2_data_t tmp;
    
    tmp = pot2_generic_read ( &pot2 );
    log_printf( &logger, " ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot2

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
