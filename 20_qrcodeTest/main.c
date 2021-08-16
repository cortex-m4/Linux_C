#include "stdio.h"
#include "qrcode.h"
#define DEFAULT_QR_VERSION 3
#define DEFAULT_QR_STRING "HELLO WORLD"


int main(uint8_t argc, char **argv)
{

    QRCode qrc;
    uint8_t x, y, *qrcodeBytes = (uint8_t *)rt_calloc(1, qrcode_getBufferSize(DEFAULT_QR_VERSION));
    int8_t result;
    char *qrstr = DEFAULT_QR_STRING;

    if (qrcodeBytes)
    {
        if (argc > 1)
        {
            qrstr = argv[1];
        }

        result = qrcode_initText(&qrc, qrcodeBytes, DEFAULT_QR_VERSION, ECC_LOW, qrstr);

        if (result >= 0)
        {
            printf("\n");
            for (y = 0; y < qrc.size; y++)
            {
                for (x = 0; x < qrc.size; x++)
                {
                    if (qrcode_getModule(&qrc, x, y))
                    {
                        printf("**");
                    }
                    else
                    {
                        printf("  ");
                    }
                }
                printf("\n");
            }
        }
        else
        {
            printf("QR CODE(%s) General FAILED(%d)\n", qrstr, result);
        }
        free(qrcodeBytes);
    }
    else
    {
        printf("Warning: no memory!\n");
    }
}