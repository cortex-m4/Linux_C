#include "user_proto.h"
#include "stdio.h"

unsigned char pb_buffer[1024];
uint16_t pb_message_length;
bool status;
HGF_Temp_DeviceStatus _hgf_temp_status_unpack;
void encode_buffer(void){
	HGF_Temp_DeviceStatus _hgf_temp_status_pakage=HGF_Temp_DeviceStatus_init_zero;
	pb_ostream_t data_stream;
	printf("creat hgf pakage\r\n");
	printf("creat data_stream\r\n");
	_hgf_temp_status_pakage.temp1=30;
	_hgf_temp_status_pakage.temp2=40;
	_hgf_temp_status_pakage.temp3=50;
	_hgf_temp_status_pakage.alarmTemp=60;
	_hgf_temp_status_pakage.targetTemp=70;
	_hgf_temp_status_pakage.refTemp=80;
	_hgf_temp_status_pakage.settingTime=90;
	_hgf_temp_status_pakage.realHotTimeMin=100;
	strcpy(_hgf_temp_status_pakage.nowCarNum,"123123");
	
	printf("load pakage data\r\n");
	memset(pb_buffer, 0, sizeof(pb_buffer));
	printf("set buffer data\r\n");
	data_stream = pb_ostream_from_buffer(pb_buffer, sizeof(pb_buffer));
	printf("pb stream from buffer\r\n");
	status = pb_encode(&data_stream, HGF_Temp_DeviceStatus_fields, &_hgf_temp_status_pakage);
	printf("pb encode\r\n");
	pb_message_length= data_stream.bytes_written;
	
}

void decode_buffer(void){
	pb_istream_t stream ;
	
	stream= pb_istream_from_buffer(pb_buffer, pb_message_length);
	status = pb_decode(&stream, HGF_Temp_DeviceStatus_fields, &_hgf_temp_status_unpack);
}

