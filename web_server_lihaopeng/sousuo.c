#include "head.h"
#include "sqlite3.h"

char ptmpInvert[4096] = {0};
char ResourceFileName[4096] = {0};
char EndHmtlBuff[4096] = {0};
char BeginBuff[4096] = {0};
char EndBuff[4096] = {0};
char InsertBuff[4096] = {0};
char PinBuff[4096] = {0};
char *ppname = NULL;
char *ppcharcter = NULL;
int zhuanhuan(char *str, char *pst)
{
	unsigned char dst[1024] = {0};
	char *ptmp = NULL;
	char *pstr = NULL;
	int num1 = 0;
	int num2 = 0;
	int num = 0;
	int cnt = 0;

	pstr = str;
	ptmp = str;
    //去除%
	while (*ptmp != '\0')
	{
		if (*ptmp != '%')
		{
			*pstr = *ptmp;
			pstr++;
		}
		ptmp++;
	}
	*pstr = '\0';
	printf("str = %s\n", str);

	ptmp = str;
    //hex char -> hex byte 
	while (*ptmp != '\0')
	{
		switch (*ptmp)
		{
		case 'A':num1 = 10;break;
		case 'B':num1 = 11;break;
		case 'C':num1 = 12;break;
		case 'D':num1 = 13;break;
		case 'E':num1 = 14;break;
		case 'F':num1 = 15;break;
		default:
				 num1 = *ptmp - '0';
		}
		ptmp++;
		switch (*ptmp)
		{
		case 'A':num2 = 10;break;
		case 'B':num2 = 11;break;
		case 'C':num2 = 12;break;
		case 'D':num2 = 13;break;
		case 'E':num2 = 14;break;
		case 'F':num2 = 15;break;
		default:
				 num2 = *ptmp - '0';
		}
		ptmp++;
		dst[cnt] = num1 * 16 + num2;
		cnt++;
	}

	strcpy(ptmpInvert, dst);
	return 0;
}

/*
    arg:传入的参数
    num:这一条记录有多少个字段
    pcontent:查出来的数据都保存在这里
    ptitle:查出来的字段字段名称
*/
int callback1(void *arg, int num, char **pcontent, char **ptitle)
{
	char *pmeanbuff = arg;
	char name[32] = {0} ;
	char charcter[256] = {0};
	char attribute[256] = {0};
	char image[256] = {0};
	char price[256] = {0};
	FILE *fp = NULL;
	strcpy(name, pcontent[0]);
	strcpy(charcter, pcontent[1]);
	strcpy(attribute, pcontent[2]);
	strcpy(price, pcontent[3]);
	strcpy(image, pcontent[4]);
	printf("=======================================\n");
	printf("name = %s\n", name);
	printf("charcter = %s\n", charcter);
	printf("attribute = %s\n", attribute);
	printf("price = %s\n", price);
	printf("image = %s\n", image);
	printf("=======================================\n");
	ppname = name;
	ppcharcter = charcter;
#if 0
	fprintf(fp, "<html>\n");
	fprintf(fp, "<head>\n");
	fprintf(fp, "<meta charset=\"utf-8\">\n");	
	fprintf(fp, "<title>%s</title>\n", name);
	fprintf(fp, "</head>\n");
	fprintf(fp, "<body>\n");
	fprintf(fp, "<hr>\n");
	fprintf(fp, "<h1 align=\"center\">\n");
	fprintf(fp, "%s", name);
	fprintf(fp, "</h1>");

	fprintf(fp, "<tr>\n");
	fprintf(fp, "<td>\n");
	fprintf(fp, "<a><img src=\"%s\" width=\"300\" height=\"300\"></a>", image);
	fprintf(fp, "<h5>%s</h5>", attribute);
	
	fprintf(fp, "</td>");
	fprintf(fp, "</tr>");
	fprintf(fp, "</body>\n");
	fprintf(fp, "</html>\n");
#endif
	
	sprintf(BeginBuff, "<html>\n<head>\n<meta charset=\"utf-8\">\n<title>%s</title>\n</head>\n<body bgcolor=\"#A9A9A9\">\n<hr><h1 align=\"right\"\n><font color=\"#0000AA\">腾讯游戏，用心创造快乐！</font><h1>\n", name);
	sprintf(EndBuff, "</body>\n</html>\n");
	sprintf(InsertBuff, "\n<h1 align=\"left\">%s</h1>\n<td>\n<a><img src=\"%s\" width=\"600\" height=\"300\"></a>\n",name, image);
	sprintf(InsertBuff, "%s<h1 align=\"right\"><font color=\"#FF0000\">仅售：%s元</font></h1>\n", InsertBuff, price);
	sprintf(InsertBuff,"%s<h5>%s</h5>\n", InsertBuff, attribute);
	sprintf(InsertBuff, "%s</td>\n", InsertBuff);

	sprintf(PinBuff, "%s%s", PinBuff, InsertBuff);
	printf("0------------------------------------------------------------------0\n");
	printf("PinBuff = %s\n", PinBuff);
	printf("0------------------------------------------------------------------0\n");
//	sprintf(EndHmtlBuff, "%s%s", BeginBuff, InsertBuff);
	return 0;
}

/*
  param1:要搜索的字符串
  param2:数据库名称
  param3:返回的名字
  param4-6:描述 图片 花费 
*/
int FindGunMsg(char *pptmp, const char *pPdbname, char *pcharcter, char *pattribute, char *pimage, int *pprice)
{
	sqlite3 *pdb = NULL;
	int ret = 0;
	char tmpbuff[4096] = {0};
	char *perrmsg = NULL;
	char meanbuff[4096] = {0};
	FILE *fp = NULL;
	ret = sqlite3_open(pPdbname, &pdb);
	if(SQLITE_OK != ret)
	{
		fprintf(stderr, "sqlite3_open pass.db failed!:%s\n", sqlite3_errmsg(pdb));
		return -1;
	}
	printf("pptmp = %s\n", pptmp);                                                                  //  pptmp = 输入
	sprintf(tmpbuff, "select *from qiang where charcter = \"%s\" or name = \"%s\"", pptmp, pptmp);
	ret = sqlite3_exec(pdb, tmpbuff, callback1, meanbuff, &perrmsg);
	if (SQLITE_OK != ret)
	{
		fprintf(stderr, "sqlite3_exec failed!:%s\n", perrmsg);
		sqlite3_free(perrmsg);
		sqlite3_close(pdb);
		return -1;
	}
	sqlite3_close(pdb);

	return 0;
}
char *MadeOf(void)
{
	char *ptmpbuf = NULL;
	char tmpbuf[1024] = {0};
	FILE *fp = NULL;
	fp = fopen("detail.html", "w");
	if(NULL == fp)
	{
		perror("fail to fopen!");
		return NULL;
	}
	sprintf(EndHmtlBuff, "%s%s%s", BeginBuff, PinBuff, EndBuff);
	ptmpbuf = EndHmtlBuff;
	printf("ptmpbuf = %s\n", ptmpbuf);
	
	fprintf(fp, "%s", ptmpbuf);
	fclose(fp);
	strcpy(tmpbuf, "detail.html");
	if(ppname == NULL && ppcharcter == NULL)
	{
		strcpy(tmpbuf, "noexit.html");
	}

	ptmpbuf = tmpbuf;
	
	return ptmpbuf;
}
char * Research(char *prequestbuff, char *pResouceFIlename)
{
	strcpy(ResourceFileName, pResouceFIlename);
	char *ptmp = NULL;
	ptmp = strstr(prequestbuff, "\r\n\r\n");
	ptmp += strlen("\r\n\r\n"); //直接查找到post 内容
	char name[32] = {0} ;
	char charcter[256] = {0};
	char attribute[256] = {0};
	char image[256] = {0};
	int price = 0;

	while(*ptmp != '=')
	{
		ptmp++;
	}
	ptmp++;
    //打印搜索内容原字符串
	printf("ptmp = %s\n", ptmp);                                                                       //拿到的16进制东西：无影(十六进制)
	zhuanhuan(ptmp, ptmpInvert);
	printf("ptmpInvert = %s\n", ptmpInvert);
	FindGunMsg(ptmpInvert, "pass.db", charcter, attribute, image, &price);
	pResouceFIlename = MadeOf();                                                                       //pResouceFIlename为html文件名
	printf("pResouceFIlename = %s\n", pResouceFIlename);
	memset(PinBuff, 0, sizeof(PinBuff));
	return pResouceFIlename;
}
