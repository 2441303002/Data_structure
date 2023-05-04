//1.�ж��Ƿ�Ϊ��С�Ĵ�Ȩ·������
//2.�ж�ǰ׺���Ƿ��������Ҷ�ӽڵ�ı���
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//����ʹ�ö���ģ�⽨�����̣������С��Ȩ·������

//���ж���
#define Maxsize 20
typedef int ElementType; 
typedef struct QNode* Quene; 
struct QNode{
    ElementType * Data;//Ȩ������
    int front,rear;//��ͷ��β�±�
}; 

//��������
Quene Init();
int IsEmpty();
void AddQ(Quene Q,ElementType X);
ElementType DeleteQ(Quene Q);

int main()
{
    //������������СWPL
    int N,round,weight,sum=0;//n���ַ�������round���ж����ױ���
    int weightlis[100];//����Ȩ��
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
    {//ʣ��һ��Ԫ��ʱֹͣ
        //����С������Ԫ�س��У��������
        int x,y;
        x=DeleteQ(Q);
        y=DeleteQ(Q);

        sum+=(x+y);

        AddQ(Q,x+y);
    }
    printf("Best_WPL=%d\n",sum);
    


    
    //�����������������
    typedef struct BNode* BinTree;
    struct BNode{
        int flag;//�б��Ƿ�ΪҶ��� ��Ϊ1 ��Ϊ0
        BinTree Left;
        BinTree Right;
    };

    
    //����������ÿ�ױ��룬�������ǵ�WPL�������������Ƿ�����ǰ׺��Ҫ����΢��Ƶ4-10��
    scanf(" %d",&round);
    
    for (int i=0;i<round;i++)//i�Ƕ�ÿ�ױ������
    {
        //ÿ�ױ��붼��ʼ����
        BinTree Root=(BinTree)malloc(sizeof(struct BNode));
        Root->flag=0;
        Root->Left=NULL;
        Root->Right=NULL;
        int wrong=0;//��¼���ױ����򲻷���ǰ׺�Զ����µĴ������
        int wpl=0;
        for (int j=0;j<N;j++)//j�Ƕ�ÿһ��������ַ��ͱ������
        {
            //ptr���������� ÿ�ζ��Ӹ���ʼ����
            BinTree ptr=Root;
            scanf(" %c",&c);
            scanf(" %s",code);
            wpl+=(strlen(code))*(weightlis[j]);
            //����
            for (int k=0;k<strlen(code);k++)//k�ǶԱ���ÿһλ���б���
            {
                if (code[k]=='0')
                {//������̽
                    if (ptr->Left == NULL)
                    {//�������ڽ�㣬�ͽ����½��
                        BinTree newnode=(BinTree)malloc(sizeof(struct BNode));

                        newnode->flag=0;
                        newnode->Left=NULL;
                        newnode->Right=NULL;

                        ptr->Left=newnode;
                    }
                    else
                    {//���Ѿ����ڽ�㣬�жϽ���ǲ���Ҷ���
                        if (ptr->Left->flag==1)
                        {
                            printf("���Ѿ�����Ҷ��㣬�������������ǵ�ǰ����%s��ǰ׺����ǰ�������ǵ�%dλ\n",code,k);
                            wrong++;
                        }
                        else
                        {
                            if (k==strlen(code)-1)//����Ǳ������һλ����ʾ������ΪҶ���,Ӧ���ж�����������������������˵����ǰ��������һ�����ǰ׺
                            {
                                if (ptr->Left->Left == NULL && ptr->Left->Right == NULL) {ptr->Left->flag=1;printf("ĩλ�����������½��\n");}
                                else
                                {
                                    printf("��ĩλ�������������ǰ����%s�����������ǰ׺����ǰ�������ǵ�%dλ\n",code,k);
                                    wrong++;
                                }
                            }
                        }
                    }
                    ptr=ptr->Left;
                }
                else if (code[k]=='1')
                {//������̽
                    if (ptr->Right == NULL)
                    {//�������ڽ�㣬�ͽ����½��
                        BinTree newnode=(BinTree)malloc(sizeof(struct BNode));

                        newnode->flag=0;
                        newnode->Left=NULL;
                        newnode->Right=NULL;

                        ptr->Right=newnode;
                    }
                    else
                    {//���Ѿ����ڽ�㣬�жϽ���ǲ���Ҷ���                        
                        if (ptr->Right->flag==1)
                        {
    
                            printf("���Ѿ�����Ҷ��㣬�������������ǵ�ǰ����%s��ǰ׺\n",code);
                            wrong++;
                        }
                        else
                        {//����Ҷ���
                            if (k==strlen(code)-1)//����Ǳ������һλ����ʾ������ΪҶ���,Ӧ���ж�����������������������˵����ǰ��������һ�����ǰ׺
                            {
                                if (ptr->Right->Left == NULL && ptr->Right->Right == NULL) {ptr->Right->flag=1;printf("ĩλ����������Ҷ���\n");}
                                else
                                {
                                    printf("��ĩλ�������������ǰ����%s�����������ǰ׺����ǰ�������ǵ�%dλ\n",code,k);
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
{//��ʼ��
    Quene Q=(Quene)malloc(sizeof(struct QNode));
    Q->Data=(ElementType*)malloc(Maxsize*sizeof(ElementType));
    Q->front=Q->rear=0;
    return Q;
}

int IsEmpty(Quene Q)
{//�Ƿ�Ϊ��
    return ((Q->rear)-(Q->front));
}

void AddQ(Quene Q,ElementType X)
{//��� Ҫ������С��������
    if (IsEmpty(Q)==0)
    {//ֱ�Ӽ����
        Q->Data[++(Q->rear)]=X;
    }
    else
    {//�Ҳ���λ��
        for(int i=(Q->front)+1;i<Maxsize;i++)
        {
            if (X<=Q->Data[i])
            {//XӦ�ó�Ϊ��i��
                //��������Ԫ�غ���
                for(int j=Maxsize-1;j>i;j--)
                {
                    Q->Data[j]=Q->Data[j-1];
                }
                //����X
                Q->Data[i]=X;
                (Q->rear)++;
                return;
            }
        }
        //���������Ԫ�ض��� ֱ�Ӽ����
        Q->Data[++(Q->rear)]=X;
    }
}

ElementType DeleteQ(Quene Q)
{//�򵥳���
    return Q->Data[++(Q->front)];
}