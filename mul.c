#include <stdio.h>
#include <stdlib.h>

typedef  int ElementType;
typedef struct Node* Pointer;
//单链表 指数降序
struct Node{
    ElementType Data;//系数
    ElementType Power;//指数
    Pointer next;//指针
};
//指数降序链表的插入
int Insert(Pointer L,ElementType data,ElementType power)
{
    //新结点存参数
    Pointer newnode=(Pointer)malloc(sizeof(struct Node));
    newnode->Data=data;
    newnode->Power=power;
    newnode->next=NULL;

    Pointer p =L;
    //找应该插入的位置
    for (;p->next != NULL;)
    {
        //指数相等则系数相加,不用再插入新结点
        if (p->next->Power == power)
        {
            p->next->Data+=data;
            if (p->next->Data == 0) p->next=p->next->next;
            else
                p=p->next;
            return 0;
        }
        else if (p->next->Power > power) p=p->next;
        else
        {
            newnode->next=p->next;
            p->next=newnode;

            return 0;
        }


    }
    //如果表为空,或者参数比所有项的指数都小，就插入到首位(末尾)
    newnode->next=p->next;
    p->next=newnode;
        
    return 0;
    
}

Pointer Mul(Pointer L,ElementType data,ElementType power)//求单个结点与链表相乘所得链表
{
    Pointer p = L;//p->next是首元结点
    Pointer x=(Pointer)malloc(sizeof(struct Node));
    x->next=NULL;
    Pointer o =x;//o用来遍历x链表
    while (p->next != NULL)
    {
        //系数相乘，指数相加，新结点存运算结果
        Pointer newnode=(Pointer)malloc(sizeof(struct Node));
        newnode->Data=(p->next->Data)*data;
        newnode->Power=(p->next->Power)+power;
        newnode->next=NULL;
        //新节点接入x
        o->next=newnode;
        //推进
        o=o->next;
        p=p->next;
    }
    return x;
}

Pointer creat(int n)//建立并初始化带头结点的链表链表，返回链表的头指针
{
    Pointer L=(Pointer)malloc(sizeof(struct Node));//L1指向头结点
    L->next=NULL;
    Pointer p=L;

    printf("请输入每一项的系数与指数\n");
    for(int i=0;i<n;i++)
    {
        //建立并初始化新结点
        Pointer newnode=(Pointer)malloc(sizeof(struct Node));
        scanf("%d",&newnode->Data);
        scanf("%d",&newnode->Power);
        newnode->next=NULL;

        p->next=newnode;
        p=p->next;


    }
    return L;
}

void PrintAll(Pointer L)
{
    Pointer p=L;
    while (p->next !=NULL)
    {
        printf("%d %d  ",p->next->Data,p->next->Power);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    int n;
    printf("请输入多项式一非零项的个数\n");
    scanf("%d",&n);
    Pointer L1=creat(n);//创建长度为n的链表
    printf("请输入多项式二非零项的个数\n");
    scanf("%d",&n);
    Pointer L2=creat(n);
    printf("L1->");
    PrintAll(L1);
    printf("L2->");
    PrintAll(L2);
    printf("\n");
    if (L1->next==0 || L2->next==0)//若有空表，则直接输出空表
        printf("0 0");
    else
    {
        //L3用来存相乘得到的项
        Pointer L3=(Pointer)malloc(sizeof(struct Node));
        L3->next=NULL;
        for (Pointer p1 = L1;p1->next != NULL;p1=p1->next)
        {
            //让L1每一项和L2相乘
            for (Pointer p2 = L2;p2->next != NULL;p2=p2->next)
            {

                Insert(L3,(p1->next->Data)*(p2->next->Data),(p1->next->Power)+(p2->next->Power));
            }
        }
        PrintAll(L3);
        
    }
}

