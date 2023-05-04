//1.判断是否为最小的带权路径长度
//2.判断前缀码是否包含其他叶子节点的编码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//首先使用队列模拟建树过程，求出最小带权路径长度

//队列定义
#define Maxsize 20
typedef int ElementType; 
typedef struct QNode* Quene; 
struct QNode{
    ElementType * Data;//权重数组
    int front,rear;//队头队尾下标
}; 

//函数声明
Quene Init();
int IsEmpty();
void AddQ(Quene Q,ElementType X);
ElementType DeleteQ(Quene Q);

int main()
{
    //借助队列求最小WPL
    int N,round,weight,sum=0;//n是字符个数，round是有多少套编码
    int weightlis[100];//储存权重
    char c;
    char code[64];
    Quene Q=Init();
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        scanf(" %c",&c);
        scanf(" %d",&weight);
        weightlis[i]=weight;
        AddQ(Q,weight);

    }

    while(IsEmpty(Q)>1)
    {//剩余一个元素时停止
        //将最小的两个元素出列，相加入列
        int x,y;
        x=DeleteQ(Q);
        y=DeleteQ(Q);

        sum+=(x+y);

        AddQ(Q,x+y);
    }
    printf("Best_WPL=%d\n",sum);
    


    
    //定义二叉树数据类型
    typedef struct BNode* BinTree;
    struct BNode{
        int flag;//判别是否为叶结点 是为1 否为0
        BinTree Left;
        BinTree Right;
    };

    
    //接下来输入每套编码，计算它们的WPL，并建树，看是否满足前缀码要求（书微视频4-10）
    scanf(" %d",&round);
    
    for (int i=0;i<round;i++)//i是对每套编码遍历
    {
        //每套编码都初始化树
        BinTree Root=(BinTree)malloc(sizeof(struct BNode));
        Root->flag=0;
        Root->Left=NULL;
        Root->Right=NULL;
        int wrong=0;//记录这套编码因不符合前缀性而导致的错误次数
        int wpl=0;
        for (int j=0;j<N;j++)//j是对每一次输入的字符和编码遍历
        {
            //ptr用来遍历树 每次都从根开始遍历
            BinTree ptr=Root;
            scanf(" %c",&c);
            scanf(" %s",code);
            wpl+=(strlen(code))*(weightlis[j]);
            //建树
            for (int k=0;k<strlen(code);k++)//k是对编码每一位进行遍历
            {
                if (code[k]=='0')
                {//向左试探
                    if (ptr->Left == NULL)
                    {//若不存在结点，就建立新结点
                        BinTree newnode=(BinTree)malloc(sizeof(struct BNode));

                        newnode->flag=0;
                        newnode->Left=NULL;
                        newnode->Right=NULL;

                        ptr->Left=newnode;
                    }
                    else
                    {//若已经存在结点，判断结点是不是叶结点
                        if (ptr->Left->flag==1)
                        {
                            printf("左已经存在叶结点，存在其他编码是当前编码%s的前缀，当前遍历的是第%d位\n",code,k);
                            wrong++;
                        }
                        else
                        {
                            if (k==strlen(code)-1)//如果是编码最后一位，表示这个结点为叶结点,应该判断它有无子树，若有子树，说明当前编码是另一编码的前缀
                            {
                                if (ptr->Left->Left == NULL && ptr->Left->Right == NULL) {ptr->Left->flag=1;printf("末位左正常插入新结点\n");}
                                else
                                {
                                    printf("左末位结点有子树，当前编码%s是其他编码的前缀，当前遍历的是第%d位\n",code,k);
                                    wrong++;
                                }
                            }
                        }
                    }
                    ptr=ptr->Left;
                }
                else if (code[k]=='1')
                {//向右试探
                    if (ptr->Right == NULL)
                    {//若不存在结点，就建立新结点
                        BinTree newnode=(BinTree)malloc(sizeof(struct BNode));

                        newnode->flag=0;
                        newnode->Left=NULL;
                        newnode->Right=NULL;

                        ptr->Right=newnode;
                    }
                    else
                    {//若已经存在结点，判断结点是不是叶结点                        
                        if (ptr->Right->flag==1)
                        {
    
                            printf("右已经存在叶结点，存在其他编码是当前编码%s的前缀\n",code);
                            wrong++;
                        }
                        else
                        {//不是叶结点
                            if (k==strlen(code)-1)//如果是编码最后一位，表示这个结点为叶结点,应该判断它有无子树，若有子树，说明当前编码是另一编码的前缀
                            {
                                if (ptr->Right->Left == NULL && ptr->Right->Right == NULL) {ptr->Right->flag=1;printf("末位右正常插入叶结点\n");}
                                else
                                {
                                    printf("右末位结点有子树，当前编码%s是其他编码的前缀，当前遍历的是第%d位\n",code,k);
                                    wrong++;
                                }
                                
                            }
                        }
                    }
                    ptr=ptr->Right;
                }
            }
            
            
        }
        free(Root);
        
        printf("sum=%d wpl=%d\n",sum,wpl);
        if (wrong==0 && sum == wpl) printf("Yes\n");
        else printf("No\n");
    }
    
    
}






Quene Init()
{//初始化
    Quene Q=(Quene)malloc(sizeof(struct QNode));
    Q->Data=(ElementType*)malloc(Maxsize*sizeof(ElementType));
    Q->front=Q->rear=0;
    return Q;
}

int IsEmpty(Quene Q)
{//是否为空
    return ((Q->rear)-(Q->front));
}

void AddQ(Quene Q,ElementType X)
{//入队 要求必须从小到大有序
    if (IsEmpty(Q)==0)
    {//直接简单入队
        Q->Data[++(Q->rear)]=X;
    }
    else
    {//找插入位置
        for(int i=(Q->front)+1;i<Maxsize;i++)
        {
            if (X<=Q->Data[i])
            {//X应该成为第i项
                //后面所有元素后移
                for(int j=Maxsize-1;j>i;j--)
                {
                    Q->Data[j]=Q->Data[j-1];
                }
                //插入X
                Q->Data[i]=X;
                (Q->rear)++;
                return;
            }
        }
        //如果比所有元素都大 直接简单入队
        Q->Data[++(Q->rear)]=X;
    }
}

ElementType DeleteQ(Quene Q)
{//简单出队
    return Q->Data[++(Q->front)];
}