#include "a.h"
#define ERROR -1
typedef struct SNode *PtrTolNode;
typedef int Position;
typedef int ElementType;
typedef PtrTolNode Stack;
struct SNode
{
    ElementType *Data;
    int Maxize;
    Position top; //栈顶指针
};

//建栈
Stack creating_stack(int Max)
{
    Stack S=(Stack)malloc(sizeof(struct SNode));
    S->Data=(int*)malloc(Max*sizeof(int));
    S->top=-1;
    S->Maxize=Max;
    return S;
}

//确认是否满栈
bool IsFull( Stack S )
{ 
    return (S->top == S->Maxize-1);
}

//压栈
bool Push(Stack S, ElementType X ) 
{
    if ( IsFull(S)==true ) 
    {
        printf("堆栈满");  
        return false;
    }
    else 
    {
        S->top++;
        S->Data[S->top] = X;
        return true;
    }
}  

//确认是否空栈
bool IsEmpty( Stack S )
{  
    return (S->top == -1);
}

ElementType Pop( Stack S ) 
{
    if ( IsEmpty(S)==true ) 
    {
        printf("堆栈空");
        return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
    }
    else
    {
        return ( S->Data[S->top--]);
    }    
}

//转换进制
int main()
{
    Stack S=creating_stack(100);
    int num=5684;
    while (num!=0)
    {
        int b=num%8;
        Push(S,b);
        num/=8;
    }
    while(!IsEmpty(S))
    {
        int a=Pop(S);
        printf("%d",a);
    }
    return 0;
}