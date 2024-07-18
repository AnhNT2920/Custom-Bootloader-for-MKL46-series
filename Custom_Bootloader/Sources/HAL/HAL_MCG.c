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
   -- MCG_C4 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_MCG_C4_set_DMX32
* Description: Select DCO max frequency for MCGFLLCLK
*
END***************************************************************************/
void HAL_MCG_C4_set_DMX32(uint8_t DMX32_value)
{
    /*If DCO is fine-tuned for maximum frequency with 32.768 kHz*/
    if (1 == DMX32_value)
    {
        MCG->C4 |= MCG_C4_DMX32_MASK;
    }
    /*DCO has default range of 25%*/
    else if (0 == DMX32_value)
    {
        MCG->C4 &= ~(1u << MCG_C4_DMX32_SHIFT);
    }
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_MCG_C4_set_DRST_DRS
* Description: Select DCO range
*
END***************************************************************************/
void HAL_MCG_C4_set_DRST_DRS(uint8_t DCO_range_value)
{
    /*If DCO range is low range*/
    if (0 == DCO_range_value)
    {
        /*Write 0 to the DRST_DRS bit field*/
        MCG->C4 &= ~(3u << MCG_C4_DRST_DRS_SHIFT);
    }
    /*If DCO has mid range, mid-high range or high range*/
    else if (DCO_range_value < 4u)
    {
        /*Clear DRST_DRS bit field*/
        MCG->C4 &= ~(3u << MCG_C4_DRST_DRS_SHIFT);
        /*Wait for the DRST_DRS is updated*/
        while (!(0u == ((MCG->C4 >> MCG_C4_DRST_DRS_SHIFT) & 3u)))
        {
            /*Do nothing*/
        }
        /*Write DCO range select to DRST_DRS bit field*/
        MCG->C4 |= DCO_range_value << MCG_C4_DRST_DRS_SHIFT;
    }
    else
    {
        /*Do nothing*/
    }

    /*Wait for the DRST_DRS is updated*/
    while (!(DCO_range_value == ((MCG->C4 >> MCG_C4_DRST_DRS_SHIFT) & 3u)))
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: HAL_MCG_C4_read_DRST_DRS
* Description: Read the value of DRST_DRS
*
END***************************************************************************/
uint8_t HAL_MCG_C4_read_DRST_DRS(void)
{
    return (MCG->C4 >> MCG_C4_DRST_DRS_SHIFT);
}

/*!
 * @}
 */
/* end of group MCG_C4 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- MCG_C5 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_MCG_C5_set_PLLCLKEN0
* Description: Select PLL clock state
*
END***************************************************************************/
void HAL_MCG_C5_set_PLLCLKEN0(uint8_t PLLCLKEN0_value)
{
    /*If MCGPLLCLK is inactive*/
    if (0 == PLLCLKEN0_value)
    {
        /*Write 0 to the PLLCLKEN0 bit field*/
        MCG->C5 &= ~(1u << MCG_C5_PLLCLKEN0_SHIFT);
    }
    /*If MCGPLLCLK is active*/
    else if (1 == PLLCLKEN0_value)
    {
        /*Write 1 to the PLLCLKEN0 bit field*/
        MCG->C5 |= MCG_C5_PLLCLKEN0_MASK;
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
/* end of group MCG_C5 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- MCG_C6 register bit setting functions group
   ---------------------------------------------------------------------------- */

/*Functions*********************************************************************
*
* Function name: HAL_MCG_C6_set_PLLS
* Description: Select whether PLL or FLL output is selected as the MCG source
*
END***************************************************************************/
void HAL_MCG_C6_set_PLLS(uint8_t PLLS_value)
{
    /*If FLL output is selected*/
    if (0 == PLLS_value)
    {
        /*Write 0 to PLLS bit field*/
        MCG->C6 &= ~(1u << MCG_C6_PLLS_SHIFT);
    }
    /*If PLL output is selected*/
    else if (1 == PLLS_value)
    {
        /*Write 1 to PLLS bit field*/
        MCG->C6 |= MCG_C6_PLLS_MASK;
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
/* end of group MCG_C5 register bit setting functions */

/*EOF*/
