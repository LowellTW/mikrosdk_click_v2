\mainpage Main Page
 
---
# 10x10 RGB click

10x10 RGB Click is a matrix of 100 intelligent RGB elements, forming a 10x10 display screen. These LED elements feature internal logic, which allows them to communicate directly with the MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/10x10rgb_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/10x10-rgb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

We provide a library for the 10x10RGB Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 10x10RGB Click driver.

#### Standard key functions :

- `c10x10rgb_cfg_setup` Config Object Initialization function.
```c
void c10x10rgb_cfg_setup ( c10x10rgb_cfg_t *cfg ); 
```

- `c10x10rgb_init` Initialization function.
```c
C10X10RGB_RETVAL c10x10rgb_init ( c10x10rgb_t *ctx, c10x10rgb_cfg_t *cfg );
```

- `c10x10rgb_default_cfg` Click Default Configuration function.
```c
void c10x10rgb_default_cfg ( c10x10rgb_t *ctx );
```


#### Example key functions :

- `c10x10rgb_display_image` This function displays an image from the specified demo_image address.
```c
void c10x10rgb_display_image ( c10x10rgb_t *ctx, const uint32_t *demo_image );
```
 
- `c10x10rgb_display_byte` This function displays the specified byte.
```c
void c10x10rgb_display_byte ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj );
```

- `c10x10rgb_display_string` This function displays the specified string.
```c
void c10x10rgb_display_string ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj, uint8_t len, uint16_t speed_ms );
```

## Examples Description

> This example showcases how to initialize, configure and use the 10x10 RGB click module. The
click has a 10 by 10 RGB LED matrix which can be programmed to show different colors or even
images. LED elements that form the matrix communicate by a single line with the host MCU. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click board.

```c

void application_init ( void )
{
    c10x10rgb_cfg_t cfg;

    //  Click initialization.
    c10x10rgb_cfg_setup( &cfg, &logic_zero, &logic_one );
    C10X10RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10x10rgb_init( &c10x10rgb, &cfg );

    c10x10rgb_fill_screen( &c10x10rgb, C10X10RGB_COLOR_OFF );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> This function first displays 3 chars { R, G, B }, the string "MIKROE", the company logo and a rainbow in the end. 

```c

void application_task ( void )
{
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 0 ] );
    Delay_ms ( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 1 ] );
    Delay_ms ( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 2 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c10x10rgb_display_string( &c10x10rgb, &scroll_data_obj, scroll_data_len, scroll_speed_ms );
    Delay_ms ( 1000 );
    c10x10rgb_display_image( &c10x10rgb, &MIKROE_IMAGE[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    c10x10rgb_demo_rainbow( &c10x10rgb, rainbow_brightness, rainbow_speed_ms );
    Delay_ms ( 1000 );
} 

``` 

## Note

> Make sure the logic delays are defined for your system in the c10x10rgb_delays.h file.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.10x10RGB

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
