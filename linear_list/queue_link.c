//队列的链式存储其实和链表类似，只是除了设置next指针外，还需要控制front 和 rear指针始终指向
//头和尾，因此我们设置两个结构体，一个是充当线性表部分的内容，另一个控制队列整体的头尾节点
//以下代码不带头节点
#include "a.h"
#define ERROR -1;
typedef  char  ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Pos	ition;

//建立节点
struct Node
{
	ElementType Data;
	PtrToNode Next;
};

//建立队列
typedef struct QNode *PtrToQNode;
struct QNode 
{
	Position Front, Rear;  //Q->rear,front本身就是指针，是Node的结点
	int MaxSize;  
};
typedef   PtrToQNode  Queue;

//初始化
Queue CreateQueue( )
{
	Queue Q = (PtrToQNode)malloc(sizeof(struct QNode));
	Q->Front = NULL;
	Q->Rear = NULL;
	Q->MaxSize = 0;
	return Q;
}

int IsEmpty( Queue Q )
{   
	return (Q->Front == NULL);  
}

//入队
int AddQueue(Queue Q,ElementType x)
{	
	Position p=(PtrToNode)malloc(sizeof(struct Node));
	p->Data=x;	
	//不带头结点第一次入队要判断是否为空，要是空则头尾指针都指向P 
	if(Q->Front==NULL)
	{
		Q->Front=p;		
		Q->Rear=p;	
	} 
	else
	{     //不为空则直接在尾指针后面操作 		
		Q->Rear->Next=p;		
		Q->Rear=p;	
	}	
	Q->MaxSize++;
	return 1;
}

//出队
ElementType DeleteQ( Queue Q ) 
{
    Position  FrontCell; 
    ElementType  FrontElem;
    if  ( IsEmpty(Q) ) 
	{
		printf("队列空");    
		return ERROR;     
	}
    else 
	{
		FrontCell = Q->Front;
		if ( Q->Front == Q->Rear ) /* 若队列只有一个元素 */
		{
			Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
		}
		else       
		{
			Q->Front = Q->Front->Next;
		}              
		FrontElem = FrontCell->Data;
		free( FrontCell );  /* 释放被删除结点空间  */
		return  FrontElem;     
	}
}

int main()
{
	printf("hello");
	return 0;
}


