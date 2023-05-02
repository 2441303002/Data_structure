#include <stdio.h>
#include <stdlib.h>

#define MaxQSize 1000
//��������
typedef enum{false,true}bool;
typedef int ElementType;
typedef int Position;
typedef struct QNode* Quene;

struct QNode{
    ElementType *Data;
    Position Front,Rear;
    int MaxSize;
};
//���л�����������
Quene CreatQuene(int MaxSize);
bool IsEmptyQ(Quene Q);
void AddQ(Quene Q,ElementType X);
ElementType DeleteQ(Quene Q);


int main()
{
    Quene A=CreatQuene(MaxQSize);
    Quene B=CreatQuene(MaxQSize);
    int N,one,i,Na,Nb;//Na Nb��ʾA�ͱȴ����ٶ�֮��
    //N�ǹ˿�������one�ǵ����˿ͱ��
    scanf("%d",&Na);
    scanf("%d",&Nb);
    N=rand()% 100+1;
    for (i=0;i<N;i++)
    {
        one=rand()% 100+1;
        //������ӵ�A����
        if (one%2) AddQ(A,one);
        else AddQ(B,one);
    }
    //Ҫ�������ͷ�ͽ�βû�ж���ո� ���ԶԵ�һλ�˿����⴦��
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
    //A����ʣ��
    while (!IsEmptyQ(A)) printf(" %d",DeleteQ(A));
    //B����ʣ��
    while (!IsEmptyQ(B)) printf(" %d",DeleteQ(B));
    return  0;
}


/*��������*/
// ��������
Quene CreatQuene(int MaxSize)
{
    Quene Q= (Quene)malloc(sizeof(struct QNode));
    Q->Data=(ElementType*)malloc(MaxSize*sizeof(ElementType));
    Q->Front=Q->Rear=0;
    Q->MaxSize=MaxSize;
    return Q;
}

//�ж��Ƿ�Ϊ��
bool IsEmptyQ(Quene Q)
{
    //��β�±���ͬ��Ϊ��
    return (Q->Front == Q->Rear);
}

//����
void AddQ(Quene Q,ElementType X)
{
    //��������λ����10001Ϊ��ȡ��õ��Ľ����1��������β�ν�   �������%����ֱ��++��ԭ��
    Q->Rear=((Q->Rear)+1)%(Q->MaxSize);
    Q->Data[Q->Rear]=X;
}

//����
ElementType DeleteQ(Quene Q)
{
    Q->Front=((Q->Front)+1)%(Q->MaxSize);
    return Q->Data[Q->Front];
}