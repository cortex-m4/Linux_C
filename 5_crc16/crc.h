#ifndef _CRC_H_
#define _CRC_H_

#include <stdint.h>

uint16_t Crc16(uint8_t *ptr, uint32_t len);

#define HIG_UINT16(a)   ( ((a)>>8) & 0xFF )
#define LOW_UINT16(a)   ( (a) & 0xFF )

#define HIG_UINT8(a)    ( ((a)>>4) & 0x0F )
#define LOW_UINT8(a)    ( (a) & 0x0F )

#endif  /* crc.h */
