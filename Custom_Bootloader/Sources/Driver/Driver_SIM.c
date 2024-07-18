/**
 * @file  : Driver_SIM.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file Driver_SIM.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/Driver/Driver_SIM.h"
#include "../Includes/HAL/HAL_SIM.h"
#include <stdlib.h>

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: Driver_SIM_SOPT2_init
* Description: Init the SIM_SOPT2 register
*
END***************************************************************************/
void Driver_SIM_SOPT2_init(SOPT2_config_info *SOPT2_config)
{
    /*Check input*/
    if (NULL != SOPT2_config)
    {
        /*Select the clock source for UART0*/
        Driver_SIM_SOPT2_select_UART0_clock(SOPT2_config->uart0_clock_source);
        /*Select FLL or PLL clock soucre for peripherals*/
        Driver_SIM_SOPT2_select_FLL_PLL(SOPT2_config->MCGPLLCLK_MCGFLLCLK_option);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_SIM_SOPT2_select_UART0_clock
* Description: Select clock source for UART0 transmitter and receiver
*
END***************************************************************************/
void Driver_SIM_SOPT2_select_UART0_clock(UART0SRC_option_enum_t clock_source)
{
    /*Check input*/
    if ((CLOCK_DISABLED <= clock_source) && (clock_source <= MCGIRCLK_CLOCK))
    {
        /*Set clock source for UART0*/
        HAL_SIM_SOPT2_set_UART0SRC((uint8_t)clock_source);
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
* Function name: Driver_SIM_SOPT2_select_FLL_PLL
* Description: Select if the clock source is MCGFLLCLK or MCGPLLCLK/2
*
END***************************************************************************/
void Driver_SIM_SOPT2_select_FLL_PLL(PLLFLLSEL_option_enum_T FLL_PLL_option)
{
    /*Check input*/
    if ((MCGFLLCLK_CLOCK_SELECTED == FLL_PLL_option) || (HALF_MCGPLLCLK_CLOCK_SELECTED == FLL_PLL_option))
    {
        /*Set the FLL/PLL clock source option*/
        HAL_SIM_SOPT2_set_PLLFLLSEL((uint8_t)FLL_PLL_option);
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
* Function name: Driver_SIM_SCGC4_init_clock
* Description: Init the SCGC4 register
*
END***************************************************************************/
void Driver_SIM_SCGC4_init_clock(SCGC4_config_info *SCGC4_config)
{
    /*Check input*/
    if (NULL != SCGC4_config)
    {
        /*Set clock gate control for UART0*/
        Driver_SIM_SCGC4_set_UART0_clock_gate(SCGC4_config->UART0_clock_gate);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_SIM_SCGC4_set_UART0_clock_gate
* Description: Set clock gate control for UART0
*
END***************************************************************************/
void Driver_SIM_SCGC4_set_UART0_clock_gate(clock_gate_state_enum_t uart0_clock_gate)
{
    /*Check input*/
    if (uart0_clock_gate <= ENABLED)
    {
        /*Set clock gate control for UART0*/
        HAL_SIM_SCGC4_set_clock_UART0((uint8_t)uart0_clock_gate);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_SIM_enable_clock_PORT
* Description: Enable clock source for a PORT.
*
END***************************************************************************/
void Driver_SIM_SCGC5_init_clock(SCGC5_config_info *SCGC5_clock_config)
{
    if (NULL != SCGC5_clock_config)
    {
        /*Set PORTA clock gate control*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(PORT_A, SCGC5_clock_config->PORTA_clock);
        /*Set PORTB clock gate control*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(PORT_B, SCGC5_clock_config->PORTB_clock);
        /*Set PORTC clock gate control*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(PORT_C, SCGC5_clock_config->PORTC_clock);
        /*Set PORTD clock gate control*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(PORT_D, SCGC5_clock_config->PORTD_clock);
        /*Set PORTE clock gate control*/
        Driver_SIM_SCGC5_set_PORTn_clock_gate(PORT_E, SCGC5_clock_config->PORTE_clock);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_SIM_SCGC5_set_PORTn_clock_gate
* Description: Set PORTn clock gate control
*
END***************************************************************************/
void Driver_SIM_SCGC5_set_PORTn_clock_gate(Port_type_enum_t port, clock_gate_state_enum_t PORTn_gate)
{
    /*Check input*/
    if ((ENABLED == PORTn_gate) || (DISABLED == PORTn_gate))
    {
        switch (port)
        {
        /*If PORTA need to set clock gate control*/
        case PORT_A:
        {
            /*Set clock gate control for PORTA*/
            HAL_SIM_SCGC5_set_clock_PORTA((uint8_t)PORTn_gate);
            break;
        }
        /*If PORTB need to set clock gate control*/
        case PORT_B:
        {
            /*Set clock gate control for PORTB*/
            HAL_SIM_SCGC5_set_clock_PORTB((uint8_t)PORTn_gate);
            break;
        }
        /*If PORTC need to set clock gate control*/
        case PORT_C:
        {
            /*Set clock gate control for PORTC*/
            HAL_SIM_SCGC5_set_clock_PORTC((uint8_t)PORTn_gate);
            break;
        }
        /*If PORTD need to set clock gate control*/
        case PORT_D:
        {
            /*Set clock gate control for PORTD*/
            HAL_SIM_SCGC5_set_clock_PORTD((uint8_t)PORTn_gate);
            break;
        }
        /*If PORTE need to set clock gate control*/
        case PORT_E:
        {
            /*Set clock gate control for PORTE*/
            HAL_SIM_SCGC5_set_clock_PORTE((uint8_t)PORTn_gate);
            break;
        }
        default:
            break;
        }
    }

    return;
}

/*EOF*/
