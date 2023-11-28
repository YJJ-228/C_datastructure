#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
typedef int ElementType;
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElementType *Data;
    Position Front, Rear;
    int MaxSize;
};
typedef PtrToQNode Queue;

// 建立队列
Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

// 确认是否队满
int IsFull(Queue Q)
{
    return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

// 正入队
int Push(Queue Q, ElementType X)
{
    if (IsFull(Q) == true)
    {
        printf("队列已满");
        return false;
    }
    else
    {
        Q->Rear = (Q->Rear + 1) % Q->MaxSize; // Rear 和Front差一
        Q->Data[Q->Rear] = X;
    }
    return 0;
}

// 反入队
int Counter_Push(Queue Q, ElementType X)
{
    if (IsFull(Q) == true)
    {
        printf("队列已满");
        return false;
    }
    else
    {
        Q->Data[Q->Front] = X;
        Q->Front = ((Q->Front - 1) + Q->MaxSize) % Q->MaxSize; 
    }
    return 0;
}

// 确认是否空队
int IsEmpty(Queue Q)
{
    return (Q->Front == Q->Rear);
}

// 正出队
ElementType Pop(Queue Q)
{
    if (IsEmpty(Q) == true)
    {
        printf("队列已空");
        return false;
    }
    else
    {
        Q->Front = (Q->Front + 1) % Q->MaxSize;
        return Q->Data[Q->Front];
    }
}

//反出队
ElementType Counter_Pop(Queue Q)
{
    if (IsEmpty(Q) == true)
    {
        printf("队列已空");
        return false;
    }
    else
    {
        int i=Q->Rear;
        Q->Rear =((Q->Rear - 1)+Q->MaxSize) % Q->MaxSize;
        return Q->Data[i];
    }
}

// 队的长度
int Length(Queue Q)
{
    return (Q->Rear - Q->Front + Q->MaxSize) % Q->MaxSize;
}

int main()
{
    Queue Q1;
    Q1=CreateQueue(200);
    for(int i=0;i<99;i++)
    {
        Push(Q1,i);
        Counter_Push(Q1,-i);
    }
    for(int i=0;i<=99;i++)
    {
        printf("%d ",Counter_Pop(Q1));
        printf("%d ",Pop(Q1));
    }
}