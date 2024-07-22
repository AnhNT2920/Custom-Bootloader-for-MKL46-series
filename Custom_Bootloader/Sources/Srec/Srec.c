/**
 * @file  : Srec.c
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Srec.c.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdlib.h>
#include "../Includes/Srec/Srec.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Static functions prototype
 ******************************************************************************/

/**
 * @brief Convert a hex digit to decimal
 *
 * @param hex_digit: Hex digit to convert to decimal
 *
 * @return decimal value of the hex
 */
static uint8_t convert_hex_to_decimal(uint8_t hex_digit);

/**
 * @brief Get length of a string
 *
 * @param str: string to get length
 *
 * @return length of the string
 */
static uint32_t get_string_length(uint8_t *str);

/**
 * @brief Convert a hex string to decimal
 *
 * @param hex_str: Hex string
 * @param hex_digit_count: Number of hex digit
 *
 * @return Decimal value of hex string
 */
static uint64_t convert_hex_string_to_decimal(uint8_t *hex_str, uint32_t hex_digit_count);

/*******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * @brief Convert a hex digit to decimal
 *
 * @param hex_digit: Hex digit to convert to decimal
 *
 * @return decimal value of the hex
 */
static uint8_t convert_hex_to_decimal(uint8_t hex_digit)
{
    uint32_t ret_val = 0; /*This variable stores the function return value*/

    /*If hex is in range 0 - 9*/
    if (('0' <= hex_digit) && (hex_digit <= '9'))
    {
        ret_val = hex_digit - 48;
    }
    /*If hex is in range A - F*/
    else if (('A' <= hex_digit) && (hex_digit <= 'F'))
    {
        ret_val = hex_digit - 55;
    }
    else
    {
        /*Do nothing*/
    }

    return ret_val;
}

/**
 * @brief Get length of a string
 *
 * @param str: string to get length
 *
 * @return length of the string
 */
static uint32_t get_string_length(uint8_t *str)
{
    uint32_t i = 0; /*i used for traversal the loop*/

    /*Loop until get null character*/
    while ('\0' != str[i])
    {
        /*Increase i*/
        i++;
    }

    return i;
}

/**
 * @brief Convert a hex string to decimal
 *
 * @param hex_str: Hex string
 * @param hex_digit_count: Number of hex digit
 *
 * @return Decimal value of hex string
 */
static uint64_t convert_hex_string_to_decimal(uint8_t *hex_str, uint32_t hex_digit_count)
{
    uint32_t i = 0;            /*i is used for traversaling the loop*/
    uint8_t decimal_value = 0; /*This variable stores decimal value of a hex digit*/
    uint32_t hex_length = 0;   /*This variable stores the length of hex string*/
    uint64_t ret_val = 0;      /*This variable stores function return value*/

    /*Get length of hex string*/
    hex_length = get_string_length(hex_str);

    /*Traversal the hex string*/
    for (i = 0; i < hex_digit_count; i++)
    {
        /*Get deciaml value of each hex digit*/
        decimal_value = convert_hex_to_decimal(hex_str[i]);
        /*Calculate the decimal value*/
        ret_val += decimal_value << (4 * (hex_digit_count - 1 - i));
    }

    return ret_val;
}

/**
 * @brief Check srec line
 *
 * @param record: Struct pointer has infomation about a srec line
 * @param line: Srec record
 *
 * @return 0 if no error, 1 if error
 */
uint8_t check_srec_line(srec_line *record, uint8_t *line)
{
    uint8_t ret_val = 0;        /*This variable stores the function return value*/
    uint8_t record_length = 0;  /*This variable stores length of a raw record*/
    uint8_t check_sum_read = 0; /*This variable stores the check sum read from raw record*/

    /*Get record length from parsed record*/
    record_length = (record->byte_count + 2u) * 2u;
    /*Get check sum from raw record*/
    check_sum_read = convert_hex_string_to_decimal(line + record_length - 2u, 2u);

    /*Check start code*/
    if ('S' != record->start_code)
    {
        ret_val = 1;
    }
    else if (record->type > S9)
    {
        ret_val = 1;
    }
    /*Check check sum value*/
    else if (check_sum_read != record->check_sum)
    {
        ret_val = 1;
    }
    /*Check record length*/
    else if (record_length != get_string_length(line))
    {
        ret_val = 1;
    }
    else
    {
        /*Do nothing*/
    }

    return ret_val;
}

/**
 * @brief Parse a srec record
 *
 * @param record_line: Input srec record
 *
 * @return a parsed record struct
 */
srec_line parse_Srecord_line(uint8_t *record_line)
{
    srec_line record = {0};          /*This struct stores the function return value*/
    uint32_t i = 0;                  /*i is used for traversaling loop*/
    uint32_t data_size = 0;          /*This variable stores length of data field*/
    uint8_t *data_pointer = NULL;    /*This pointer stores address of data field in raw record*/
    uint8_t *address_pointer = NULL; /*This pointer stores address of address field in raw record*/

    /*Get address field pointer*/
    address_pointer = record_line + ADDRESS_FIELD_OFFSET;

    /*Get start code*/
    record.start_code = record_line[START_CODE_OFFSET];
    /*Get record type*/
    record.type = convert_hex_to_decimal(record_line[RECORD_TYPE_OFFSET]);
    /*Get byte count value*/
    record.byte_count = convert_hex_string_to_decimal(record_line + BYTE_COUNT_OFFSET, 2u);

    /*Evaluate record type*/
    switch (record.type)
    {
    /*If record is header record*/
    case S0:
    {
        /*Get data field pointer*/
        data_pointer = record_line + S0_DATA_OFFSET;
        /*Calculate record checksum*/
        record.check_sum = record.byte_count + (record.address >> 8) + (record.address & 0xFF);
        /*Get data field length*/
        data_size = record.byte_count - S0_NOT_DATA_COUNT;
        /*Get data field size in word align to write to flash*/
        record.data_word = data_size / WORD_ALIGN;
        break;
    }
    /*Data record 16 bits address*/
    case S1:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_16BIT_WIDTH);
        /*Get data field pointer*/
        data_pointer = record_line + S1_DATA_OFFSET;
        /*Calculate checksum*/
        record.check_sum = record.byte_count + (record.address >> 8u) + (record.address & 0xFFu);
        /*Get data field length*/
        data_size = record.byte_count - S1_NOT_DATA_COUNT;
        /*Get data field size in word align to write to flash*/
        record.data_word = data_size / WORD_ALIGN;
        break;
    }
    /*Data record with 24 bits address*/
    case S2:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_24BIT_WIDTH);
        /*Calculate record checksum*/
        record.check_sum = record.byte_count + (record.address >> 12u) + (record.address >> 8u) + (record.address & 0xFFu);
        /*Get data field pointer*/
        data_pointer = record_line + S2_DATA_OFFSET;
        /*Get data field length*/
        data_size = record.byte_count - S2_NOT_DATA_COUNT;
        /*Get data field length in word align to write to flash*/
        record.data_word = data_size / WORD_ALIGN;
        break;
    }
    /*Data record with 32 bits address*/
    case S3:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_32BIT_WIDTH);
        /*Calculate record checksum*/
        record.check_sum = record.byte_count + (record.address >> 16u) + (record.address >> 12u) + (record.address >> 8u) + (record.address & 0xFFu);
        /*Get data field pointer*/
        data_pointer = record_line + S3_DATA_OFFSET;
        /*Get data size in byte align*/
        data_size = record.byte_count - S3_NOT_DATA_COUNT;
        /*Get data size in word align to write to flash*/
        record.data_word = data_size / WORD_ALIGN;
        break;
    }
    /*Termination record for S3 series*/
    case S7:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_32BIT_WIDTH);
        /*Calculate record checksum*/
        record.check_sum = record.byte_count + (record.address >> 16u) + (record.address >> 12u) + (record.address >> 8u) + (record.address & 0xFFu);
        /*Get data size in word align*/
        record.data_word = 0;
        /*Get data size in byte align*/
        data_size = 0;
        break;
    }
    /*Termination record for S2 series*/
    case S8:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_24BIT_WIDTH);
        /*Calculate record checksum*/
        record.check_sum = record.byte_count + (record.address >> 12u) + (record.address >> 8u) + (record.address & 0xFFu);
        /*Get data size in word align*/
        record.data_word = 0;
        /*Get data size in byte align*/
        data_size = 0;
        break;
    }
    /*Termination record for S1 series*/
    case S9:
    {
        /*Get address value*/
        record.address = convert_hex_string_to_decimal(address_pointer, ADDRESS_16BIT_WIDTH);
        /*Calculate checksum*/
        record.check_sum = record.byte_count + (record.address >> 8) + (record.address & 0xFF);
        /*Get data size in word align*/
        record.data_word = 0;
        /*Get data size in byte align*/
        data_size = 0;
        break;
    }
    default:
    {
        break;
    }
    }

    /*Parse data of srec record*/
    for (i = 0; i < data_size; i++)
    {
        /*Get decimal value of each 2-hex digits*/
        record.data[i] = convert_hex_string_to_decimal(data_pointer + (i * 2u), 2u);
        /*Get checksum*/
        record.check_sum += record.data[i];
    }
    record.check_sum = ~record.check_sum;

    return record;
}

/*EOF*/
