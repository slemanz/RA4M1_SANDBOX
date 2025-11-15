#include "driver_clock.h"

uint32_t clock_system_value = 0;

void clock_init(void)
{
    MMIO16(REG_PRCR_ADDRESS) = (PRCR_KEY_CODE | 1); // enable write to clock

    MMIO8(REG_HOCOCR_ADDRESS) = 0;  // should be already zero
    MMIO8(REG_MEMWAIT_ADDRESS) = 1; // clock > 32MHz

    // switch to HOCO
    MMIO8(REG_SCKSCR_ADDRESS) = 0;

    /*
        ICK = 48MHz
        FCK = 24MHz
        PCKA = 48MHz
        PCKB = 24MHz
        PCKC = 48MHz
        PCKD = 48MHz 
    */
    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x7 << SCKDIVCR_ICK_OFFSET);

    MMIO32(REG_SCKDIVCR_ADDRESS) |=  (0x1 << SCKDIVCR_FCK_OFFSET);
    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x6 << SCKDIVCR_FCK_OFFSET);

    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x7 << SCKDIVCR_PCKA_OFFSET);

    MMIO32(REG_SCKDIVCR_ADDRESS) |=  (0x1 << SCKDIVCR_PCKB_OFFSET);
    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x6 << SCKDIVCR_PCKB_OFFSET);

    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x7 << SCKDIVCR_PCKC_OFFSET);

    MMIO32(REG_SCKDIVCR_ADDRESS) &= ~(0x7 << SCKDIVCR_PCKD_OFFSET);

    MMIO16(REG_PRCR_ADDRESS) = (PRCR_KEY_CODE); // disble write to clock

    clock_system_value = 48000000;
}

uint32_t clock_system_get(void)
{
    return clock_system_value;
}
