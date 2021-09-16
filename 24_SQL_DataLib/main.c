#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <pthread.h>

#include "sqlite3.h"


#define FILE_NAME	"dataLib.db"
/*
一些最重要的 SQL 命令
SELECT - 从数据库中提取数据
UPDATE - 更新数据库中的数据
DELETE - 从数据库中删除数据
INSERT INTO - 向数据库中插入新数据
CREATE DATABASE - 创建新数据库
ALTER DATABASE - 修改数据库
CREATE TABLE - 创建新表
ALTER TABLE - 变更（改变）数据库表
DROP TABLE - 删除表
CREATE INDEX - 创建索引（搜索键）
DROP INDEX - 删除索引

creat 语句
创建列内容和数据类型
create table table_name(
	lie1 data_type(size),
	lie2 data_type(size),
	...
)

insert into 语句
直接插入 不指定列 要插入所有元素
insert into table_name
value()

指定列插入
insert into table_name(lie1,lie2,lie3,...)
value(val1,val2,val3,...)

update 语句
修改指定列数据
update table_name
set lie1=val1,lie1=val2,...
where lie_name=some_name

select语句
选择并且读取 所有指定列名的数据
select 列名1,列名2 from 表名
读取这个表的所有数据
select * from 表名
选择指定列名的值 读取该值
select 列明 from 表名 where 列名=xxx

delete 语句
delete from table_name
where lie_name=some_name

delete * from table_name
*/

int searchCallback(void *arg,int num,char **pcontent,char **ptitle){
	int i;
	printf("记录保护%d个字段\n",num);
	for(i=0;i<num;i++){
		printf("字段名:%s--字段值:%s\n",ptitle[i],pcontent[i]);
		
	}
	printf("------\n");
	return 0;

}



int main(void){
	sqlite3 *db;
	int ret;
	char *errmsg=NULL;
	
	ret=sqlite3_open(FILE_NAME,&db);
	if(ret!=SQLITE_OK){
		
		return -1;
	}
	//创建表
	ret=sqlite3_exec(db,"create table MyTable_1(Age int,name varchar(32))",NULL,NULL,&errmsg);
	if(ret!=SQLITE_OK){
		printf("创建表失败，错误码:%d，错误原因:%s\n", ret, errmsg );
		if(strstr(errmsg,"already")==NULL)
		return -1;
	}
	/*
	//插入表
	ret=sqlite3_exec(db,"insert into MyTable_1(Age,name) values(23,'张三')", 0, 0, &errmsg );
	if(ret!=SQLITE_OK){
		printf("插入失败，错误码:%d，错误原因:%s\n",ret,errmsg);
	}
	ret=sqlite3_exec(db,"insert into MyTable_1(Age,name) values(18,'李四')", 0, 0, &errmsg );
	if(ret!=SQLITE_OK){
		printf("插入失败，错误码:%d，错误原因:%s\n",ret,errmsg);
	}
	ret=sqlite3_exec(db,"insert into MyTable_1(Age,name) values(20,'王五')", 0, 0, &errmsg );
	if(ret!=SQLITE_OK){
		printf("插入失败，错误码:%d，错误原因:%s\n",ret,errmsg);
	}
	*/
	//查询数据库
	ret=sqlite3_exec(db,"select Age from MyTable_1 where name=\"张三\"",searchCallback,NULL,&errmsg);
	if(ret!=SQLITE_OK){
		printf("查找失败\n");
	}
	sqlite3_close(db);
	return 0;
	
}
