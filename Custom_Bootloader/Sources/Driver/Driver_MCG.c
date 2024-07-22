/**
 * @file  : Driver_MCG.c
 * @author: Nguyen The Anh.
 * @brief : Definition of function using in file Driver_MCG.c
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include "../Includes/HAL/HAL_MCG.h"
#include "../Includes/Driver/Driver_MCG.h"
#include <stdlib.h>

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/

/*Functions*********************************************************************
*
* Function name: Driver_MCG_Init_MCGFLLCLK
* Description: Init the MCGFLLCLK clock
*
END***************************************************************************/
void Driver_MCG_Init_MCGFLLCLK(MCG_C4_config_info *MCGFLLCLK_config)
{
    /*check input*/
    if (NULL != MCGFLLCLK_config)
    {
        /*Disable the PLL*/
        Driver_MCG_disable_PLL();

        /*Select FLL output as the MCG source*/
        Driver_MCG_select_MCG_source(FLL_SELECTED);

        /*Select the frequency range for FLL output*/
        Driver_MCG_select_FLL_output_range(MCGFLLCLK_config->DCO_range);

        /*Select the max frequency for MCGFLLCLK clock whether has a default range of 25% ( max +- 25% )
          Or fixed at max frequency*/
        Driver_MCG_select_MCGFLLCLK_max_frequency(MCGFLLCLK_config->DCO_max_frequency);
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
* Function name: Driver_MCG_disable_PLL
* Description: Set MCPGLLCLK to be inactive
*
END***************************************************************************/
void Driver_MCG_disable_PLL(void)
{
    /*Set the MCGPLLCLK be disabled*/
    HAL_MCG_C5_set_PLLCLKEN0((uint8_t)MCGPLLCLK_INACTIVE);

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_MCG_select_MCG_source
* Description: Select whether FLL or PLL output as MCG source
*
END***************************************************************************/
void Driver_MCG_select_MCG_source(PLLS_type_enum_t MCG_clock_source)
{
    /*Check input*/
    if ((FLL_SELECTED == MCG_clock_source) || (PLL_SELECTED == MCG_clock_source))
    {
        /*Select whether FLL or PLL output is the MCG source*/
        HAL_MCG_C6_set_PLLS((uint8_t)MCG_clock_source);
    }
    /*Any invalid write will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_MCG_get_MCGFLLCLK_frequency
* Description: Get frequency of the MCGFLLCLK
*
END***************************************************************************/
uint32_t Driver_MCG_get_MCGFLLCLK_frequency(MCG_C4_config_info *MCGFLLCLK_config)
{
    uint8_t DMX32_value = 0;          /*This variable stores the DMX32 bit seting*/
    uint8_t DRST_DRS_value = 0;       /*This variable stores the DCO range bit setting*/
    uint32_t MCGFLLCLK_frequency = 0; /*This variable stores the MCGFLLCLK frequency*/

    /*This 2-D array stores the FLL factors according to DMX32 and DRST_DRS value*/
    uint16_t FLL_factor_table[DMX32_OPTION_COUNT][DRST_DRS_OPTION_COUNT] = {{640, 1280, 1920, 2560},
                                                                            {732, 1464, 2197, 2929}};

    /*Check input*/
    if (NULL != MCGFLLCLK_config)
    {
        /*Check DMX32 input*/
        if (MCGFLLCLK_config->DCO_max_frequency <= DCO_FIX_TUNED_MAX_FREQUENCY)
        {
            /*Get DMX32_value*/
            DMX32_value = (uint8_t)MCGFLLCLK_config->DCO_max_frequency;
        }
        else
        {
            /*Do nothing*/
        }

        /*Check DRST_DRS input*/
        if (MCGFLLCLK_config->DCO_range <= DCO_HIGH_RANGE)
        {
            /*Get DRST_DRS value*/
            DRST_DRS_value = (uint8_t)MCGFLLCLK_config->DCO_range;
        }
        else
        {
            /*Do nothing*/
        }

        /*Calculate MCGFLLCLK clock frequency*/
        MCGFLLCLK_frequency = FLL_factor_table[DMX32_value][DRST_DRS_value] * MCGFLLCLK_REFERENCE_CLOCK;
    }
    else
    {
        /*Do nothing*/
    }

    return MCGFLLCLK_frequency;
}

/*Functions*********************************************************************
*
* Function name: Driver_MCG_select_MCGFLLCLK_max_frequency
* Description: Select max frequency for MCGFLLCLk
*
END***************************************************************************/
void Driver_MCG_select_MCGFLLCLK_max_frequency(DMX32_type_enum_t MCGFLLCLK_max_range)
{
    /*Check input*/
    if ((DCO_DEFAULT_RANGE == MCGFLLCLK_max_range) || (DCO_FIX_TUNED_MAX_FREQUENCY == MCGFLLCLK_max_range))
    {
        /*Set the MCGFLLCLK frequency whether the internal reference clock (32.768 kHz) multiple with
          higher FLL factor or lower FLL factor in selected range.
          Exp: If selected range is low-range and the MCGFLLCLK has the default max frequency(DCO_DEFAULT_RANGE)
               The MCGFLLCLK frequency would be: 32.768 kHz multiple with 640.
               If The MCGFLLCLK has the fix_tuned max frequency. The MCGFLLCLK freuqency would be: 32.768 * 732*/
        HAL_MCG_C4_set_DMX32((uint8_t)MCGFLLCLK_max_range);
    }
    /*Any invalid write will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}

/*Functions*********************************************************************
*
* Function name: Driver_MCG_select_FLL_output_range
* Description: Select FLL output frequency range
*
END***************************************************************************/
void Driver_MCG_select_FLL_output_range(DCO_range_type_enum_t FLL_range)
{
    /*Check input*/
    if (FLL_range <= DCO_HIGH_RANGE)
    {
        /*The FLL output frequency range decide the FLL factor affected by the DMX32 value*/
        /*Low range: 640 - 732*/
        /*Mid range: 1280 - 1464*/
        /*Mid-high range: 1920 - 2197*/
        /*High range: 2560 - 2929*/
        HAL_MCG_C4_set_DRST_DRS((uint8_t)FLL_range);
    }
    /*Any invalid write will be ignored*/
    else
    {
        /*Do nothing*/
    }

    return;
}
/*EOF*/
