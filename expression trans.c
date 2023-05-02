#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>//isdigit函数来自于此
int Maxsize=20;
typedef struct SNode* Stack;//堆栈头指针类型为Stack
typedef struct NNode* NumStack;
typedef enum {false,true} bool;//布尔类型
typedef char ElementType;
typedef enum {lpr,rpr,plus,minus,times,divide,eos,operand}Precedence;//precedence类型 默认从0开始 lpr是0 operand是7 数字越大优先级越高


/*
struct SNode
{
    int Data[Maxsize];
    int Top;//栈顶位置的数组下标

} */

/* Stack CreatStack()//创建一个堆栈
{
    Stack S=(Stack)malloc(sizeof(struct SNode));//为堆栈头指针要空间
    S->Top=-1;//初始时栈顶为-1
    return S;
} */


struct SNode
{
    char *Data;//指向运算符数组
    int Top;//栈顶位置的数组下标
    int Maxsize;
};


//创建一个堆栈
Stack CreatStack(int Maxsize)
{
    Stack S=(Stack)malloc(sizeof(struct SNode));//为堆栈头指针要空间
    S->Data=(ElementType *)malloc(Maxsize*sizeof(ElementType));//为数组要空间，大小为maxsize*char
    S->Top=-1;//初始时栈顶为-1
    S->Maxsize=Maxsize;
    return S;
}


//判断堆栈是否为空
bool IsEmpty(Stack S)
{
    //若栈顶为-1就是空
    return (S->Top == -1);
}

bool IsSign(char *expr,int i)//判断+ -是正负号还是运算符
{
    if (!i || (!isdigit(expr[i-1]) && (expr[i-1] != ')')))
    {
        //如果在首位 或者前一项为运算符（不包括右括号），就说明是正负号
        return true;
    }
    else return false;

}

//入栈
void Push(Stack S,ElementType X)
{
    if (S->Top != Maxsize-1)
    {
        S->Data[++(S->Top)]=X;

    }
    else printf("栈满，入栈失败\n");
}

//出栈,返回栈顶元素  不用删除堆栈中的该元素  因为下次入栈会覆盖元素
ElementType Pop(Stack S)
{
    if (S->Top != -1)
    {

        return (S->Data[(S->Top)--]);
        //printf("%c出栈成功\n",S->Data[(S->Top)+1]);
    }
    else 
    {
        printf("S->Top为%d,栈空\n",S->Top);
        return '0';
    }
}

//返回栈顶元素
ElementType Peek(Stack S)
{
    return(S->Data[(S->Top)]);
} 

Precedence GetToken(char op)//返回运算符优先级
{
    switch (op)
    {
        case '(':return lpr;
        case ')':return rpr;
        case '+':return plus;
        case '-':return minus;
        case '*':return times;
        case '/':return divide;
        case '\0':return eos;
        default:return operand;
    }
}

char GetOp(char *expr,int *i,char *Postfix,int *j)//如果是数字，直接写入Postfix[]并返回‘0’，是运算符就返回运算符
{
    //之所以用*i,*j 指针的方式传值，是因为要改变参数的值（连续读几个数字，ToPostfix的循环变量i推进好几位）
    if (isdigit(expr[(*i)]))//存数 
    {
        //如果字符串第i个字符（也就是当前遍历到的字符）是数字或者小数点的话，就存到Postfix字符串里去
        while(isdigit(expr[(*i)]) || (expr[(*i)]=='.'))  Postfix[(*j)++]=expr[(*i)++];

        Postfix[(*j)++]=' ';//令下一项为空格，再让j推进一位
        (*i)--;//最后一次执行i多加了一位，所以减一
        return '0';
    }
    switch(expr[(*i)])
    {
        case '+'://如果是正号 就从下一项开始把连续的数存进Postfix[]
            if (IsSign(expr,(*i)))
            {
                (*i)++;
                return GetOp(expr,i,Postfix,j);//由于i，j已经是地址了，所以直接把i,j传参进去
            }
            else return '+';//如果是运算符 加 则直接返回运算符
        case '-':
            if (IsSign(expr,(*i)))
            {
                Postfix[(*j)++]='-';//如果是负号 就先向字符串Postfix插入负号
                (*i)++;
                return GetOp(expr,i,Postfix,j);
            }
            else return '-';//如果是运算符 减 则直接返回运算符
        default: return expr[(*i)];//其他符号无需判断，直接返回
    }
}

void ToPostfix(char *expr,char *expr1)
{
    int i,j,L;
    char Postfix[2*Maxsize],Op;
    Stack S;//建立堆栈S
    Precedence token;

    S=CreatStack(Maxsize);//初始化堆栈S
    L=strlen(expr);//L为字符串长度
    j=0;//j指向Postfix[]当前要写入的位置 Postfix存后缀表达式

    for(i=0;i<L;i++)
    {
        Op=GetOp(expr,&i,Postfix,&j);//取运算符
        if (Op == '0')continue;//是数字就扫描下一个
        token =GetToken(Op);//取运算符优先级
        switch(token)
        {
            case lpr: Push(S,'(');break;//左括号入栈
            case rpr://括号内的表达式扫描完毕 就把到左括号之前的所有运算符写入Postfix
                while (Peek(S) != '(')
                {

                    Postfix[j++]= Pop(S);
                    Postfix[j++]= ' ';
                }
                Pop(S);//删除左括号
                break;
            default://其他运算符 需要和栈顶运算符比较优先级

                while (!IsEmpty(S) && Peek(S)!='(' && token<=GetToken(Peek(S)) )//如果堆栈非空 且 未扫描到（ 且 当前运算符优先级小于等于栈顶运算符 
                {

                    Postfix[j++]=Pop(S);
                    Postfix[j++]=' ';
                }

  
                Push(S,Op);//当前运算符入栈
                break;
        }
    }
    //字符串扫描结束后
    
    while (!IsEmpty(S))
    {

        Postfix[j++]=Pop(S);
        Postfix[j++]= ' ';
    }
        Postfix[j-1]='\0';
    printf("Postfix->%s\n",Postfix);
    
    strcpy(expr1,Postfix);
}

void ToPostend(char *expr)
{
    Stack S=CreatStack(Maxsize);
    int len=strlen(expr);
    int i,j,end=0;
    char num[Maxsize]="";//临时字符串，用来存每个数
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
            memset(num,0,Maxsize);//清空字符串
            Push(S,num);
        }
        else//如果扫描到运算符，最近的两个数出栈运算
        {
            if (expr[i]=='+') end+=atoi(Pop(S))+atoi(Pop(S));
            else if (expr[i]=='-') end+=(-1)*atoi(Pop(S))+atoi(Pop(S));
            else if (expr[i]=='*') end+=atoi(Pop(S))*atoi(Pop(S));
            else if (expr[i]=='/') end+=(1/atoi(Pop(S)))*atoi(Pop(S));
            else if (expr[i]=='*') end+=atoi(Pop(S))*atoi(Pop(S));
        }

    }
    printf("end=%d\n",end);
}

int main()
{
    char Str[Maxsize];
    char expr[2*Maxsize];
    scanf("%s",Str);
    ToPostfix(Str,expr);//由expr带回中值表达式
    ToPostend(expr);
    return 0;

}