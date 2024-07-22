/**
 * @file  : Driver_GPIO.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Driver_GPIO.h.
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

#ifndef _DRIVER_GPIO_H_
#define _DRIVER_GPIO_H_

/*******************************************************************************
 * Enum
 ******************************************************************************/

typedef enum Driver_pin_state
{
    LOW_STATE,
    HIGH_STATE,
} Pin_state_enum_t;

typedef enum Driver_pin_direction
{
    GPIO_INPUT,
    GPIO_OUTPUT
} GPIO_pin_direction_enum_t;

/*******************************************************************************
 * Struct
 ******************************************************************************/

typedef struct Driver_GPIO_info
{
    Port_type_enum_t port_type;
    uint8_t pin;
    Pull_type_enum_t pull_type;
    GPIO_pin_direction_enum_t direction;
    Pin_state_enum_t initial_state;
} GPIO_config_info_t;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Initialize a GPIO pin
 *
 * @param GPIO_info is a struct pointer that has information of a pin we want to set as GPIO
 *
 * @return: This function return nothing.
 */
void Driver_GPIO_init_pin(GPIO_config_info_t *GPIO_info);

/**
 * @brief Set pin direction for a pin
 *
 * @param port_type is the PORT which contains the pin to set direction.
 * @param pin is the pin number we want to set MUX.
 * @param pin_direction is the direction we want to set.
 *
 * @return: This function return nothing.
 */
void Driver_GPIO_set_pin_direction(Port_type_enum_t port_type, uint8_t pin, GPIO_pin_direction_enum_t pin_direction);

/**
 * @brief Write a logic level to a GPIO pin.
 *
 * @param port_type is the PORT which contains the pin to write.
 * @param pin is the pin we want to set to GPIO pin.
 * @param state has the value of HIGH_STATE or LOW_STATE.
 *
 * @return: this function return nothing.
 */
void Driver_GPIO_set_pin_State(Port_type_enum_t port_type, uint8_t pin, Pin_state_enum_t state);

/**
 * @brief Read the state of a GPIO pin.
 *
 * @param port_type is the PORT which contains the pin to read.
 * @param pin is the pin we want to set to GPIO pin.
 *
 * @return state of the pin.
 */
uint8_t Driver_GPIO_read_pin_state(Port_type_enum_t port_type, uint8_t pin);

/**
 * @brief Toggle state of a pin
 *
 * @param port_type is the PORT which contains the pin to toggle.
 * @param pin is the pin we want to set to GPIO pin.
 *
 * @return: this function return nothing.
 */
void Driver_GPIO_toggle_pin_state(Port_type_enum_t port_type, uint8_t pin);

/*Header Guard*/
#endif
/*EOF*/
