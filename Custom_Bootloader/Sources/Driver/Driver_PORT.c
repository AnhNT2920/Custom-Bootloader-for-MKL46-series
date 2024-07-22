/**
 * @file  : Driver_PORT.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file Driver_PORT.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/HAL/HAL_PORT.h"
#include "../Includes/Driver/Driver_PORT.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*This array stores all the PORT type*/
static PORT_Type *port_array[5] = {PORTA, PORTB, PORTC, PORTD, PORTE};

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: Driver_PORT_set_MUX_pin
* Description: Select MUX for a pin buy calling set MUX function in HAL layer.
*
END***************************************************************************/
void Driver_PORT_set_MUX_pin(Port_type_enum_t port_type, uint8_t pin, Mux_type_enum_t mux_type)
{
    /*Set MUX for pin*/
    if ((pin < 32) && (PORT_A <= port_type && port_type <= PORT_E) && (MUX_PIN_DISABLED <= mux_type && mux_type <= MUX_ALTERNATIVE7))
    {
        HAL_PORT_PCR_set_MUX_pin(port_array[port_type], pin, mux_type);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_PORT_set_pull_pin
* Description: Set Pull resistor for a pin by calling set pull function in HAL
*
END***************************************************************************/
void Driver_PORT_set_pull_pin(Port_type_enum_t port_type, uint8_t pin, Pull_type_enum_t pull_type)
{
    /*Set pull for pin*/
    if ((pin < 32) && (PORT_A <= port_type && port_type <= PORT_E) && (PULL_DOWN <= pull_type && pull_type <= PULL_UP))
    {
        HAL_PORT_PCR_set_Pull_pin(port_array[port_type], pin, pull_type);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}
/*EOF*/
