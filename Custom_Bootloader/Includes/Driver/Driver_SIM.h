/**
 * @file  : Driver_SIM.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum, typdef, macro and function using in Driver_SIM.h.
 * @version: 0.0
 *
 * @copyright Copyright (c) 2024.
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/

#include <stdint.h>
#include "../Includes/Driver/Driver_common.h"

/*******************************************************************************
 * Header guard
 ******************************************************************************/

#ifndef _DRIVER_SIM_H_
#define _DRIVER_SIM_H_

/*******************************************************************************
 * Enum
 ******************************************************************************/

/**
 * @brief Reference the state of the clock gate.
 */
typedef enum clock_gate_state
{
    DISABLED = 0u, /*Clock gate is disabled*/
    ENABLED = 1u,  /*Clock gate is enabled*/
} clock_gate_state_enum_t;

/**
 * @brief Reference the UART0 clock source options.
 */
typedef enum UART0SRC_option
{
    CLOCK_DISABLED = 0u,                 /*Clock for UART0 is disabled*/
    MCGFLLCLK_HALF_MCGPLLCLK_CLOCK = 1u, /*Clock for UART0 is MCGFLLCLK or (MCGPLLCLK clock / 2)*/
    OSCERCLK_CLOCK = 2u,                 /*Clock for UART0 is OSCERCLK clock*/
    MCGIRCLK_CLOCK = 3u,                 /*Clock for UART0 is MCGIRCLK clock*/
} UART0SRC_option_enum_t;

/**
 * @brief Reference the MCGFLLCLK or MCGPLLCLK/2 options.
 */
typedef enum PLLFLLSEL_option
{
    MCGFLLCLK_CLOCK_SELECTED = 0u,      /*Clock for various peripheral is MCGFLLCLK clock*/
    HALF_MCGPLLCLK_CLOCK_SELECTED = 1u, /*Clock for various peripheral is MGPLLCLK clock*/
} PLLFLLSEL_option_enum_T;

/*******************************************************************************
 * Struct
 ******************************************************************************/

/**
 * @brief Contain the information about the SOPT2 configuration.
 */
typedef struct SOPT2_config
{
    UART0SRC_option_enum_t uart0_clock_source;
    PLLFLLSEL_option_enum_T MCGPLLCLK_MCGFLLCLK_option;
} SOPT2_config_info;

/**
 * @brief Contain the infomation of the SCGC4 configuration.
 */
typedef struct SCGC4_config
{
    clock_gate_state_enum_t UART0_clock_gate; /*UART0 clock gate status*/
} SCGC4_config_info;

/**
 * @brief Contain the infomation of the SCGC5 configuration.
 */
typedef struct SCGC5_config
{
    clock_gate_state_enum_t PORTA_clock; /*PORTA clock gate status*/
    clock_gate_state_enum_t PORTB_clock; /*PORTB clock gate status*/
    clock_gate_state_enum_t PORTC_clock; /*PORTC clock gate status*/
    clock_gate_state_enum_t PORTD_clock; /*PORTD clock gate status*/
    clock_gate_state_enum_t PORTE_clock; /*PORTE clock gate status*/
} SCGC5_config_info;

/**
 * @brief Contain the infomation of the SCGC6 configuration.
 */
typedef struct SCGC6_config
{
    clock_gate_state_enum_t ADC0_clock; /*ADC0 clock gate status*/
    clock_gate_state_enum_t PIT_clock;  /*PIT clock gate status*/
} SCGC6_config_info;

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Init the SOPT2 register to select FLL or PLL clock source for peripherals.
 *
 * @param SOPT2_config is a struct pointer that has the information about the SOPT2 configuration.
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SOPT2_init(SOPT2_config_info *SOPT2_config);

/**
 * @brief Select clock source for UART0
 *
 * @param clock_source is the type of clock source supplied for UART0
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SOPT2_select_UART0_clock(UART0SRC_option_enum_t clock_source);

/**
 * @brief Select if the clock source for peripherals are MCGFLLCLK or MCGPLLCLK/2
 *
 * @param FLL_PLL_option is the option between MCFGLLCLK or MCGPLLCLK/2
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SOPT2_select_FLL_PLL(PLLFLLSEL_option_enum_T FLL_PLL_option);

/**
 * @brief Init the SCGC4_config register to set clock gate control for UART0
 *
 * @param SCGC4_config is a struct pointer that has the information about the SCGC4 configuration.
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SCGC4_init_clock(SCGC4_config_info *SCGC4_config);

/**
 * @brief Set clock gate control for UART0 clock gate
 *
 * @param uart0_cock_gate is the state of the UART0 clock gate.
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SCGC4_set_UART0_clock_gate(clock_gate_state_enum_t uart0_clock_gate);

/**
 * @brief Init the SCGC5 register to control clock gate in SCGC5.
 *
 * @param SCGC5_clock_config has the configuration information of the SCGC5.
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SCGC5_init_clock(SCGC5_config_info *SCGC5_clock_config);

/**
 * @brief Init the SCGC6 register to control clock gate in SCGC6.
 *
 * @param SCGC6_clock_config has the configuration information of the SCGC6.
 *
 * @return: This function return nothing.
 */
void Driver_SIM_SCGC5_set_PORTn_clock_gate(Port_type_enum_t port, clock_gate_state_enum_t PORTn_gate);

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
/*EOF*/
