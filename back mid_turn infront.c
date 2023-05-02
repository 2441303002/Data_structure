#include <stdio.h>
#include <stdlib.h>
#define MAXN 30
typedef int ElementType;
//bintree��ָ��
typedef struct TNode* BinTree;
//�����������Ͷ���
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    //ָ����������
};
//��������
BinTree BuildTree(int Inorder[],int Postorder[],int N);
void PreorderTraversal(BinTree BT);

int main()
{
    BinTree T;
    int Inorder[MAXN],Postorder[MAXN],N,i;
    //�����
    scanf("%d",&N);
    //����
    for (i=0;i<N;i++) scanf("%d",&Postorder[i]);
    //����
    for (i=0;i<N;i++) scanf("%d",&Inorder[i]);
    //������������򣬽���һ���ڵ���ΪN����
    T =BuildTree(Inorder,Postorder,N);
    printf("Preorder:");
    //ǰ����������T��
    PreorderTraversal(T);
}

//ǰ��������T
void PreorderTraversal(BinTree T)
{
    if (T)
    {//��ָ�벻Ϊ��
        printf("%d ",T->Data);
        PreorderTraversal(T->Left);
        PreorderTraversal(T->Right);
    }
}

BinTree BuildTree(int Inorder[],int Postorder[],int N)
{
    BinTree T;
    int p;
    //���������ݹ���ֹ
    if (!N) return NULL;
    T=(BinTree)malloc(sizeof(struct TNode));
    //�����ĸ����ֵΪ������������һλ
    T->Data=Postorder[N-1];
    T->Left=T->Right=NULL;

    //�������������ҳ���Ӧ��������ݵ��±� ����Ϊ���� �Ҳ�ľ�������
    for (p=0;p<N;p++)
        if (Inorder[p] == Postorder[N-1])break;
    //�ٶ������������ݹ鴦��
    //���������0��p-1λ�������� ��p-1λ���������ĸ����ֵ
    T->Left=BuildTree(Inorder,Postorder,p);

    //�и������������p+1��
    //�и����������߶���Ĳ��ֺ����ұ߶�Ӧ�����ֵ��һλ
    //���鳤�ȼ�С��p+1��
    
    //�������ӳ������������������������͵Ŀռ�
    T->Right=BuildTree(Inorder+p+1,Postorder+p,N-p-1);

    return T;

}   