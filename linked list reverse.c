#include <stdio.h>
#include <stdlib.h>

typedef  int ElementType;
typedef struct Node* Pointer;

struct Node{
    ElementType Data;
    Pointer next;
};

void Print(Pointer L)//�������
{
    Pointer p=L;
    while (p->next !=NULL)
    {
        printf("%d ",p->next->Data);
        p=p->next;
    }
    printf("\n");
}

void InitPointer(Pointer *L)//��ʼ��ͷָ�� �ö���ָ��ķ�ʽ�ſɸı����L��ֵ ����ֻ��ı���ʱ������ֵ
{
    *L=(Pointer)malloc(sizeof(struct Node));
    (*L)->next=NULL;
}

void InputPointer(Pointer L)//����ֵ
{
    Pointer p=L;
    int n;
    printf("�����������\n");
    scanf("%d",&n);
    p->Data=n;
    printf("������ÿһ������\n");
    for(int i=0;i<n;i++)
    {
        //��������ʼ���½��
        Pointer newnode=(Pointer)malloc(sizeof(struct Node));
        scanf("%d",&newnode->Data);
        newnode->next=NULL;

        p->next=newnode;
        p=p->next;


    }

}

Pointer Reverse(Pointer L,int k)//��תLͷ���֮���K�����
{
    Pointer new,old,tmp;InitPointer(&new);InitPointer(&old);InitPointer(&tmp);
    int count;
    //count�����ã�����k��ֹͣ
    new=L->next;
    old=new->next;
    for(count=1;count<k;count++)
    {
        tmp=old->next;//tmp������סold����һ��
        old->next=new;

        //new��tmp���ƽ�
        new=old;
        old=tmp;

    }
    L->next->next=old;
    L->next=new;
    return L;
}

int main()
{
    //���� ��ʼ�� ��ֵ
    Pointer L;
    InitPointer(&L);
    InputPointer(L);
    Print(L);
    int len=L->Data;
    int remain=len;
    int k,step=0;//k�����ڣ�step���Ѿ���ת���Ĵ���
    printf("�����뷴ת����\n");
    scanf("%d",&k);
    Pointer p=L;
    if (k!=1)
    {
        while (remain>=k)
        {
        //�ȱ�����Ҫ��������ʼλ��
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