#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char ElementType;
typedef struct TNode* BinTree;
#define Max 260
struct TNode
{
    ElementType *Data;
    BinTree Leftchild;
    BinTree Rightbrother;
    int flag_file;//�����ж����������ļ���Ҷ������Ŀ¼ 1��Ŀ¼ 0���ļ�
};

//��������
BinTree Init();
void CreatTree(BinTree T,ElementType *str);
BinTree InsertNode(BinTree T, ElementType* str, int flag);
//void BTreeLevelOrder(BinTree root);
void PreOrderTraverse(BinTree T, int space);
int CountSize(BinTree root);

int main()
{
    int N;
    ElementType Str[Max];
    BinTree tree=Init("Root");
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        scanf("%s",Str);
        CreatTree(tree,Str);
    }
    PreOrderTraverse(tree,0);
    return 0;
}

BinTree Init(ElementType* str)
{//��ʼ��
    //Ϊ����������Ҫ�ռ�
    BinTree T=(BinTree)malloc(sizeof(struct TNode));
    T->Data=(ElementType*)malloc(Max*sizeof(ElementType));
    T->Leftchild=T->Rightbrother=NULL;
    //ע�ⲻ��ֱ�Ӷ�ָ�루�ַ�����������ֵ��Ӧ����strcpy����
    strcpy(T->Data,str);
    T->flag_file=1;//root��Ŀ¼  1��Ŀ¼ 0���ļ�
    return T;
}

//�����ַ������� ����Ϊ�ȷָ��ַ������ٲ�����
void CreatTree(BinTree T,ElementType *str)
{
    ElementType file[Max];//��ָ��ĵ����ַ���
    int index=0;//�����ַ�����ͷλ��
    int i,j;
    for(i=0;i<strlen(str);i++)
    {// i�����ַ���
        if (str[i]== '\\')//��б����Ҫת��
        {//���������б�ܣ��Ͱ�indexλ�õ���б��λ�õĵ����ַ����浽file��
            
            for(j=0;index<i;file[j++]=str[index++]);

            file[j]='\0';
            index++;//index��б��λ������ƽ�һλ������һ���ַ�����ͷλ��
            //��Ŀ¼�����뵽��
            T=InsertNode(T,file,1);
        }
    }
    //����ַ�����б�ܽ�β��ô��ʾ·���������ʾ�ļ�
    //��ʾ�ļ���Ҫ�����⴦�����ļ��ӵ�file��
    if (index < strlen(str))
    {//�жϵķ������ǿ�index��û�б�����β�����������б�ܽ�β����ôindex���ջᵽβ��б��λ��+1��λ��
        for(j=0;index<strlen(str);file[j++]=str[index++]);
        file[j]='\0';
        index++;
        //���ļ������뵽��
        T=InsertNode(T,file,0);
        //����ָ��λ�ã��´�������ӾͲ������ƶ�ָ��λ��
    }
    else printf("\n");
    
}

//�����ַ�������Ŀ¼��
BinTree InsertNode(BinTree T, ElementType* str, int flag)
{
    BinTree ptr,pre;
    //�Ƚ����½��
    BinTree newnode=Init(str);
    newnode->flag_file=flag;

    if (T->Leftchild == NULL)
    {//�������Ŀ¼û���ӣ�ֱ�Ӳ����½��
        T->Leftchild = newnode;
        return T->Leftchild;
    }

    //prt��pre����
    ptr=T->Leftchild;
    //prt�Ǹ�Ŀ¼����
    pre=T;
    //��Ŀ¼�����ֵ�����Ҫ�����λ�� Ҫ����Ŀ¼��ǰ���ֵ���
    //ע���ַ�������ֱ�ӱȽϣ�Ҫ��strcmp,����ֻ��Ƚϵ�һ���ַ�
    while(ptr != NULL && ((ptr->flag_file > newnode->flag_file) || (ptr->flag_file == newnode->flag_file && strcmp(str,ptr->Data)>0)))
    {//���ȱ�֤Ŀ¼��ǰ��Ȼ��֤�ֵ���
        pre=ptr;
        ptr=ptr->Rightbrother;
    }
    //ptr�����Ҫ�����λ��
    //�޴��ɲ��룬������β
    if (ptr==NULL)
    {
        newnode->Rightbrother=pre->Rightbrother;
        pre->Rightbrother=newnode;
        return newnode;
    }
    //���ļ���Ŀ¼�Ѵ��� ��Ҫ�����λ���� �����ȫ��ͬ
    else if (strcmp(ptr->Data,newnode->Data)==0 && ptr->flag_file==newnode->flag_file)
    {
        //��β����������´���ptrĿ¼�²���
        return ptr;
    }
    else//�ҵ���Ӧ�ò����λ��
    {
        if (strcmp(pre->Data,T->Data)==0)//���ǰ���ڵ��Ǹ�Ŀ¼�����ڸ�Ŀ¼�ĳ���λ
        {
            newnode->Rightbrother=pre->Leftchild;
            pre->Leftchild=newnode;
        }
        else //��������
        {
            newnode->Rightbrother=pre->Rightbrother;
            pre->Rightbrother=newnode;
        }
        return newnode;  //��������newnodeΪ��Ŀ¼����
    }
}


//���������
void PreOrderTraverse(BinTree T, int space)
{
    if (T == NULL)
        return;
    for (int i = 0; i < space; i++)
    {
        printf(" ");
    }
    if (T->Leftchild==NULL) printf("%s(1)\n",T->Data);
    else
    printf("%s(%d)\n",T->Data,CountSize(T->Leftchild));    //ǰ�����
    PreOrderTraverse(T->Leftchild,space + 2);    //��һ��������ո�
    PreOrderTraverse(T->Rightbrother,space);    //�ֵܽ�㲻��Ҫ��ո�

}

int CountSize(BinTree root)
{
    if (root == NULL) return 0;
    return 1+CountSize(root->Leftchild)+CountSize(root->Rightbrother);

}
/* 
//�������
int BTreeDepth(BinTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int left_height = BTreeDepth(T->Leftchild);
        int right_height = BTreeDepth(T->Rightbrother);
        return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
    }
}

//������������ݹ飩
void _BTreeLevelOrder(BinTree root, size_t i)
{
    if (root == NULL || i == 0)
    {
        return;
    }
    if (i == 1)
    {
        printf("%s ",root->Data);
        return;
    }
    _BTreeLevelOrder(root->Leftchild, i - 1);
    _BTreeLevelOrder(root->Rightbrother, i - 1);
}

void BTreeLevelOrder(BinTree root)
{
    if (root == NULL)
        return;
    int dep = BTreeDepth(root);
    for (int i = 1; i <= dep; i++)
    {
        printf("   ");
        _BTreeLevelOrder(root, i);
        printf("\n");
    }

}
 */

