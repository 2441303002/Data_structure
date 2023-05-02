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
{//判断堆栈是否已满
    return (S->Top==(S->Maxsize)-1);
}

int IsEmpty(Stack S)
{//判断堆栈是否为空
    return ((S->Top)==-1);
}

void Push(Stack S,ElementType X)
{//入栈
    S->Data[++(S->Top)]=X;

}

ElementType Pop(Stack S)
{//返回并删除栈顶元素
        return (S->Data[(S->Top)--]);
}



int main()
{
    int N1,N2,num;
    Stack S1,S2;
    char op='0';//存操作类型 A入列 D出列
    //表示两堆栈大小 容量小的作为S1堆栈，用入栈模拟队尾入列
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
        scanf(" %c",&op);//格式控制串前加空格可以防止scanf读取空格
        if (op == 'A')
        {//入列操作
            scanf("%d",&num);
            //先判断S1栈有没有满
            if (!IsFull(S1))
            {//若S1未满，直接入栈
                Push(S1,num);
            }
            else
            {//如果S1满了，就先判断S2有没有元素 如果有Error Full 如果没有就让S1元素依次入栈S2

                if (IsEmpty(S2))
                {
                    while (!IsEmpty(S1))
                    {
                        Push(S2,Pop(S1));
                    }
                    //再让num入列
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
        {//出列操作
            //先判断S2是否为空
            if (IsEmpty(S2))
            {//若S2为空
                if (IsEmpty(S1))
                {//且S1为空 说明队列为空 输出Error
                    printf("ERROR:Empty\n");
                }
                else
                {//若S1不为空 就让S1元素依次入栈S2
                    while (!IsEmpty(S1))
                    {
                        Push(S2,Pop(S1));
                    }
                    //再出列
                    printf("%d\n",Pop(S2));
                }
            }
            else
            {//若不为空，直接出栈
                printf("%d\n",Pop(S2));
            }
        }
    }
}