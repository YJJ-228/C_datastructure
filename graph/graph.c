#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100

typedef int Vertex;     //用顶点下标表示顶点
typedef int Weighttype;     //权重
typedef char Datatype;

int Visited[MaxVertexNum]={0};

//定义边
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1,V2;
    Weighttype Weight; 
};
typedef PtrToENode Edge;

//定义邻接点
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode
{
    Vertex AdjV;
    Weighttype Weight;
    PtrToAdjVNode Next;
};

//顶点表头结点定义
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;  //第一个邻接点
    Datatype Data;
}AdjList[MaxVertexNum];

//图结点定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv; //顶点数
    int Ne; //边数
    AdjList G; //邻接表
};
typedef PtrToGNode LGraph;

//图的创建
LGraph CreateGraph(int vertexnum)
{
    Vertex V;
    LGraph Graph;
    Graph=(LGraph)malloc(sizeof(struct GNode));
    Graph->Nv=vertexnum;
    Graph->Ne=0;
    for(V=1;V<=Graph->Nv;V++)
    {
        Graph->G[V].FirstEdge=NULL;
    }
    return Graph;
}

//插入边
void InsertEdge(LGraph Graph,Edge E)
{
    PtrToAdjVNode NewNode;
    //插入边<V1,V2>
    NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV=E->V2;
    NewNode->Weight=E->Weight;
    //将V2插入V1表头
    NewNode->Next=Graph->G[E->V1].FirstEdge;   
    Graph->G[E->V1].FirstEdge=NewNode;

    //若是无向图，还需要插入边<v1,v2>
    //为v1建立邻接点
    NewNode=(PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV=E->V1;
    NewNode->Weight=E->Weight;
    //将V2插入V1表头
    NewNode->Next=Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge=NewNode;
}

//建立图
LGraph BuildGraph()
{
    //定义图，边，点，顶点数
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv;
    printf("输入顶点个数：\n");
    scanf("%d",&Nv);
    Graph=CreateGraph(Nv);
    printf("输入边个数：\n");
    scanf("%d",&(Graph->Ne));
    if(Graph->Ne!=0)        //如果有边
    {
        E=(Edge)malloc(sizeof(struct ENode));
        printf("依次输入边的V1,V2,Weight \n");
        for(int i=0;i<Graph->Ne;i++)
        {
            scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
            InsertEdge(Graph,E);
            
        }
    }
    //如果顶点有数据的话，读入
    printf("输入顶点数据:");
    getchar();
    for(V=1;V<=Graph->Nv;V++)
    {
        scanf("%c",&(Graph->G[V].Data));
    }
    return Graph;
}

//图的遍历＿DFS
void DFS(LGraph Graph, Vertex V)
{
    printf("正在访问第%d个结点\t",V);
    printf("该顶点信息为%c\t邻接点为",Graph->G[V].Data);
    Visited[V]=1;
    for(PtrToAdjVNode W=Graph->G[V].FirstEdge;W!=NULL;W=W->Next)
    {
        printf("%d ",W->AdjV);
    }
    printf("\n");
    for(PtrToAdjVNode W=Graph->G[V].FirstEdge;W!=NULL;W=W->Next)
    {
        if(Visited[W->AdjV]==0)
            DFS(Graph,W->AdjV);
    }
}

int main()
{
    LGraph Graph=BuildGraph();
    DFS(Graph,1);
    return 0;
}