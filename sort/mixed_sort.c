#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void Swap( ElementType *a, ElementType *b )
{
    ElementType t = *a; *a = *b; *b = t;
}

void SimpleInsert_Sort(ElementType A[],int N)
{
    int p,i;
    ElementType Tmp;
    for(p=1;p<N;p++)   //默认0为第一个，不参与插入
    {
        Tmp=A[p];
        for(i=p;i>0&&A[i-1]>Tmp;i--)
        {
            A[i]=A[i-1];   //将已收录的后移，相当于给p腾位置
        }
        A[i]=Tmp;    //找到合适位置插入
    }
}

void Bubble_Sort(ElementType A[],int N)
{
    int i,j,flag;
    for(i=0;i<N-1;i++)
    {
        flag=0;         //标记每轮循环是否交换
        for(j=0;j<N-1-i;j++)
        {
            if(A[j]>A[j+1])
            {
                Swap(&A[j],&A[j+1]);
                flag=1;
            }
        }
        if(flag==0)break;
    }
}

//left right都是下标，并非序号
ElementType Median(ElementType A[],int Left,int Right)
{
    int Center=(Left+Right)/2;
    if(A[Left]>A[Center])
        Swap(&A[Left],&A[Center]);
    if(A[Left]>A[Right])
        Swap(&A[Left],&A[Right]);
    if(A[Center]>A[Right])
        Swap(&A[Right],&A[Center]);
    //此时left<center<right,把center藏到right的左边，减小问题规模
    Swap(&A[Center],&A[Right-1]);
    return A[Right-1];
}

void Q_sort(ElementType A[],int Left,int Right)
{
    int Pivot,Cutoff=2,Low,High;      //设定标兵，低位和高位
    //如果序列元素充分多，开始快排
    if(Cutoff<=Right-Left)
    {
        Pivot=Median(A,Left,Right);  //选出基准
        Low=Left+1;
        High=Right-2;
        while(1)
        {
            while(A[Low]<Pivot)
            {
                Low++;
            }
            while(A[High]>Pivot)
            {
                High--;
            }
            if(Low<High) Swap(&A[Low],&A[High]);
            else break;
        }
        Swap(&A[Low],&A[Right-1]);      //将基准换到正确的位置
        //开始递归,此时Low左边的全为较小，Low右边的全为较大
        Q_sort(A,Left,Low-1);
        Q_sort(A,Low+1,Right);
    }
    else if(Right-Left<=1)
    {
        if(A[Right]<A[Left])Swap(&A[Right],&A[Left]);
    }
}

void Quick_sort(ElementType A[],int N)
{
    Q_sort(A,0,N-1);
}


int main()
{
    int test1[]={48,27,96,48,25,6,90,17,84,62,49,72,17};
    int test2[]={48,27,96,48,25,6,90,17,84,62,49,72,17};
    int test3[]={48,27,96,48,25,6,90,17,84,62,49,72,17};
    SimpleInsert_Sort(test1,13);
    Bubble_Sort(test2,13);
    Quick_sort(test3,13);
    for(int i=0;i<13;i++)
    {
        printf("%d %d %d\n",test1[i],test2[i],test3[i]);
    }
    return 0;
}