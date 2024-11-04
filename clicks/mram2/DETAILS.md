
---
# MRAM 2 Click

MRAM 2 Click is a compact add-on board for applications that must store and retrieve data and programs quickly using a small number of pins.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mram2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mram-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mram2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mram2 Click driver.

#### Standard key functions :

- `mram2_cfg_setup` Config Object Initialization function.
```c
void mram2_cfg_setup ( mram2_cfg_t *cfg ); 
```

- `mram2_init` Initialization function.
```c
err_t mram2_init ( mram2_t *ctx, mram2_cfg_t *cfg );
```

#### Example key functions :

- `mram2_wren` Write Enable function
```c
void mram2_wren ( mram2_t *ctx );
```

- `mram2_read` Read Data Bytes function
```c
void mram2_read ( mram2_t *ctx, uint32_t mem_adr, uint8_t *rd_data, uint8_t n_bytes );
```

- `mram2_write` Write Data Bytes function
```c
void mram2_write ( mram2_t *ctx, uint32_t mem_adr, uint8_t *wr_data, uint8_t n_bytes );
```

## Examples Description

> This example demonstrates the use of MRAM 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, sets the write protect and disables the hold signal.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram2_cfg_t cfg;

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

    mram2_cfg_setup( &cfg );
    MRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram2_init( &mram2, &cfg );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   MRAM 2 Click     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    mram2_write_protect( &mram2, MRAM2_WP_ENABLE );
    mram2_hold( &mram2, MRAM2_HLD_DISABLE );
    log_printf( &logger, "   Initialized      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Writes "MikroE" into the first 6 memory locations, and then reads it back 
> and displays it to the USB UART approximately every 5 seconds.

```c

void application_task ( void )
{
    mram2_wren( &mram2 );
    log_printf( &logger, "Write enabled!\r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, "Writing \"%s\" to memory...\r\n", val_in );
    mram2_write( &mram2, 0x000000, &val_in[ 0 ], 6 );
    Delay_ms ( 100 );
    mram2_wrdi ( &mram2 );
    log_printf( &logger, "Write disabled!\r\n" );
    Delay_ms ( 100 );
    mram2_read ( &mram2, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read data : %s\r\n", val_out );
    
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mram2

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
