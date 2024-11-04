/*!
 * @file main.c
 * @brief SE051 Plug n Trust Click example
 *
 * # Description
 * This application is showcasing basic functionality of SE051 Plug&Trust Click board. 
 * It gets identify data from device, selects card manager and applet. 
 * Then checks free memory, reads all objects and deletes not reserved ones. 
 * After that showcases a few of functionality: 
 *      - Generating random data, 
 *      - Creating, reading and deleting binary objects, 
 *      - Creating AES symmetrical key and cipher with it;
 * In the end it is showcasing funcionality in the endless loop.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * At the start it sets comunication interface to I2C and resets the chip, 
 * reads identifying data from device, and then selects card manager and applet. 
 * After that it reads free persistent memory, reads all objects and deletes
 * objects that are not reserved by the Applet. Then it generates 2 byte of
 * random data, and gets the version information from the Applet. That's
 * followed up with creating binary object with 'MikroE' data inside. Then it checks
 * if object is created and reads data back. After that, the object is deleted and
 * it's checked if it still exists. Finally it creates 128AES key (16bytes), encrypts it
 * and then decrypts data with that key, and in the end it deletes that key object.
 *
 * ## Application Task
 * It generates 16bytes of data, writes it in binary object and then reads it back and displays 
 * on the USB UART. Then creates AES key and encrypts that generated data with it, and then decrypts it. 
 * In the end it deletes both AES key object and binary object that's created at the start of the task.
 *
 * @note
 * For more information refer to documents from NXP: AN12413 and UM11225.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "se051plugntrust.h"

// Library and log objects
static se051plugntrust_t se051plugntrust;
static log_t logger;

// Communication objects
static se051plugntrust_apdu_t apdu_data;
static se051plugntrust_frame_data_t frame_data;

// Parsing parameters
#define PARSE_BUF_LEN 0xFF
static uint32_t parse_index = 0;
static uint32_t parse_len = PARSE_BUF_LEN;
static uint8_t parse_data[ PARSE_BUF_LEN ] = { 0 };

/**
 * @brief Reset parse data.
 * @details Clears parse index, buffer and resets @b parse_len.
 * @return Nothing.
 * @note None.
 */
static void reset_parse ( void );

/**
 * @brief Log buffer data to .
 * @details Logs buffer data to UART Terminal
 * @param[in] buf : Buffer to log.
 * @param[in] buf_len : Length of buffer to log.
 * @return Nothing.
 * @note None.
 */
static void log_buf_hex ( uint8_t *buf, uint8_t buf_len );

/**
 * @brief Log status data.
 * @details Log status data from @b apdu_data.
 * @return Nothing.
 * @note None.
 */
static void log_status ( void );

/**
 * @brief Log frame data.
 * @details Logs data from @b frame_data.
 * @return Nothing.
 * @note None.
 */
static void log_rsp_data_default ( void );

/**
 * @brief End APDU session.
 * @details Sends request to end APDU session.
 * @return Nothing.
 * @note None.
 */
static void end_apdu_session ( void );

/**
 * @brief Send request to reset device.
 * @details Sends request to reset device and logs ATR data.
 * @return Nothing.
 * @note None.
 */
static void soft_reset( void );

/**
 * @brief Check presistant free memory.
 * @details Sends request to check presistant free
 * memory from Applet, and logs it.
 * @return Nothing.
 * @note None.
 */
static void check_free_memory ( void );

/**
 * @brief Reads 2 bytes of random data from Applet.
 * @details Sends request to Applet to get 2 bytes of 
 * random data, and logs it.
 * @return Nothing.
 * @note None.
 */
static void get_random ( void );

/**
 * @brief Read Object with UID.
 * @details Checks if Object with UID exists and then
 * reads its data, and logs it.
 * @return Nothing.
 * @note None.
 */
static void read_uid_object ( void );

/**
 * @brief Checks the current version of the Applet.
 * @details Send request to check the current version 
 * of Applet and logs return data.
 * @return Nothing.
 * @note None.
 */
static void get_version ( void );

/**
 * @brief Get identify data from device.
 * @details Sends request to get identification data 
 * from device, and logs data.
 * @return Nothing.
 * @note None.
 */
static void get_data_identify ( void );

/**
 * @brief Create, write, read, and delete binary object.
 * @details Creates and writes data to binary object. 
 * Checks if that object exists. Reads that binary object,
 * and then delets it, and checks if its deleted. 
 * Every step and status will be logged.
 * @return Nothing.
 * @note None.
 */
static void create_check_delete ( void );

/**
 * @brief List of all Applet objects and delete if not reserved.
 * @details Create one random object and then lists all objects
 * and delete ones that are not reserved.
 * @return Nothing.
 * @note None.
 */
static void list_and_delete_objects ( void );

/**
 * @brief Select Applet.
 * @details Select applet and log version info.
 * @return Nothing.
 * @note None.
 */
static void select_applet ( void );

/**
 * @brief Create AES key, Encrypt and Decrypt data, and delete AES key.
 * @details Creates 128AES Symmetrical key. 
 * Encrypts data with it. Decrypt data with that key. 
 * and in the end delete that AES key. Logs every status in the process.
 * @return Nothing.
 * @note None.
 */
static void aes_cipher ( void );

/**
 * @brief Select Card manager.
 * @details Select Card manager without return value request
 * @return Nothing.
 * @note None.
 */
static void select_card_manger ( void );

/**
 * @brief Create 128 AES symmetrical key.
 * @details Create 128 AES symetrical key and sets its value.
 * @param[in] aes_id : Object ID.
 * @param[in] aes_key : AES key value.
 * @return Nothing.
 * @note AES key value because it's 128 key should be 16 bytes of data.
 */
static void create_128_aes_key ( uint32_t aes_id, uint8_t *aes_key );

/**
 * @brief Encrypt or decrypt data with AES key.
 * @details Encrypt or decrypt data with AES key.
 * @param[in] aes_id : Object ID.
 * @param[in] cipher_type : Encrypt or decrypt macro @b[SE051PLUGNTRUST_P2_ENCRYPT_ONESHOT] || @b[SE051PLUGNTRUST_P2_DECRYPT_ONESHOT].
 * @param[in] data_in : Input buffer.
 * @param[out] data_out : Output buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t cipher_data_with_aes_key ( uint32_t aes_id, uint8_t cipher_type, uint8_t *data_in, uint8_t *data_out );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    se051plugntrust_cfg_t se051plugntrust_cfg;  /**< Click config object. */

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
    se051plugntrust_cfg_setup( &se051plugntrust_cfg );
    SE051PLUGNTRUST_MAP_MIKROBUS( se051plugntrust_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == se051plugntrust_init( &se051plugntrust, &se051plugntrust_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    frame_data.apdu = &apdu_data;

    se051plugntrust.interface = SE051PLUGNTRUST_INTERFACE_I2C;
    se051plugntrust_reset( &se051plugntrust );
    if ( SE051PLUGNTRUST_INTERFACE_ISO14443 == se051plugntrust.interface )
    {
        log_info( &logger, " ISO14443 Interface active..." );
        for ( ; ; );
    }
    
    soft_reset( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_data_identify( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_card_manger( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_applet( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    check_free_memory( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    list_and_delete_objects( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_random( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    read_uid_object( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_version(  );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    create_check_delete( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    aes_cipher( );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void ) 
{
    #define DATA_LEN 16
    static uint8_t aes_value[ DATA_LEN ]    = { 0x40, 0x41, 0x42, 0x43,0x44, 0x45, 0x46, 0x47,
                                                0x48, 0x49, 0x4A, 0x4B,0x4C, 0x4D, 0x4E, 0x4F };
    static uint32_t binary_id               = 0xBBBBBBBB;
    static uint32_t aes_id                  = 0xCCCCCCCC;
    uint8_t random_data[ DATA_LEN ]         = { 0 };
    uint8_t read_data[ DATA_LEN ]           = { 0 };
    uint8_t encrypted_data[ DATA_LEN ]      = { 0 };
    uint32_t read_len = DATA_LEN;
    
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_random_numbers( &se051plugntrust, random_data, DATA_LEN ) )
    {
        log_printf( &logger, " > Generated random data: 0x" );
        log_buf_hex( random_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Random" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OBJECT_DOESNT_EXIST == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        log_printf( &logger, " Write random data to binary object...\r\n" );
        if ( SE051PLUGNTRUST_OK != se051plugntrust_write_binary_object( &se051plugntrust, binary_id, 
                                                                        0, DATA_LEN, random_data ) )
        {
            log_error( &logger, " Write Binary" );
        }
        else
        {
            log_info( &logger, " Status OK" );
        }
    }
    else
    {
        log_error( &logger, " Binary object already exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        if ( SE051PLUGNTRUST_OK == se051plugntrust_read_object( &se051plugntrust, binary_id, 0, 0, 
                                                                read_data, &read_len ) )
        {
            log_printf( &logger, " > Read data from binary object: 0x" );
            log_buf_hex( read_data, read_len );
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_error( &logger, " Read binray object" );
        } 
    }
    else
    {
        log_error( &logger, " Binary object doesn't exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Create AES key...\r\n" );
    create_128_aes_key( aes_id, aes_value );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, SE051PLUGNTRUST_P2_ENCRYPT_ONESHOT, 
                                                         read_data, encrypted_data ) )
    {
        log_printf( &logger, " > Encrypted data: 0x" );
        log_buf_hex( encrypted_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Encrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, SE051PLUGNTRUST_P2_DECRYPT_ONESHOT, 
                                                         encrypted_data, read_data ) )
    {
        log_printf( &logger, " > Decrypted data: 0x" );
        log_buf_hex( read_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Decrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Delete Binary and AES object...\r\n" );
    if ( ( SE051PLUGNTRUST_OK != se051plugntrust_delete_object( &se051plugntrust, binary_id ) ) || 
         ( SE051PLUGNTRUST_OK != se051plugntrust_delete_object( &se051plugntrust, aes_id ) ) )
    {
        log_error( &logger, " Deleting objects" );
    }
    log_printf( &logger, "*****************************************************************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void reset_parse ( void )
{
    parse_index = 0;
    parse_len = PARSE_BUF_LEN;
    memset( parse_data, 0, parse_len );
}

static void log_buf_hex ( uint8_t *buf, uint8_t buf_len )
{
    for ( uint8_t i = 0; i < buf_len; i++ )
    {
        log_printf( &logger, "%0.2X", ( uint16_t ) buf[ i ] );
    }
}

static void log_status ( void )
{
    if ( ( ( frame_data.pcb & SE051PLUGNTRUST_PCB_BLOCK_R ) != SE051PLUGNTRUST_PCB_BLOCK_R ) && 
         ( ( frame_data.pcb & SE051PLUGNTRUST_PCB_BLOCK_S ) != SE051PLUGNTRUST_PCB_BLOCK_S ) )
    {
        switch ( frame_data.apdu->status )
        {
            case SE051PLUGNTRUST_SW_NOERROR:
            {
                log_info( &logger, " Status OK" );
                break;
            }
            default:
            {
                log_error( &logger, " Status: 0x%.4X", frame_data.apdu->status );
            }
        }
    }
}

static void log_rsp_data_default ( void )
{
    log_printf( &logger, " >NAD: 0x%0.2X \r\n", ( uint16_t ) frame_data.nad );
    log_printf( &logger, " >PCB: 0x%0.2X \r\n", ( uint16_t ) frame_data.pcb );
    log_printf( &logger, " >LEN: 0x%0.2X \r\n", ( uint16_t ) frame_data.len );
    if ( frame_data.len > 0 )
    {
        log_printf( &logger, " >APDU: 0x" );
    }
    log_buf_hex( frame_data.apdu->payload, frame_data.len );
    if ( frame_data.len > 0 )
    {
        log_printf( &logger, " \r\n" );
    }
    log_printf( &logger, " >CRC: 0x%0.4X \r\n", frame_data.crc16 );
    log_printf( &logger, "************************************************************************\r\n" );
}

static void soft_reset( void )
{       
    log_info( &logger, " Resetting device..." );
    se051plugntrust_atr_t atr_data;
    if ( SE051PLUGNTRUST_OK == se051plugntrust_sw_reset( &se051plugntrust, &atr_data ) )
    {
        log_printf( &logger, " > Protocol version: %d\r\n", ( uint16_t ) atr_data.protocol_version );
        log_printf( &logger, " > Length of Data Link Layer Parameters value: %d\r\n", 
                    ( uint16_t ) atr_data.data_link_layer_parameters_len );
        log_printf( &logger, " > Data Link Layer Parameters: 0x" );
        log_buf_hex( atr_data.data_link_layer_parameters, atr_data.data_link_layer_parameters_len );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Physical Layer ID: %d\r\n", ( uint16_t ) atr_data.physical_layer_id );
        log_printf( &logger, " > Length of Physical Layer Parameters value: %d\r\n", 
                    ( uint16_t ) atr_data.physical_layer_parameters_len );
        log_printf( &logger, " > Physical Layer Parameters: 0x" );
        log_buf_hex( atr_data.physical_layer_parameters, atr_data.physical_layer_parameters_len );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Length of Historical Bytes value: %d\r\n", ( uint16_t ) atr_data.historical_len );
        log_printf( &logger, " > Historical Bytes: 0x" );
        log_buf_hex( atr_data.historical, atr_data.historical_len );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Resetting..." );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void check_free_memory ( void )
{
    log_info( &logger, " Check free memory" );
    uint16_t free_memory = 0;
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_free_memory( &se051plugntrust, 
                                                                SE051PLUGNTRUST_MEM_TRANSIENT_DESELECT, &free_memory ) )
    {
        log_printf( &logger, " > Free Memory: %d\r\n", free_memory );
    }
    else
    {
        log_error( &logger, " Reading Memory" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void get_random ( void )
{
    log_info( &logger, " Get Random" );
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_random_numbers( &se051plugntrust, parse_data, 2 ) )
    {
        log_printf( &logger, " > Random data: 0x" );
        log_buf_hex( parse_data, 2 );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Random" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void read_uid_object ( void )
{
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, 
                                                                                   SE051PLUGNTRUST_APPLET_RES_ID_UNIQUE_ID ) )
    {
        log_info( &logger, " Read object with Unique ID" );
        
        if ( SE051PLUGNTRUST_OK == se051plugntrust_read_object( &se051plugntrust, SE051PLUGNTRUST_APPLET_RES_ID_UNIQUE_ID, 
                                                                0, 0, parse_data, &parse_len ) )
        {
            log_printf( &logger, " > Object data: 0x" );
            log_buf_hex( parse_data, parse_len );
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_error( &logger, " Read object with Unique ID" );
        } 
        log_printf( &logger, "************************************************************************\r\n" );
    }
}

static void get_version ( void )
{
    log_info( &logger, " Get Version" );
    se051plugntrust_version_info_t ver_info;
    if ( SE051PLUGNTRUST_OK == se051plugntrust_get_applet_info( &se051plugntrust, &ver_info ) )
    {
        log_printf( &logger, " > Applet Version = %d.%d.%d\r\n", ( uint16_t ) ver_info.major_version, 
                                                                 ( uint16_t ) ver_info.minor_version, 
                                                                 ( uint16_t ) ver_info.patch_version );
        log_printf( &logger, " > AppletConfig = 0x%0.4X\r\n", ver_info.applet_config );
        log_printf( &logger, " > SecureBox = 0x%0.4X\r\n", ver_info.secure_box );
    }
    else
    {
        log_error( &logger, " Version Info" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void get_data_identify ( void )
{
    // select card
    select_card_manger( );
    end_apdu_session( );
    // get data identify
    typedef struct
    {
        uint8_t tag_value_proprietary_data; // 0xFE Tag value - proprietary data Only present if class byte is 0x80
        uint8_t length_of_following_data; // 0x49 / 0x45 Length of following data Only present if class byte is 0x80
        uint8_t tag_card_identification_data[ 0x02 ]; // 0xDF28 Tag card identification data Only present if class byte is 0x80
        uint8_t length_of_card_identification_data; // 0x46 Length of card identification data Only present if class byte is 0x80
        
        uint8_t tag_configuration_id; // 0x01 Tag configuration ID Identifies the configuration content
        uint8_t length_configuration_id; // 0x0C Length configuration ID
        uint8_t configuration_id[ 0x0C ];  // var Configuration ID
        
        uint8_t tag_patch_id;    // 0x02 Tag patch ID Identifies the patch level
        uint8_t length_patch_id; // 0x08 Length patch ID
        uint8_t patch_id[ 0x08 ];  // var Patch ID
        
        uint8_t tag_platform_build_id1; // 0x03 Tag platform build ID1 Identifies the JCOP platform
        uint8_t length_platform_build_id; // 0x18 Length platform build ID
        uint8_t platform_build_id[ 0x18 ]; // var Platform build ID
        
        uint8_t tag_fips_mode;    // 0x052 Tag FIPS mode FIPS mode active
        uint8_t length_fips_mode; // 0x01 Length FIPS mode
        uint8_t fips_mode; // var FIPS mode 0x00 - FIPS mode not active, 0x01 - FIPS mode active
        
        uint8_t tag_pre_perso_state; // 0x07 Tag pre-perso state Lists pre-perso state
        uint8_t length_pre_perso_state; // 0x01 Length pre-perso state
        // var Bit mask of pre-perso state bit0 = 1 = config module available,
        // bit1 = 1 = transport state is active.
        // Unused bits are set to 0x0.
        uint8_t bit_mask_of_pre_perso_state;

        uint8_t tag_rom_id;    // '08' Tag ROM ID Indentifies the ROM content
        uint8_t length_rom_id; // '08' Length ROM ID Normal ending
        uint8_t rom_id[ 0x08 ]; // var ROM ID
        uint8_t status_word_sw[ 0x02 ]; // 9000h Status Word (SW)
    } identify_rsp_t;
    
    identify_rsp_t identify_rsp = { 0 };
    uint32_t prsp_len = sizeof ( identify_rsp_t );
    log_info( &logger, " Get data identify" );
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.len = 8;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = 0xCA;
    frame_data.apdu->p1 = 0x00;
    frame_data.apdu->p2 = 0xFE;
    frame_data.apdu->payload_len = 0x02;
    frame_data.apdu->rsp_len = 0x00;
    uint8_t df28[ 2 ] = { 0xDF, 0x28 };
    memcpy( frame_data.apdu->payload, df28, 2 );
    se051plugntrust_apdu_transfer( &se051plugntrust, &frame_data );
    if ( frame_data.len == prsp_len )
    {
        memcpy( ( uint8_t * )&identify_rsp, frame_data.apdu->payload, prsp_len );
        log_printf( &logger, " > Tag value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_value_proprietary_data );
        log_printf( &logger, " > Length value: %d\r\n", ( uint16_t ) identify_rsp.length_of_following_data );
        log_printf( &logger, " > Tag Card ID value: 0x" );
        log_buf_hex( identify_rsp.tag_card_identification_data, 2 );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Length of Card ID value: %d\r\n", ( uint16_t ) identify_rsp.length_of_card_identification_data );
        log_printf( &logger, " > Tag of Configuration ID value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_configuration_id );
        log_printf( &logger, " > Length of Configuration ID value: %d\r\n", ( uint16_t ) identify_rsp.length_configuration_id );
        log_printf( &logger, " > Configuration ID: 0x" );
        log_buf_hex( identify_rsp.configuration_id, identify_rsp.length_configuration_id );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Tag of Patch ID value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_patch_id );
        log_printf( &logger, " > Length of Patch ID value: %d\r\n", ( uint16_t ) identify_rsp.length_patch_id );
        log_printf( &logger, " > Patch ID: 0x" );
        log_buf_hex( identify_rsp.patch_id, identify_rsp.length_patch_id );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Tag of Platform Build ID1 value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_platform_build_id1 );
        log_printf( &logger, " > Length of Platform Build ID1 value: %d\r\n", ( uint16_t ) identify_rsp.length_platform_build_id );
        log_printf( &logger, " > Platform Build ID1: 0x" );
        log_buf_hex( identify_rsp.platform_build_id, identify_rsp.length_platform_build_id );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Tag of FIPS Mode value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_fips_mode );
        log_printf( &logger, " > Length of FIPS Mode value: %d\r\n", ( uint16_t ) identify_rsp.length_fips_mode );
        log_printf( &logger, " > FIPS Mode: 0x" );
        log_buf_hex( &identify_rsp.fips_mode, identify_rsp.length_fips_mode );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Tag of Pre-Preso State value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_pre_perso_state );
        log_printf( &logger, " > Length of Pre-Preso State value: %d\r\n", ( uint16_t ) identify_rsp.length_pre_perso_state );
        log_printf( &logger, " > Pre-Preso State: 0x" );
        log_buf_hex( &identify_rsp.bit_mask_of_pre_perso_state, identify_rsp.length_pre_perso_state );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Tag of ROM ID value: 0x%0.2X\r\n", ( uint16_t ) identify_rsp.tag_rom_id );
        log_printf( &logger, " > Length of ROM ID value: %d\r\n", ( uint16_t ) identify_rsp.length_rom_id );
        log_printf( &logger, " > ROM ID: 0x" );
        log_buf_hex( identify_rsp.rom_id, identify_rsp.length_rom_id );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Status Word: 0x" );
        log_buf_hex( identify_rsp.status_word_sw, 2 );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Size Error" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
    end_apdu_session( );
}

static void end_apdu_session ( void )
{
    if ( SE051PLUGNTRUST_OK != se051plugntrust_end_apdu_session( &se051plugntrust ) )
    {
        log_error( &logger, " End APDU session" );
    }
}

static void create_check_delete ( void )
{    
    // create binary object
    log_info( &logger, " Write Binary" );
    uint8_t data_buf[ 7 ] = "MikroE";
    uint32_t binary_id = 0xAAAAAAAAul;

    if ( SE051PLUGNTRUST_OK != se051plugntrust_write_binary_object( &se051plugntrust, binary_id, 0, 6, data_buf ) )
    {
        log_error( &logger, " Write Binary" );
    }
    log_printf( &logger, "************************************************************************\r\n" );

    // check if object exists
    log_info( &logger, " Check object exists" );
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        log_printf( &logger, " > Object exist\r\n" );
    }
    else
    {
        log_printf( &logger, " > Object doesn't exist\r\n" );
    } 
    log_printf( &logger, "************************************************************************\r\n" );
    
    // read binary object
    log_info( &logger, " Read object" );
    reset_parse();
    if ( SE051PLUGNTRUST_OK == se051plugntrust_read_object( &se051plugntrust, binary_id, 0, 0, parse_data, &parse_len ) )
    {
        log_printf( &logger, " > Object data: %s\r\n", parse_data );
    }
    else
    {
        log_error( &logger, " Read binary object" );
    } 
    log_printf( &logger, "************************************************************************\r\n" );
    // delete object
    log_info( &logger, " Delete Secure Object" );
    if ( SE051PLUGNTRUST_OK == se051plugntrust_delete_object( &se051plugntrust, binary_id ) )
    {
        log_printf( &logger, " Object 0x%0.8LX deleted\r\n", binary_id );
    }
    else
    {
        log_error( &logger, " Delete Object"  );
    }
    log_printf( &logger, "************************************************************************\r\n" );
    // check if object exists
    log_info( &logger, " Check object exists" );
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, binary_id ) )
    {
        log_printf( &logger, " > Object exist\r\n" );
    }
    else
    {
        log_printf( &logger, " > Object doesn't exist\r\n" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void list_and_delete_objects( void )
{     
    se051plugntrust_write_binary_object( &se051plugntrust, 0xAABBCCDDul, 0, 4, "Data" );
    
    log_info( &logger, " Get Object list" );  
    uint32_t ids[ 30 ] = { 0 };
    uint8_t len = 0;
    if ( SE051PLUGNTRUST_OK == se051plugntrust_object_id_list( &se051plugntrust, ids, &len ) )
    {
        log_info( &logger, " List len: %d", ( uint16_t )len );
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {   // if not NXP defined objectect delete that object
            if ( ( SE051PLUGNTRUST_OBJID_SE05X_APPLET_RES_START != ( SE051PLUGNTRUST_OBJID_APPLET_MASK & ids[ cnt ] ) ) &&
                 ( SE051PLUGNTRUST_SSS_OBJID_DEMO_AUTH_START != ( SE051PLUGNTRUST_OBJID_APPLET_MASK & ids[ cnt ] ) ) &&
                 ( SE051PLUGNTRUST_SSS_OBJID_IOT_HUB_A_START != ( SE051PLUGNTRUST_OBJID_IOT_MASK & ids[ cnt ] ) ) )
            {
                if ( SE051PLUGNTRUST_OK == se051plugntrust_delete_object( &se051plugntrust, ids[ cnt ] ) )
                {
                    log_printf( &logger, " > Object Deleted 0x%.8LX\r\n", ids[ cnt ] );
                }
                else
                {
                    log_error( &logger, " Delecte Object  0x%.8LX", ids[ cnt ] );
                }
            }
            else
            {
                log_printf( &logger, " > Object ID: 0x%.8LX\r\n", ids[ cnt ] );
            }
        }
    }
    else
    {
        log_error( &logger, " Object ID List" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void select_applet ( void )
{
    log_info( &logger, " Select SE050 Applet" );
    se051plugntrust_version_info_t ver_info;
    se051plugntrust_select_applet( &se051plugntrust, SE051PLUGNTRUST_PCB_BLOCK_I_NS_ENCODE, &ver_info );
    log_printf( &logger, " > Applet Version = %d.%d.%d\r\n", ( uint16_t ) ver_info.major_version, 
                                                             ( uint16_t ) ver_info.minor_version, 
                                                             ( uint16_t ) ver_info.patch_version );
    log_printf( &logger, " > AppletConfig = 0x%0.4X\r\n", ver_info.applet_config );
    log_printf( &logger, " > SecureBox = 0x%0.4X\r\n", ver_info.secure_box );
    log_printf( &logger, "************************************************************************\r\n" );
}

static void aes_cipher ( void )
{
    // Create AES Key
    log_info( &logger, " Write AES Key" );
    #define AES_DATA_SIZE 16
    uint8_t aes_value[ AES_DATA_SIZE ] = { 0x40, 0x41, 0x42, 0x43,0x44, 0x45, 0x46, 0x47,
                                           0x48, 0x49, 0x4A, 0x4B,0x4C, 0x4D, 0x4E, 0x4F };
    uint32_t symm_id = 0x12345678ul;
    create_128_aes_key( symm_id, aes_value );
    
    // Encrypt Data
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, symm_id ) )
    {
        log_info( &logger, " Encrypt Data" );
        uint8_t data_value[ 16 ] = { ' ', '>', 'P', 'l', 'u', 'g', ' ', '&', ' ', 'T', 'r', 'u', 's', 't', '<', ' ' };
        reset_parse( );
        if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( symm_id, SE051PLUGNTRUST_P2_ENCRYPT_ONESHOT, 
                                                             data_value, parse_data ) )
        {
            log_printf( &logger, " > Encrypted data hex: 0x" );
            log_buf_hex( parse_data, AES_DATA_SIZE );
            log_printf( &logger, "\r\n" );
            log_printf( &logger, " > Encrypted data string: %s\r\n", parse_data );
        }
        else
        {
            log_error( &logger, " Parse error" );
        }
    }
    else
    {
        log_printf( &logger, " > Object doesn't exist\r\n" );
    } 
    log_printf( &logger, "************************************************************************\r\n" );

    // Decrypt Data
    log_info( &logger, " Decrypt Data" );
    if ( SE051PLUGNTRUST_OK == cipher_data_with_aes_key( symm_id, SE051PLUGNTRUST_P2_DECRYPT_ONESHOT, 
                                                         parse_data, parse_data ) )
    {
        log_printf( &logger, " > Decrypted data hex: 0x" );
        log_buf_hex( parse_data, parse_len );
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " > Decrypted data string: %s\r\n", parse_data );
    }
    else
    {
        log_error( &logger, " Parse error" );
    }
    log_printf( &logger, "************************************************************************\r\n" );
    
    // Delete Object
    log_info( &logger, " Delete Secure Object" );
    if ( SE051PLUGNTRUST_OK == se051plugntrust_delete_object( &se051plugntrust, symm_id ) )
    {
        log_printf( &logger, " Object 0x%0.8LX deleted\r\n", symm_id );
    }
    else
    {
        log_error( &logger, " Delete Object"  );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void select_card_manger ( void )
{
    log_info( &logger, " Select the card manager " );
    if ( SE051PLUGNTRUST_OK != se051plugntrust_select_card_manager( &se051plugntrust, 
                                                                    SE051PLUGNTRUST_CARD_MANAGER_WITHOUT_RSP, 0, 0 ) )
    {
        log_error( &logger, " Card manager"  );
    }
    log_printf( &logger, "************************************************************************\r\n" );
}

static void create_128_aes_key ( uint32_t aes_id, uint8_t *aes_key )
{
    #define AES_KEY_SIZE 16
    frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
    frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
    frame_data.apdu->ins = SE051PLUGNTRUST_INS_WRITE | SE051PLUGNTRUST_INS_TRANSIENT;
    frame_data.apdu->p1 = SE051PLUGNTRUST_P1_AES;
    frame_data.apdu->p2 = SE051PLUGNTRUST_P2_DEFAULT;
    frame_data.apdu->payload_len = 0;// reset apdu payload_len
    frame_data.apdu->rsp_len = 0;// reset apdu le value
    se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                 SE051PLUGNTRUST_TLV_TAG_1, aes_id ); // AES key ID
    se051plugntrust_set_tlv_u8buf( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                   SE051PLUGNTRUST_TLV_TAG_3, aes_key, AES_KEY_SIZE ); // AES key value
    frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu ); // calculate apdu size
    se051plugntrust_apdu_transfer( &se051plugntrust, &frame_data );
    log_status( );
    end_apdu_session( );
}

static err_t cipher_data_with_aes_key ( uint32_t aes_id, uint8_t cipher_type, uint8_t *data_in, uint8_t *data_out )
{
    // check if object with aes_id exists
    if ( SE051PLUGNTRUST_OBJECT_DOES_EXISTS == se051plugntrust_check_object_exist( &se051plugntrust, aes_id ) )
    {
        frame_data.pcb = SE051PLUGNTRUST_PCB_BLOCK_I;
        frame_data.apdu->cla = SE051PLUGNTRUST_CLA_NOT_SECURE;
        frame_data.apdu->ins = SE051PLUGNTRUST_INS_CRYPTO;
        frame_data.apdu->p1 = SE051PLUGNTRUST_P1_CIPHER;
        frame_data.apdu->p2 = cipher_type; // SE051PLUGNTRUST_P2_ENCRYPT_ONESHOT || SE051PLUGNTRUST_P2_DECRYPT_ONESHOT
        frame_data.apdu->payload_len = 0;
        frame_data.apdu->rsp_len = 0;
        frame_data.len = 0;
        se051plugntrust_set_tlv_u32( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                     SE051PLUGNTRUST_TLV_TAG_1, aes_id ); // set aes key to be used
        se051plugntrust_set_tlv_u8( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                    SE051PLUGNTRUST_TLV_TAG_2, SE051PLUGNTRUST_CIPHER_AES_CTR ); // set ae cipher type to be used
        se051plugntrust_set_tlv_u8buf( frame_data.apdu->payload, &frame_data.apdu->payload_len, 
                                       SE051PLUGNTRUST_TLV_TAG_3, data_in, 16 ); // set data to encrypt/decrypt
        frame_data.len = se051plugntrust_calculate_apdu_size( frame_data.apdu ); // calculate apdu data
        frame_data.len++; // increment data
        se051plugntrust_apdu_transfer( &se051plugntrust, &frame_data );
        reset_parse( ); // reset prase data
        // get encryted/decrypted data
        if ( SE051PLUGNTRUST_OK == se051plugntrust_get_tlv_u8buf( frame_data.apdu->payload, &parse_index, frame_data.len, 
                                                                  SE051PLUGNTRUST_TLV_TAG_1, data_out, &parse_len ) ) 
        {
            end_apdu_session( );
            return SE051PLUGNTRUST_OK;
        }
        else
        {
            end_apdu_session( );
            return SE051PLUGNTRUST_ERROR;
        }
    }
    else
    {
        return SE051PLUGNTRUST_ERROR;
    }
}

// ------------------------------------------------------------------------ END
