#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>//isdigit���������ڴ�
//atof()�ַ���תfloat memset(str,0,size)�ַ������  ps:itoa ����ת�ַ���

#define Max 20
typedef struct NumNode* Stack;
typedef float ElementType;
struct NumNode{
    ElementType* Data;
    int Top;
};

Stack CreatStack(int Maxsize)
{
    Stack S=(Stack)malloc(sizeof(struct NumNode));//Ϊ��ջͷָ��Ҫ�ռ�
    S->Data=(ElementType *)malloc(Maxsize*sizeof(ElementType));//Ϊ����Ҫ�ռ䣬��СΪmaxsize*int
    S->Top=-1;//��ʼʱջ��Ϊ-1
    return S;
}

void Push(Stack S,ElementType X)
{
    if (S->Top != Max-1)
    {
        S->Data[++(S->Top)]=X;

    }
    else printf("ջ������ջʧ��\n");
}
ElementType Pop(Stack S)
{
    if (S->Top != -1)
    {

        return (S->Data[(S->Top)--]);
    }
    else 
    {
        printf("S->TopΪ%d,ջ��\n",S->Top);
        return 0;
    }
}

void trans(char* expr)
{
    Stack S=CreatStack(Max);
    int len=strlen(expr);
    int i,j=0;
    char num[Max]="";//��ʱ�ַ�����������ÿ����
    for(i=0;i<len;i++)
    {
        if (expr[i] == ' ')continue;//�ո�����
        else if (isdigit(expr[i]) || (expr[i]=='.'))//���ִ����ջ
        {
            while (isdigit(expr[i]) || (expr[i]=='.'))
            {
                num[j++]=expr[i++];
            }
            j=0;
            Push(S,atof(num));
            memset(num,0,Max);//����ַ���
            
        }
        else 
        {
            float a=Pop(S);
            float b=Pop(S);
            switch(expr[i])
            {
                case '+': Push(S,a+b);break;
                case '-': Push(S,b-a);break;
                case '*': Push(S,a*b);break;
                case '/': Push(S,b/a);break;
            }
        }
    }
    printf("%f",S->Data[S->Top]);
}



int main()
{
    char str[100]="2 3 7 4 - * + 8 4 / +";
    trans(str);
    return 0;
}