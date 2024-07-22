/**
 * @file  : HAL_GPIO.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum and function using in HAL_GPIO.c.
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

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Select the direction for a GPIO pin.
 *
 * @param port is the GPIO register of the GPIO pin we want to set.
 * @param pin is the pin we want to set to GPIO pin.
 * @param logic has the value of 0 or 1.
 *
 * @return: this function return nothing.
 *
 * Select if the pin is the input GPIO pin or ouput GPIO pin.
 */
void HAL_GPIO_set_direct_PIN(GPIO_Type *port, int8_t pin, uint8_t logic);

/**
 * @brief Write a logic level to a GPIO pin.
 *
 * @param port is the GPIO register of the GPIO pin we want to set.
 * @param pin is the pin we want to set to GPIO pin.
 * @param logic has the value of 0 or 1.
 *
 * @return: this function return nothing.
 */
void HAL_GPIO_write_PIN(GPIO_Type *GPIO, uint8_t pin, uint8_t logic);

/**
 * @brief Read the state of a GPIO pin.
 *
 * @param port is the GPIO register of the GPIO pin we want to set.
 * @param pin is the pin we want to set to GPIO pin.
 *
 * @return state of the pin.
 */
uint8_t HAL_GPIO_read_PIN(GPIO_Type *port, uint8_t pin);

/**
 * @brief Toggle state of a pin
 *
 * @param port is the GPIO register of the GPIO pin we want to set.
 * @param pin is the pin we want to set to GPIO pin.
 *
 * @return: this function return nothing.
 */
void HAL_GPIO_toggle_PIN(GPIO_Type *port, int8_t pin);

/*Header guard*/
#endif
/*EOF*/
