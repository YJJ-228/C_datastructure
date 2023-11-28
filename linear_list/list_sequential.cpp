//i表示位序，比下标多1，Last 表示最后一个元素的下标
#include "a.h"

typedef int ElementType;
typedef int Position;
typedef struct LNode *PtrTolNode;
struct LNode
{
    ElementType Data[Maxn];
    Position Last; //Last 表示最后一个数字的下标
};
typedef PtrTolNode List;          //List 就是一个线性表

//*初始化*
List init_list()    //初始化list
{
    List L;
    L=(List)malloc(sizeof(struct  LNode));
    L->Last=-1;
    return L;
}

//*插入元素（i处插入x）*
bool insert(List L,ElementType X,int i)     //i是位序，数组下标为i-1
{
    if(L->Last==Maxn-1)
    {
        printf("表满");
        return false;
    }    
    else if(i<1||i>L->Last+2)
    {
        printf("位序过小/过大");
        return false;
    }
    for(int j=L->Last;j>=i-1;j--) //后面的往后移
    {
        L->Data[j+1]=L->Data[j];
    }
    L->Data[i-1]=X;
    L->Last++;
    return true;
}

//*查找* 
int Find_index(List L, int X)
{
    for(Position i=0;i<=L->Last;i++)
    {
        if(L->Data[i-1]==X)
            return i;
    }
    return Error;
}

//*用序号求值*
int Find_value(List L, int i)
{
    return L->Data[i-1];
}

//*删除位序为i的内容*
bool Delete(List L,int i)
{
    Position j;
    if(i<1||i>L->Last+1)
    {
        printf("位序%d不在表内",&i);
        return false;
    }
    for(j=i;j<=L->Last;j++);
    {
        L->Data[j-1]=L->Data[j];
    }
    L->Last--;
    return true;
}

//*显示链表中元素*
void expressing(List L)
{
    for(int i=0;i<=L->Last;i++)
    {
        printf("%d\n",L->Data[i]);
    }
}


int main()
{
    int n,X;
    List L=init_list();
    printf("输入数据数量：");
    scanf("%d",&n);
    for (int k=1;k<=n;k++)
    {
        scanf("%d",&X);
        insert(L,X,k);
    }
    expressing(L);
    return 0;
}
