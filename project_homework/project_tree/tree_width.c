#include <stdio.h>
#include <stdlib.h>
#define NoInfo '#'
#define Maxn 100

// 树
typedef char ElementType;
typedef struct TNode *BinTree; /* 二叉树类型 */
struct TNode
{                     /* 树结点定义 */
    ElementType Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
};

// 先序创建二叉树
BinTree Create_Bintree()
{
	BinTree bt;
	char ch;
	if ((ch = getchar()) == '#')
	{
		bt = NULL;
	}
	else
	{
		bt = (BinTree)malloc(sizeof(struct TNode));
		(bt)->Data = ch;
		(bt)->Left = Create_Bintree();	// 创建左子树
		(bt)->Right = Create_Bintree(); // 创建右子树
	}
	return bt;
}

// 计算宽度
int *get_width(BinTree BT,int depth,int *width)
{
    if(BT)
    {
        width[depth]++;
        get_width(BT->Left,depth+1,width);
        get_width(BT->Right,depth+1,width);
    }
    return width;
}

//最大值
int max_width(int*width)
{
    int *p,max_index=0;
    p=width;
    while(*p!=0)
    {
        if(*p>max_index)max_index=*p;
        p++;
    }
    return max_index;
}

int main()
{
    BinTree T;
    int width[1000]={0};
    printf("请用先序输入结点信息,空为'#'\n");
    T = Create_Bintree();
    printf("%d",max_width(get_width(T,0,width)));
    return 0;
}