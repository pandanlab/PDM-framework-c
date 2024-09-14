#ifndef UNIT_BOOT_H
#define UNIT_BOOT_H

#include <stdint.h>
#define APPLICATION_ADDRESS 0x08001004;
typedef void (*pFunction)(void);
void jump_application(void);

#endif // UNIT_BOOT_H
