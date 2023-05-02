#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>//isdigit函数来自于此
//atof()字符串转float memset(str,0,size)字符串清空  ps:itoa 整数转字符串

#define Max 20
typedef struct NumNode* Stack;
typedef float ElementType;
struct NumNode{
    ElementType* Data;
    int Top;
};

Stack CreatStack(int Maxsize)
{
    Stack S=(Stack)malloc(sizeof(struct NumNode));//为堆栈头指针要空间
    S->Data=(ElementType *)malloc(Maxsize*sizeof(ElementType));//为数组要空间，大小为maxsize*int
    S->Top=-1;//初始时栈顶为-1
    return S;
}

void Push(Stack S,ElementType X)
{
    if (S->Top != Max-1)
    {
        S->Data[++(S->Top)]=X;

    }
    else printf("栈满，入栈失败\n");
}
ElementType Pop(Stack S)
{
    if (S->Top != -1)
    {

        return (S->Data[(S->Top)--]);
    }
    else 
    {
        printf("S->Top为%d,栈空\n",S->Top);
        return 0;
    }
}

void trans(char* expr)
{
    Stack S=CreatStack(Max);
    int len=strlen(expr);
    int i,j=0;
    char num[Max]="";//临时字符串，用来存每个数
    for(i=0;i<len;i++)
    {
        if (expr[i] == ' ')continue;//空格跳过
        else if (isdigit(expr[i]) || (expr[i]=='.'))//数字存进堆栈
        {
            while (isdigit(expr[i]) || (expr[i]=='.'))
            {
                num[j++]=expr[i++];
            }
            j=0;
            Push(S,atof(num));
            memset(num,0,Max);//清空字符串
            
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