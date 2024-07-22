/**
 * @file  : Driver_MCG.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Driver_MCG.c.
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

#ifndef _DRIVER_MCG_H_
#define _DRIVER_MCG_H_

/*******************************************************************************
 * Macro
 ******************************************************************************/

/**
 * @brief Reference of the total option for setting the DMX32 value.
 */
#define DMX32_OPTION_COUNT (2u)

/**
 * @brief Reference of the total option for setting the DRST_DRS value.
 */
#define DRST_DRS_OPTION_COUNT (4u)

/**
 * @brief Reference of the internal reference clock frequency
 */
#define MCGFLLCLK_REFERENCE_CLOCK (32768u)

/*******************************************************************************
 * Enum
 ******************************************************************************/

/**
 * @brief Reference of DCO range
 */
typedef enum DRST_DRS_type
{
    DCO_LOW_RANGE = 0u,      /*The FLL output has the low range of frequency*/
    DCO_MID_RANGE = 1u,      /*The FLL output has the mid range of frequency*/
    DCO_MID_HIGH_RANGE = 2u, /*The FLL output has the mid-high range of frequency*/
    DCO_HIGH_RANGE = 3u,     /*The FLL output has the high range of frequency*/
} DCO_range_type_enum_t;

/**
 * @brief Reference of DCO max frequency
 */
typedef enum DMX32_type
{
    DCO_DEFAULT_RANGE = 0u,           /*The MCGFLLCLK uses the lower FLL factor in selected range*/
    DCO_FIX_TUNED_MAX_FREQUENCY = 1u, /*The MCGFLLCLK used the higher FLL factor in selected range*/
} DMX32_type_enum_t;

/**
 * @brief Reference of MCGPLLCLK state
 */
typedef enum PLLKEN0_type
{
    MCGPLLCLK_INACTIVE = 0u, /*MCGPLLCLK is disabled*/
    MCGPLLCLK_ACTIVE = 1u,   /*MCGPLLCLK is enabled*/
} PLLKEN0_type_enum_t;

/**
 * @brief Reference of MCG source options
 */
typedef enum PLLS_type
{
    FLL_SELECTED = 0u, /*FLL output is selected for MCG source*/
    PLL_SELECTED = 1u, /*PLL output is selected for MCG source*/
} PLLS_type_enum_t;

/*******************************************************************************
 * Struct
 ******************************************************************************/

/**
 * @brief Contain the information about the MCG_C4 register configuration.
 */
typedef struct MCG_C4_config
{
    DCO_range_type_enum_t DCO_range;     /*FLL ouput frequency range*/
    DMX32_type_enum_t DCO_max_frequency; /*MCGFLLCLK max frequency option is using the lower FLL factor
                                           or higher FLL factor in selected range*/
} MCG_C4_config_info;

/**
 * @brief Contain the information about the MCG_C5 register configuration.
 */
typedef struct MCG_C5_config
{
    PLLKEN0_type_enum_t PLL_clock_state; /*MCGPLLCLK clock state*/
} MCG_C5_config_info;

/**
 * @brief Contain the information about the MCG_C6 register configuration.
 */
typedef struct MCG_C6_config
{
    PLLS_type_enum_t MCG_source; /*MCG source*/
} MCG_C6_config_info;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Init the MCGFLLCLK clock
 *
 * @param MCGFLLCLK_config is a struct pointer that has the information about
 *                         the MCGFLLCLK configuration.
 *
 * @return: This function return nothing.
 */
void Driver_MCG_Init_MCGFLLCLK(MCG_C4_config_info *MCGFLLCLK_config);

/**
 * @brief Disable the PLL
 *
 * @param: This function has no parameter.
 *
 * @return: This function return nothing.
 */
void Driver_MCG_disable_PLL(void);

/**
 * @brief Select whether FLL or PLL output is used as MCG source
 *
 * @param MCG_clock_source is the MCG source
 *
 * @return: This function return nothing.
 */
void Driver_MCG_select_MCG_source(PLLS_type_enum_t MCG_clock_source);

/**
 * @brief Get the MCGFLLCLK clock frequency
 *
 * @param MCGFLLCLK_config is a struct pointer that has the information about
 *                         the MCGFLLCLK configuration.
 *
 * @return the frequency of MCGFLLCLK clock
 */
uint32_t Driver_MCG_get_MCGFLLCLK_frequency(MCG_C4_config_info *MCGFLLCLK_config);

/**
 * @brief Select whether whether MCGFLLCLK uses lower or higher FLL factor in selected range
 *
 * @param MCGFLLCLK_max_range is the DCO_max_frequency option
 *
 * @return: This function return nothing.
 */
void Driver_MCG_select_MCGFLLCLK_max_frequency(DMX32_type_enum_t MCGFLLCLK_max_range);

/**
 * @brief Select the frequency range for FLL output
 *
 * @param FLL_range is the FLL output frequency range
 *
 * @return: This function return nothing.
 */
void Driver_MCG_select_FLL_output_range(DCO_range_type_enum_t FLL_range);

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
/*EOF*/
