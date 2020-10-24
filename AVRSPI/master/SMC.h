#ifndef __SMC_H__
#define __SMC_H__

#include <avr/io.h>

#define SMC_NUM_OF_SLOTS				5

void SMC_extScan(void);
uint8_t SMC_extSwitchOn(uint8_t slot);
uint8_t SMC_extQuery(uint8_t slot, uint8_t data);

#endif /* __SMC_H__ */
