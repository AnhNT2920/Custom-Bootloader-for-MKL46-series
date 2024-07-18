/**
 * @file  : HAL_MCG.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum and function using in HAL_SIM.c.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _HAL_MCG_H_
#define _HAL_MCG_H_

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* ----------------------------------------------------------------------------
   -- MCG_C4 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select if MCGFLLCLK has maximum FLL factor or lower FLL factor in
 *        the selected range
 *
 * @param DMX32_value is the state(0 / 1) to write to DMX32 bit field.
 *
 * @return: this function return nothing.
 */
void HAL_MCG_C4_set_DMX32(uint8_t DMX32_value);

/**
 * @brief Select range for MCGFLLCLK frequency
 *
 * @param range_select is the value to write to DRST_DRS bit field (0 -> 3)
 *
 * @return: this function return nothing.
 */
void HAL_MCG_C4_set_DRST_DRS(uint8_t range_select);

/*!
 * @}
 */
/* end of group MCG_C4 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- MCG_C5 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select if MCGPLLCLK is inactive or active
 *
 * @param PLL_option is the state to write to PLLCLKEN0 bit field (0/1)
 *
 * @return: this function return nothing.
 */
void HAL_MCG_C5_set_PLLCLKEN0(uint8_t PLL_option);

/*!
 * @}
 */
/* end of group MCG_C5 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- MCG_C6 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select whether FLL or PLL output is used as MCG source
 *
 * @param pll_option is the value to write to PLLS bit field (0/1)
 *
 * @return: this function return nothing.
 */
void HAL_MCG_C6_set_PLLS(uint8_t pll_option);

/*!
 * @}
 */
/* end of group MCG_C6 register bit setting functions */

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
/*EOF*/
