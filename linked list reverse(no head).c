#include <stdio.h>
#include <stdlib.h>

typedef  int ElementType;
typedef struct Node* Pointer;

struct Node{
    ElementType Data;
    Pointer next;
};

void Print(Pointer L)//链表输出
{
    Pointer p=L;
    while (p !=NULL)
    {
        printf("%d ",p->Data);
        p=p->next;
    }
    printf("\n");
}

void InitPointer(Pointer *L)//初始化头指针 用二重指针的方式才可改变参数L的值 否则只会改变临时副本的值
{
    *L=(Pointer)malloc(sizeof(struct Node));

}

int InputPointer(Pointer L)//链表赋值
{
    Pointer p=L;
    int n;
    printf("请输入结点个数\n");
    scanf("%d",&n);
    printf("请输入每一项数据\n");
    for(int i=0;i<n;i++)
    {
        if (i==0)
        {
            scanf("%d",&L->Data);
            L->next=NULL;
            p=L;
        }
        else{
            //建立并初始化新结点
            Pointer newnode=(Pointer)malloc(sizeof(struct Node));
            scanf("%d",&newnode->Data);
            newnode->next=NULL;

            p->next=newnode;
            p=p->next;
        }


            


    }
    return n;

}

void Reverse(Pointer Lis,int k)//反转L头结点之后的K个结点
{
    Pointer new,old,tmp;InitPointer(&new);InitPointer(&old);InitPointer(&tmp);
    int count;
    //count计数用，大于k就停止
    new=Lis;
    old=new->next;
    for(count=1;count<k;count++)
    {
        tmp=old->next;//tmp用来记住old的下一项
        old->next=new;

        //new和tmp都推进
        new=old;
        old=tmp;

    }
    Lis->next=old;
    Lis=new;

}

int main()
{
    //声明 初始化 赋值
    Pointer L;
    L=(Pointer)malloc(sizeof(struct Node));
    L->next=NULL;  
    int len=InputPointer(L);
    printf("L->");
    Print(L);
    printf("len=%d\n",len);
    int remain=len;
    int k,step=0;//k是周期，step是已经反转过的次数
    printf("请输入反转周期\n");
    scanf("%d",&k);
    Pointer p=L;
    if (k!=1)
    {
        while (remain>=k)
        {
        //先遍历到要操作的起始位置
        for(int i=0;i<step*k;i++)
        {
            p=p->next;
        }
        Reverse(p,k);
        step++;
        remain-=k;
    
        }
        Print(L);
        
    }
    else Print(L);

    

    return 0;
}