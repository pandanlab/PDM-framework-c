#include "unit_boot.h"

void jump_application(void) {
    uint32_t *appStartAddr = (uint32_t *)APPLICATION_ADDRESS;
    pFunction appEntry;
    appEntry = (pFunction)(*appStartAddr);
    appEntry();
}
