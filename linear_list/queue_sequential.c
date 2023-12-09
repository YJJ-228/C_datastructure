#include "a.h"
typedef  int  ElementType;
typedef  int  Position;
typedef struct QNode *PtrToQNode;
struct QNode 
{
	ElementType *Data;	
	Position Front, Rear;  
	int MaxSize;  
};
typedef   PtrToQNode  Queue;

//建立队列
Queue CreateQueue( int MaxSize ) 
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

//确认是否队满
int IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

//入队
int Push(Queue Q, ElementType X)
{
    if(IsFull(Q)==true)
    {
        printf("队列已满");
        return 0;
    }
    else
    {
        Q->Rear=(Q->Rear+1)%Q->MaxSize;    //Rear 和Front差一
        Q->Data[Q->Rear]=X;
    }
    return true;
}

//确认是否空队
int IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

//出队
int Pop(Queue Q)
{
    if(IsEmpty(Q)==1)
    {
        printf("队列已空");
        return 0;
    }
    else
    {
        Q->Front=(Q->Front+1)%Q->MaxSize;
        return Q->Data[Q->Front];
    }
}

//队的长度
int Length(Queue Q)
{
    return (Q->Rear-Q->Front+Q->MaxSize)%Q->MaxSize;
}

int main()
{
   printf("hello");
}