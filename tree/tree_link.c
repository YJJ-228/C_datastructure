#include <stdio.h>
#include <stdlib.h>
#define NoInfo '#'
#define Maxn 100

// 树
typedef char ElementType;
typedef struct TNode *BinTree; /* 二叉树类型 */
struct TNode
{					  /* 树结点定义 */
	ElementType Data; /* 结点数据 */
	BinTree Left;	  /* 指向左子树 */
	BinTree Right;	  /* 指向右子树 */
};

// 队列,用于遍历时使用
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode
{
	BinTree *data;		  /* 存储元素的数组 */
	Position Front, Rear; /* 队列的头、尾指针 */
	int MaxSize;		  /* 队列最大容量 */
};
typedef PtrToQNode Queue;

// 创建队列
Queue CreatQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->data = (BinTree *)malloc(MaxSize * sizeof(struct TNode));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

// 检查队列是否为满
bool IsFull(Queue Q)
{
	return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

// 在队列中添加节点
bool AddQ(Queue Q, BinTree T)
{
	if (IsFull(Q))
	{
		printf("队列满");
		return false;
	}
	else
	{
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->data[Q->Rear] = T;
		return true;
	}
}

bool IsEmpty(Queue Q)
{
	return (Q->Front == Q->Rear);
}

BinTree DeleteQ(Queue Q)
{
	if (IsEmpty(Q))
	{
		printf("队列空");
		return NULL;
	}
	else
	{
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return Q->data[Q->Front];
	}
}

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

// 中序遍历	先左后中再右
void InorderTraversal(BinTree BT)
{
	if (BT)
	{
		InorderTraversal(BT->Left);
		printf("%c", BT->Data);
		InorderTraversal(BT->Right);
	}
}

// 先序遍历
void FistorderTraversal(BinTree BT)
{
	if (BT)
	{
		printf("%c", BT->Data);
		FistorderTraversal(BT->Left);
		FistorderTraversal(BT->Right);
	}
}

// 后序遍历
void PostorderTraversal(BinTree BT)
{
	if (BT)
	{
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%c", BT->Data);
	}
}

// 层序创建二叉树
BinTree CreatBinTree_layer()
{
	ElementType Data;
	BinTree BT, T;
	Queue Q = CreatQueue(Maxn);
	printf("请以数字的形式输入结点信息：\n");
	scanf("%c", &Data);
	if (Data == NoInfo)
		return NULL;
	// 生成第一个二叉树结点
	else
	{
		BT = (BinTree)malloc(sizeof(struct TNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		AddQ(Q, BT);
	}

	// 向下添加
	while (!IsEmpty(Q))
	{
		T = DeleteQ(Q);		// T就是第一个节点
		scanf("%d", &Data); // 读入左孩子
		if (Data == NoInfo)
		{
			T->Left = NULL;
		}
		else
		{
			T->Left = (BinTree)malloc(sizeof(struct TNode));
			T->Left->Data = Data;
			T->Left->Left = T->Left->Right = NULL;
			AddQ(Q, T->Left);
		}

		scanf("%d", &Data); // 读入右孩子
		if (Data == NoInfo)
		{
			T->Right = NULL;
		}
		else
		{
			T->Right = (BinTree)malloc(sizeof(struct TNode));
			T->Right->Data = Data;
			T->Right->Left = T->Right->Right = NULL;
			AddQ(Q, T->Right);
		}
	}
	return BT;
}

// 层序遍历
void Level_order_Traversal(BinTree BT)
{
	Queue Q;
	BinTree T;
	int size;
	if (!BT)
		return; /* 若是空树则直接返回 */
	printf("输入队列的规模:\n");
	scanf("%d", &size);
	Q = CreatQueue(size); /* 创建空队列Q */
	AddQ(Q, BT);
	while (!IsEmpty(Q)) // 如果队列非空
	{
		T = DeleteQ(Q);
		printf("%c ", T->Data);
		if (T->Left)
			AddQ(Q, T->Left);
		if (T->Right)
			AddQ(Q, T->Right);
	}
}

// 求二叉树高度
int GetHeight(BinTree BT)
{
	int HL, HR, MaxH;
	if (BT)
	{
		HL = GetHeight(BT->Left);
		HR = GetHeight(BT->Right);
		MaxH = HL > HR ? HL : HR;
		return (MaxH + 1);
	}
	else
	{
		return 0; // 空树高度为0
	}
}

int main()
{
	BinTree T;
	printf("请输入二叉树（空以#代替）：");
	T = Create_Bintree();
	Level_order_Traversal(T);
	return 0;
}