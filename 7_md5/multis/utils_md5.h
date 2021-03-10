/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*                                                 */
/*         ����Ѱ�ҵĿ�Դ���򣬹���md5             */
/*                                                 */
/*-------------------------------------------------*/

#ifndef UTILS_MD5_H_
#define UTILS_MD5_H_

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[4];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
} iot_md5_context;


 /**
 * @brief ��ʼ��MD5������
 *
 * @param ctx   MD5������ָ��
 */
void utils_md5_init(iot_md5_context *ctx);

/**
 * @brief ���MD5������
 *
 * @param ctx   MD5������ָ��
 */
void utils_md5_free(iot_md5_context *ctx);

/**
 * @brief ����MD5������
 *
 * @param dst   Ŀ��MD5������
 * @param src   ԴMD5������
 */
void utils_md5_clone(iot_md5_context *dst,
                     const iot_md5_context *src);

/**
 * @brief ����MD5������
 *
 * @param ctx   MD5������ָ��
 */
void utils_md5_starts(iot_md5_context *ctx);

/**
 * @brief MD5���̻�����
 *
 * @param ctx MD5������ָ��
 * @param input    ��������
 * @param ilen     �������ݳ���
 */
void utils_md5_update(iot_md5_context *ctx, const unsigned char *input, size_t ilen);

/**
 * @brief          MD5����
 *
 * @param ctx      MD5������ָ��
 * @param output   MD5У��ͽ��
 */
void utils_md5_finish(iot_md5_context *ctx, unsigned char output[16]);

/* �ڲ�ʹ�� */
void utils_md5_process(iot_md5_context *ctx, const unsigned char data[64]);

/**
 * @brief          Output = MD5( input buffer )
 *
 * @param input    ��������
 * @param ilen     �������ݳ���
 * @param output   MD5У��ͽ��
 */
void utils_md5(const unsigned char *input, size_t ilen, unsigned char output[16]);


int8_t utils_hb2hex(uint8_t hb);


#endif

