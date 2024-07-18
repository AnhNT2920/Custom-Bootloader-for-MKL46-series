/**
 * @file  : Driver_GPIO.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file Driver_GPIO.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/Driver/Driver_GPIO.h"
#include "../Includes/Driver/Driver_PORT.h"
#include "../Includes/HAL/HAL_GPIO.h"
#include <stdlib.h>

/*******************************************************************************
 * Variable
 ******************************************************************************/

static GPIO_Type *GPIO_port_array[5] = {PTA, PTB, PTC, PTD, PTE};

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: Driver_GPIO_init_pin
* Description: Init a pin as a GPIO pin by set up MUX, Pull resistor, direction.
*
END***************************************************************************/
void Driver_GPIO_init_pin(GPIO_config_info_t *GPIO_info)
{
    uint32_t i = 0;

    if (NULL != GPIO_info)
    {
        /*Set MUX for pin*/
        Driver_PORT_set_MUX_pin(GPIO_info->port_type, GPIO_info->pin, MUX_GPIO);

        /*Set pull for pin*/
        Driver_PORT_set_pull_pin(GPIO_info->port_type, GPIO_info->pin, GPIO_info->pull_type);

        /*Set pin direction*/
        HAL_GPIO_set_direct_PIN(GPIO_port_array[GPIO_info->port_type], GPIO_info->pin, (uint8_t)GPIO_info->direction);

        if (GPIO_OUTPUT == GPIO_info->direction)
        {
            /*Write initial value to the pin*/
            HAL_GPIO_write_PIN(GPIO_port_array[GPIO_info->port_type], GPIO_info->pin, (uint8_t)GPIO_info->initial_state);
        }
        else
        {
            if(PULL_UP == GPIO_info->pull_type)
            {
                /*Wait until the Pull up finish setting*/
                while(i < 100000)
                {
                    i++;
                }
            }
            else
            {
                /*Do nothing*/
            }
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
* Function name: Driver_GPIO_set_pin_direction
* Description: Select direction for a pin by calling set direction function in HAL
*
END***************************************************************************/
void Driver_GPIO_set_pin_direction(Port_type_enum_t port_type, uint8_t pin, GPIO_pin_direction_enum_t pin_direction)
{
    if ((PORT_A <= port_type) && (port_type <= PORT_E))
    {
        /*Set direction for a pin*/
        HAL_GPIO_set_direct_PIN(GPIO_port_array[port_type], pin, (uint8_t)pin_direction);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_GPIO_set_pin_State
* Description: Write a state to the pin by calling write state function in HAL
*
END***************************************************************************/
void Driver_GPIO_set_pin_State(Port_type_enum_t port_type, uint8_t pin, Pin_state_enum_t state)
{
    if ((PORT_A <= port_type) && (port_type <= PORT_E))
    {
        /*Write a state to the pin*/
        HAL_GPIO_write_PIN(GPIO_port_array[port_type], pin, (uint8_t)state);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_GPIO_read_pin_state
* Description: Read state of a pin and return it's value.
*
END***************************************************************************/
uint8_t Driver_GPIO_read_pin_state(Port_type_enum_t port_type, uint8_t pin)
{
    uint8_t pin_state = 0; /*pin_state stores the state of the pin*/

    if ((PORT_A <= port_type && port_type <= PORT_E))
    {
        /*Get state of the pin*/
        pin_state = HAL_GPIO_read_PIN(GPIO_port_array[port_type], pin);
    }
    else
    {
        /*Do nothing*/
    }

    return pin_state;
}

/*Functions*********************************************************************
*
* Function name: Driver_GPIO_toggle_pin_state
* Description: Toggle state of a pin.
*
END***************************************************************************/
void Driver_GPIO_toggle_pin_state(Port_type_enum_t port_type, uint8_t pin)
{
    if ((PORT_A <= port_type && port_type <= PORT_E))
    {
        /*Toggle state of a pin*/
        HAL_GPIO_toggle_PIN(GPIO_port_array[port_type], pin);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}
/*EOF*/
