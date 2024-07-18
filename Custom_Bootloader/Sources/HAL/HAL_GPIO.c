/**
 * @file  : HAL_GPIO.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file HAL_GPIO.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/HAL/HAL_GPIO.h"
#include <stdlib.h>

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: HAL_GPIO_set_direct_PIN.
* Description: Set direction for a GPIO pin
*
END***************************************************************************/
void HAL_GPIO_set_direct_PIN(GPIO_Type *port, int8_t pin, uint8_t logic)
{
    if (0 <= pin && pin <= 31 && NULL != port)
    {
        /*Logic = 1, the pin is ouput GPIO*/
        if (1 == logic)
        {
            port->PDDR |= 1 << pin;
        }
        /*Logic = 0, the pin is input GPIO*/
        else if (0 == logic)
        {
            port->PDDR &= ~(1 << pin);
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
* Function name: HAL_GPIO_write_PIN.
* Description: Write a logic level (0/1) to a pin.
*
END***************************************************************************/
void HAL_GPIO_write_PIN(GPIO_Type *GPIO, uint8_t pin, uint8_t logic)
{
    if ((0 <= pin && pin <= 31) && (NULL != GPIO))
    {
        /*Logic = 1, write 1 to the pin*/
        if (1 == logic)
        {
            GPIO->PDOR |= 1 << pin;
        }
        /*Logic = 0, write 0 to the pin*/
        else if (0 == logic)
        {
            GPIO->PDOR &= ~(1 << pin);
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
* Function name: HAL_GPIO_read_PIN.
* Description: Read state of a pin.
*
END***************************************************************************/
uint8_t HAL_GPIO_read_PIN(GPIO_Type *port, uint8_t pin)
{
    uint8_t read_logic = 0; /*read_logic will store the logic level of the pin*/

    if ((0 <= pin) && (pin <= 31))
    {
        read_logic = (port->PDIR >> pin) & 1;
    }
    else
    {
        /*Do nothing*/
    }

    return read_logic;
}

/*Functions*********************************************************************
*
* Function name: HAL_GPIO_toggle_PIN.
* Description: Toggle the state of a pin.
*
END***************************************************************************/
void HAL_GPIO_toggle_PIN(GPIO_Type *port, int8_t pin)
{
    if ((0 <= pin) && (pin <= 31))
    {
        /*Write 1 to PTORn*/
        port->PTOR |= 1 << pin;
    }
    else
    {
        /*Do nothing*/
    }

    return;
}
/*EOF*/
