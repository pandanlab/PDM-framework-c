#ifndef UNIT_BOOT_H
#define UNIT_BOOT_H

#include <stdint.h>
typedef void (*pFunction)(void);
void jump_application(uint32_t address);

#endif // UNIT_BOOT_H
