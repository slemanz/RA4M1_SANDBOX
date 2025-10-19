#include "driver_gpio.h"

void GPIO_PfsweControl(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        MMIO8(PWPR_BASEADDR) |= GPIO_PFSWE_MASK;
    }else
    {
        MMIO8(PWPR_BASEADDR) &= ~GPIO_PFSWE_MASK;
    }
}

void GPIO_WriteToOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber, uint8_t value)
{
    if(value == GPIO_SET)
    {
        pPORTx->PCNTR1 |= (1U << (PinNumber + 16));
    }else
    {
        pPORTx->PCNTR1 &= ~(1U << (PinNumber + 16));
    }
}

void GPIO_ToggleOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber)
{
    pPORTx->PCNTR1 ^= (1U << (PinNumber + 16));
}