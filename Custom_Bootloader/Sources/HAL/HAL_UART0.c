/**
 * @file  : HAL_MCG.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file HAL_MCG.c
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
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/* ----------------------------------------------------------------------------
   -- UART0_BDH register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_BDH_set_SBR
* Description: Set value for 5 high bits of Baud rate modulo divisor
*
END***************************************************************************/
void HAL_UART0_BDH_set_SBR(uint16_t baud_rate_divisor)
{
    /*Check input. Because the baud rate modulo divisor has 13 bits width, maximum valuse is 8191*/
    if (baud_rate_divisor >= 1 && baud_rate_divisor <= 8191)
    {
        /*Clear the SBR bit field*/
        UART0->BDH &= ~(UART0_BDH_SBR_MASK);
        /*Write 5 bits high of baud rate modulo divisor into SBR field of BDH register*/
        UART0->BDH |= (baud_rate_divisor >> 8u) & UART_BDH_SBR_MASK;
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
* Function name: HAL_UART0_BDH_set_SBNS
* Description: Set stop bit count for UART0
*
END***************************************************************************/
void HAL_UART0_BDH_set_SBNS(uint8_t SBNS_value)
{
    /*If stop bit number is 1*/
    if (0 == SBNS_value)
    {
        /*Write 0 to the SBNS bit field*/
        UART0->BDH &= ~(1u << UART0_BDH_SBNS_SHIFT);
    }
    /*If stop bit number is 2*/
    else if (1 == SBNS_value)
    {
        /*Write 1 to the SBNS bit field*/
        UART0->BDH |= UART0_BDH_SBNS_MASK;
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group UART0_BDH register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_BDL register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_BDL_set_SBR
* Description: Set value for 8 bits low of baud rate modulo divisor
*
END***************************************************************************/
void HAL_UART0_BDL_set_SBR(uint16_t baud_rate_divisor)
{
    /*Check input. The baud rate modulo divisor has 13 bits width. Maximum value is 8191*/
    if (baud_rate_divisor >= 1 && baud_rate_divisor <= 8191)
    {
        /*Set BDL register value as 8 bits low of baud rate divisor*/
        UART0->BDL = baud_rate_divisor & UART0_BDL_SBR_MASK;
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group UART0_BDL register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C1 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C1_set_M
* Description: Set length of data for UART0
*
END***************************************************************************/
void HAL_UART0_C1_set_M(uint8_t M_value)
{
    /*If data length is 9 bits*/
    if (1 == M_value)
    {
        /*Write 1 to M bit field*/
        UART0->C1 |= UART0_C1_M(M_value);
    }
    /*If data length is 8 bits*/
    else if (0 == M_value)
    {
        /*Write 0 to M bit field*/
        UART0->C1 &= ~(1u << UART0_C1_M_SHIFT);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C1_set_PE
* Description: Set parity state for UART0
*
END***************************************************************************/
void HAL_UART0_C1_set_PE(uint8_t PE_value)
{
    /*If parity enabled*/
    if (1 == PE_value)
    {
        /*Write 1 to PE bit field*/
        UART0->C1 |= UART0_C1_PE(PE_value);
    }
    /*If parity disabled*/
    else if (0 == PE_value)
    {
        /*Write 0 to PE bit field*/
        UART0->C1 &= ~(1u << UART0_C1_PE_SHIFT);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C1_set_PT
* Description: Set parity type for UART0
*
END***************************************************************************/
void HAL_UART0_C1_set_PT(uint8_t PT_value)
{
    /*If parity type is Odd parity*/
    if (1 == PT_value)
    {
        /*Write 1 to PT bit field*/
        UART0->C1 |= 1u << UART0_C1_PT_SHIFT;
    }
    /*If parity type is even parity*/
    else if(0 == PT_value)
    {
        UART0->C1 &= ~(1u << UART0_C1_PT_SHIFT);
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group UART0_C1 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C2 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C2_set_TIE
* Description: Set transmit interrupt state for UART0
*
END***************************************************************************/
void HAL_UART0_C2_set_TIE(uint8_t TIE_value)
{
    /*If transmit interrupt request when TDRE flag is 1*/
    if (1 == TIE_value)
    {
        /*Write 1 to the TIE bit field*/
        UART0->C2 |= UART0_C2_TIE(1);
    }
    /*If transmit interrupt is disabled*/
    else if (0 == TIE_value)
    {
        /*Write 0 to the TIE bit field*/
        UART0->C2 &= ~(1u << UART0_C2_TIE_SHIFT);
    }
    /*Any invallid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C2_set_RIE
* Description: Set receive interrupt state for UART0
*
END***************************************************************************/
void HAL_UART0_C2_set_RIE(uint8_t RIE_value)
{
    /*If receive interrupt requestd when RDRF flag is 1*/
    if (1 == RIE_value)
    {
        /*Write 1 to RIE bit field*/
        UART0->C2 |= UART0_C2_RIE(RIE_value);
    }
    /*If receive interrupt is disabled*/
    else if (0 == RIE_value)
    {
        /*Write 0 to RIE bit field*/
        UART0->C2 &= ~(1u << UART0_C2_RIE_SHIFT);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C2_set_TE
* Description: Set transmitter state for UART0
*
END***************************************************************************/
void HAL_UART0_C2_set_TE(uint8_t TE_value)
{
    /*If transmitter is enabled*/
    if (1 == TE_value)
    {
        /*Write 1 to TE bit field*/
        UART0->C2 |= UART0_C2_TE(TE_value);
    }
    /*If transmitter is disabled*/
    else if (0 == TE_value)
    {
        /*Write 0 to TE bit field*/
        UART0->C2 &= ~(1u << UART0_C2_TE_SHIFT);
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
* Function name: HAL_UART0_C2_set_RE
* Description: Set receiver state for UART0
*
END***************************************************************************/
void HAL_UART0_C2_set_RE(uint8_t RE_value)
{
    /*If receiver is enabled*/
    if (1 == RE_value)
    {
        /*Write 1 to RE bit field*/
        UART0->C2 |= UART0_C2_RE(RE_value);
    }
    /*If receiver is disabled*/
    else if (0 == RE_value)
    {
        /*Write 0 to RE bit field*/
        UART0->C2 &= ~(1u << UART0_C2_RE_SHIFT);
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }
    UART0->D;

    return;
}

/*!
 * @}
 */
/* end of group UART0_C2 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C4 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_C4_set_OSR
* Description: Set over sampling ratio for UART0
*
END***************************************************************************/
void HAL_UART0_C4_set_OSR(uint8_t OSR_value)
{
    uint8_t OSR_write = OSR_value - 1;  /*This variable stores the exact OSR value to write to C4 register*/

    /*Check input. This OSR has 5 bits width so the maximum value is 31. The minumum value is 4*/
    if (3u <= OSR_write && OSR_write <= 31)
    {
        /*Clear the OSR bit field*/
        UART0->C4 &= ~(UART0_C4_OSR_MASK);
        /*Write desired value to OSR bit field*/
        UART0->C4 |= UART0_C4_OSR(OSR_write);
    }
    /*Any invalid input will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*!
 * @}
 */
/* end of group UART0_C4 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_S1 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_S1_read_TDRE
* Description: Read the transmit data register empty flag(Ready to send data)
*
END***************************************************************************/
uint8_t HAL_UART0_S1_read_TDRE(void)
{
    /*Get the state of TDRE bit field*/
    return UART0->S1 & UART0_S1_TDRE_MASK;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_S1_read_RDRF
* Description: Read the receive data register full flag(Ready to get data)
*
END***************************************************************************/
uint8_t HAL_UART0_S1_read_RDRF(void)
{
    /*Get the state of RDRF bit field*/
    return UART0->S1 & UART0_S1_RDRF_MASK;
}

/*!
 * @}
 */
/* end of group UART0_S2 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_D register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_UART0_D_write_data
* Description: Write data to the data buffer register to send data
*
END***************************************************************************/
void HAL_UART0_D_write_data(uint8_t data)
{
    /*Check input*/
    UART0->D = data;

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_UART0_D_read_data
* Description: Read data from the data register
*
END***************************************************************************/
uint8_t HAL_UART0_D_read_data(void)
{
    /*Get the received data*/
    return UART0->D;
}

/*!
 * @}
 */
/* end of group UART0_S2 register bit setting functions */

/*EOF*/
