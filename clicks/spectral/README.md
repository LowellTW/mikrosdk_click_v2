\mainpage Main Page
 
---
# Spectral click

> Spectral click is a multispectral light sensing device, which uses the state-of-the-art sensor IC for a very accurate chromatic white color sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spectral_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spectral-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Mar 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Spectral Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spectral Click driver.

#### Standard key functions :

- `spectral_cfg_setup` Config Object Initialization function.
```c
void spectral_cfg_setup ( spectral_cfg_t *cfg ); 
```

- `spectral_init` Initialization function.
```c
err_t spectral_init ( spectral_t *ctx, spectral_cfg_t *cfg );
```

#### Example key functions :

- `spectral_uart_read` Generic read function.
```c
int32_t spectral_uart_read ( spectral_t *ctx, uint8_t *data_buf, uint16_t max_len );
```

- `spectral_send_command` Send Command
```c
void spectral_send_command ( spectral_t *ctx, uint8_t *command );
```

- `spectral_get_data` Read raw X, Y, Z and NIR data as well as two special internal registers D, & C.
```c
void spectral_get_data ( uint8_t *rsp, uint16_t *c_data );
```

## Examples Description

> This example reads and processes data from Spectral clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the sensor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral_cfg_t cfg;

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

    // Click initialization.
    spectral_cfg_setup( &cfg );
    SPECTRAL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral_init( &spectral, &cfg );

    spectral_module_reset( &spectral );
    Delay_ms ( 500 );

    log_printf( &logger, "Configuring the sensor...\r\n" );
    spectral_send_command( &spectral, SPECTRAL_CMD_AT );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_GAIN );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_MODE );
    spectral_process( );
    log_printf( &logger, "The sensor has been configured!\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Reads the values of all 6 channels and parses it to the USB UART each second.

```c

void application_task ( void )
{
    parser_application( );  
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectral

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
