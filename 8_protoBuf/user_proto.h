#ifndef	__USER_PROTO_H__
#define __USER_PROTO_H__

#include "HGF_Temp.pb.h"
#include "user_proto.h"
#include "pb_decode.h"
#include "pb_encode.h"


extern unsigned char pb_buffer[1024];

extern HGF_Temp_DeviceStatus _hgf_temp_status_unpack;

void encode_buffer(void);
void decode_buffer(void);

#endif
