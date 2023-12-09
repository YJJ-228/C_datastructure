#include <stdio.h>
#include <stdlib.h>
typedef int Elementtype;

void Swap( Elementtype *a, Elementtype *b )
{
    Elementtype t = *a; *a = *b; *b = t;
}


void PercDown(Elementtype A[],int p,int N)
{
    int Parent,Child;
    Elementtype X;
    X=A[p];     //取出根结点的值
    for(Parent=p;(Parent*2+1)<N;Parent=Child)
    {
        Child=2*Parent+1;   //因为数组从0开始记，所以这里+1
        if((Child!=N-1)&&(A[Child]>A[Child+1]))
        {
            Child=Child+1;
        }
        if(X<=A[Child])break;
        else
        {
            A[Parent]=A[Child];
        }
    }
    A[Parent]=X;    
}

void HeapSort( Elementtype A[], int N ) 
{   int i;
    for ( i=N/2-1; i>=0; i-- )
        PercDown( A, i, N );     
    for ( i=N-1; i>0; i-- ) 
    { 
        Swap( &A[0], &A[i] );
        PercDown( A, 0, i );
    }
}

int main()
{
    int A[100],N,M;
    char b[100]={'0'};
    printf("please input M, N:\n");
    scanf("%d %d",&M,&N);
    for(int i=0;i<N;i++)
    {
        scanf("%d",&A[i]);
    }
    HeapSort(A,N);
    for(int i=0;i<M;i++)
    {
        printf("%d ",A[i]);
    }
    return 0;
}

