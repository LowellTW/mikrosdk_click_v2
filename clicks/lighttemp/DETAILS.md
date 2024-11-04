
---
# Light Temp Click

Light Temp Click is a dual-channel LED driver, designed to be used in tunable Smart Connected Lighting (SCL) applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lighttemp_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/light-temp-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the LightTemp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightTemp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lighttemp_cfg_setup ( lighttemp_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTTEMP_RETVAL lighttemp_init ( lighttemp_t *ctx, lighttemp_cfg_t *cfg );

#### Example key functions :

- Get INT pin state
> uint8_t lighttemp_get_interrupt_state ( lighttemp_t *ctx );
 
- Get voltage
> uint16_t lighttemp_get_pg_voltage ( lighttemp_t *ctx );

- Start PW2 module.
> void lighttemp_cs_set_state( lighttemp_t *ctx, uint8_t state );

## Examples Description

> This application controls light intensity of LEDs.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and pwm init for all LED's

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lighttemp_cfg_t cfg;

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
    Delay_ms ( 100 );
    
    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );
    
    lighttemp_led1_set_duty_cycle ( &lighttemp, 0.0 );
    lighttemp_led2_set_duty_cycle ( &lighttemp, 0.0 );
    
    log_info( &logger, "---- Application Task ----" );

    Delay_ms ( 500 );
}
  
```

### Application Task

>  This is an example that demonstrates the use of the Light Temp Click board.
>  This example shows the automatic control of the LED light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes. 

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    lighttemp_led1_set_duty_cycle ( &lighttemp, duty );
    lighttemp_led2_set_duty_cycle ( &lighttemp, duty );
    
    lighttemp_led1_pwm_start( &lighttemp );
    lighttemp_led2_pwm_start( &lighttemp );

    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightTemp

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
