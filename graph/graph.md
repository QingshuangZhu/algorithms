# Graph

> Status: interface-only。`graph.h` 提供邻接表数据结构和操作声明，仓库当前没有图算法实现；本文其余内容为学习笔记。


## [图（graph）](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653197523&idx=2&sn=893c01a31446d3c479c312836ae83819&chksm=8c99e609bbee6f1fb0df2fb60edb8fba5166b49ef200ab8fb3af4ff144b3f96b283a34ff776c&scene=21#wechat_redirect)
图中结点之间的关系可以任意的，任意两个数据元素之间都可能相关。二元组定义：图G = (V, VR)，其中V是顶点（vertex）的非空集合，VR是两个顶点之间的关系的集合。
* 有向图（directed graph）：若(v, w) ∈ VR，则(v, w)表示从v到w的一条弧（arc），且称v为弧尾（tail）或初始点（initial node），称w为弧头（head）或终端点（terminal node），此时的图称为有向图。

* 无向图（undirected graph）：若(v, w) ∈ VR必有(w, v) ∈ VR，即VR是对称的，则以无序对{v, w}代替这两个有序对，表示v和w之间的一条边（edge），此时的图称为无向图。

* 完全图（complete graph）：有n(n-1)/2条边的无向图称为无向完全图；同时含每一对不同顶点的两个方向、共n(n-1)条弧的简单有向图称为有向完全图。

* 稀疏图（sparse graph）：有很少条边或弧的图称为稀疏图，反之称为稠密图。

* 网（network）：带权的图称为网。图的边或弧具有与它相关的数叫做权（weight）。

* 邻接点（adjacent）：对于无向图，一条边的两个顶点互为邻接点；对于有向图的一条弧，弧尾邻接到弧头，弧头邻接自弧尾。

* 度（degree）：对于无向图顶点的度是和该顶点相关的边数；对于有向图顶点的度为该顶点的入度与出度的和，入度是以该顶点为头的弧的数目，出度是以该顶点为尾的弧的数目。

* 路径（path）：对于无向图的路径是一个顶点序列；有向图的路径是遵循弧方向的顶点序列。无权图中路径长度是路径上的边或弧的数目；带权图还可讨论路径的权值和。

* 环（cycle）：第一个顶点和最后一个顶点相同的路径称为环或回路。

* Eulerian tour：经过所有的边一次且恰好一次的环路称为欧拉环路。

* Hamiltonian tour：经过所有的顶点一次且恰好一次的环路称为汉密尔顿环路。

* 连通（connect）：两个顶点之间有路径则称为连通的。对于图中任意两顶点都是连通的则称为连通图（connected graph）。

* [生成树（spanning tree）](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653198768&idx=1&sn=7ee80d95715e9267d0b562027dd4bce6&chksm=8c99eb6abbee627cacc6454cc8400710188f949437778e67ed077a707025e934ce0d926aa147&scene=21#wechat_redirect)：一个连通图的生成树是一个极小连通子图，它含由图中全部n个顶点，但有足以构成一颗树的n-1条边。一颗树有n个顶点的生成树有且仅有n-1条边。如果一个图有n个顶点和小于n-1条边,则是非连通图。如果它多于n-1条边，则一定有环。但是有n-1条边的图不一定是生成树。

### 存储结构
由于图的结构比较复杂，任意两个顶点之间都可能存在联系，因此无法以数据元素在存储区域中的物理位置来表示元素之间的关系，即图没有顺序映像的存储结构，但可以借助数组的数据类型表示元素之间的关系。另一方面，用多重链表表示图是自然的事，它是一种最简单的链式映像结构，即以一个由一个数据域和多个指针域组成的结点表示图中一个顶点，其中数据域存储该顶点的信息，指针域存储指向其邻接点的指针。但是由于各个顶点的度各不相同，最大度和最小度数可能相差很多，因此，若按度数最大的顶点设计结点结构，则会浪费很多存储单元，反之，若按每个顶点自己的度数设计不同的结点结构，又会给操作带来不便。因此，和树类似，在实际应用中不宜采用这种结构。常用的有邻接矩阵、邻接表、十字链表、邻接多重表。
1. 邻接矩阵（adjacency matrix）：用两个数组分别存储数据元素（顶点）的信息和数据元素之间的关系（边或弧）的信息。
```
#define MAX_VERTEX_NUM    20
typedef enum {DG, DN, UDG, UDN} graphKind;  /* 有向图，有向网，无向图，无向网 */
typedef struct arcCell {
    VRType adj;    /* VRType是顶点关系类型。对于无权图，用1或0表示是否相邻；对于带权图，则为权值类型*/
    infoType *info;    /* 该弧/边相关信息的指针 */
}arcCell, adjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    vertexType vexs[MAX_VERTEX_NUM];    /* 顶点向量 */
    adjMatrix arcs;    /* 邻接矩阵 */
    int vexNum;    /* 图的顶点数 */
    int arcNum;    /* 图的弧/边数 */
    graphKind kind;   /* 图的种类标志 */
}aMGraph;
```
2. 邻接表（adjacency list）：是图的一种链式存储结构。在邻接表中，对图中的每个顶点建立一个单链表，该链表中的表结点便是依附于该顶点的边或弧，并且该顶点是每个链表的表头结点。
```
#define MAX_VERTEX_NUM 20
typedef enum {DG, DN, UDG, UDN} graphKind;
/* 表结点（弧/边） */
typedef struct arcNode {
    int adjVex;    /* 该弧/边所指向的顶点位置 */
    struct arcNode *nextArc;    /* 指向下一条弧/边的指针 */
    infoType *info;    /*该弧/边相关的信息指针 */
}arcNode;
/* 表头结点（顶点） */
typedef struct vexNode {
    vertexType data;    /* 顶点信息 */
    arcNode *firstArc;    /* 指向第一条依附该顶点的弧/边的指针 */
}vexNode, adjList[MAX_VERTEX_NUM];
typedef struct {
    adjList vertices;    /* 表头向量 */
    int vexNum;    /* 图的顶点数 */
    int arcNum;    /* 图的弧/边数 */
    graphKind kind;    /* 图的种类标志 */
}aLGraph;
```
3. 十字链表（orthogonal list）：是有向图的另一种链式存储结构。在十字链表中，对应于有向图中每一条弧有一个表结点，对应于每个顶点也有一个表头结点。
```
#define MAX_VERTEX_NUM 20
/* 表结点（弧） */
typedef struct arcNode {
    int tailVex;    /* 该弧的尾顶点位置 */
    int headVex;    /* 该弧的头顶点位置 */
    struct arcNode *hLink;    /* 弧头相同的弧的链域 */
    struct arcNode *tLink;    /* 弧尾相同的弧的链域 */
    infoType *info;    /* 该弧相关信息的指针 */
}arcNode;
/* 表头结点（顶点） */
typedef struct vexNode {
    vertexType data;
    arcNode *firstIn;    /* 指向该顶点的第一条入弧 */
    arcNode *firstOut;    /* 指向该顶点的第一条出弧 */
}vexNode;
typedef struct {
    vexNode xList[MAX_VERTEX_NUM];    /* 表头向量 */
    int vexNum;    /* 图的顶点数 */
    int arcNum;    /* 图的弧数 */
}oLGraph;
```

4. 邻接多重表（adjacency multilist）：是无向图的另一种链式存储结构。邻接多重表和十字链表类似。在邻接多重表中，对应于无向图中每一条边有一个表结点，对应于每个顶点也有一个表头结点。
```
#define MAX_VERTEX_NUM 20
typedef enum {unvisited, visited} visitIf;
/* 表结点（边） */
typedef struct edgeNode {
    visitIf mark;    /* 访问标记 */
    int iVex;    /* 依附的顶点i */
    struct edgeNode *iLink;    /* 依附顶点i的下一条边的指针 */
    int jVex;   /* 依附的顶点j */
    struct edgeNode *jLink;    /* 依附顶点j的下一条边的指针 */
    infoType *info;    /* 该边相关信息的指针 */
}edgeNode;
/*表头结点（顶点） */
typedef struct vexNode {
    vertexType data;
    edgeNode *firstEdge;    /* 指向第一条依附该顶点的边 */
}vexNode;
typedef struct {
    vexNode adjMulist[MAX_VERTEX_NUM];   /* 表头向量 */
    int vexNum;    /* 图的顶点数 */
    int edgeNum;    /* 图的边数 */
}aMlGraph;
```

邻接矩阵需要Θ(n²)存储；邻接表对有向图需要Θ(n+e)存储，无向图通常为每条边保存两个邻接表结点，渐近空间仍为Θ(n+e)。

### [图的遍历](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653197523&idx=1&sn=4edecca7392534177eef521511ff740b&chksm=8c99e609bbee6f1fdb736f1bc45da5f6b6765ce190db68eac5a65ca22cc2694dc151f8db828f&scene=21#wechat_redirect)
图的遍历（traversing graph）:从图中某一顶点出发访遍图中的其余顶点，且使每一个顶点仅被访问一次。由于图中可能存在环，为了避免同一顶点被访问多次，在遍历图的过程中，必须记下每个已访问过的顶点。因此需要一个额外的数组记录是否访问了顶点，数组的长度为图的顶点数。通常有两条遍历图的路径：深度优先搜索和广度优先搜索。它们对无向图和有向图都适用。

1. 深度优先搜索（Depth First Search, DFS）：又称回溯法，其采用了一种“一直向下走，走不通就掉头”的思想；类似于树的先根遍历，是树的先根遍历的推广。基本思路：从图的某个顶点V出发，访问此顶点；然后依次从V的未被访问的邻接点出发深度优先遍历图，直至图中所有和V有路径相通的顶点都被访问到；若此时图中尚有顶点未被访问到，则另选图中一个未曾被访问的顶点作起始点，重复上述过程，直至图中所有顶点都被访问到为止。在DFS遍历时会生成DFS树/DFS森林。

2. 广度优先搜索（Breadth First Search, BFS）：类似于树的按层次遍历。基本思路是从顶点V出发，按发现顺序依次访问各顶点尚未访问的邻接点；若图不连通，再从未访问顶点重新开始。对于无权图或所有边权相等的图，BFS树中从起点S到可达顶点的树路径具有最少边数；一般带权图不能据此得到最小权值路径。

图遍历的过程实质上是通过边或弧查找邻接点。使用邻接表时，DFS和BFS的时间复杂度均为O(n+e)；使用邻接矩阵时，即使边很少也需要检查矩阵项，时间复杂度为Θ(n²)。在遍历图时图的顶点状态分为{UNDISCOVERED, DISCOVERED, VISITED}，及顶点时间标签dTime（顶点被发现时刻）和fTime（顶点被访问完毕时刻）；顶点的活动期：active[u] = (dTime[u], fTime[u])。括号引理（parenthesis lemma）：给定有向图G = (V, E)及其任一DFS森林，则u是v的后代，iff active[u] ⊆ active[v]；u是v的祖先，iff active[u] ⊇ active[v]；u与v“无关”，iff active[u] ∩ active[v] = Ø。
有向图DFS可将边分类为{TREE, CROSS, FORWARD, BACKWARD}；存在BACKWARD边当且仅当存在有向环。无向图中，遇到连接当前结点与非父祖先的非树边也表明存在环。

### 有向无环图
有向无环图（directed acyclic graph）：一个无环的有向图称为有向无环图，简称DAG。
* 拓扑排序（topological sort）：由某个集合上的偏序得到该集合上的一个全序，这个操作称之为拓扑排序。
* AOV网：用顶点表示活动，用弧表示活动间的优先关系的有向图称为顶点表示活动的网（activity on vertex network），简称AOV网。
* AOE网：与AOV网对应的是用边（弧）表示活动，顶点表示事件的带权的有向无环图称为边表示活动的网（activity on edge），简称AOE网。

### [最短路径](https://mp.weixin.qq.com/s?__biz=MzIxMjE5MTE1Nw==&mid=2653197626&idx=1&sn=fca7472af006a7f8890ee84ad7cf1116&chksm=8c99e7e0bbee6ef6faa1a34160a5e135503425e37552e90dfca2fbc10f223dbf3b875e84e418&scene=21#wechat_redirect)
最短路径（shortest path）：一个顶点到另一个顶点的最短路径（路径上边的数目/路径上边的权值之和）。
1. 单源最短路径：从某个源点到其余各顶点的最短路径。Dijkstra算法要求所有可达边权非负。Bellman-Ford算法允许负权边，并可检测源点可达的负权环；若存在这种负权环，相关顶点没有有限最短路径。SPFA是Bellman-Ford的一种队列优化，仍不能为可达负权环给出有限最短路径，应检测并报告该情况。松弛操作（relaxation）通过边(u,v)尝试减小从源点到v的当前距离上界。
2. 所有点对最短路径：求每一对顶点之间的最短路径。Floyd算法又称插点法，是一种动态规划算法，允许正权或负权边；要得到有限最短路径，相关路径上不能存在负权环。算法逐步允许编号不大于k的顶点作为中间点，并比较经过k与不经过k的两种路径长度。
