/**
 * @file  : HAL_SIM.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum and function using in HAL_SIM.c.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "MKL46Z4.h"

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _HAL_SIM_H_
#define _HAL_SIM_H_

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* ----------------------------------------------------------------------------
   -- SOPT2 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select clock source for UART0 receiver and transmitter.
 *
 * @param UART0SRC_value (2 bit width) Define each clock source option for UART0.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SOPT2_set_UART0SRC(uint8_t UART0SRC_value);

/**
 * @brief Select the MCGFLLCLK or MCGPLLCLK/2 clock source for various peripheral
 *
 * @param PLLFLLSEL_value (0 = MCGFLLCLK/ 1 = MCGPLLCLK/2).
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SOPT2_set_PLLFLLSEL(uint8_t PLLFLLSEL_value);

/*!
 * @}
 */
/* end of group SOPT2 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- SCGC4 register bit setting function group
   ---------------------------------------------------------------------------- */

void HAL_SIM_SCGC4_set_clock_UART0(uint8_t UART0_gate_value);

/*!
 * @}
 */
/* end of group SCGC4 register bit setting function */

/* ----------------------------------------------------------------------------
   -- SCGC5 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Enable clock source for PORTA
 *
 * @param portA_gate_value is the value we will write to bit PORTA in SCGC5 register.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SCGC5_set_clock_PORTA(uint8_t portA_gate_value);

/**
 * @brief Enable clock source for PORTB
 *
 * @param portB_gate_value is the value we will write to bit PORTA in SCGC5 register.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SCGC5_set_clock_PORTB(uint8_t portB_gate_value);

/**
 * @brief Enable clock source for PORTC
 *
 * @param portC_gate_value is the value we will write to bit PORTA in SCGC5 register.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SCGC5_set_clock_PORTC(uint8_t portC_gate_value);

/**
 * @brief Enable clock source for PORTD
 *
 * @param portD_gate_value is the value we will write to bit PORTA in SCGC5 register.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SCGC5_set_clock_PORTD(uint8_t portD_gate_value);

/**
 * @brief Enable clock source for PORTE
 *
 * @param portE_gate_value is the value we will write to bit PORTA in SCGC5 register.
 *
 * @return: this function return nothing.
 */
void HAL_SIM_SCGC5_set_clock_PORTE(uint8_t portE_gate_value);

/*!
 * @}
 */
/* end of group SCGC5 register bit setting function */

/*Header guard*/
#endif
/*EOF*/