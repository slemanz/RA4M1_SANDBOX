#include <stdint.h>
#include "ra4m1.h"

#include "driver_gpio.h"


int main(void)
{
    // config pin
    GPIO_PfsweControl(ENABLE);
    MMIO32(0x40040020) |= (1 << 11);
    GPIO_PfsweControl(DISABLE);

    while(1)
    {
        GPIO_ToggleOutputPin(PORT1, GPIO_PIN_NO_11);
        for(uint32_t i = 0; i < 30000; i++) __asm("NOP");
    }
}