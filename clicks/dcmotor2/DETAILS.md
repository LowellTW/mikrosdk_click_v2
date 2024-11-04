
---
# DC Motor 2 Click

<DC MOTOR 2 Click carries the TB6593FNG driver IC for direct current motors. With two pairs of screw terminals (power supply and outputs), the Click board can drive motors with voltages from 2.5 to 13V (output current of up to 1.2 amps with peaks up to 3.2 amps) . The PWM signal drives the motor while the IN1 and IN2 pins provide binary direction signals that set the direction of the motor (clockwise or counter clockwise), or apply stop or short brake functions.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dc-motor-2-click)

---

#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

We provide a library for the DcMotor2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor2_cfg_setup ( dcmotor2_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR2_RETVAL dcmotor2_init ( dcmotor2_t *ctx, dcmotor2_cfg_t *cfg );

- Click Default Configuration function.
> void dcmotor2_default_cfg ( dcmotor2_t *ctx );


#### Example key functions :

- This function sets the IN1/IN2 pins to 0/1 and makes the motor spin counter
  clockwise.
> void dcmotor2_spin_counter_clockwise ( dcmotor2_t *ctx );
 
- This function sets the IN1/IN2 pins to 1/0 and makes the motor spin clockwise.
> void dcmotor2_spin_clockwise ( dcmotor2_t *ctx );

- This function sets the IN1/IN2 pins to 1/1 and forces the motor to break.
> void dcmotor2_pull_brake ( dcmotor2_t *ctx );

- This function sets the IN1/IN2 pins to 0/0 and stops the motor completely.
> void dcmotor2_stop_motor ( dcmotor2_t *ctx );

## Examples Description

>  This library contains API for the DC Motor 2 Click driver.
>  This example showcases how to initialize and use the DC Motor 2 Click. The Click contains a 
>  Driver IC for DC motors which can spin the motor clockwise, counter-clockwise, break it and
>  completely stop the motor. The example needs a DC motor and a power supply in order to work.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and Click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor2_cfg_t cfg;

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

    dcmotor2_cfg_setup( &cfg );
    DCMOTOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms ( 100 );
    dcmotor2_init( &dcmotor2, &cfg );
    dcmotor2_pwm_start( &dcmotor2 );
    Delay_ms ( 1000 );
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

>  This is an example that demonstrates the use of the DC Motor 2 Click board.
>  DC Motor 2 Click communicates with register via PWM interface.
>  It shows moving in the Clockwise direction from slow to fast speed
>  and from fast to slow speed, then rotating Counter Clockwise,
>  Results are being sent to the Usart Terminal where you can track their changes. 

```c

void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_clockwise ( &dcmotor2 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }
    else
    {
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_counter_clockwise ( &dcmotor2 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }

    dcmotor2_set_duty_cycle ( &dcmotor2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;        
        if ( dcmotor_direction == 1 )
        {
            dcmotor_direction = 0;
        }
        else if ( dcmotor_direction == 0 )
        {
            dcmotor_direction = 1;
        }
    }
    duty_cnt += duty_inc;

}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor2

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
