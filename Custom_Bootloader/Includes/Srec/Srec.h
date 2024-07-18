/**
 * @file  : Srec.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Srec.c.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _SREC_H_
#define _SREC_H_

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * Macro
 ******************************************************************************/

/*\Start position of address, start code, record type and byte count*/
#define ADDRESS_FIELD_OFFSET    (4u)
#define START_CODE_OFFSET       (0u)
#define RECORD_TYPE_OFFSET      (1u)
#define BYTE_COUNT_OFFSET       (2u)

/*\Start position of data field in header and each data record type*/
#define S0_DATA_OFFSET          (8u)
#define S1_DATA_OFFSET          (8u)
#define S2_DATA_OFFSET          (10u)
#define S3_DATA_OFFSET          (12u)

/*\Address field width in byte*/
#define ADDRESS_16BIT_WIDTH     (4u)
#define ADDRESS_24BIT_WIDTH     (6u)
#define ADDRESS_32BIT_WIDTH     (8u)

/*\Number of bytes that are not data*/
#define S0_NOT_DATA_COUNT       (3u)
#define S1_NOT_DATA_COUNT       (3u)
#define S2_NOT_DATA_COUNT       (4u)
#define S3_NOT_DATA_COUNT       (5u)

/*\Size of a word in byte*/
#define WORD_ALIGN              (4u)

/*******************************************************************************
 * Enum
 ******************************************************************************/

/**
 * @brief Reference of srec record type
 */
typedef enum srec_record_type
{
    S0 = 0u, /*Header record*/
    S1 = 1U, /*Data record with 16-bit address*/
    S2 = 2U, /*Data record with 24-bit address*/
    S3 = 3U, /*Data record with 32-bit address*/
    S4 = 4U, /*Reserved record*/
    S5 = 5U, /*Count record with 16-bit count*/
    S6 = 6U, /*Count record with 24-bit count*/
    S7 = 7U, /*Start address(Termination) to terminate S3 series*/
    S8 = 8U, /*Start address(Termination) to terminate S2 series*/
    S9 = 9U  /*Start address(Termination) to terminate S1 series*/
} srec_record_type;

/*******************************************************************************
 * Struct
 ******************************************************************************/

/**
 * @brief Reference of parsed record information
 */
typedef struct srec_line
{
    uint8_t start_code; /*Start code*/
    uint8_t type;       /*Record type*/
    uint8_t byte_count; /*Record byte count*/
    uint32_t address;   /*Record address*/
    uint8_t data[255];  /*Record data*/
    uint8_t check_sum;  /*Record check sum*/
    uint8_t data_word;  /*Size of record data in word align*/
} srec_line;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Check srec line
 *
 * @param record: Struct pointer has infomation about a srec line
 * @param line: Srec record
 *
 * @return 0 if no error, 1 if error
 */
uint8_t check_srec_line(srec_line *record, uint8_t *line);

/**
 * @brief Parse a srec record
 *
 * @param record_line: Input srec record
 *
 * @return a parsed record struct
 */
srec_line parse_Srecord_line(uint8_t *record_line);

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif

/*EOF*/
