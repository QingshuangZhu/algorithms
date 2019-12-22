/*
 * graph
 */

#ifndef GRAPH_H
#define GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VERTEX_NUM 20

typedef int vertexType;
typedef char infoType;

typedef enum {DG, DN, UDG, UDN} graphKind;
/* 表结点（弧/边） */
typedef struct arcNode {
    int adjVex;                         /* 该弧/边所指向的顶点位置 */
    struct arcNode *nextArc;            /* 指向下一条弧/边的指针 */
    infoType *info;                     /*该弧/边相关的信息指针 */
}arcNode;
/* 表头结点（顶点） */
typedef struct vexNode {
    vertexType data;                    /* 顶点信息 */
    arcNode *firstArc;                  /* 指向第一条依附该顶点的弧/边的指针 */
}vexNode, adjList[MAX_VERTEX_NUM];
typedef struct {
    adjList vertices;                   /* 表头向量 */
    int vexNum;                         /* 图的顶点数 */
    int arcNum;                         /* 图的弧/边数 */
    graphKind kind;                     /* 图的种类标志 */
}aLGraph;

int createGraph(aLGraph **g);
int destroyGraph(aLGraph **g);
int locateVex(aLGraph *g, vexNode *v);
vertexType getVex(aLGraph *g, vexNode *v);
int putVex(aLGraph *g, vexNode *v, vertexType data);
int firstAdjVex(aLGraph *g, vexNode *v);
int nextAdjVex(aLGraph *g, vexNode *v, vexNode *w);
int insertVex(aLGraph *g, vexNode *v);
int deleteVex(aLGraph *g, vexNode *v);
int insertArc(aLGraph *g, vexNode *v, vexNode *w);
int deleteArc(aLGraph *g, vexNode *v, vexNode *w);
void DFS(aLGraph *g);
void BFS(aLGraph *g);

#ifdef __cplusplus
}
#endif

#endif
