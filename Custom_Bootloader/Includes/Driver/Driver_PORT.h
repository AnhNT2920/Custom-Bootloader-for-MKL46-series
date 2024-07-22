/**
 * @file  : Driver_PORT.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Driver_PORT.h.
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

#ifndef _DRIVER_PORT_H_
#define _DRIVER_PORT_H_

/*******************************************************************************
 * Typedef
 ******************************************************************************/

typedef enum Driver_mux_type
{
    MUX_PIN_DISABLED    = 0u,   /*<< Pin disable mod >>*/
    MUX_GPIO            = 1u,   /*<< Pin GPIO mod >>*/
    MUX_ALTERNATIVE2    = 2u,   /*<< Pin alternative 2 mod >>*/
    MUX_ALTERNATIVE3    = 3u,   /*<< Pin alternative 3 mod >>*/
    MUX_ALTERNATIVE4    = 4u,   /*<< Pin alternative 4 mod >>*/
    MUX_ALTERNATIVE5    = 5u,   /*<< Pin alternative 5 mod >>*/
    MUX_ALTERNATIVE6    = 6u,   /*<< Pin alternative 6 mod >>*/
    MUX_ALTERNATIVE7    = 7u    /*<< Pin alternative 7 mod >>*/
} Mux_type_enum_t;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Select MUX for a pin by calling set MUX function in HAL
 *
 * @param port_type is the PORT which contains the pin to set MUX.
 * @param pin is the pin number we want to set MUX.
 * @param mux_type is the type of MUX we want to set.
 *
 * @return: This function return nothing.
 */
void Driver_PORT_set_MUX_pin(Port_type_enum_t port_type, uint8_t pin, Mux_type_enum_t mux_type);

/**
 * @brief Select Pull resistor for a pin by calling set pull function in HAL
 *
 * @param port_type is the PORT which contains the pin to set pull resistor.
 * @param pin is the pin number we want to set pull resistor.
 * @param pull_type is the type of pull we want to set.
 *
 * @return: This function return nothing.
 */
void Driver_PORT_set_pull_pin(Port_type_enum_t port_type, uint8_t pin, Pull_type_enum_t pull_type);

#endif
/*EOF*/
