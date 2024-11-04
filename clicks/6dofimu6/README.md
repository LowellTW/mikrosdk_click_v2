\mainpage Main Page
 
---
# 6DOF IMU 6 Click

6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, a 3-axis accelerometer, and a Digital Motion Processor™ (DMP) labeled as ICM-20689. The ICM-20689 from company TDK InvenSense includes on-chip 16-bit ADCs, programmable digital filters, an embedded temperature sensor, and programmable interrupts. The gyroscope and accelerometer are full-scale range, user-programmable sensors with factory-calibrated initial sensitivity for reduced production-line calibration requirements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu6_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/6dof-imu-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DofImu6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 6DofImu6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c6dofimu6_cfg_setup ( c6dofimu6_cfg_t *cfg ); 
 
- Initialization function.
> C6DOFIMU6_RETVAL c6dofimu6_init ( c6dofimu6_t *ctx, c6dofimu6_cfg_t *cfg );

- Click Default Configuration function.
> void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );


#### Example key functions :

- This function executes default configuration for 6DOF IMU 6 Click.
> void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );
 
- Function is used to calculate angular rate.
> void c6dofimu6_angular_rate ( c6dofimu6_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );

- Function is used to calculate acceleration rate.
> void c6dofimu6_acceleration_rate ( c6dofimu6_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );

## Examples Description

> 6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, 
> a 3-axis accelerometer, and a Digital Motion Processor. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI and I2C drivers, performs safety check, applies default 
> settings and writes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu6_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c6dofimu6_cfg_setup( &cfg );
    C6DOFIMU6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu6_init( &c6dofimu6, &cfg );

    Delay_ms ( 100 );
    c6dofimu6_generic_read ( &c6dofimu6, C6DOFIMU6_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU6_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   6DOF  IMU  6  Click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        c6dofimu6_power ( &c6dofimu6, C6DOFIMU6_POWER_ON );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu6_default_cfg( &c6dofimu6 );

    log_printf( &logger, "    ---Initialised---    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms ( 100 );
}
  
```

### Application Task

> Demonstrates the use of 6DOF IMU 6 Click board by reading angular rate, acceleration rate 
> and displaying data to USB UART.

```c

void application_task ( void )
{
    c6dofimu6_angular_rate( &c6dofimu6, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Gyro \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_gyro );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_gyro );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_gyro );
    log_printf( &logger, "---------------------\r\n" );

    c6dofimu6_acceleration_rate( &c6dofimu6, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Accel \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_accel );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_accel );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_accel );
    log_printf( &logger, "---------------------\r\n\r\n" );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.6DofImu6

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
