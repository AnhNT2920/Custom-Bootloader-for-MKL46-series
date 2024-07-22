/**
 * @file  : Driver_UART0.h
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file Driver_UART0.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdint.h>
#include "../Includes/Driver/Driver_common.h"

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _DRIVER_UART0_H_
#define _DRIVER_UART0_H_

/*******************************************************************************
 * Macro
 ******************************************************************************/

/**
 * @brief Reference of a string buffer size.
 */
#define BUFFER_SIZE (256u)

/*******************************************************************************
 * Enum
 ******************************************************************************/

/**
 * @brief Reference of data length in UART0
 */
typedef enum uart0_mode
{
    DATA_8BITS, /*Data has 8 bits in length*/
    DATA_9BITS, /*Data has 9 bits in length*/
} uart0_data_mod_enum_t;

/**
 * @brief Reference of stop bit number
 */
typedef enum stopbit_number
{
    ONE_STOP_BIT = 0u, /*Stop bit number is 1*/
    TWO_STOP_BIT = 1u, /*Stop bit number is 2*/
} uart0_stop_bit_number_enum_t;

/**
 * @brief Reference of parity check state
 */
typedef enum PE_state
{
    PARITY_DISABLED = 0u, /*Parity is disabled*/
    PARITY_ENABLED = 1u,  /*Parity is enabled*/
} uart0_parity_state_enum_t;

/**
 * @brief Reference of parity type
 */
typedef enum PT_type
{
    EVEN_PARITY = 0u, /*Even parity*/
    ODD_PARITY = 1u,  /*Odd parity*/
} uart0_parity_type_enum_t;

/**
 * @brief Reference of transmit interrupt request state
 */
typedef enum TIE_type
{
    TRANSMIT_IRQ_DISABLED = 0u, /*Transmit interrupt request disabled*/
    TRANSMIT_IRQ_ENABLED = 1u,  /*Transmit interrupt request enabled*/
} uart0_Tx_irq_enum_t;

/**
 * @brief Reference of receive interrupt request state
 */
typedef enum RIE_type
{
    RECEIVE_IRQ_DISABLED = 0u, /*Receive interrupt request disabled*/
    RECEIVE_IRQ_ENABLED = 1u,  /*Receive interrupt request enabled*/
} uart0_Rx_irq_enum_t;

/**
 * @brief Reference of Transmitter state
 */
typedef enum TE_type
{
    TRANSMITTER_DISABLED = 0u, /*Transmitter is disabled*/
    TRANSMITTER_ENABLED = 1u,  /*Transmitter is enabled*/
} uart0_Tx_state_enum_t;

/**
 * @brief Reference of Receiver state
 */
typedef enum RE_type
{
    RECEIVER_DISABLED = 0u, /*Receiver is disabled*/
    RECEIVER_ENABLED = 1u,  /*Receiver is enabled*/
} uart0_Rx_state_enum_t;

/**
 * @brief Reference of transmit data register emtpty flag
 */
typedef enum TDRE_type
{
    TRANSMIT_BUFFER_FULL = 0u,  /*TDRE is clear*/
    TRANSMIT_BUFFER_EMPTY = 1u, /*TDRE is set*/
} uart0_Tx_buffer_state_enum_t;

/**
 * @brief Reference of receive data register emtpty flag
 */
typedef enum RDRF_type
{
    RECEIVE_BUFFER_EMPTY = 0u, /*RDRF is clear*/
    RECEIVE_BUFFER_FULL = 1u,  /*RDRF is set*/
} uart0_Rx_buffer_state_enum_t;

/*******************************************************************************
 * Struct
 ******************************************************************************/

/**
 * @brief Contain the information about the UART0 configuration.
 */
typedef struct uart0_config
{
    uint32_t baud_rate;                          /*UART0 baud rate*/
    uart0_data_mod_enum_t data_mode;             /*Data length*/
    uart0_parity_state_enum_t parity_state;      /*Parity state*/
    uart0_parity_type_enum_t parity_type;        /*Type of parity*/
    uart0_stop_bit_number_enum_t stop_bit_count; /*Stop bit number*/
    uart0_Tx_irq_enum_t transmiter_IRQ;          /*Transmitter interrupt request state*/
    uart0_Rx_irq_enum_t receiver_IRQ;            /*Receiver interrupt request state*/
    uart0_Tx_state_enum_t transmitter_state;     /*Transmitter state*/
    uart0_Rx_state_enum_t receiver_state;        /*Receiver state*/
    Port_type_enum_t Tx_Rx_port;                 /*Receiver and Transmitter port*/
    uint8_t Tx_pin;                              /*Transmitter pin*/
    uint8_t Rx_pin;                              /*Receiver pin*/
    uint8_t OSR;                                 /*Oversampling ratio*/
} uart0_config_info;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Init the UART0
 *
 * @param uart0_config is a struct pointer that has the information about UART0 configuration
 * @param clock_frequency is the frequency of the UART0 source clock
 *
 * @return: This function return nothing.
 */
void Driver_UART0_init(uart0_config_info *uart0_config, uint32_t clock_frequency);

/**
 * @brief Select the length of data to receive and send by UART0
 *
 * @param data_length is the data length option for UART0
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_data_length(uart0_data_mod_enum_t data_length);

/**
 * @brief Select the stop bit number for UART0
 *
 * @param stop_bit_count is the stop bit number for UART0
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_Stop_bit_number(uart0_stop_bit_number_enum_t stop_bit_count);

/**
 * @brief Select the stop bit number for UART0
 *
 * @param stop_bit_count is the stop bit number for UART0
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_parity_state(uart0_parity_state_enum_t parity_state);

/**
 * @brief Select the parity check state UART0
 *
 * @param parity_state is the parity check state for UART0
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_parity_type(uart0_parity_type_enum_t parity_type);

/**
 * @brief Select the Transmitter state
 *
 * @param Tx_state is the transmitter state
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_Tx_state(uart0_Tx_state_enum_t Tx_state);

/**
 * @brief Select the Receiver state
 *
 * @param Rx_state is the receiver state
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_Rx_state(uart0_Rx_state_enum_t Rx_state);

/**
 * @brief Select transmitter interrupt request state
 *
 * @param Tx_irq_state is the transmitter interrupt request state option
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_Tx_IRQ_state(uart0_Tx_irq_enum_t Tx_irq_state);

/**
 * @brief Select receiver interrupt request state
 *
 * @param Rx_irq_state is the receiver interrupt request state option
 *
 * @return: This function return nothing.
 */
void Driver_UART0_select_Rx_IRQ_state(uart0_Rx_irq_enum_t Rx_irq_state);

/**
 * @brief Update the baud rate modulo divisor
 *
 * @param baud_rate is the baud rate value
 * @param OSR is the oversampling ratio value
 * @param clock_value is the frequency of the UART0 source clock
 *
 * @return: This function return nothing.
 */
void Driver_UART0_update_Baud_div(uint32_t baud_rate, uint8_t OSR, uint32_t clock_value);

/**
 * @brief Update oversampling ratio for UART0
 *
 * @param OSR is the oversampling ratio value
 *
 * @return: This function return nothing.
 */
void Driver_UART0_update_Over_sampling_ratio(uint8_t OSR);

/**
 * @brief Get the status of the trasmit ready state
 *
 * @param: This function has no parameter
 *
 * @return 0 (Not ready to transmit data) or 1 (Ready to transmit data)
 */
uint8_t Driver_UART0_Is_transmit_ready(void);

/**
 * @brief Get the status of the receive ready state
 *
 * @param: This function has no parameter
 *
 * @return 0 (Not ready to read received data) or 1 (Ready to read received data)
 */
uint8_t Driver_UART0_Is_read_data_ready(void);

/**
 * @brief Get a received data byte from UART0
 *
 * @param: This function has no parameter
 *
 * @return the received data byte value
 */
uint8_t Driver_UART0_receive_data_byte(void);

/**
 * @brief Send a data byte by UART0
 *
 * @param byte_data is the data value to send
 *
 * @return: This function return nothing
 */
void Driver_UART0_send_data_byte(uint8_t byte_data);

/**
 * @brief Enable the UART0 interrupt handler
 *
 * @param: This function has no parameter
 *
 * @return: This function return nothing
 */
void Driver_UART0_enable_interrupt_handler(void);

/**
 * @brief Disable the UART0 interrupt handler
 *
 * @param: This function has no parameter
 *
 * @return: This function return nothing
 */
void Driver_UART0_disable_interrupt_handler(void);

/**
 * @brief Send a string by UART0
 *
 * @param str is a string to be sent
 *
 * @return: This function return nothing
 */
void Driver_UART0_send_string(uint8_t *str);

/**
 * @brief Check if the first element in queue is ready to read
 *
 * @param: This fucntion has no parameter
 *
 * @return 0 if not ready, 1 if ready
 */
uint8_t Driver_UART0_check_first_buffer(void);

/**
 * @brief Get string in the Rx buffer
 *
 * @param str is the array to store the string get from Rx buffer
 *
 * @return: This function return nothing
 */
void Driver_UART0_receive_string(uint8_t *str);

/**
 * @brief Pop the S-rec queue
 *
 * @param: This function has no param
 *
 * @return: This function return nothing
 */
void Driver_UART0_dequeue(void);

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
