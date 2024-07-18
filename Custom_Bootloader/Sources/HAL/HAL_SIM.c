/**
 * @file  : HAL_SIM.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file HAL_SIM.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/HAL/HAL_SIM.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/* ----------------------------------------------------------------------------
   -- SOPT2 register bit setting function group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SOPT2_set_UART0SRC
* Description: Select clock source for UART0 transmitter and receiver.
*
END***************************************************************************/
void HAL_SIM_SOPT2_set_UART0SRC(uint8_t UART0SRC_value)
{
    /*If UART0 clock source is disabled*/
    if (0 == UART0SRC_value)
    {
        /*Write 0 to UART0SRC bit field*/
        SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK);
    }
    /*If UART0 clock source is MCGFLLCLK, MCGPLLCLK/2, OSCERCLK, MCGIRCLK*/
    else if (UART0SRC_value < 4u)
    {
        /*Clear UART0SRC bit field*/
        SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK);
        /*Write UART0SRC value to the UART0SRC bit field*/
        SIM->SOPT2 |= UART0SRC_value << SIM_SOPT2_UART0SRC_SHIFT;
    }
    /*Any invalid write will be ignore, the bit field will hold its previous value*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SOPT2_set_PLLFLLSEL
* Description: Select MCGFLLCLK or MCGPLLCLK clock for various peripheral
*
END***************************************************************************/
void HAL_SIM_SOPT2_set_PLLFLLSEL(uint8_t PLLFLLSEL_value)
{
    /*If MCGFLLCLK clock is selected for various peripheral*/
    if (0 == PLLFLLSEL_value)
    {
        /*Write 0 to PLLFLLSEL bit field*/
        SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
    }
    /*If MCGPLLCLK clock is selected for various peripheral*/
    else if (1 == PLLFLLSEL_value)
    {
        /*Write 1 to PLLFLLSEL bit field*/
        SIM->SOPT2 |= PLLFLLSEL_value << SIM_SOPT2_PLLFLLSEL_SHIFT;
    }
    /*Any invalid write will be ignore, the bit field will hold its previous value*/
    else
    {
        /**/
    }

    return;
}

/*!
 * @}
 */
/* end of group SOPT2 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- SCGC4 register bit setting function group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC4_set_clock_UART0
* Description: Enable clock for a PORTA.
*
END***************************************************************************/

void HAL_SIM_SCGC4_set_clock_UART0(uint8_t UART0_gate_value)
{
    /*If UART0 clock gate is enabled*/
    if (1 == UART0_gate_value)
    {
        /*Write 1 to UART0 bit field*/
        SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    }
    else if (0 == UART0_gate_value)
    {
        /*Write 0 to UART0 bit field*/
        SIM->SCGC4 &= ~(1u << UART0_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group SCGC4 register bit setting function */

/* ----------------------------------------------------------------------------
   -- SCGC5 register bit setting function group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC5_set_clock_PORTA
* Description: Enable clock for a PORTA.
*
END***************************************************************************/
void HAL_SIM_SCGC5_set_clock_PORTA(uint8_t portA_gate_value)
{
    /*If PORTA clock gate is enabled*/
    if (1 == portA_gate_value)
    {
        /*Write 1 to the bit field PORTA to enable clock source*/
        SIM->SCGC5 |= portA_gate_value << SIM_SCGC5_PORTA_SHIFT;
    }
    /*If PORTA clock gate is disabled*/
    else if (0 == portA_gate_value)
    {
        /*Write 0 to the bit field PORTA to disable clock source*/
        SIM->SCGC5 &= ~(1u << portA_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC5_set_clock_PORTB
* Description: Enable clock for a PORTB.
*
END***************************************************************************/
void HAL_SIM_SCGC5_set_clock_PORTB(uint8_t portB_gate_value)
{
    /*If PORTB clock gate is enabled*/
    if (1 == portB_gate_value)
    {
        /*Write 1 to the bit field PORTB to enable clock source*/
        SIM->SCGC5 |= portB_gate_value << SIM_SCGC5_PORTB_SHIFT;
    }
    /*If PORTB clock gate is disabled*/
    else if (0 == portB_gate_value)
    {
        /*Write 0 to the bit field PORTB to disable clock source*/
        SIM->SCGC5 &= ~(1u << portB_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC5_set_clock_PORTC
* Description: Enable clock for a PORTC.
*
END***************************************************************************/
void HAL_SIM_SCGC5_set_clock_PORTC(uint8_t portC_gate_value)
{
    /*If PORTC clock gate is enabled*/
    if (1 == portC_gate_value)
    {
        /*Write 1 to the bit field PORTC to enable clock source*/
        SIM->SCGC5 |= portC_gate_value << SIM_SCGC5_PORTC_SHIFT;
    }
    /*If PORTC clock gate is disabled*/
    else if (0 == portC_gate_value)
    {
        /*Write 0 to the bit field PORTC to disable clock source*/
        SIM->SCGC5 &= ~(1u << portC_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC5_set_clock_PORTD
* Description: Enable clock for a PORTD.
*
END***************************************************************************/
void HAL_SIM_SCGC5_set_clock_PORTD(uint8_t portD_gate_value)
{
    /*If PORTD clock gate is enabled*/
    if (1 == portD_gate_value)
    {
        /*Write 1 to the bit field PORTD to enable clock source*/
        SIM->SCGC5 |= portD_gate_value << SIM_SCGC5_PORTD_SHIFT;
    }
    /*If PORTD clock gate is disabled*/
    else if (0 == portD_gate_value)
    {
        /*Write 0 to the bit field PORTD to disable clock source*/
        SIM->SCGC5 &= ~(1u << portD_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_SIM_SCGC5_set_clock_PORTE
* Description: Enable clock for a PORTE.
*
END***************************************************************************/
void HAL_SIM_SCGC5_set_clock_PORTE(uint8_t portE_gate_value)
{
    /*If PORTE clock gate is enabled*/
    if (1 == portE_gate_value)
    {
        /*Write 1 to the bit field PORTE to enable clock source*/
        SIM->SCGC5 |= portE_gate_value << SIM_SCGC5_PORTE_SHIFT;
    }
    /*If PORTE clock gate is disabled*/
    else if (0 == portE_gate_value)
    {
        /*Write 0 to the bit field PORTE to disable clock source*/
        SIM->SCGC5 &= ~(1u << portE_gate_value);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group SCGC5 register bit setting function */
/*EOF*/
