#include <stdio.h>
 
int main()
{

   FILE *fpW = NULL;
   FILE *fpR = NULL; 
   char buff[255];      //读取数据暂存
   
   fpW = fopen("./tmp/test.txt", "w+");                 //创建一个文件
   fprintf(fpW, "This is testing for fprintf...\n");   //向这个文件内写入数据
   fputs("This is testing for fputs...\n", fpW);       //写入第二行数据
   fclose(fpW);                                        //关闭文件
   printf("data save compete!\n");                    //输出状态
   
   
   fpR = fopen("./tmp/test.txt", "r");
   //fscanf(fpR, "%s", buff);
   //printf("1: %s\n", buff );
 
   fgets(buff, 255, (FILE*)fpR);
   printf("2: %s\n", buff );
   
   fgets(buff, 255, (FILE*)fpR);
   printf("3: %s\n", buff );
   fclose(fpR);

   return 0;
}