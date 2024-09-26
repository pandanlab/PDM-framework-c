#include "unit_boot.h"

void jump_application(uint32_t address) {
    uint32_t *appStartAddr = (uint32_t *)(address+4);
    pFunction appEntry;
    appEntry = (pFunction)(*appStartAddr);
    appEntry();
}
