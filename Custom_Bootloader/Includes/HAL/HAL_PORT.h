/**
 * @file  : HAL_PORT.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum and function using in HAL_PORT.c.
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

#ifndef _HAL_PORT_H_
#define _HAL_PORT_H_

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief set MUX field for the destinated pin.
 *
 * @param port_selected is the port we're working on(PORT A, PORT B...).
 * @param pin is the pin we want to set MUX.
 *
 * @return: this function return nothing.
 */
void HAL_PORT_PCR_set_MUX_pin(PORT_Type *port_selected, uint8_t pin, uint8_t MUX_value);

/**
 * @brief Select pull resistor for a pin.
 *
 * @param port_selected is the port we're working on(PORT A, PORT B...).
 * @param pin is the pin we want to set to GPIO pin.
 * @param pull_select is the type of Pull we want to set.
 *
 * @return: this function return nothing.
 *
 * Select pull-up or pull-down for a pin.
 */
void HAL_PORT_PCR_set_Pull_pin(PORT_Type *port_select, uint8_t pin, uint8_t pull_type);

#endif
/*EOF*/
