/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.8 at Tue Nov 17 11:51:40 2020. */

#ifndef PB_HGF_TEMP_HGF_TEMP_PB_H_INCLUDED
#define PB_HGF_TEMP_HGF_TEMP_PB_H_INCLUDED
#include "pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _HGF_Temp_EmCmdId {
    HGF_Temp_EmCmdId_CMD_NONE = 0,
    HGF_Temp_EmCmdId_STATUS_REPORT = 1001,
    HGF_Temp_EmCmdId_PARAM_REPORT = 1002,
    HGF_Temp_EmCmdId_PARAM_CONFIG = 2001,
    HGF_Temp_EmCmdId_DEVICE_CONTROL = 2002
} HGF_Temp_EmCmdId;
#define _HGF_Temp_EmCmdId_MIN HGF_Temp_EmCmdId_CMD_NONE
#define _HGF_Temp_EmCmdId_MAX HGF_Temp_EmCmdId_DEVICE_CONTROL
#define _HGF_Temp_EmCmdId_ARRAYSIZE ((HGF_Temp_EmCmdId)(HGF_Temp_EmCmdId_DEVICE_CONTROL+1))

typedef enum _HGF_Temp_EmErrorCode {
    HGF_Temp_EmErrorCode_ERR_NONE = 0,
    HGF_Temp_EmErrorCode_CMD_ID = 1,
    HGF_Temp_EmErrorCode_CRC_CHECK = 2,
    HGF_Temp_EmErrorCode_PARSER = 3
} HGF_Temp_EmErrorCode;
#define _HGF_Temp_EmErrorCode_MIN HGF_Temp_EmErrorCode_ERR_NONE
#define _HGF_Temp_EmErrorCode_MAX HGF_Temp_EmErrorCode_PARSER
#define _HGF_Temp_EmErrorCode_ARRAYSIZE ((HGF_Temp_EmErrorCode)(HGF_Temp_EmErrorCode_PARSER+1))

typedef enum _HGF_Temp_EmFaultCode {
    HGF_Temp_EmFaultCode_FAULT_NONE = 0,
    HGF_Temp_EmFaultCode_FAULTY = 1,
    HGF_Temp_EmFaultCode_START = 2,
    HGF_Temp_EmFaultCode_HIGH_TEMP = 3,
    HGF_Temp_EmFaultCode_LOW_TEMP = 4,
    HGF_Temp_EmFaultCode_COMMCARDFAULT = 5,
    HGF_Temp_EmFaultCode_OVERCURRENT = 6,
    HGF_Temp_EmFaultCode_SHORT_CIRCUIT = 7,
    HGF_Temp_EmFaultCode_NOT_DETECTED = 8
} HGF_Temp_EmFaultCode;
#define _HGF_Temp_EmFaultCode_MIN HGF_Temp_EmFaultCode_FAULT_NONE
#define _HGF_Temp_EmFaultCode_MAX HGF_Temp_EmFaultCode_NOT_DETECTED
#define _HGF_Temp_EmFaultCode_ARRAYSIZE ((HGF_Temp_EmFaultCode)(HGF_Temp_EmFaultCode_NOT_DETECTED+1))

/* Struct definitions */
typedef struct _HGF_Temp_DeviceInfo {
    pb_callback_t HwVersion;
    pb_callback_t FwVersion;
    pb_callback_t BootVersion;
    pb_callback_t IMEI;
    pb_callback_t SimIMSI;
    pb_callback_t SimICCID;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceInfo) */
} HGF_Temp_DeviceInfo;

typedef struct _HGF_Temp_BasePush {
    pb_callback_t DeviceId;
    uint32_t Timestamp;
/* @@protoc_insertion_point(struct:HGF_Temp_BasePush) */
} HGF_Temp_BasePush;

typedef struct _HGF_Temp_BaseRequest {
    pb_callback_t DeviceId;
    uint32_t Timestamp;
    bool NeedResp;
/* @@protoc_insertion_point(struct:HGF_Temp_BaseRequest) */
} HGF_Temp_BaseRequest;

typedef struct _HGF_Temp_BaseResponse {
    pb_callback_t DeviceId;
    uint32_t Timestamp;
    HGF_Temp_EmErrorCode ErrCode;
/* @@protoc_insertion_point(struct:HGF_Temp_BaseResponse) */
} HGF_Temp_BaseResponse;

typedef struct _HGF_Temp_DeviceCtrl {
    int32_t open;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceCtrl) */
} HGF_Temp_DeviceCtrl;

typedef struct _HGF_Temp_PlatCmd {
    bool DevReboot;
    bool FactorySetting;
    pb_callback_t DownloadURL;
    bool UploadParam;
    bool UploadState;
/* @@protoc_insertion_point(struct:HGF_Temp_PlatCmd) */
} HGF_Temp_PlatCmd;

typedef struct _HGF_Temp_PlcParam {
    int32_t MotorState;
/* @@protoc_insertion_point(struct:HGF_Temp_PlcParam) */
} HGF_Temp_PlcParam;

typedef struct _HGF_Temp_PlcStatus {
    uint32_t Link;
    int32_t run;
/* @@protoc_insertion_point(struct:HGF_Temp_PlcStatus) */
} HGF_Temp_PlcStatus;

typedef struct _HGF_Temp_DeviceControl {
    HGF_Temp_BaseRequest Base;
    HGF_Temp_DeviceCtrl DevCtrl;
    HGF_Temp_PlatCmd Cmd;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceControl) */
} HGF_Temp_DeviceControl;

typedef struct _HGF_Temp_DeviceParam {
    uint32_t ReportPeriod;
    HGF_Temp_PlcParam PlcWriteReg;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceParam) */
} HGF_Temp_DeviceParam;

typedef struct _HGF_Temp_DeviceStatus {
    uint32_t IntelnetType;
    pb_callback_t LanIpAddr;
    int32_t Signal4G;
    HGF_Temp_PlcStatus Plc;
    uint32_t warning;
    double temp1;
    double temp2;
    double temp3;
    double temp4;
    double temp5;
    double temp6;
    double temp7;
    double temp8;
    pb_callback_t car_num;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceStatus) */
} HGF_Temp_DeviceStatus;

typedef struct _HGF_Temp_DeviceParamReport {
    HGF_Temp_BasePush Base;
    HGF_Temp_DeviceInfo DevInfo;
    HGF_Temp_DeviceParam Param;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceParamReport) */
} HGF_Temp_DeviceParamReport;

typedef struct _HGF_Temp_DeviceParamSet {
    HGF_Temp_BaseRequest Base;
    HGF_Temp_DeviceParam Param;
/* @@protoc_insertion_point(struct:HGF_Temp_DeviceParamSet) */
} HGF_Temp_DeviceParamSet;

typedef struct _HGF_Temp_StatusReport {
    HGF_Temp_BasePush Base;
    HGF_Temp_DeviceInfo DevInfo;
    HGF_Temp_DeviceStatus DevStatus;
/* @@protoc_insertion_point(struct:HGF_Temp_StatusReport) */
} HGF_Temp_StatusReport;

/* Default values for struct fields */

/* Initializer values for message structs */
#define HGF_Temp_StatusReport_init_default       {HGF_Temp_BasePush_init_default, HGF_Temp_DeviceInfo_init_default, HGF_Temp_DeviceStatus_init_default}
#define HGF_Temp_DeviceParamReport_init_default  {HGF_Temp_BasePush_init_default, HGF_Temp_DeviceInfo_init_default, HGF_Temp_DeviceParam_init_default}
#define HGF_Temp_DeviceParamSet_init_default     {HGF_Temp_BaseRequest_init_default, HGF_Temp_DeviceParam_init_default}
#define HGF_Temp_DeviceControl_init_default      {HGF_Temp_BaseRequest_init_default, HGF_Temp_DeviceCtrl_init_default, HGF_Temp_PlatCmd_init_default}
#define HGF_Temp_BaseRequest_init_default        {{{NULL}, NULL}, 0, 0}
#define HGF_Temp_BaseResponse_init_default       {{{NULL}, NULL}, 0, (HGF_Temp_EmErrorCode)0}
#define HGF_Temp_BasePush_init_default           {{{NULL}, NULL}, 0}
#define HGF_Temp_DeviceStatus_init_default       {0, {{NULL}, NULL}, 0, HGF_Temp_PlcStatus_init_default, 0, 0, 0, 0, 0, 0, 0, 0, 0, {{NULL}, NULL}}
#define HGF_Temp_PlcStatus_init_default          {0, 0}
#define HGF_Temp_DeviceParam_init_default        {0, HGF_Temp_PlcParam_init_default}
#define HGF_Temp_PlcParam_init_default           {0}
#define HGF_Temp_DeviceInfo_init_default         {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define HGF_Temp_DeviceCtrl_init_default         {0}
#define HGF_Temp_PlatCmd_init_default            {0, 0, {{NULL}, NULL}, 0, 0}
#define HGF_Temp_StatusReport_init_zero          {HGF_Temp_BasePush_init_zero, HGF_Temp_DeviceInfo_init_zero, HGF_Temp_DeviceStatus_init_zero}
#define HGF_Temp_DeviceParamReport_init_zero     {HGF_Temp_BasePush_init_zero, HGF_Temp_DeviceInfo_init_zero, HGF_Temp_DeviceParam_init_zero}
#define HGF_Temp_DeviceParamSet_init_zero        {HGF_Temp_BaseRequest_init_zero, HGF_Temp_DeviceParam_init_zero}
#define HGF_Temp_DeviceControl_init_zero         {HGF_Temp_BaseRequest_init_zero, HGF_Temp_DeviceCtrl_init_zero, HGF_Temp_PlatCmd_init_zero}
#define HGF_Temp_BaseRequest_init_zero           {{{NULL}, NULL}, 0, 0}
#define HGF_Temp_BaseResponse_init_zero          {{{NULL}, NULL}, 0, (HGF_Temp_EmErrorCode)0}
#define HGF_Temp_BasePush_init_zero              {{{NULL}, NULL}, 0}
#define HGF_Temp_DeviceStatus_init_zero          {0, {{NULL}, NULL}, 0, HGF_Temp_PlcStatus_init_zero, 0, 0, 0, 0, 0, 0, 0, 0, 0, {{NULL}, NULL}}
#define HGF_Temp_PlcStatus_init_zero             {0, 0}
#define HGF_Temp_DeviceParam_init_zero           {0, HGF_Temp_PlcParam_init_zero}
#define HGF_Temp_PlcParam_init_zero              {0}
#define HGF_Temp_DeviceInfo_init_zero            {{{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define HGF_Temp_DeviceCtrl_init_zero            {0}
#define HGF_Temp_PlatCmd_init_zero               {0, 0, {{NULL}, NULL}, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define HGF_Temp_DeviceInfo_HwVersion_tag        1
#define HGF_Temp_DeviceInfo_FwVersion_tag        2
#define HGF_Temp_DeviceInfo_BootVersion_tag      3
#define HGF_Temp_DeviceInfo_IMEI_tag             4
#define HGF_Temp_DeviceInfo_SimIMSI_tag          5
#define HGF_Temp_DeviceInfo_SimICCID_tag         6
#define HGF_Temp_BasePush_DeviceId_tag           1
#define HGF_Temp_BasePush_Timestamp_tag          2
#define HGF_Temp_BaseRequest_DeviceId_tag        1
#define HGF_Temp_BaseRequest_Timestamp_tag       2
#define HGF_Temp_BaseRequest_NeedResp_tag        3
#define HGF_Temp_BaseResponse_DeviceId_tag       1
#define HGF_Temp_BaseResponse_Timestamp_tag      2
#define HGF_Temp_BaseResponse_ErrCode_tag        3
#define HGF_Temp_DeviceCtrl_open_tag             1
#define HGF_Temp_PlatCmd_DevReboot_tag           1
#define HGF_Temp_PlatCmd_FactorySetting_tag      2
#define HGF_Temp_PlatCmd_DownloadURL_tag         3
#define HGF_Temp_PlatCmd_UploadParam_tag         4
#define HGF_Temp_PlatCmd_UploadState_tag         5
#define HGF_Temp_PlcParam_MotorState_tag         1
#define HGF_Temp_PlcStatus_Link_tag              1
#define HGF_Temp_PlcStatus_run_tag               2
#define HGF_Temp_DeviceControl_Base_tag          1
#define HGF_Temp_DeviceControl_DevCtrl_tag       2
#define HGF_Temp_DeviceControl_Cmd_tag           3
#define HGF_Temp_DeviceParam_ReportPeriod_tag    1
#define HGF_Temp_DeviceParam_PlcWriteReg_tag     2
#define HGF_Temp_DeviceStatus_IntelnetType_tag   1
#define HGF_Temp_DeviceStatus_LanIpAddr_tag      2
#define HGF_Temp_DeviceStatus_Signal4G_tag       3
#define HGF_Temp_DeviceStatus_Plc_tag            4
#define HGF_Temp_DeviceStatus_warning_tag        5
#define HGF_Temp_DeviceStatus_temp1_tag          6
#define HGF_Temp_DeviceStatus_temp2_tag          7
#define HGF_Temp_DeviceStatus_temp3_tag          8
#define HGF_Temp_DeviceStatus_temp4_tag          9
#define HGF_Temp_DeviceStatus_temp5_tag          10
#define HGF_Temp_DeviceStatus_temp6_tag          11
#define HGF_Temp_DeviceStatus_temp7_tag          12
#define HGF_Temp_DeviceStatus_temp8_tag          13
#define HGF_Temp_DeviceStatus_car_num_tag        14
#define HGF_Temp_DeviceParamReport_Base_tag      1
#define HGF_Temp_DeviceParamReport_DevInfo_tag   2
#define HGF_Temp_DeviceParamReport_Param_tag     3
#define HGF_Temp_DeviceParamSet_Base_tag         1
#define HGF_Temp_DeviceParamSet_Param_tag        2
#define HGF_Temp_StatusReport_Base_tag           1
#define HGF_Temp_StatusReport_DevInfo_tag        2
#define HGF_Temp_StatusReport_DevStatus_tag      3

/* Struct field encoding specification for nanopb */
extern const pb_field_t HGF_Temp_StatusReport_fields[4];
extern const pb_field_t HGF_Temp_DeviceParamReport_fields[4];
extern const pb_field_t HGF_Temp_DeviceParamSet_fields[3];
extern const pb_field_t HGF_Temp_DeviceControl_fields[4];
extern const pb_field_t HGF_Temp_BaseRequest_fields[4];
extern const pb_field_t HGF_Temp_BaseResponse_fields[4];
extern const pb_field_t HGF_Temp_BasePush_fields[3];
extern const pb_field_t HGF_Temp_DeviceStatus_fields[15];
extern const pb_field_t HGF_Temp_PlcStatus_fields[3];
extern const pb_field_t HGF_Temp_DeviceParam_fields[3];
extern const pb_field_t HGF_Temp_PlcParam_fields[2];
extern const pb_field_t HGF_Temp_DeviceInfo_fields[7];
extern const pb_field_t HGF_Temp_DeviceCtrl_fields[2];
extern const pb_field_t HGF_Temp_PlatCmd_fields[6];

/* Maximum encoded size of messages (where known) */
#define HGF_Temp_StatusReport_size               (18 + HGF_Temp_BasePush_size + HGF_Temp_DeviceInfo_size + HGF_Temp_DeviceStatus_size)
#define HGF_Temp_DeviceParamReport_size          (33 + HGF_Temp_BasePush_size + HGF_Temp_DeviceInfo_size)
#define HGF_Temp_DeviceParamSet_size             (27 + HGF_Temp_BaseRequest_size)
#define HGF_Temp_DeviceControl_size              (25 + HGF_Temp_BaseRequest_size + HGF_Temp_PlatCmd_size)
/* HGF_Temp_BaseRequest_size depends on runtime parameters */
/* HGF_Temp_BaseResponse_size depends on runtime parameters */
/* HGF_Temp_BasePush_size depends on runtime parameters */
/* HGF_Temp_DeviceStatus_size depends on runtime parameters */
#define HGF_Temp_PlcStatus_size                  17
#define HGF_Temp_DeviceParam_size                19
#define HGF_Temp_PlcParam_size                   11
/* HGF_Temp_DeviceInfo_size depends on runtime parameters */
#define HGF_Temp_DeviceCtrl_size                 11
/* HGF_Temp_PlatCmd_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define HGF_TEMP_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif