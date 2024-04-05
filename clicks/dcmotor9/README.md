\mainpage Main Page
 
---
# DC Motor 9 click

DC Motor 9 Click is a brushed DC motor driver with the current limiting and current sensing. It is based on the DRV8871, an integrated H-Bridge driver IC, optimized for motor driving applications. It can be operated by two logic signals, allowing to drive the connected motor in two different ways: it can use fixed logic levels for the direction control, or it can be controlled by a PWM signal, offering an additional speed control option. The DRV8871 also contains a set of protection features, offering a very high level of reliability. Besides driving capabilities, DC Motor 9 click can also sense current consumption at its output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-9-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR9_RETVAL dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg );


#### Example key functions :

- This function read ADC data.
> dcmotor9_data_t dcmotor9_generic_read ( dcmotor9_t *ctx );
 
- This function starts PWM module.
> void dcmotor9_pwm_start ( dcmotor9_t *ctx );

- This function sets the PWM duty cycle.
> void dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle );

## Examples Description

> DC Motor 9 Click is a brushed DC motor driver with the current limiting and current sensing. It can
> be operated by two logic signals, allowing to drive the connected motor in two different ways: 
> it can use fixed logic levels for the direction control, or it can be controlled by a PWM signal, 
> offering an additional speed control option. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO, PWM and logger and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t dcmotor9_cfg;

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

    dcmotor9_cfg_setup( &dcmotor9_cfg );
    DCMOTOR9_MAP_MIKROBUS( dcmotor9_cfg, MIKROBUS_1 );
    if ( dcmotor9_init( &dcmotor9, &dcmotor9_cfg ) == PWM_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }

    dcmotor9_set_duty_cycle ( &dcmotor9, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    
    dcmotor9_enable( &dcmotor9 );
    dcmotor9_pwm_start( &dcmotor9 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>  This is a example which demonstrates the use of DC Motor 5 Click board.
>  DC Motor 9 Click controls DC Motor speed via PWM interface.
>  It shows moving in the both directions from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.
```c

void application_task ( void )
{
    static float duty;
    static uint8_t n_cnt;
    
    dcmotor9_clockwise ( &dcmotor9 );
    log_printf( &logger, "> CLOCKWISE <\r\n" );
    dcmotor9_enable ( &dcmotor9 );
    
    for ( n_cnt = 10; n_cnt > 0; n_cnt--  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++ )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
    log_printf( &logger, "* Pull break *\r\n" );
    dcmotor9_short_brake( &dcmotor9 );
    Delay_ms ( 1000 );
    
    dcmotor9_counter_clockwise ( &dcmotor9 );
    log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 10; n_cnt > 0; n_cnt-- )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
}
  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor9

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
