\mainpage Main Page
 
---
# Compass 4 click

Compass 4 Click is a compact add-on board that can measure the three-axis magnetic field that is perfect for implementation in applications such as electric compasses.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass4_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/compass-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Compass4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Compass4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void compass4_cfg_setup ( compass4_cfg_t *cfg ); 
 
- Initialization function.
> COMPASS4_RETVAL compass4_init ( compass4_t *ctx, compass4_cfg_t *cfg );

#### Example key functions :

- Gets INT pin state (DRDY pin)
> uint8_t compass4_get_interrupt ( compass4_t *ctx );
 
- Gets single axis value
> uint8_t compass4_get_single_axis ( compass4_t *ctx, uint8_t axis_reg, int16_t *axis_data );

- Gets magnetic flux of X\Y\Z axis value
> uint8_t compass4_get_magnetic_flux ( compass4_t *ctx, compass4_flux_t *flux );

## Examples Description

> This demo application measures magnetic flux data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and resets the module, then checks the communication with the module and sets the module default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass4_cfg_t cfg;

    uint8_t device;

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

    compass4_cfg_setup( &cfg );
    COMPASS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass4_init( &compass4, &cfg );

    compass4_hardware_reset( &compass4 );
    Delay_ms ( 500 );
    
    device = compass4_check_device( &compass4 );
    if ( device == 0 )
    {
        log_printf( &logger, ">> Device communication [ OK ] \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Device communication [ ERROR ] \r\n" );
        for ( ; ; );
    }
    
    compass4_configuration ( &compass4, COMPASS4_CTRL1_WM_STEPS_5 | 
                                        COMPASS4_CTRL1_NOISE_ENABLE,
                                        COMPASS4_CTRL2_MODE_CONT_1 | 
                                        COMPASS4_CTRL2_SDR_LOW_NOISE |
                                        COMPASS4_CTRL2_FIFO_ENABLE );
                             
    log_printf( &logger, ">> Start measurement  \r\n" );
}
  
```

### Application Task

> Reads magnetic flux data and displays the values of X, Y, and Z axis to the USB UART each second.

```c

void application_task ( void )
{
    compass4_flux_t flux;
    uint8_t err;
    
    err = compass4_get_magnetic_flux( &compass4, &flux );
    if ( err != 0 )
    {
        log_printf( &logger, ">> Measurement error  \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Magnetic flux data << \r\n" );
        log_printf( &logger, ">> X: %.2f \r\n", flux.x );
        log_printf( &logger, ">> Y: %.2f \r\n", flux.y );
        log_printf( &logger, ">> Z: %.2f \r\n", flux.z );
    }
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass4

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
