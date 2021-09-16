#include "main.h"

#define RECV_BUFFLEN    4096

#define SEVERIP     "127.0.0.1"

#define MAIN_WEB_WINDOW     "login.html"
#define MEUN_WEB_WINDOW     "menu.html"

char recvSocketBuff[RECV_BUFFLEN];

char htmlFileName[64]={0};

typedef struct HttpRequestInfo
{
	char *pmethod;
	char *purl;
}HttpRequestInfo_t;


/*
    返回文件大小
*/
int file_sizeof(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);
    
    return size;
}


/*
    发送html信息
*/
int SendStaticHtml(int confd, char *pHtmlName)
{
	int fd = 0;
	char *tmpbuff;
	ssize_t nsize = 0;
    int filesize=0;
    filesize=file_sizeof(pHtmlName);
    tmpbuff=(char *)malloc(filesize);
    if(tmpbuff==NULL){
        printf("open html failed \n");
        return -1;
    }
    memset(tmpbuff,0,filesize);
	fd = open(pHtmlName, O_RDONLY);
	if (fd<0)
	{
		printf("fail to open html\n");
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
		if (nsize<0)
		{
			printf("fail to send\n");
			return -1;
		}
	}
    free(tmpbuff);
	close(fd);

	return 0;
}

/*
    发送服务器回复信息
*/
int SendHttpRespone(int confd, char *pHtmlName)
{
	char ResponeBuff[4096] = {0};
	ssize_t nsize = 0;

	sprintf(ResponeBuff, "HTTP/1.1 200 OK\r\n");
	sprintf(ResponeBuff, "%sConnection: keep-alive\r\n", ResponeBuff);
	sprintf(ResponeBuff, "%sContent-Type: text/html\r\n", ResponeBuff);
	sprintf(ResponeBuff, "%sServer: yan/1.1\r\n\r\n", ResponeBuff);

	nsize = send(confd, ResponeBuff, strlen(ResponeBuff), 0);
	if (nsize<0)
	{
		printf("fail to send\n");
		return -1;
	}

	SendStaticHtml(confd, pHtmlName);

	return 0;
}


int PraseHttpRequest(char *ptmpRequstBuff, HttpRequestInfo_t *ptmpRequst)
{
    char i=0;
	ptmpRequst->pmethod = strtok(ptmpRequstBuff, " ");
	ptmpRequst->purl = strtok(NULL, " ");                                          //分割出来的东西
    if(ptmpRequst->pmethod!=NULL&&ptmpRequst->purl!=NULL){
        while(1){
            if(*ptmpRequstBuff=='\0')
            {
                *ptmpRequstBuff=' ';
                i++;
            }
            if(i==2)break;
            ptmpRequstBuff++;
        }
    }
	return 0;
}


int RecvSocketRequest(int confd,char *pRecvBuff,int len){
    ssize_t nsize = 0;
    nsize=recv(confd,pRecvBuff,len,0);
    if(nsize<0){
        printf("recv socket request failed\n");
        return -1;
    }
    return nsize;
}

int CreateSocket(const char *pIp, int Port)
{
	int ret = 0;
	int sockfd = 0;
	struct sockaddr_in seraddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd<0)
	{
		printf("create socket error\n");
		return -1;
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(Port);
	seraddr.sin_addr.s_addr = inet_addr(pIp);
	ret = bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	if (ret<0)
	{
		printf("fail to bind\n");
		return -1;
	}

	ret = listen(sockfd, 10);
	if (ret<0)
	{
		printf("fail to listen\n");
		return -1;
	}

	return sockfd;
}

/*
    解析用户名和密码
*/
void prasePassword(char *ptempRequstBuff,char *ppassword,char *pname){

    char *ptemp;
    ptemp=ptempRequstBuff+strlen(ptempRequstBuff);
    while(*ptemp!='='){
        ptemp--;
    }
    memcpy(ppassword,ptemp+1,strlen(ptemp+1));
    do{
        ptemp--;
        if(*ptemp=='&')*ptemp='\0';
    }while(*ptemp!='=');
    memcpy(pname,ptemp+1,strlen(ptemp+1));

}

/*
    储存或者判断用户名和密码
    0 成功
    -1 密码错误
    -2 注册失败 用户已满
*/

int  saveCmpUserInfo(char *pass,char *name){
    FILE *fp;
    int i=0;
    int tempSize=0;
    char *temp;
    char buffer[1024]={0};
    char mixFormat[64]={0};
    char userNameBuf[16][32];
    fp=fopen("pass","r+");
    fread(buffer,1,sizeof(buffer),fp);
    sprintf(mixFormat,"%s,%s\r\n",name,pass);
    //预存用户名
    temp=buffer;
    while(temp!='\0'||i<16){
        tempSize=strchr(temp,',')-temp;
        memcpy(userNameBuf[i++],temp,tempSize);
        temp=strchr(temp+1,'\n')+1;
    }
    //判断用户名
    for(i=0;i<16;i++){
        if(!strcmp(userNameBuf[i],name)){
            if(strstr(buffer,mixFormat)==NULL){
                fclose(fp);
                return -1;
            }
        }
    }
    //没有此用户，就注册
    if(i==16){
        strcat(buffer,mixFormat);
        if((strlen(buffer)+strlen(mixFormat))>1024){
            fclose(fp);
            return -2;
        }else{
            fwrite(buffer,1,sizeof(buffer),fp);
            fclose(fp);
        }
    }
    
    return 0;
}

/*
    尾插
*/
char *insert(char *s1, char *s2, char n)
{
	int len1 = 0, len2 = 0, j = 0;
	char *s4;
	char *s3 = s4;
	if (s1 == NULL)
		return NULL;
	if (s2 == NULL)
		return s1;
	len1 = strlen(s1);
	len2 = strlen(s2);
 
	if(n>len1)
		return NULL;
    j=n;
    s4=(char *)malloc(strlen(s1));
    memset(s4,0,strlen(s1));
    strcpy(s4,s1);
 
	for (int i = 0; i<len2; i++)
		s1[j++] = s2[i];
	  
	for(int i=n;i<len1;i++)
		s1[j++]=s4[i];
    free(s4);
	s1[j] = '\0';
	
 
	return s1;
}


/*
    sta:
    0:没有
    1:密码错误
    2:无法注册，数据库已满
*/
void updateMainWebHtml(int sta){
    FILE *fp;
    char *htmlDat;
    char *temp;
    int filesize=0;

    int insertN=0;

    char insertChar[16]={0};

    
    filesize=file_sizeof(MAIN_WEB_WINDOW);
    htmlDat=(char *)malloc(filesize+16);
    if(htmlDat==NULL){
        printf("updata html file failed \n");
        return;
    }
    memset(htmlDat,0,filesize+16);
    fp=fopen(MAIN_WEB_WINDOW,"r+");
    fread(htmlDat,1,filesize,fp);
    temp=strstr(htmlDat,"class=\"returnInfo\">")+strlen("class=\"returnInfo\">");
    
    insertN=temp-htmlDat;
    if(sta==1){
        strcpy(insertChar,"密码错误");
    }
    if(sta==1){
        strcpy(insertChar,"注册失败");
    }
    htmlDat=insert(htmlDat,insertChar,insertN);
    fwrite(htmlDat,1,filesize+strlen(insertChar),fp);
    
    fclose(fp);
    
}


int main(int argc,char **argv){

    int socketfd=0;
    int confd=0;

    int recv_len=0; 

    int ret=0;

    char tempUsername[32]={0};
    char tempPassword[32]={0};

    HttpRequestInfo_t tempRequest;
    
    socketfd=CreateSocket(SEVERIP,80);

    while(1){
        //等待数据输入
        confd=accept(socketfd,NULL,NULL);
        if(confd<0){
            printf("failed to accept\n");
            return -1;
        }
        //读取数据
        memset(recvSocketBuff,0,RECV_BUFFLEN);
        recv_len=RecvSocketRequest(confd,recvSocketBuff,sizeof(recvSocketBuff));
        if(recv_len<0){
            printf("recv socket data failed\n");
            return -1;
        }else if(recv_len>4096){
            printf("recv socket data too big\n");
            return -1;
        }
		printf("web recv len:%d data:\n%s\n",recv_len,recvSocketBuff);
        //获取数据的方法和 url
        PraseHttpRequest(recvSocketBuff, &tempRequest);
        //HTTP GET
        if(tempRequest.pmethod!=NULL&&!strcmp(tempRequest.pmethod,"GET")){
            //主界面
            if (tempRequest.purl != NULL && !strcmp(tempRequest.purl, "/")){
                strcpy(htmlFileName,MAIN_WEB_WINDOW);
            }
            //文件
            else if(tempRequest.purl != NULL){
                sprintf(htmlFileName,".%s",tempRequest.purl);
            }


        }
        else if(tempRequest.pmethod!=NULL&&strcmp(tempRequest.pmethod,"POST")){
            //注册界面发送的post请求
            if(!strcmp(tempRequest.purl,"/")){
                memset(tempPassword,0,sizeof(tempPassword));
                memset(tempUsername,0,sizeof(tempUsername));
                prasePassword(recvSocketBuff,tempPassword,tempUsername);
                ret=saveCmpUserInfo(tempPassword,tempUsername);
                switch(ret){
                    case 0:
                        strcpy(htmlFileName,MEUN_WEB_WINDOW);
                    break;
                    case -1:
                        updateMainWebHtml(1);
                    break;
                    case -2:
                        updateMainWebHtml(2);
                    break;
                    
                }
                
            }
            else if(!strcmp(tempRequest.purl,"/sousuo.cgi")){

            }
            //printf("web recv data:\n%s\n",recvSocketBuff);
        }
        SendHttpRespone(confd, htmlFileName);
        close(confd);
        

    }
    
}




