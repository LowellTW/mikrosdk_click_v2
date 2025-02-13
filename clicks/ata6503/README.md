
---
# ATA6503 Click

> [ATA6503 Click](https://www.mikroe.com/?pid_product=MIKROE-6462) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6462&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an ATA6503 Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ATA6503

### Example Key Functions

- `ata6503_cfg_setup` Config Object Initialization function.
```c
void ata6503_cfg_setup ( ata6503_cfg_t *cfg );
```

- `ata6503_init` Initialization function.
```c
err_t ata6503_init ( ata6503_t *ctx, ata6503_cfg_t *cfg );
```

- `ata6503_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ata6503_generic_write ( ata6503_t *ctx, uint8_t *data_in, uint16_t len );
```

- `ata6503_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ata6503_generic_read ( ata6503_t *ctx, uint8_t *data_out, uint16_t len );
```

- `ata6503_set_en_pin` This function sets the EN pin logic state.
```c
void ata6503_set_en_pin ( ata6503_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ata6503_cfg_t ata6503_cfg;  /**< Click config object. */

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
    ata6503_cfg_setup( &ata6503_cfg );
    ATA6503_MAP_MIKROBUS( ata6503_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ata6503_init( &ata6503, &ata6503_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired message every 3 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ata6503_generic_write( &ata6503, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    if ( ATA6503_OK == ata6503_process( &ata6503 ) ) 
    {
        ata6503_log_app_buf ( );
        ata6503_clear_app_buf ( );
    }
#endif
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
