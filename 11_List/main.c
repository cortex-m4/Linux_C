#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stddef.h"
#define Test_Header printf("\n-----%s-----\n",__FUNCTION__)
typedef unsigned int LType;
typedef struct link_list{
    LType count;
    struct link_list *next;
}LinkList;

LinkList *head_list;
/*
    链表初始化
*/ 
void linklistInit(LinkList **head)
{
    *head = NULL;
}
/*
    创建链表新节点
*/
LinkList *creatListNode(LType dat){
    //创建空间
    LinkList *new_node=(LinkList *)malloc(sizeof(LinkList));
    new_node->count=dat;
    new_node->next=NULL;
    return new_node;
}
/*
    销毁一个节点
*/
void deleteListNode(LinkList *node){
    free(node);
}
/*
    顺序打印链表元素
*/
void printList(LinkList *head){
    if(head==NULL){
        printf("print list is null!\n");
        return;
    }
    LinkList *temp=head;
    //遍历
    while(temp!=NULL){
        printf("%d|%p\n",temp->count,temp);
        temp=temp->next;
    }
}
/*
    逆序打印链表
*/
void printListReverse(LinkList *head){
    if(head==NULL){
        printf("print list is null!\n");
        return;
    }
    printListReverse(head->next);
    printf("%d|%p\n",head->count,head);
}
/*
    头插函数
*/
void addFrontList(LinkList **head,LType value)
{
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表
    if(*head == NULL)
    {
        //直接创建一个新节点完成插入
        *head = creatListNode(value);
        return;
    }
    else
    {
        //创建一个新的指针指向头结点
        LinkList *new_node = *head;
        //创建一个新的头结点
        *head = creatListNode(value);
        //将新的头结点的next指向旧的头结点
        (*head)->next = new_node;
    }
    return;
}

/*
    尾插链表
*/
LinkList *addBackList(LinkList **head,LType dat){
    //非法
    if(head==NULL){
        return NULL;
    }
    //空链表
    if(*head==NULL){
        *head=creatListNode(dat);
        return NULL;
    }else{
        LinkList *temp=*head;
        //遍历
        while(temp->next!=NULL){
            temp=temp->next;
        }
        //创建一个新的节点
        LinkList *new_node=creatListNode(dat);
        //最后的元素与新的连接一起
        temp->next=new_node;
        return new_node;
    }

}
/*
    头删
*/
void deleteFrontList(LinkList **head){
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表没有可删除的元素
    if(*head == NULL)
    {
        return;
    }
    else
    {
        //创建一个新的指针指向第二个元素
        LinkList *new_node = (*head)->next;
        //将头结点的next指向空
        (*head)->next = NULL;
        //删除该头结点
        deleteListNode(*head);
        //将第二个元素设置成新的头结点
        *head = new_node;
    }
    return;
}
/*
    尾删链表
*/
void deleteBackList(LinkList **head){
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表没有可删除的元素
    if(*head == NULL)
    {
        return;
    }
    //只有一个元素
    if((*head)->next == NULL)
    {
        //直接删除节点
        deleteListNode(*head);
        //将头结点置空
        *head = NULL;
        return;
    }
    else
    {
        LinkList *temp = *head;
        //遍历链表，使temp指向倒数第二个元素
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        //创建指针指向最后一个元素，即我们需要删除的元素
        LinkList *to_delete = temp->next;
        //将该节点销毁
        deleteListNode(to_delete);
        //将倒数第二个元素的next指向空
        temp->next = NULL;
    }
    return;

}
/*
    查找链表中指定元素的地址
*/
LinkList *findLinkList(LinkList *head,LType to_find)
{
    int count = 0;
    LinkList *find = head;
    //空链表
    if(head == NULL)
    {
        return NULL;
    }
    else
    {
        //循环遍历链表
        for(;find->next != NULL;find = find->next)
        {
            if(find->count == to_find)
            {
                count++;
                //找到了返回该元素的地址
                return find;
            }
        }
    }
    //如果count计数为0，说明没有链表中不存在想要查找的元素
    if(count == 0)
    {
        printf("this value is non-existence\n");
    }
    //没找到返回空
    return NULL;
}
/*
    在指定位置之前插入指定元素
    时间复杂度为O(n)
    head:被插的链表
    pos:插入的链表
    value:值
*/
void insertBackLinkList(LinkList **head,LinkList *pos,LType value)
{
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表
    if(*head == NULL)
    {
        //直接创建一个新的节点
        *head = creatListNode(value);
        return;
    }
    //如果是头结点位置
    if(pos == *head)
    {
        //则进行头插
        addFrontList(head,value);
        return;
    }
    //如果为空
    if(pos == NULL)
    {
        //则进行尾插
        addBackList(head,value);
        return;
    }
    else
    {
        //定义一个新指针指向pos的下一个位置(保存pos下个位置)
        LinkList *temp = pos->next;
        //用pos位置的值创建一个新的节点
        LinkList *new_node = creatListNode(pos->count);
        //将pos位置原本的值修改为value
        pos->count = value;
        //将pos的next指向新的节点
        pos->next = new_node;
        //将新节点的next指向pos的next，即指向之前pos指向的next:temp
        new_node->next = temp;
    }
}
/*
    删除指定位置的链表
*/
void deleteLinkList(LinkList **head,LinkList *pos){
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表无法删除
    if(*head == NULL)
    {
        return;
    }
    //如果pos位置为空
    if(pos == NULL)
    {
        //则进行尾删
        deleteBackList(head);
        return;
    }
    //如果pos为头结点位置
    if(pos == *head)
    {
        //则进行头删
        deleteFrontList(head);
        return;
    }
    else
    {
        //创建一个新的指针指向pos的next
        LinkList *to_delete = pos->next;
        //将pos的下一个位置的元素赋给pos
        pos->count = to_delete->count;
        //再将pos的next指向其下一个元素的next
        pos->next = to_delete->next;
        //将pos的下一个位置节点删除
        deleteListNode(to_delete);
    }
}
/*
    删除指定元素,如果存在重复，只删除第一个
*/
void removeLinkListValue(LinkList **head,LType to_delete){
    //非法输入
    if(head == NULL)
    {
        return;
    }
    //空链表没有可删除的元素
    if(*head == NULL)
    {
        return;
    }
    //如果头结点的元素是要删除的元素
    if((*head)->count == to_delete)
    {
        //则进行头删
        deleteFrontList(head);
        return;
    }
    LinkList *temp = *head;
    //遍历链表
    while(temp != NULL && temp->next != NULL)
    {
        //要删除的元素是temp的下一个元素
        if(temp->next->count == to_delete)
        {
            //定义一个新的指针指向temp的下一个元素（待删除元素）的位置
            LinkList *to_remove = temp->next;
            //将temp的next指向其下一个元素（待删除元素）的下一个位置
            temp->next = to_remove->next;
            //删除新的节点（即一开始定义的指向待删除元素的指针）
            deleteListNode(to_remove);
            return;
        }
        temp = temp->next;
    }
}
/*
    判断是不是空链表
*/
int isEmptyLinkList(LinkList *head){
    return head == NULL ?0:1;
}
/*
    返回链表元素的个数
*/
int sizeofLinkList(LinkList *head){
    //空链表返回0
    if(head == NULL)
    {
        return 0;
    }
    int count = 0;
    LinkList *temp = head;
    //遍历链表
    for(;temp != NULL;temp = temp->next)
    {
        count++;
    }
    return count;

}

/******************************************test***********************************/
//尾插测试
void Test_BackInsert(){
    Test_Header;
    //初始化链表
    linklistInit(&head_list);
    addBackList(&head_list,1);
    addBackList(&head_list,2);
    addBackList(&head_list,3);
    addBackList(&head_list,4);
    printList(head_list);
}
//头插测试
void Test_FrontInsert(){
    Test_Header;
    //初始化链表
    addFrontList(&head_list,9);
    addFrontList(&head_list,8);
    addFrontList(&head_list,7);
    addFrontList(&head_list,6);
    printList(head_list);
}
//头删测试
void Test_FrontDelete(){
    Test_Header;
    deleteFrontList(&head_list);
    deleteFrontList(&head_list);
    deleteFrontList(&head_list);
    printList(head_list);
}
//尾删测试
void Test_BackDelete(){
    Test_Header;
    deleteBackList(&head_list);
    deleteBackList(&head_list);
    deleteBackList(&head_list);
    printList(head_list);
}
//删除指定元素测试
void Test_MoveValue(LType dat){
    Test_Header;
    removeLinkListValue(&head_list,dat);
    printList(head_list);
}
//添加指定元素测试
void Test_AddValue(LType dat){
    
}
void main(){
    Test_BackInsert();
    printf("1_size:%d\n",sizeofLinkList(&head_list));
    printf("head value is:%d\n",head_list->count);
    Test_FrontInsert();
    printf("2_size:%d\n",sizeofLinkList(&head_list));
    printf("head value is:%d\n",head_list->count);
    Test_MoveValue(9);
    Test_FrontDelete();
    printf("3_size:%d\n",sizeofLinkList(&head_list));
    printf("head value is:%d\n",head_list->count);
    Test_BackDelete();
    printf("4_size:%d\n",sizeofLinkList(&head_list));
    printf("head value is:%d\n",head_list->count);
}