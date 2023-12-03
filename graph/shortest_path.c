#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535
#define ERROR -1

typedef int Vertex;     //用顶点下标表示顶点
typedef int Weighttype;     //权重
typedef char Datatype;

int Dist[MaxVertexNum]={INFINITY},Path[MaxVertexNum]={-1};

//定义边
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1,V2;
    Weighttype Weight; 
};
typedef PtrToENode Edge;

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    Weighttype G[MaxVertexNum][MaxVertexNum];
    Datatype Data[MaxVertexNum];   //顶点数据
};
typedef PtrToGNode MGraph;


MGraph CreateGraph(int VertexNum)
{
    Vertex V,W;
    MGraph Graph;

    Graph=(MGraph)malloc(sizeof(struct GNode));
    Graph->Nv=VertexNum;
    Graph->Ne=0;
    for (V=0;V<Graph->Nv;V++)
    {
        for(W=0;W<Graph->Nv;W++)
        {
            Graph->G[V][W]=INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph,Edge E)
{
    Graph->G[E->V1][E->V2]=E->Weight;
    Graph->G[E->V2][E->V1]=E->Weight;
}

MGraph BuildGraph()
{
    FILE *fp;
    fp=fopen("D:/Code/C_class/graph/test2.txt","r");
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv;
    fscanf(fp,"%d",&Nv);
    Graph=CreateGraph(Nv);
    fscanf(fp,"%d",&(Graph->Ne));
    if(Graph->Ne!=0)
    {
        E=(Edge)malloc(sizeof(struct ENode));
        for(int i=0;i<Graph->Ne;i++)
        {
            fscanf(fp,"%d %d %d",&E->V1,&E->V2,&E->Weight);
            InsertEdge(Graph,E);
        }
    
    // //如果顶点有数据的话，读入
    // printf("输入顶点数据:\n");
    // for(V=0;V<Graph->Nv;V++)
    // {
    //     scanf("%c",&(Graph->Data[V]));
    // }
    fclose(fp);
    }
    return Graph;
}

//以下为Dijsktra算法
//返回dist中最小点的坐标编号
Vertex FindMinDist(MGraph Graph,int dist[],int collected[])
{
    Vertex MinV,V;
    int MinDist=INFINITY;

    for(V=0;V<Graph->Nv;V++)
    {
        //如果未被收录，并且dist[V]最小，更新数据
        if(collected[V]==0&&dist[V]<MinDist)
        {
            MinDist=dist[V];
            MinV=V;
        }
    }
    if(MinDist<INFINITY)
    {
        return MinV;
    }
    else 
        return  ERROR;
}

//S为起点
int Dijkstra(MGraph Graph,int dist[],int path[],Vertex S)
{
    int collected[MaxVertexNum];
    Vertex V,W;
    //初始化
    for(V=0;V<Graph->Nv;V++)
    {
        dist[V]=Graph->G[S][V];
        if(dist[V]<INFINITY)
        {
            path[V]=S;
        }
        else
        {
            path[V]=-1;
        }
        collected[V]=0;  //初始时全部都未收录
    }
    //收录起点
    dist[S]=0;
    collected[S]=1;

    while(1)
    {
        V=FindMinDist(Graph,dist,collected);
        if(V==ERROR)
        {
            break;
        }
        collected[V]=1;
        for(W=0;W<Graph->Nv;W++)
        {
            if(collected[W]==0&&Graph->G[V][W]<INFINITY)
            {
                if(Graph->G[V][W]<0)
                {
                    return -1;
                }
                else if(dist[V]+Graph->G[V][W]<dist[W])
                {
                    dist[W]=dist[V]+Graph->G[V][W];
                    path[W]=V;
                }
            }
        }
    }
    return 1;
}

int main()
{
    MGraph Graph=BuildGraph();
    Dijkstra(Graph,Dist,Path,0);
    for(int i=1;i<Graph->Nv;i++)
    {
        printf("V0到V%d的最短距离为%d\n",i,Dist[i]);
    }
    return 0;
}
