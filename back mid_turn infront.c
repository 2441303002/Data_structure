#include <stdio.h>
#include <stdlib.h>
#define MAXN 30
typedef int ElementType;
//bintree是指针
typedef struct TNode* BinTree;
//树的数据类型定义
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    //指向左右子树
};
//函数声明
BinTree BuildTree(int Inorder[],int Postorder[],int N);
void PreorderTraversal(BinTree BT);

int main()
{
    BinTree T;
    int Inorder[MAXN],Postorder[MAXN],N,i;
    //结点数
    scanf("%d",&N);
    //后序
    for (i=0;i<N;i++) scanf("%d",&Postorder[i]);
    //中序
    for (i=0;i<N;i++) scanf("%d",&Inorder[i]);
    //根据中序与后序，建立一个节点数为N的树
    T =BuildTree(Inorder,Postorder,N);
    printf("Preorder:");
    //前序遍历并输出T树
    PreorderTraversal(T);
}

//前序遍历输出T
void PreorderTraversal(BinTree T)
{
    if (T)
    {//若指针不为空
        printf("%d ",T->Data);
        PreorderTraversal(T->Left);
        PreorderTraversal(T->Right);
    }
}

BinTree BuildTree(int Inorder[],int Postorder[],int N)
{
    BinTree T;
    int p;
    //若空树，递归终止
    if (!N) return NULL;
    T=(BinTree)malloc(sizeof(struct TNode));
    //新树的根结点值为后序数组的最后一位
    T->Data=Postorder[N-1];
    T->Left=T->Right=NULL;

    //遍历中序数组找出对应根结点数据的下标 左侧的为左树 右侧的就是右树
    for (p=0;p<N;p++)
        if (Inorder[p] == Postorder[N-1])break;
    //再对左树和右树递归处理
    //后序数组的0到p-1位就是左树 第p-1位就是左树的根结点值
    T->Left=BuildTree(Inorder,Postorder,p);

    //切割中序数组左边p+1项
    //切割后序数组左边多余的部分和最右边对应根结点值的一位
    //数组长度减小（p+1）
    
    //数组名加常数可以跳过常数个数据类型的空间
    T->Right=BuildTree(Inorder+p+1,Postorder+p,N-p-1);

    return T;

}   