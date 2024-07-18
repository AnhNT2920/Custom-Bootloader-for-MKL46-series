/**
 * @file  : HAL_UART0.h
 * @author: Nguyen The Anh.
 * @brief : Declare enum and function using in HAL_UART0.c.
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

#ifndef _HAL_UART0_H_
#define _HAL_UART0_H_

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* ----------------------------------------------------------------------------
   -- UART0_BDH register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Set value for 5 bits high of baud rate modulo divisor
 *
 * @param baud_rate_divisor is the value of baud rate divisor.
 *
 * @return: this function return nothing.
 */
void HAL_UART0_BDH_set_SBR(uint16_t baud_rate_divisor);

/**
 * @brief Select stop bit count for UART0
 *
 * @param SBNS_value is the state to write to SBNS bit field of BDH register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_BDH_set_SBNS(uint8_t SBNS_value);

/*!
 * @}
 */
/* end of group UART0_BDH register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_BDL register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Set value for 8 bits lows of baud rate modulo divisor
 *
 * @param baud_rate_divisor is the value of baud rate divisor.
 *
 * @return: this function return nothing.
 */
void HAL_UART0_BDL_set_SBR(uint16_t baud_rate_divisor);

/*!
 * @}
 */
/* end of group UART0_BDH register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C1 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select whether data length is 8 bits or 9 bits
 *
 * @param M_value is the state to write to M bit field in C1 (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C1_set_M(uint8_t M_value);

/**
 * @brief Select whether parity is enabled or disabled.
 *
 * @param PE_value is the state to write to PE bit field in C1 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C1_set_PE(uint8_t PE_value);

/**
 * @brief Select whether parity is Odd parity or Even parity
 *
 * @param PT_value is the state to write to PT bit field in C1 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C1_set_PT(uint8_t PT_value);

/*!
 * @}
 */
/* end of group UART0_C1 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C2 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Select whether transmit interrupt request is disabled or enabled
 *
 * @param TIE_value is the state to write to TIE bit field in C2 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C2_set_TIE(uint8_t TIE_value);

/**
 * @brief Select whether receive interrupt request is disabled or enabled
 *
 * @param RIE_value is the state to write to RIE bit field in C2 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C2_set_RIE(uint8_t RIE_value);

/**
 * @brief Select whether transmitter is disabled or enabled
 *
 * @param TE_value is the state to write to TE bit field in C2 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C2_set_TE(uint8_t TE_value);

/**
 * @brief Select whether receiver is disabled or enabled
 *
 * @param RE_value is the state to write to RE bit field in C2 register (0 / 1).
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C2_set_RE(uint8_t RE_value);

/*!
 * @}
 */
/* end of group UART0_C2 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_C4 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Set oversampling ratio for UART0
 *
 * @param OSR_value is the value to write to OSR bit field in C4 register.
 *
 * @return: this function return nothing.
 */
void HAL_UART0_C4_set_OSR(uint8_t OSR_value);

/*!
 * @}
 */
/* end of group UART0_C4 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_S1 register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Read the transmit data register empty flag (ready to send data)
 *
 * @param: This function has no parameter.
 *
 * @return the state of the TDRE flag.
 */
uint8_t HAL_UART0_S1_read_TDRE(void);

/**
 * @brief Read the receive data register full flag (ready to get data)
 *
 * @param: This function has no parameter.
 *
 * @return the state of the RDRF flag.
 */
uint8_t HAL_UART0_S1_read_RDRF(void);

/*!
 * @}
 */
/* end of group UART0_S1 register bit setting functions */

/* ----------------------------------------------------------------------------
   -- UART0_D register bit setting function group
   ---------------------------------------------------------------------------- */

/**
 * @brief Write data to the data register to send data
 *
 * @param data is the data need to be sent by UART
 *
 * @return: This function return nothing.
 */
void HAL_UART0_D_write_data(uint8_t data);

/**
 * @brief Read data from the data register.
 *
 * @param: This function has no parameter.
 *
 * @return: This function return nothing.
 */
uint8_t HAL_UART0_D_read_data(void);

/*!
 * @}
 */
/* end of group UART0_D register bit setting functions */

/*******************************************************************************
 * End of header guard
 ******************************************************************************/
#endif
/*EOF*/
