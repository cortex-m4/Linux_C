#include "stdio.h"

int testArray[9]={32,41,21,3,76,23,84,43,57};

//直接插入法一
void InsertSort1(int a[], int n)
{
    int i, j;
    for(i=1; i<n; i++)
        if(a[i] < a[i-1])   
        {
            int temp = a[i];                       //保存要比较的值
            for(j=i-1; j>=0 && a[j]>temp; j--)    //从后向前查找待插入位置
                a[j+1] = a[j];                    //挪位
            a[j+1] = temp;                       //复制到插入位置
        }
}

void main(){
    int i;
    InsertSort1(testArray,9);
    for(i=0;i<9;i++){
        printf("outputArray is :%d\r\n",testArray[i]);
    }
    printf("\r\n");
}
