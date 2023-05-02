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
    int flag_file;//用来判断这个结点是文件（叶）还是目录 1是目录 0是文件
};

//函数声明
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
{//初始化
    //为树和数据域要空间
    BinTree T=(BinTree)malloc(sizeof(struct TNode));
    T->Data=(ElementType*)malloc(Max*sizeof(ElementType));
    T->Leftchild=T->Rightbrother=NULL;
    //注意不能直接对指针（字符数组名）赋值，应该用strcpy函数
    strcpy(T->Data,str);
    T->flag_file=1;//root是目录  1是目录 0是文件
    return T;
}

//根据字符串建树 步骤为先分割字符串，再插入树
void CreatTree(BinTree T,ElementType *str)
{
    ElementType file[Max];//存分割后的单个字符串
    int index=0;//单个字符串的头位置
    int i,j;
    for(i=0;i<strlen(str);i++)
    {// i遍历字符串
        if (str[i]== '\\')//反斜杠需要转义
        {//如果遇到反斜杠，就把index位置到反斜杠位置的单个字符串存到file中
            
            for(j=0;index<i;file[j++]=str[index++]);

            file[j]='\0';
            index++;//index从斜杠位置向后推进一位，到下一个字符串的头位置
            //把目录结点插入到树
            T=InsertNode(T,file,1);
        }
    }
    //如果字符串以斜杠结尾那么表示路径，否则表示文件
    //表示文件就要做特殊处理，把文件加到file中
    if (index < strlen(str))
    {//判断的方法就是看index有没有遍历到尾部，如果是以斜杠结尾，那么index最终会到尾部斜杠位置+1的位置
        for(j=0;index<strlen(str);file[j++]=str[index++]);
        file[j]='\0';
        index++;
        //把文件结点插入到树
        T=InsertNode(T,file,0);
        //返回指针位置，下次连续添加就不用再移动指针位置
    }
    else printf("\n");
    
}

//将单字符串插入目录树
BinTree InsertNode(BinTree T, ElementType* str, int flag)
{
    BinTree ptr,pre;
    //先建立新结点
    BinTree newnode=Init(str);
    newnode->flag_file=flag;

    if (T->Leftchild == NULL)
    {//如果所在目录没孩子，直接插入新结点
        T->Leftchild = newnode;
        return T->Leftchild;
    }

    //prt和pre遍历
    ptr=T->Leftchild;
    //prt是根目录长子
    pre=T;
    //在目录所有兄弟里找要插入的位置 要保持目录在前的字典序
    //注意字符串不能直接比较，要用strcmp,否则只会比较第一个字符
    while(ptr != NULL && ((ptr->flag_file > newnode->flag_file) || (ptr->flag_file == newnode->flag_file && strcmp(str,ptr->Data)>0)))
    {//优先保证目录在前，然后保证字典序
        pre=ptr;
        ptr=ptr->Rightbrother;
    }
    //ptr变成了要插入的位置
    //无处可插入，插在链尾
    if (ptr==NULL)
    {
        newnode->Rightbrother=pre->Rightbrother;
        pre->Rightbrother=newnode;
        return newnode;
    }
    //若文件或目录已存在 即要插入的位置上 结点完全相同
    else if (strcmp(ptr->Data,newnode->Data)==0 && ptr->flag_file==newnode->flag_file)
    {
        //这次不做操作，下次在ptr目录下操作
        return ptr;
    }
    else//找到了应该插入的位置
    {
        if (strcmp(pre->Data,T->Data)==0)//如果前驱节点是根目录，插在根目录的长子位
        {
            newnode->Rightbrother=pre->Leftchild;
            pre->Leftchild=newnode;
        }
        else //正常插入
        {
            newnode->Rightbrother=pre->Rightbrother;
            pre->Rightbrother=newnode;
        }
        return newnode;  //接下来以newnode为根目录操作
    }
}


//先序输出树
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
    printf("%s(%d)\n",T->Data,CountSize(T->Leftchild));    //前序遍历
    PreOrderTraverse(T->Leftchild,space + 2);    //下一层多两个空格
    PreOrderTraverse(T->Rightbrother,space);    //兄弟结点不需要多空格

}

int CountSize(BinTree root)
{
    if (root == NULL) return 0;
    return 1+CountSize(root->Leftchild)+CountSize(root->Rightbrother);

}
/* 
//计算深度
int BTreeDepth(BinTree T) {
    if (T == NULL) {
        return 0;
    } else {
        int left_height = BTreeDepth(T->Leftchild);
        int right_height = BTreeDepth(T->Rightbrother);
        return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
    }
}

//层序输出树（递归）
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

