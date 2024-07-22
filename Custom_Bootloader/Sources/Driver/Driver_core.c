#include "../Includes/Driver/Driver_core.h"
#include "MKL46Z4.h"

void Driver_Disable_current_IRQs(void)
{
    __disable_irq();

    return;
}

void Driver_Enable_current_IRQs(void)
{
    __enable_irq();

    return;
}

void Driver_Set_MSP(uint32_t MSP_value)
{
    __set_MSP(MSP_value);

    return;
}

void Driver_Set_PSP(uint32_t PSP_value)
{
    __set_PSP(PSP_value);

    return;
}

void Driver_Set_VectorTable_offset(uint32_t offset_value)
{
    if (offset_value % 256 == 0)
    {
        SCB->VTOR = offset_value;
    }
    else
    {
        /*Do nothing*/
    }

    return;
}
/*EOF*/
