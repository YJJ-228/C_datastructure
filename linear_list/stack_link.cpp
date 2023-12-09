#include <stdio.h>
#include <stdlib.h>
#define Maxn 100
#define Error -1

typedef struct SNode *PtrToSNode;
typedef int ElementType;
struct SNode 
{
    ElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;
typedef PtrToSNode Position;

Stack Create_Stack()
{
    Stack S;
    S=(PtrToSNode)malloc(sizeof(struct SNode));
    S->Next==NULL;
    return S;
}
 
bool Ifempty(Stack S)
{
    return(S->Next==NULL);
}d

//入栈
bool Push(Stack S,ElementType X)
{
    Position Tempcell;
    Tempcell=(Position)malloc(sizeof(struct SNode));
    Tempcell->Next=S->Next;
    S->Next=Tempcell;
    Tempcell->Data=X;
    return true;
}

//出栈
ElementType Pop(Stack S)
{
    if(Ifempty(S))
    {
        printf("栈空");
        return false;
    }
    else
    {
        Position First;
        First=S->Next;
        S->Next=S->Next->Next;
        return First->Data;
    }
}