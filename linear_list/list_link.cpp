#include "a.h"

typedef struct LNode *PtrTolNode;
struct LNode
{
    int Data;
    PtrTolNode Next; 
};
typedef PtrTolNode Position; //position为节点地址
typedef PtrTolNode List;

//初始化，带头节点
List Init_List(List L)
{
    L=(List)malloc(sizeof(struct LNode));
    L->Next=NULL;
    return L;
}

//求表长
int Length(List L)
{
    Position p;
    int cnt=0;
    while(p!=NULL)
    {
        p=p->Next;
        cnt++;
    }
    return cnt;
}

//通过位序查找
int Find_value(List L,int index)
{
    int cnt=1;
    Position p=L;
    while(p!=NULL&&cnt!=index)
    {
        p=p->Next;
        cnt++;
    }
    if((p!=NULL)&&(cnt==index))
    {
        return p->Data;
    }
    else
    {
        return Error;
    }
}

//通过值来查找
Position Find_index(List L,int value)
{
    Position p;
    while(p!=NULL&&p->Data!=value)
    {
        p=p->Next;
    }
    if(p!=NULL)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

//插入
bool insert(List L,int X,int i)
{
    Position tmp,p;
    int cnt=0;   //第一个节点是头节点，第二个才是“cnt=1”的节点
    p=L; //先把p放在表头
    while(p!=NULL&&cnt<i-1)  //把cnt移动到i-1处,p是i-1个节点
    {
        p=p->Next;
        cnt++;
    }
    if(p==NULL||cnt!=i-1)
    {
        printf("输入位置错误");
        free(tmp);
        return false;
    }
    else
    {
        tmp=(Position)malloc(sizeof(struct LNode));
        tmp->Next=p->Next;
        p->Next=tmp;
        tmp->Data=X;
        return L;
    }
    return true;
}   

//*删除位序为i的节点*
//大概就是找到目标节点前一个的节点和位序p,cnt
//然后tmp=p->Next
//p->Next=tmp->Next, free(tmp)
bool Delete(List L,int i)
{
    Position p,tmp;
    p=L;
    int cnt=0;
    while(p!=NULL&&cnt<i-1)
    {
        p=p->Next;
        cnt++;
    }
    if(p||p->Next==NULL||cnt!=i-1)
    {
        printf("错误");
        return false;
    }
    tmp=p->Next;
    p->Next=tmp->Next;
    free(tmp);
    return true;
}

List Reverse(List L)
{
    Position head=L,p=L->Next,q=p->Next,r; //p为第一节点,指向第一个元素，q为第二，r为第三,head为头节点
    p->Next=NULL;
    r=q->Next;
    while(q!=NULL)
    {
        q->Next=p;
        p=q;
        q=r;
    }
    return L;
}

int main()
{
    printf("%d",15/16);
    return 0;
}