
---
# OSD click

> OSD Click features MAX7456 single-channel monochrome OSD module with integrated EEPROM memory as well as two RCA sockets. It is used to create on-screen menus and other video overlays, such as custom graphics, company logo, time and date using 256 user-programmable characters or pictographs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/osd_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/osd-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the OSD Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OSD Click driver.

#### Standard key functions :

- `osd_cfg_setup` Config Object Initialization function.
```c
void osd_cfg_setup ( osd_cfg_t *cfg ); 
```

- `osd_init` Initialization function.
```c
err_t osd_init ( osd_t *ctx, osd_cfg_t *cfg );
```

- `osd_default_cfg` Click Default Configuration function.
```c
void osd_default_cfg ( osd_t *ctx );
```

#### Example key functions :

- `osd_clear_display_memory` This function clears display memory.
```c
void osd_clear_display_memory( osd_t *ctx );
```

- `osd_insert_custom_char` This function writes custom character.
```c
void osd_insert_custom_char( osd_t *ctx, uint8_t chr_address, uint8_t custom_char );
```

- `osd_enable_video_buffer` This function enables video buffer.
```c
void osd_enable_video_buffer( osd_t *ctx );
```

## Examples Description

> This demo performs basic OSD Click functionality - write text on screen.

**The demo application is composed of two sections :**

### Application Init 

> Device initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    osd_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    osd_cfg_setup( &cfg );
    OSD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    osd_init( &osd, &cfg );

    osd_default_cfg( &osd );
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Write text on the screen, write character per 1 second in the first, seventh and fifteenth row of the screen.

```c

void application_task ( void )
{
    log_printf( &logger, "\r\n Writing characters on the screen...\r\n" );
    for ( uint8_t cnt = 0; cnt < 30; cnt++ )
    {
        if ( HEADER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 1, cnt, HEADER_TEXT[ cnt ] );
        }

        if ( MESSAGE_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 7, cnt, MESSAGE_TEXT[ cnt ] );
        }

        if ( FOOTER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 14, cnt, FOOTER_TEXT[ cnt ] );
        }

        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clear display\r\n" );
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OSD

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