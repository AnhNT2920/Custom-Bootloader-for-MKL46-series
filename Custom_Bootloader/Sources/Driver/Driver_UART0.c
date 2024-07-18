/**
 * @file  : Driver_UART0.c
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

#include "../Includes/Driver/Driver_UART0.h"
#include "../Includes/Driver/Driver_PORT.h"
#include "../Includes/HAL/HAL_UART0.h"
#include "../Includes/Driver/Driver_SIM.h"
#include "../Includes/Queue/Queque.h"
#include "MKL46Z4.h"
#include <stdlib.h>

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*This queue stores the srec line*/
static srec_queue queue;

/*This variable stores the current position in Rx_buffer*/
static volatile uint16_t Rx_buff_index = 0;

/*This variable stores the byte received from UART0*/
static volatile uint8_t received_byte;

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: UART0_IRQHandler
* Description: UART0 interrupt handler for transmit and receive data
*
END***************************************************************************/

void UART0_IRQHandler(void)
{
    /*If receiver send interrupt request*/
    if (HAL_UART0_S1_read_RDRF())
    {
        /*Get the data byte*/
        received_byte = HAL_UART0_D_read_data();

        /*Check the received data*/
        if (('\r' != received_byte) && ('\n' != received_byte) && ('\0' != received_byte))
        {
            // /*Add the received data to Rx_buffer*/
            queue.record[queue.end][Rx_buff_index++] = received_byte;
        }
        /*If received data is NULL character*/
        else if (received_byte == '\n')
        {
            // /*Asign the current position in Rx buffer with NULL character*/
            queue.record[queue.end][Rx_buff_index] = '\0';
            // /*Set Rx_buff_flag to 1 to indicate that the UART0 has finished receving a string*/
            /*Reset the Rx_buffer index to ready for receving other string*/
            Rx_buff_index = 0;
            queue.queue_state[queue.end] = 1;
            Queue_Enqueue(&queue);
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_init
* Description: Init the UART0 module
*
END***************************************************************************/
void Driver_UART0_init(uart0_config_info *uart0_config, uint32_t clock_frequency)
{
    /*Check input*/
    if ((NULL != uart0_config) && (0 != clock_frequency))
    {
        /*Enable clock gate for UART0*/
        Driver_SIM_SCGC4_set_UART0_clock_gate(ENABLED);

        /*Enable clock gate for Rx and Tx port*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(uart0_config->Tx_Rx_port, ENABLED);
        /*Set the MUX-UART0 for Rx pin*/
        Driver_PORT_set_MUX_pin(uart0_config->Tx_Rx_port, uart0_config->Rx_pin, MUX_ALTERNATIVE2);
        /*Set the MUX-UART0 for Tx pin*/
        Driver_PORT_set_MUX_pin(uart0_config->Tx_Rx_port, uart0_config->Tx_pin, MUX_ALTERNATIVE2);

        /*Disable UART0 Receiver for any configuration*/
        Driver_UART0_select_Rx_state(RECEIVER_DISABLED);
        /*Disable UART0 Transmitter for any configuration*/
        Driver_UART0_select_Tx_state(TRANSMITTER_DISABLED);

        /*Update the baud divisor of the UART0*/
        Driver_UART0_update_Baud_div(uart0_config->baud_rate, uart0_config->OSR, clock_frequency);
        /*Set the stop bit count*/
        Driver_UART0_select_Stop_bit_number(uart0_config->stop_bit_count);
        /*Update the oversampling ratio*/
        Driver_UART0_update_Over_sampling_ratio(uart0_config->OSR);
        /*Select the length of data whether is 8 bits or 9 bits*/
        Driver_UART0_select_data_length(uart0_config->data_mode);
        /*Select the UART0 parity state whether is enabled is disabled*/
        Driver_UART0_select_parity_state(uart0_config->parity_state);
        /*Set the UART0 receiver state*/
        Driver_UART0_select_Rx_state(uart0_config->receiver_state);
        /*Set the UART0 transmitter state*/
        Driver_UART0_select_Tx_state(uart0_config->transmitter_state);
        /*Set the UART0 receiver interrupt request state*/
        Driver_UART0_select_Rx_IRQ_state(uart0_config->receiver_IRQ);
        /*Set the UART0 transmitter interrupt request to be disabled to prevent always jump to IRQ handler*/
        Driver_UART0_select_Tx_IRQ_state(TRANSMIT_IRQ_DISABLED);
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_data_length
* Description: Select the length of data for UART0
*
END***************************************************************************/
void Driver_UART0_select_data_length(uart0_data_mod_enum_t data_length)
{
    /*Check input*/
    if ((DATA_8BITS <= data_length) && (data_length <= DATA_9BITS))
    {
        /*Set the data length for UART0 is whether 8 bits length or 9 bits length*/
        HAL_UART0_C1_set_M((uint8_t)data_length);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_Stop_bit_number
* Description: Select the stop bit count for UART0
*
END***************************************************************************/
void Driver_UART0_select_Stop_bit_number(uart0_stop_bit_number_enum_t stop_bit_count)
{
    /*Check input*/
    if (stop_bit_count <= TWO_STOP_BIT)
    {
        /*Set stop bit count for UART0*/
        HAL_UART0_BDH_set_SBNS((uint8_t)stop_bit_count);
    }
    /*Any invalid input will be ignored, the bit field hold it previous vvalue*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_parity_state
* Description: Select whether using parity bit or disabled parity bit
*
END***************************************************************************/
void Driver_UART0_select_parity_state(uart0_parity_state_enum_t parity_state)
{
    /*Check input*/
    if ((PARITY_DISABLED <= parity_state) && (parity_state <= PARITY_ENABLED))
    {
        /*Set the parity state is whether enabled or disabled*/
        HAL_UART0_C1_set_PE((uint8_t)parity_state);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_parity_type
* Description: Select the type of parity checking (Odd / Even parity)
*
END***************************************************************************/
void Driver_UART0_select_parity_type(uart0_parity_type_enum_t parity_type)
{
    /*Check input*/
    if ((EVEN_PARITY <= parity_type) && (parity_type <= ODD_PARITY))
    {
        /*Select parity type is whether Odd parity or Even parity checking*/
        HAL_UART0_C1_set_PT((uint8_t)parity_type);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_Tx_state
* Description: Select whether the Transmitter is enabled or disabled
*
END***************************************************************************/
void Driver_UART0_select_Tx_state(uart0_Tx_state_enum_t Tx_state)
{
    /*Check input*/
    if ((TRANSMITTER_DISABLED <= Tx_state) && (Tx_state <= TRANSMITTER_ENABLED))
    {
        /*Set the Transmitter state is whether enabled or disabled*/
        HAL_UART0_C2_set_TE((uint8_t)Tx_state);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_Rx_state
* Description: Select whether the Receiver is enabled or disabled
*
END***************************************************************************/
void Driver_UART0_select_Rx_state(uart0_Rx_state_enum_t Rx_state)
{
    /*Check input*/
    if ((RECEIVER_DISABLED <= Rx_state) && (Rx_state <= RECEIVER_ENABLED))
    {
        /*Set the Receiver state is whether enabled or disabled*/
        HAL_UART0_C2_set_RE((uint8_t)Rx_state);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_Tx_IRQ_state
* Description: Select whether the Transmitter interrupt request is enabled or
*              disabled.
*
END***************************************************************************/
void Driver_UART0_select_Tx_IRQ_state(uart0_Tx_irq_enum_t Tx_irq_state)
{
    /*Check input*/
    if ((TRANSMIT_IRQ_DISABLED <= Tx_irq_state) && (Tx_irq_state <= TRANSMIT_IRQ_ENABLED))
    {
        /*Set the Transmitter interrupt request state is whether enabled or disabled*/
        HAL_UART0_C2_set_TIE((uint8_t)Tx_irq_state);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_select_Rx_IRQ_state
* Description: Select whether the Receiver interrupt request is enabled or
*              disabled.
*
END***************************************************************************/
void Driver_UART0_select_Rx_IRQ_state(uart0_Rx_irq_enum_t Rx_irq_state)
{
    /*Check input*/
    if ((RECEIVE_IRQ_DISABLED <= Rx_irq_state) && (Rx_irq_state <= RECEIVE_IRQ_ENABLED))
    {
        /*Set the Receiver interrupt request state is whether enabled or disabled*/
        HAL_UART0_C2_set_RIE((uint8_t)Rx_irq_state);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_update_Baud_div
* Description: Set baud rate modulo divisor for UART0
*
END***************************************************************************/
void Driver_UART0_update_Baud_div(uint32_t baud_rate, uint8_t OSR, uint32_t clock_value)
{
    uint16_t baud_div = 0; /*This variable stores the baud rate divisor value*/

    /*Get the baud rate divisor*/
    baud_div = clock_value / (baud_rate * OSR);

    /*Set baud rate modulo divisor for the baud rate high register(high 5 bits)*/
    HAL_UART0_BDH_set_SBR(baud_div);
    /*Set baud rate modulo divisor for the baud rate low register(low 8 bits)*/
    HAL_UART0_BDL_set_SBR(baud_div);

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_update_Over_sampling_ratio
* Description: Set Oversampling ratio for UART0
*
END***************************************************************************/
void Driver_UART0_update_Over_sampling_ratio(uint8_t OSR)
{
    /*Check input*/
    if ((4 <= OSR) && (OSR <= 32))
    {
        /*Set over sampling ratio for UART0*/
        HAL_UART0_C4_set_OSR(OSR);
    }
    /*Any invalid write will be ignored, the bit field hold it previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_read_Tx_buffer_flag
* Description: Read the transmit data ready flag
*
END***************************************************************************/
uint8_t Driver_UART0_Is_transmit_ready(void)
{
    /*Read the transmit data empty flag*/
    return HAL_UART0_S1_read_TDRE();
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_read_Rx_buffer_flag
* Description: Read the receive data ready flag
*
END***************************************************************************/
uint8_t Driver_UART0_Is_read_data_ready(void)
{
    /*Read the receive data register full flag*/
    return HAL_UART0_S1_read_RDRF();
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_receive_data_byte
* Description: Receive a byte data from UART
*
END***************************************************************************/
uint8_t Driver_UART0_receive_data_byte(void)
{
    /*Read the data register*/
    return HAL_UART0_D_read_data();
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_send_data_byte
* Description: Send the a data byte by UART.
*
END***************************************************************************/
void Driver_UART0_send_data_byte(uint8_t byte_data)
{
    while (!Driver_UART0_Is_transmit_ready())
    {
        /*Wait for the transmit register is ready*/
    }
    /*Write data to the data register*/
    HAL_UART0_D_write_data(byte_data);

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_enable_interrupt_handler
* Description: Enable the UART0 interrupt handler
*
END***************************************************************************/
void Driver_UART0_enable_interrupt_handler(void)
{
    /*Enable the UART0 interrupt handler*/
    NVIC_EnableIRQ(UART0_IRQn);

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_disable_interrupt_handler
* Description: Disable the UART0 interrupt handler
*
END***************************************************************************/
void Driver_UART0_disable_interrupt_handler(void)
{
    /*Disable the UART0 interrupt handler*/
    NVIC_DisableIRQ(UART0_IRQn);

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_send_string
* Description: Send a string by UART0
*
END***************************************************************************/
void Driver_UART0_send_string(uint8_t *str)
{
    uint32_t i = 0; /*This variable is used for traversal the array*/

    while (str[i] != '\0')
    {
        Driver_UART0_send_data_byte(str[i++]);
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_check_Rx_buffer
* Description: Return a flag that indicate if finished received a string by UART0
*
END***************************************************************************/
uint8_t Driver_UART0_check_Rx_buffer(void)
{
    /*Return a flag that indicate if finished received a string by UART0*/
    return queue.queue_state[queue.first];
}

/*Functions*********************************************************************
*
* Function name: Driver_UART0_receive_string
* Description: Get the string in Rx_buffer
*
END***************************************************************************/
void Driver_UART0_receive_string(uint8_t *str)
{
    uint8_t i = 0; /*This variable is used to traversal the array*/

    /*Loop until meet the NULL character*/
    while ('\0' != queue.record[queue.first][i])
    {
        /*Copy Rx buffer element to str*/
        str[i] = queue.record[queue.first][i];
        /*Increase index*/
        i++;
    }
    /*Add NULL character to the string to indicate the string has finished*/
    str[i] = '\0';

    return;
}

void Driver_UART0_dequeue(void)
{
    queue.queue_state[queue.first] = 0;
    Queue_Dequeue(&queue);
    return;
}

/*EOF*/
