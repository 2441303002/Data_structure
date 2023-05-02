#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>//isdigit���������ڴ�
int Maxsize=20;
typedef struct SNode* Stack;//��ջͷָ������ΪStack
typedef struct NNode* NumStack;
typedef enum {false,true} bool;//��������
typedef char ElementType;
typedef enum {lpr,rpr,plus,minus,times,divide,eos,operand}Precedence;//precedence���� Ĭ�ϴ�0��ʼ lpr��0 operand��7 ����Խ�����ȼ�Խ��


/*
struct SNode
{
    int Data[Maxsize];
    int Top;//ջ��λ�õ������±�

} */

/* Stack CreatStack()//����һ����ջ
{
    Stack S=(Stack)malloc(sizeof(struct SNode));//Ϊ��ջͷָ��Ҫ�ռ�
    S->Top=-1;//��ʼʱջ��Ϊ-1
    return S;
} */


struct SNode
{
    char *Data;//ָ�����������
    int Top;//ջ��λ�õ������±�
    int Maxsize;
};


//����һ����ջ
Stack CreatStack(int Maxsize)
{
    Stack S=(Stack)malloc(sizeof(struct SNode));//Ϊ��ջͷָ��Ҫ�ռ�
    S->Data=(ElementType *)malloc(Maxsize*sizeof(ElementType));//Ϊ����Ҫ�ռ䣬��СΪmaxsize*char
    S->Top=-1;//��ʼʱջ��Ϊ-1
    S->Maxsize=Maxsize;
    return S;
}


//�ж϶�ջ�Ƿ�Ϊ��
bool IsEmpty(Stack S)
{
    //��ջ��Ϊ-1���ǿ�
    return (S->Top == -1);
}

bool IsSign(char *expr,int i)//�ж�+ -�������Ż��������
{
    if (!i || (!isdigit(expr[i-1]) && (expr[i-1] != ')')))
    {
        //�������λ ����ǰһ��Ϊ������������������ţ�����˵����������
        return true;
    }
    else return false;

}

//��ջ
void Push(Stack S,ElementType X)
{
    if (S->Top != Maxsize-1)
    {
        S->Data[++(S->Top)]=X;

    }
    else printf("ջ������ջʧ��\n");
}

//��ջ,����ջ��Ԫ��  ����ɾ����ջ�еĸ�Ԫ��  ��Ϊ�´���ջ�Ḳ��Ԫ��
ElementType Pop(Stack S)
{
    if (S->Top != -1)
    {

        return (S->Data[(S->Top)--]);
        //printf("%c��ջ�ɹ�\n",S->Data[(S->Top)+1]);
    }
    else 
    {
        printf("S->TopΪ%d,ջ��\n",S->Top);
        return '0';
    }
}

//����ջ��Ԫ��
ElementType Peek(Stack S)
{
    return(S->Data[(S->Top)]);
} 

Precedence GetToken(char op)//������������ȼ�
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

char GetOp(char *expr,int *i,char *Postfix,int *j)//��������֣�ֱ��д��Postfix[]�����ء�0������������ͷ��������
{
    //֮������*i,*j ָ��ķ�ʽ��ֵ������ΪҪ�ı������ֵ���������������֣�ToPostfix��ѭ������i�ƽ��ü�λ��
    if (isdigit(expr[(*i)]))//���� 
    {
        //����ַ�����i���ַ���Ҳ���ǵ�ǰ���������ַ��������ֻ���С����Ļ����ʹ浽Postfix�ַ�����ȥ
        while(isdigit(expr[(*i)]) || (expr[(*i)]=='.'))  Postfix[(*j)++]=expr[(*i)++];

        Postfix[(*j)++]=' ';//����һ��Ϊ�ո�����j�ƽ�һλ
        (*i)--;//���һ��ִ��i�����һλ�����Լ�һ
        return '0';
    }
    switch(expr[(*i)])
    {
        case '+'://��������� �ʹ���һ�ʼ�������������Postfix[]
            if (IsSign(expr,(*i)))
            {
                (*i)++;
                return GetOp(expr,i,Postfix,j);//����i��j�Ѿ��ǵ�ַ�ˣ�����ֱ�Ӱ�i,j���ν�ȥ
            }
            else return '+';//���������� �� ��ֱ�ӷ��������
        case '-':
            if (IsSign(expr,(*i)))
            {
                Postfix[(*j)++]='-';//����Ǹ��� �������ַ���Postfix���븺��
                (*i)++;
                return GetOp(expr,i,Postfix,j);
            }
            else return '-';//���������� �� ��ֱ�ӷ��������
        default: return expr[(*i)];//�������������жϣ�ֱ�ӷ���
    }
}

void ToPostfix(char *expr,char *expr1)
{
    int i,j,L;
    char Postfix[2*Maxsize],Op;
    Stack S;//������ջS
    Precedence token;

    S=CreatStack(Maxsize);//��ʼ����ջS
    L=strlen(expr);//LΪ�ַ�������
    j=0;//jָ��Postfix[]��ǰҪд���λ�� Postfix���׺���ʽ

    for(i=0;i<L;i++)
    {
        Op=GetOp(expr,&i,Postfix,&j);//ȡ�����
        if (Op == '0')continue;//�����־�ɨ����һ��
        token =GetToken(Op);//ȡ��������ȼ�
        switch(token)
        {
            case lpr: Push(S,'(');break;//��������ջ
            case rpr://�����ڵı��ʽɨ����� �Ͱѵ�������֮ǰ�����������д��Postfix
                while (Peek(S) != '(')
                {

                    Postfix[j++]= Pop(S);
                    Postfix[j++]= ' ';
                }
                Pop(S);//ɾ��������
                break;
            default://��������� ��Ҫ��ջ��������Ƚ����ȼ�

                while (!IsEmpty(S) && Peek(S)!='(' && token<=GetToken(Peek(S)) )//�����ջ�ǿ� �� δɨ�赽�� �� ��ǰ��������ȼ�С�ڵ���ջ������� 
                {

                    Postfix[j++]=Pop(S);
                    Postfix[j++]=' ';
                }

  
                Push(S,Op);//��ǰ�������ջ
                break;
        }
    }
    //�ַ���ɨ�������
    
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
    char num[Maxsize]="";//��ʱ�ַ�����������ÿ����
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
            memset(num,0,Maxsize);//����ַ���
            Push(S,num);
        }
        else//���ɨ�赽��������������������ջ����
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
    ToPostfix(Str,expr);//��expr������ֵ���ʽ
    ToPostend(expr);
    return 0;

}