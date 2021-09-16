#include "head.h"
#include "sqlite3.h"
#include "sousuo.h"
char password[1024] = {0};
char nameword[1024] = {0};

pthread_t key_tid,main_tid;



typedef struct HttpRequestInfo
{
	char *pmethod;
	char *purl;
}HttpRequestInfo_t;

int CreateListeSocket(const char *pIp, int Port)
{
	int ret = 0;
	int sockfd = 0;
	struct sockaddr_in seraddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("fail to socket");
		return -1;
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(Port);
	seraddr.sin_addr.s_addr = inet_addr(pIp);
	ret = bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	if (-1 == ret)
	{
		perror("fail to bind");
		return -1;
	}

	ret = listen(sockfd, 10);
	if (-1 == ret)
	{
		perror("fail to listen");
		return -1;
	}

	return sockfd;
}

int RecvHttpRequest(int confd, char *pRequestBuff, int maxlen)
{
	ssize_t nsize = 0;

	nsize = recv(confd, pRequestBuff, maxlen, 0);
	if (-1 == nsize)
	{
		perror("fail to recv");
		return -1;
	}

	return 0;
}

int SendStaticHtml(int confd, char *pHtmlName)
{
	int fd = 0;
	char tmpbuff[4096] = {0};
	ssize_t nsize = 0;

	fd = open(pHtmlName, O_RDONLY);
	if (-1 == fd)
	{
		perror("fail to open");
		return -1;
	}

	while (1)
	{
		nsize = read(fd, tmpbuff, sizeof(tmpbuff));
		if (nsize <= 0)
		{
			break;
		}

		nsize = send(confd, tmpbuff, nsize, 0);
		if (-1 == nsize)
		{
			perror("fail to send");
			return -1;
		}
	}

	close(fd);

	return 0;
}

int SendHttpRespone(int confd, char *pHtmlName)
{
	char ResponeBuff[4096] = {0};
	ssize_t nsize = 0;

	sprintf(ResponeBuff, "HTTP/1.1 200 OK\r\n");
	sprintf(ResponeBuff, "%sConnection: keep-alive\r\n", ResponeBuff);
	sprintf(ResponeBuff, "%sContent-Type: text/html\r\n", ResponeBuff);
	sprintf(ResponeBuff, "%sServer: zhao/1.1\r\n\r\n", ResponeBuff);

	nsize = send(confd, ResponeBuff, strlen(ResponeBuff), 0);
	if (-1 == nsize)
	{
		perror("fail to send");
		return -1;
	}

	SendStaticHtml(confd, pHtmlName);

	return 0;
}

int PraseHttpRequest(char *ptmpRequstBuff, HttpRequestInfo_t *ptmpRequst)
{
	ptmpRequst->pmethod = strtok(ptmpRequstBuff, " ");
	ptmpRequst->purl = strtok(NULL, " ");                                          //分割出来的东西

	return 0;
}
int prasepassword (char *ptmpRequstBuff, char *ppassword, char *pnameword)
{
		
	char *ptmp = NULL;
	char *pend = NULL;
	pend = ptmpRequstBuff + strlen(ptmpRequstBuff);
	*(pend+1) = '\0';
	while(*pend != '=')
	{
		pend--;
	}
	pend++;  //此时pend是password  
	ptmp = pend;
	while(*ptmp != '&')
	{
		ptmp--;
	}
	*ptmp = '\0';
	while(*ptmp != '=')
	{
		ptmp--;
	}
	ptmp++; //此时ptmp 是usrname
	pnameword = ptmp;
	ppassword = pend;
	strcpy(nameword, pnameword);
	strcpy(password, ppassword);
	return 0;
}
int callback(void *arg, int num, char **pcontent, char **ptitle)
{

	char **pptmp = arg;

	*pptmp = malloc(strlen(pcontent[0])+1);
	strcpy(*pptmp, pcontent[1]);

	return 0;
}

char* findDictDB(char *pnameword, char *ppassword, char **ppmean)
{
	sqlite3 *pdb = NULL;
	int ret = 0;
	char cmdbuff[1024] = {0};
	char *perrmsg = NULL;
	*ppmean = NULL;
	ret = sqlite3_open("./pass.db", &pdb);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_open failed:%s\n", sqlite3_errmsg(pdb));
		return NULL;
	}
	sprintf(cmdbuff, "select * from pass where name = \"%s\";", pnameword);
	ret = sqlite3_exec(pdb, cmdbuff, callback, ppmean, &perrmsg);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_exec failed:%s\n", perrmsg);
		sqlite3_free(perrmsg);
		sqlite3_close(pdb);
		return NULL;
	}

	return *ppmean;
}
int registerform(char *pnameword, char *ppassword)
{
	char cmdbuff[1024] = {0};
	sqlite3 *pdb = NULL;
	int ret = 0;
	char *perrmsg = NULL;
	char *pmean = NULL;
	ret = sqlite3_open("./pass.db", &pdb);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_open failed:%s\n", sqlite3_errmsg(pdb));
		return -1;
	}
	
	sprintf(cmdbuff, "insert into pass values(\"%s\", \"%s\");", pnameword, ppassword);
	ret = sqlite3_exec(pdb, cmdbuff, NULL, NULL, &perrmsg);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "sqlite3_exec failed:%s\n", perrmsg);
		sqlite3_free(perrmsg);
		sqlite3_close(pdb);
		return -1;
	}
	sqlite3_close(pdb);
	return 0;
}
int CreateDynamicRejester(const char *ptmpHtml)
{
	FILE *fp = NULL;
	fp = fopen(ptmpHtml, "w");
	if(NULL == fp)
	{
		perror("fail to fopen");
		return -1;
	}
	fprintf(fp, "<html>\n");
	fprintf(fp, "<head>\n");
	fprintf(fp, "<title>register success!!</title>\n");
	fprintf(fp, "</head>\n");
	fprintf(fp, "<body><hr><h1 align = \"center\">register success!!<h1><br></body>\n");
	fprintf(fp, "</html>\n");

	fclose(fp);


	return 0;
}


void *key_thread(void *arg){
    char key_input_ch=0;
    while(1){
        scanf("%c",&key_input_ch);
        getchar();
        if(key_input_ch=='q'||key_input_ch=='Q')break;
        usleep(1000);
    }
    printf("main tid:%d\nkey tid:%d\n",main_tid,key_tid);
    pthread_cancel(key_tid);
    pthread_cancel(main_tid);
}

int main(int argc, const char *argv[])
{
	int sockfd = 0;
	int confd = 0;
	int form = 0;
	int result = 0;
	char *pmean = NULL;
	char *pret = NULL;
	char RequestBuff[4096] = {0};
	HttpRequestInfo_t tmpRequest;
	char ResourceFileName[1024] = {0};
	char *pResourceFileName = NULL;
	char *ppassword = NULL;
	char *pnameword = NULL;
	char requestbuff[4096] = {0};
	char tmpword[256] = {0};
	sockfd = CreateListeSocket("127.0.0.1", 80);
    pthread_create(&key_tid,NULL,key_thread,NULL);
    main_tid=pthread_self();
	while (1)
	{   
	    
	    //等待client 发送数据
		confd = accept(sockfd, NULL, NULL);
		if (-1 == confd)
		{
			perror("fail to accept");
			return -1;
		}

		memset(RequestBuff, 0, sizeof(RequestBuff));
		RecvHttpRequest(confd, RequestBuff, sizeof(RequestBuff));
		printf("===================RECV HTTP REQUEST ==================\n");
		printf("%s\n", RequestBuff);
		strcpy(requestbuff, RequestBuff);

		memset(&tmpRequest, 0, sizeof(tmpRequest));
		PraseHttpRequest(RequestBuff, &tmpRequest);
		printf("tmpRequest.pmethod = %s\n", tmpRequest.pmethod);
		printf("tmpRequest.purl = %s\n", tmpRequest.purl);
        //客户端请求数据
		if(tmpRequest.pmethod != NULL && !strcmp(tmpRequest.pmethod, "GET"))
		{
		    //主界面
			if (tmpRequest.purl != NULL && !strcmp(tmpRequest.purl, "/")&& strcmp(tmpRequest.pmethod, "POST"))     //purl为跳转的网页
			{
				sprintf(ResourceFileName, "zhujiemian.html");
			}
            //文件
			else if (tmpRequest.purl != NULL)
			{
				sprintf(ResourceFileName, ".%s", tmpRequest.purl);
			}
		}
        //客户端发送数据
		else if (tmpRequest.pmethod != NULL && !strcmp(tmpRequest.pmethod, "POST"))//如果是没有在数据库中找到则添加到数据库，若是在数据库中找到则跳转下一级界面
		{
			if(!strcmp(tmpRequest.purl, "/"))
			{
				prasepassword(requestbuff, password, nameword);			
				printf("nameword = %s\n", nameword);
				printf("password = %s\n", password);
				pret = findDictDB(nameword,password,&pmean);                    //查询用户和密码在数据库中是否存在
				if(NULL == pret)                            					//没有注册
				{                   
					printf("未注册!\n");
					registerform(nameword, password);                     		 //进行注册
					memset(ResourceFileName, 0, sizeof(ResourceFileName));
                    //写入注册成功的html文件
					CreateDynamicRejester("mean.html");
					sprintf(ResourceFileName, "mean.html");
				}
				else         													//注册过的用户
				{
					printf("pmean = %s\n", pmean); 
					result = strcmp(pmean, password);
					if(result == 0)
					{
						printf("密码正确！\n");
						memset(ResourceFileName, 0, sizeof(ResourceFileName));
						sprintf(ResourceFileName, "index2.html");
					}
					else
					{
						printf("密码错误!\n");
						memset(ResourceFileName, 0, sizeof(ResourceFileName));
						sprintf(ResourceFileName, "passwrong.html");
					}
				}
			}
			else if(!strcmp(tmpRequest.purl, "/sousuo.cgi"))
			{
				pResourceFileName = Research(requestbuff, ResourceFileName);                                              //requestbuff是接收报文
				printf("pResourceFileName =%s\n", pResourceFileName);
				strcpy(ResourceFileName, pResourceFileName);
			}
		}
		SendHttpRespone(confd, ResourceFileName);

		close(confd);

	}

	close(sockfd);

	return 0;
}

