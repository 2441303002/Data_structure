#include <stdio.h>
#include <stdlib.h>

typedef  int ElementType;
typedef struct Node* Pointer;
//������ ָ������
struct Node{
    ElementType Data;//ϵ��
    ElementType Power;//ָ��
    Pointer next;//ָ��
};
//ָ����������Ĳ���
int Insert(Pointer L,ElementType data,ElementType power)
{
    //�½������
    Pointer newnode=(Pointer)malloc(sizeof(struct Node));
    newnode->Data=data;
    newnode->Power=power;
    newnode->next=NULL;

    Pointer p =L;
    //��Ӧ�ò����λ��
    for (;p->next != NULL;)
    {
        //ָ�������ϵ�����,�����ٲ����½��
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
    //�����Ϊ��,���߲������������ָ����С���Ͳ��뵽��λ(ĩβ)
    newnode->next=p->next;
    p->next=newnode;
        
    return 0;
    
}

Pointer Mul(Pointer L,ElementType data,ElementType power)//�󵥸���������������������
{
    Pointer p = L;//p->next����Ԫ���
    Pointer x=(Pointer)malloc(sizeof(struct Node));
    x->next=NULL;
    Pointer o =x;//o��������x����
    while (p->next != NULL)
    {
        //ϵ����ˣ�ָ����ӣ��½���������
        Pointer newnode=(Pointer)malloc(sizeof(struct Node));
        newnode->Data=(p->next->Data)*data;
        newnode->Power=(p->next->Power)+power;
        newnode->next=NULL;
        //�½ڵ����x
        o->next=newnode;
        //�ƽ�
        o=o->next;
        p=p->next;
    }
    return x;
}

Pointer creat(int n)//��������ʼ����ͷ���������������������ͷָ��
{
    Pointer L=(Pointer)malloc(sizeof(struct Node));//L1ָ��ͷ���
    L->next=NULL;
    Pointer p=L;

    printf("������ÿһ���ϵ����ָ��\n");
    for(int i=0;i<n;i++)
    {
        //��������ʼ���½��
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
    printf("���������ʽһ������ĸ���\n");
    scanf("%d",&n);
    Pointer L1=creat(n);//��������Ϊn������
    printf("���������ʽ��������ĸ���\n");
    scanf("%d",&n);
    Pointer L2=creat(n);
    printf("L1->");
    PrintAll(L1);
    printf("L2->");
    PrintAll(L2);
    printf("\n");
    if (L1->next==0 || L2->next==0)//���пձ���ֱ������ձ�
        printf("0 0");
    else
    {
        //L3��������˵õ�����
        Pointer L3=(Pointer)malloc(sizeof(struct Node));
        L3->next=NULL;
        for (Pointer p1 = L1;p1->next != NULL;p1=p1->next)
        {
            //��L1ÿһ���L2���
            for (Pointer p2 = L2;p2->next != NULL;p2=p2->next)
            {

                Insert(L3,(p1->next->Data)*(p2->next->Data),(p1->next->Power)+(p2->next->Power));
            }
        }
        PrintAll(L3);
        
    }
}

