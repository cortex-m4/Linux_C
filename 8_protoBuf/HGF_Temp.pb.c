/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.8 at Tue Nov 17 11:51:40 2020. */

#include "HGF_Temp.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t HGF_Temp_StatusReport_fields[4] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, HGF_Temp_StatusReport, Base, Base, &HGF_Temp_BasePush_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_StatusReport, DevInfo, Base, &HGF_Temp_DeviceInfo_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_StatusReport, DevStatus, DevInfo, &HGF_Temp_DeviceStatus_fields),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceParamReport_fields[4] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceParamReport, Base, Base, &HGF_Temp_BasePush_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceParamReport, DevInfo, Base, &HGF_Temp_DeviceInfo_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceParamReport, Param, DevInfo, &HGF_Temp_DeviceParam_fields),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceParamSet_fields[3] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceParamSet, Base, Base, &HGF_Temp_BaseRequest_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceParamSet, Param, Base, &HGF_Temp_DeviceParam_fields),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceControl_fields[4] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceControl, Base, Base, &HGF_Temp_BaseRequest_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceControl, DevCtrl, Base, &HGF_Temp_DeviceCtrl_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceControl, Cmd, DevCtrl, &HGF_Temp_PlatCmd_fields),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_BaseRequest_fields[4] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, HGF_Temp_BaseRequest, DeviceId, DeviceId, 0),
    PB_FIELD(  2, UINT32  , SINGULAR, STATIC  , OTHER, HGF_Temp_BaseRequest, Timestamp, DeviceId, 0),
    PB_FIELD(  3, BOOL    , SINGULAR, STATIC  , OTHER, HGF_Temp_BaseRequest, NeedResp, Timestamp, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_BaseResponse_fields[4] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, HGF_Temp_BaseResponse, DeviceId, DeviceId, 0),
    PB_FIELD(  2, UINT32  , SINGULAR, STATIC  , OTHER, HGF_Temp_BaseResponse, Timestamp, DeviceId, 0),
    PB_FIELD(  3, UENUM   , SINGULAR, STATIC  , OTHER, HGF_Temp_BaseResponse, ErrCode, Timestamp, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_BasePush_fields[3] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, HGF_Temp_BasePush, DeviceId, DeviceId, 0),
    PB_FIELD(  2, UINT32  , SINGULAR, STATIC  , OTHER, HGF_Temp_BasePush, Timestamp, DeviceId, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceStatus_fields[15] = {
    PB_FIELD(  1, UINT32  , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceStatus, IntelnetType, IntelnetType, 0),
    PB_FIELD(  2, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceStatus, LanIpAddr, IntelnetType, 0),
    PB_FIELD(  3, INT32   , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, Signal4G, LanIpAddr, 0),
    PB_FIELD(  4, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, Plc, Signal4G, &HGF_Temp_PlcStatus_fields),
    PB_FIELD(  5, UINT32  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, warning, Plc, 0),
    PB_FIELD(  6, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp1, warning, 0),
    PB_FIELD(  7, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp2, temp1, 0),
    PB_FIELD(  8, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp3, temp2, 0),
    PB_FIELD(  9, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp4, temp3, 0),
    PB_FIELD( 10, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp5, temp4, 0),
    PB_FIELD( 11, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp6, temp5, 0),
    PB_FIELD( 12, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp7, temp6, 0),
    PB_FIELD( 13, DOUBLE  , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceStatus, temp8, temp7, 0),
    PB_FIELD( 14, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceStatus, car_num, temp8, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_PlcStatus_fields[3] = {
    PB_FIELD(  1, UINT32  , SINGULAR, STATIC  , FIRST, HGF_Temp_PlcStatus, Link, Link, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, HGF_Temp_PlcStatus, run, Link, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceParam_fields[3] = {
    PB_FIELD(  1, UINT32  , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceParam, ReportPeriod, ReportPeriod, 0),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, HGF_Temp_DeviceParam, PlcWriteReg, ReportPeriod, &HGF_Temp_PlcParam_fields),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_PlcParam_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, HGF_Temp_PlcParam, MotorState, MotorState, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceInfo_fields[7] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, HGF_Temp_DeviceInfo, HwVersion, HwVersion, 0),
    PB_FIELD(  2, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceInfo, FwVersion, HwVersion, 0),
    PB_FIELD(  3, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceInfo, BootVersion, FwVersion, 0),
    PB_FIELD(  4, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceInfo, IMEI, BootVersion, 0),
    PB_FIELD(  5, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceInfo, SimIMSI, IMEI, 0),
    PB_FIELD(  6, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_DeviceInfo, SimICCID, SimIMSI, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_DeviceCtrl_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, HGF_Temp_DeviceCtrl, open, open, 0),
    PB_LAST_FIELD
};

const pb_field_t HGF_Temp_PlatCmd_fields[6] = {
    PB_FIELD(  1, BOOL    , SINGULAR, STATIC  , FIRST, HGF_Temp_PlatCmd, DevReboot, DevReboot, 0),
    PB_FIELD(  2, BOOL    , SINGULAR, STATIC  , OTHER, HGF_Temp_PlatCmd, FactorySetting, DevReboot, 0),
    PB_FIELD(  3, STRING  , SINGULAR, CALLBACK, OTHER, HGF_Temp_PlatCmd, DownloadURL, FactorySetting, 0),
    PB_FIELD(  4, BOOL    , SINGULAR, STATIC  , OTHER, HGF_Temp_PlatCmd, UploadParam, DownloadURL, 0),
    PB_FIELD(  5, BOOL    , SINGULAR, STATIC  , OTHER, HGF_Temp_PlatCmd, UploadState, UploadParam, 0),
    PB_LAST_FIELD
};





/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(HGF_Temp_StatusReport, Base) < 65536 && pb_membersize(HGF_Temp_StatusReport, DevInfo) < 65536 && pb_membersize(HGF_Temp_StatusReport, DevStatus) < 65536 && pb_membersize(HGF_Temp_DeviceParamReport, Base) < 65536 && pb_membersize(HGF_Temp_DeviceParamReport, DevInfo) < 65536 && pb_membersize(HGF_Temp_DeviceParamReport, Param) < 65536 && pb_membersize(HGF_Temp_DeviceParamSet, Base) < 65536 && pb_membersize(HGF_Temp_DeviceParamSet, Param) < 65536 && pb_membersize(HGF_Temp_DeviceControl, Base) < 65536 && pb_membersize(HGF_Temp_DeviceControl, DevCtrl) < 65536 && pb_membersize(HGF_Temp_DeviceControl, Cmd) < 65536 && pb_membersize(HGF_Temp_DeviceStatus, Plc) < 65536 && pb_membersize(HGF_Temp_DeviceParam, PlcWriteReg) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_HGF_Temp_StatusReport_HGF_Temp_DeviceParamReport_HGF_Temp_DeviceParamSet_HGF_Temp_DeviceControl_HGF_Temp_BaseRequest_HGF_Temp_BaseResponse_HGF_Temp_BasePush_HGF_Temp_DeviceStatus_HGF_Temp_PlcStatus_HGF_Temp_DeviceParam_HGF_Temp_PlcParam_HGF_Temp_DeviceInfo_HGF_Temp_DeviceCtrl_HGF_Temp_PlatCmd)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(HGF_Temp_StatusReport, Base) < 256 && pb_membersize(HGF_Temp_StatusReport, DevInfo) < 256 && pb_membersize(HGF_Temp_StatusReport, DevStatus) < 256 && pb_membersize(HGF_Temp_DeviceParamReport, Base) < 256 && pb_membersize(HGF_Temp_DeviceParamReport, DevInfo) < 256 && pb_membersize(HGF_Temp_DeviceParamReport, Param) < 256 && pb_membersize(HGF_Temp_DeviceParamSet, Base) < 256 && pb_membersize(HGF_Temp_DeviceParamSet, Param) < 256 && pb_membersize(HGF_Temp_DeviceControl, Base) < 256 && pb_membersize(HGF_Temp_DeviceControl, DevCtrl) < 256 && pb_membersize(HGF_Temp_DeviceControl, Cmd) < 256 && pb_membersize(HGF_Temp_DeviceStatus, Plc) < 256 && pb_membersize(HGF_Temp_DeviceParam, PlcWriteReg) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_HGF_Temp_StatusReport_HGF_Temp_DeviceParamReport_HGF_Temp_DeviceParamSet_HGF_Temp_DeviceControl_HGF_Temp_BaseRequest_HGF_Temp_BaseResponse_HGF_Temp_BasePush_HGF_Temp_DeviceStatus_HGF_Temp_PlcStatus_HGF_Temp_DeviceParam_HGF_Temp_PlcParam_HGF_Temp_DeviceInfo_HGF_Temp_DeviceCtrl_HGF_Temp_PlatCmd)
#endif


/* On some platforms (such as AVR), double is really float.
 * These are not directly supported by nanopb, but see example_avr_double.
 * To get rid of this error, remove any double fields from your .proto.
 */
PB_STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)

/* @@protoc_insertion_point(eof) */