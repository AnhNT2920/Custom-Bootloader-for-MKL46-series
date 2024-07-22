/**
 * @file  : HAL_PORT.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file HAL_PORT.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/HAL/HAL_PORT.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: HAL_PORT_set_MUX_pin
* Description: Set MUX for a pin.
*
END***************************************************************************/
void HAL_PORT_PCR_set_MUX_pin(PORT_Type *port_selected, uint8_t pin, uint8_t MUX_value)
{
    /*Clear MUX field*/
    port_selected->PCR[pin] &= ~(7 << 8);

    /*Set MUX field to GPIO*/
    port_selected->PCR[pin] |= (MUX_value << 8);

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_PORT_set_pull_option.
* Description: Select pull for a GPIO pin.
*
END***************************************************************************/
void HAL_PORT_PCR_set_Pull_pin(PORT_Type *port_select, uint8_t pin, uint8_t pull_type)
{
    port_select->PCR[pin] &= ~3;
    /*Set pull resistor for pin*/
    port_select->PCR[pin] |= pull_type;

    return;
}
/*EOF*/
