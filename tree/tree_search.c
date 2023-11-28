#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct TNode *BinTree;
struct TNode /* 树结点定义 */
{
    ElementType Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
};
typedef BinTree Position;

BinTree Create_Bintree()
{ // 前序建二叉树
    BinTree T;
    ElementType x;
    scanf("%d", &x);
    if (x == 0)
        T = NULL;
    else
    {
        T = (BinTree)malloc(sizeof(struct TNode));
        T->Data = x;                 // 生成根结点
        T->Left = Create_Bintree();  // 构造左子树
        T->Right = Create_Bintree(); // 构造右子树
    }
    return T;
}

// 查找搜索树中元素
BinTree Find(BinTree BST, ElementType X)
{
    while (BST)
    {
        if (X > BST->Data)
            BST = BST->Right;
        else if (X < BST->Data)
            BST = BST->Left;
        else
            break; /* 在当前结点查找成功，跳出循环 */
    }
    return BST; /* 返回找到的结点地址，或是NULL */
}

// 插入元素
BinTree Insert(BinTree BST, ElementType X)
{
    if (BST == NULL)
    { /*若原树为空，生成并返回一个结点的二叉搜索树*/
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    { /* 开始找要插入元素的位置 */
        if (X < BST->Data)
            BST->Left = Insert(BST->Left, X);
        /*递归插入左子树*/
        else if (X > BST->Data)
            BST->Right = Insert(BST->Right, X);
        /*递归插入右子树*/
        /* else X已经存在，什么都不做 */
    }
    return BST;
}

Position FindMin(BinTree BST)
{
    if (BST == NULL)
    {
        return NULL;
    }
    else if (BST->Left == NULL)
    {
        return BST;
    }
    else
    {
        return FindMin(BST->Left);
    }
}

// 删除树中元素
BinTree Delete(BinTree BST, ElementType X)
{
    BinTree Tmp;
    if (BST == NULL)
        printf("要删除的元素未找到");
    else
    {
        if (X < BST->Data)
            BST->Left = Delete(BST->Left, X); /*左子树递归删除 */
        else if (X > BST->Data)
            BST->Right = Delete(BST->Right, X); /* 从右子树递归删除 */
        else //找到BST，调整位置，策略：找到右子树最小元素顶上
        {
            if (BST->Left && BST->Right)
            {
                Tmp = FindMin(BST->Right);
                BST->Data = Tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data);   //重新删除
            }
            else   //叶结点，或仅有一支的结点
            {
                Tmp = BST;
                if (BST->Left==NULL)
                    BST = BST->Right;
                else
                    BST = BST->Left;
                free(Tmp);
            }
        }
    }
    return BST;
}

int main()
{
    BinTree T, BST;
    int X;
    printf("请按先序序列输入结点信息（空用0来表示）\n");
    T = Create_Bintree();
    printf("请输入要查找的信息：");
    scanf("%d", &X);
    BST = Find(T, X);
    if (BST)
        printf("找到了！");
    else
        printf("没有找到！");
    return 0;
}
