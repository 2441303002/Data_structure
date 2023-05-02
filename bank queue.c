#include <stdio.h>
#include <stdlib.h>

#define MaxQSize 1000
//布尔类型
typedef enum{false,true}bool;
typedef int ElementType;
typedef int Position;
typedef struct QNode* Quene;

struct QNode{
    ElementType *Data;
    Position Front,Rear;
    int MaxSize;
};
//队列基础函数声明
Quene CreatQuene(int MaxSize);
bool IsEmptyQ(Quene Q);
void AddQ(Quene Q,ElementType X);
ElementType DeleteQ(Quene Q);


int main()
{
    Quene A=CreatQuene(MaxQSize);
    Quene B=CreatQuene(MaxQSize);
    int N,one,i,Na,Nb;//Na Nb表示A和比处理速度之比
    //N是顾客总数，one是单个顾客编号
    scanf("%d",&Na);
    scanf("%d",&Nb);
    N=rand()% 100+1;
    for (i=0;i<N;i++)
    {
        one=rand()% 100+1;
        //奇数添加到A队列
        if (one%2) AddQ(A,one);
        else AddQ(B,one);
    }
    //要求输出开头和结尾没有多余空格 所以对第一位顾客特殊处理
    if (!IsEmptyQ(A)) printf("%d",DeleteQ(A));
    else printf("%d",DeleteQ(B));
    while (!IsEmptyQ(A) && !IsEmptyQ(B))
    {
        for (int j=0; j<Na-1;j++)
            if (!IsEmptyQ(A)) printf(" %d",DeleteQ(A));
        for (int j=0; j<Nb;j++)
            if (!IsEmptyQ(B)) printf(" %d",DeleteQ(B));
        if (!IsEmptyQ(A)) printf(" %d",DeleteQ(A));
    }
    //A还有剩余
    while (!IsEmptyQ(A)) printf(" %d",DeleteQ(A));
    //B还有剩余
    while (!IsEmptyQ(B)) printf(" %d",DeleteQ(B));
    return  0;
}


/*基础函数*/
// 创建队列
Quene CreatQuene(int MaxSize)
{
    Quene Q= (Quene)malloc(sizeof(struct QNode));
    Q->Data=(ElementType*)malloc(MaxSize*sizeof(ElementType));
    Q->Front=Q->Rear=0;
    Q->MaxSize=MaxSize;
    return Q;
}

//判断是否为空
bool IsEmptyQ(Quene Q)
{
    //首尾下标相同则为空
    return (Q->Front == Q->Rear);
}

//入列
void AddQ(Quene Q,ElementType X)
{
    //假设入列位置在10001为，取余得到的结果是1，队列首尾衔接   这就是用%而不直接++的原因
    Q->Rear=((Q->Rear)+1)%(Q->MaxSize);
    Q->Data[Q->Rear]=X;
}

//出列
ElementType DeleteQ(Quene Q)
{
    Q->Front=((Q->Front)+1)%(Q->MaxSize);
    return Q->Data[Q->Front];
}