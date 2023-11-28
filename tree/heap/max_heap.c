#include <stdio.h>
#include <stdlib.h>
#define MAXDATA 10000
#define ERROR -1

typedef int ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode
{
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */

MaxHeap CreateHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最大堆 */
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA;
    return H;
}

bool IsFull(MaxHeap H)
{
    return (H->Size == H->Capacity);
}

bool Insert(MaxHeap H, ElementType X)
{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
    if (IsFull(H))
    {
        printf("最大堆已满");
        return false;
    }
    i = ++H->Size; //i为目前最后一个元素的序号
    for (; H->Data[i / 2] < X; i /= 2)
        H->Data[i] = H->Data[i / 2]; /* 上滤X ，直到X小于上方某个值*/
    H->Data[i] = X;                  /* 将X插入 */
    return true;
}

bool IsEmpty(MaxHeap H)
{
    return(H->Size==0);
}

//取走根节点最大值，然后删除末节点，重整堆结构
ElementType DeleteMax(MaxHeap H)
{
    int Parent,Child;
    ElementType MaxItem,X;
    if(IsEmpty(H))
    {
        printf("最大堆已空");
    }
    MaxItem=H->Data[1];//取出根节点
    X=H->Data[H->Size--];//取出最后一个节点的值
    for(Parent=1;Parent*2<=H->Size;Parent=Child) //parent不断下滤，直到parent到了叶子
    {
        Child=Parent*2;
        if((Child!=H->Size)&&(H->Data[Child]<H->Data[Child+1]))  
        {
            Child++;
        }
        if(X>H->Data[Child])break;
        else
        {
            H->Data[Parent]=H->Data[Child]; //将较大的子节点上移
        }
    }
    H->Data[Parent]=X;
    return MaxItem;
}

