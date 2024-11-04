\mainpage Main Page
 
 

---
# DAC 5 Click

DAC 5 Click carries Texas Instruments DAC53608 IC, a low-power, eight-channel, 10-bit buffered Digital-to-Analog Converter. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-5-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Dac5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac5_cfg_setup ( dac5_cfg_t *cfg ); 
 
- Initialization function.
> DAC5_RETVAL dac5_init ( dac5_t *ctx, dac5_cfg_t *cfg );


#### Example key functions :

- Function for sending data to one output
> uint8_t dac5_send_data ( dac5_t *ctx, uint8_t data_reg, uint16_t data_buf );
 
- Function for configurating Click
> void dac5_config ( dac5_t *ctx, uint16_t config_data );

- Function for reading device id
> uint16_t dac5_get_device_id ( dac5_t *ctx );

## Examples Description

> This demo example sends digital signal to one of the outputs and converts it to analog

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, tests communication and configures device for measuring

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac5_cfg_t cfg;

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

    dac5_cfg_setup( &cfg );
    DAC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac5_init( &dac5, &cfg );

    if ( dac5_get_device_id( &dac5 ) != DAC5_DEVICE_ID )
    {
        log_printf( &logger, "ERROR - DEVICE IS NOT READY\r\n" );
        log_printf( &logger, "Please check the onboard jumpers position.\r\n" );
        for ( ; ; );
    }

    dac5_config( &dac5, DAC5_CONFIG_GLOBAL_ENABLED );
    log_printf( &logger, "The Click board is configured.\r\n" );

    Delay_ms ( 100 );
}
  
```

### Application Task

> Sets the channel H with different values and logs the expected output on USB UART

```c

void application_task ( void )
{
    for ( uint16_t cnt = DAC5_MIN_DATA; cnt < DAC5_MAX_DATA; cnt += 500 )
    {
        if ( dac5_send_data( &dac5, DAC5_REG_DAC_H_DATA, cnt ) == DAC5_ERROR )
        {
            log_printf( &logger, "ERROR SENDING DATA\r\n" );
        }
        else
        {
            log_printf( &logger, "Expected output on channel H:\t %d mV\r\n", ( uint16_t )( ( ( float ) cnt / DAC5_MAX_DATA ) * dac5.vref ) );
        }
        log_printf( &logger,"------------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}  

```

### Note

> In order to improve the accuracy, measure the voltage on the Click board VrefIN SEL jumper and set it as VREF.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac5

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
