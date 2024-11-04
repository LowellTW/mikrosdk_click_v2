\mainpage Main Page
 
 

---
# IR reflect Click

IR reflect Click carries a GP2S700HCP reflective photointerrupter and an onboard potentiometer. On this type of photointerrupter the infrared emitter and receiver are facing the same direction.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irreflect_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-reflect-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the IrReflect Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrReflect Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irreflect_cfg_setup ( irreflect_cfg_t *cfg ); 
 
- Initialization function.
> IRREFLECT_RETVAL irreflect_init ( irreflect_t *ctx, irreflect_cfg_t *cfg );

- Click Default Configuration function.
> void irreflect_default_cfg ( irreflect_t *ctx );


#### Example key functions :

- Function detecting interrupt states of IR reflection
> uint8_t irreflect_reflect_status ( irreflect_t *ctx );
 
- Function detecting states of analog pin of IR reflection
> uint8_t irreflect_analog_status ( irreflect_t *ctx );


## Examples Description

> Example demonstrates the use of IR Reflect Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - Start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irreflect_cfg_t cfg;

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
    log_info(&logger, "---- Application ----\n");

    //  Click initialization.
    irreflect_cfg_setup( &cfg );
    IRREFLECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irreflect_init( &irreflect, &cfg );
    
    ir_state = 0;
    ir_state_old = 0;
    counter = 1;
}
  
```

### Application Task

> This is a example which demonstrates the use of IR Reflect Click board.
> On this type of photointerrupter the infrared emitter and receiver are facing the same direction,
> the infrared beam from the emitter gets bounced back to the receiver when an object 
> is placed within the detecting range of the sensor ( optimal range is 3mm ).
> These sensors are used to detect an object's presence or motion, such as a piece of paper passing through a printer
> and counting when sensor is triggered.
> Results are being sent to the Usart Terminal where you can track their changes.
> Data logs on usb uart when the sensor is triggered.

```c

void application_task ( void )
{
    //  Task implementation.
    
    ir_state = irreflect_reflect_status( &irreflect );

    if ( ir_state_old != ir_state )
    {
        if ( ir_state )
        {
            log_printf( &logger, "  Counter = %u\n", counter);
            counter++;
        }
        ir_state_old = ir_state;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrReflect

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
