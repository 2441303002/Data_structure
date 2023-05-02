#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct SNode* Stack;
struct SNode
{
    ElementType* Data;
    int Top;
    int Maxsize;
};

Stack CreatStack(int Max)
{
    Stack S=(Stack)malloc(sizeof(struct SNode));
    S->Data=(ElementType *)malloc(Max*sizeof(ElementType));
    S->Top=-1;
    S->Maxsize=Max;
    return S;
}

int IsFull(Stack S)
{//�ж϶�ջ�Ƿ�����
    return (S->Top==(S->Maxsize)-1);
}

int IsEmpty(Stack S)
{//�ж϶�ջ�Ƿ�Ϊ��
    return ((S->Top)==-1);
}

void Push(Stack S,ElementType X)
{//��ջ
    S->Data[++(S->Top)]=X;

}

ElementType Pop(Stack S)
{//���ز�ɾ��ջ��Ԫ��
        return (S->Data[(S->Top)--]);
}



int main()
{
    int N1,N2,num;
    Stack S1,S2;
    char op='0';//��������� A���� D����
    //��ʾ����ջ��С ����С����ΪS1��ջ������ջģ���β����
    scanf("%d",&N1);
    scanf("%d",&N2);
    if (N1!=N2)
    {
        S1=CreatStack(N1>N2? N2:N1);
        S2=CreatStack(N1>N2? N1:N2);
    }
    else
    {
        S1=CreatStack(N1);
        S2=CreatStack(N2);
    }

    while (op!= 'T')
    {
        scanf(" %c",&op);//��ʽ���ƴ�ǰ�ӿո���Է�ֹscanf��ȡ�ո�
        if (op == 'A')
        {//���в���
            scanf("%d",&num);
            //���ж�S1ջ��û����
            if (!IsFull(S1))
            {//��S1δ����ֱ����ջ
                Push(S1,num);
            }
            else
            {//���S1���ˣ������ж�S2��û��Ԫ�� �����Error Full ���û�о���S1Ԫ��������ջS2

                if (IsEmpty(S2))
                {
                    while (!IsEmpty(S1))
                    {
                        Push(S2,Pop(S1));
                    }
                    //����num����
                    Push(S1,num);
                }
                else
                {
                    printf("ERROR:Full\n");
                    continue;
                }
            }
        }
        if (op == 'D')
        {//���в���
            //���ж�S2�Ƿ�Ϊ��
            if (IsEmpty(S2))
            {//��S2Ϊ��
                if (IsEmpty(S1))
                {//��S1Ϊ�� ˵������Ϊ�� ���Error
                    printf("ERROR:Empty\n");
                }
                else
                {//��S1��Ϊ�� ����S1Ԫ��������ջS2
                    while (!IsEmpty(S1))
                    {
                        Push(S2,Pop(S1));
                    }
                    //�ٳ���
                    printf("%d\n",Pop(S2));
                }
            }
            else
            {//����Ϊ�գ�ֱ�ӳ�ջ
                printf("%d\n",Pop(S2));
            }
        }
    }
}