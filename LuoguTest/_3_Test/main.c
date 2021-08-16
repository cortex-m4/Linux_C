#include "stdio.h"
#include<stdlib.h>
#include<string.h>
int size;			//map大小
int Bx,By;			//终点坐标
int horseX,horseY;	//马的坐标




/*
	在该位置放置数
*/
void setPos(char **buff,int x,int y,char num){
	
	if(x>=Bx&&y>=By){
		printf("error!\n");
		return;
	}else{
		x-=1;
		y-=1;
		*(buff+(By*x)+y)=num;
	}
	
}
/*
	读取该点的数
*/
char readPos(char **buff,int x,int y){
	x-=1;
	y-=1;
	if(x>=Bx&&y>=By){
		printf("error!\n");
		return;
	}else{
		x-=1;
		y-=1;
		retrun *(buff+(By*x)+y);
	}
}
void setOther(char **buff,int x,int y,char num){
	int x1,y1;
	x1=x+2;
	y1=y-1;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x+2;
	y1=y+1;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x+1;
	y1=y+2;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x+1;
	y1=y-2;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x-2;
	y1=y-1;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x-2;
	y1=y+1;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x-1;
	y1=y+2;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}
	x1=x-1;
	y1=y-2;
	if(x1<=By&&x1>0&&y1<=Bx&&y1>0){
		setPos(buff,x1,y1,num);
	}

}
/*全路径遍历*/
void passAll(char **buff){
	int dx,dy;
	int i,j;

	

}
int main(void){
	char **map=NULL;
	

	
	int i,j;
	
	
	scanf("%d %d %d %d",&Bx,&By,&horseX,&horseY);
	
	size=(Bx*By)*sizeof(char *);
	printf("size is:%d\n",size);
	map=(char **)malloc(size);
	
	setPos(map,1,1,'S');
	setPos(map,Bx,By,'O');
	printf("setpos\n");
	setPos(map,horseX,horseY,'M');
	printf("setOther\n");
	setOther(map,horseX,horseY,'M');
	printf("setOther over\n");
	for(i=0;i<Bx;i++){
		for(j=0;j<By;j++){
			printf("%c_,\t",*map);
			map++;
		}
		printf("\n");
	}
	
	/*
	memset(map,0,15);
	map=test;
	for(i=0;i<3;i++){
		for(j=0;j<5;j++){
			
			printf("%d,\t",*map);
			map++;
		}
		printf("\n");
	}
	*/
}