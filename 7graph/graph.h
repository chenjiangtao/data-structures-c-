//
// Created by user on 2020/9/26.
//
#ifndef CHAPTER07_GRAPH_H
#define CHAPTER07_GRAPH_H

#include <iostream>
#include <stack>

using namespace std;
const int MaxValue = 32767;//无穷大
const int MaxEdge = 50;//
const int MaxVertices = 10;
typedef int DataType;

/*
*用邻接矩阵作为存储表示的图
*数组表示法
*/
class Node {
    DataType data;
    Node *next;
public:
    Node(DataType data, Node *next = NULL) {
        this.data = data;
        this.next = next;
    }
};

class Graph {
    DataType VerticesList[MaxVertices];   //顶点集
    float Edge[MaxVertices][MaxVertices];//边集
    int numberEdges; //边数
    int numberVertices//顶点数
    Node *AdjTable[MaxVertices];
public:
    Graph();  //构造函数
    void CreatEdge(int k);

    　//建图边
    void CreatVertices(int num);//建顶点
    void dfsMatrix(int i, bool *visited);//深度优先遍历算法
    void bfsMatrix(int i, bool *visited);//广度优先遍历算法
    void Prim(int v);//普里姆算法
    void Kruskal();

    // 克鲁斯卡尔算法
    void Floyd();

    //弗洛伊德算法
    void Dijkstra(int i);

    void dfsTraverse();

    void bfsTraverse();

    void MatrixToTable();//例7.3邻接矩阵转换成邻接表
    void TableToMatrix();//例7.3邻接表转换成邻接矩阵
    bool ExistPath(int u, int v);

    void ShortPath(int u, int v);

    void TopSort(int SortArray[]);//拓扑排序
    void CriticalPath();//
    　
};

Graph::Graph() {        //图的构造函数
    for (int i = 0; i < MaxVertices; i++)　　　//初始化Edge数组
    for (int j = 0; j < MaxVertices; j++)
        Edge[i][j] = 0;
    numberVertices = 0;　　　　//初始化   numberVertices
}

void Graph::CreatVertices(int num) {
    numberVertices = num;
}

void Graph::CreatEdge(int k) {
    int i, j, weight;
    //用i,j,weight保存一条边的起点、终点序号和权值
    char c1, c2, c3, c4;//用来保存输入的字符
    cout << "请输入边(以#结束,边的形式()或<>)：" << endl;
    if (k == 1)      //建立无向无权图
        do {
            cin >> c1 >> i >> c2 >> j >> c3;//依次读入一条边5的个数据
            Edge[i][j] = 1;
            Edge[j][i] = 1;                  //置相应的对称元素为1
            cin >> c4;   //读入逗号或右花括号
            if (c4 == '#') break;   //边集处理完毕，退出循环
        } while (1);
    if (k == 2)         //建立无向有权图
        do {
            cin >> c1 >> i >> c2 >> j >> c2 >> weight >> c3;
            Edge[i][j] = weight;
            Edge[j][i] = weight;        //置相应的对称元素为weight
            cin >> c4;
            if (c4 == '#') break;
        } while (1);
    if (k == 3)         //建立有向无权图
        do {
            cin >> c1 >> i >> c2 >> j >> c2 >> weight >> c3;
            Edge[i][j] = 1;
            cin >> c4;
            if (c4 == '#') break;
        } while (1);

    if (k == 4)         //建立有向有权图
        do {
            cin >> c1 >> i >> c2 >> j >> c2 >> weight >> c3;
            Edge[i][j] = weight;
            //置相应的对称元素为weight
            cin >> c4;
            if (c4 == '#') break;
        } while (1);
}

//例7.3邻接矩阵转换成邻接表
//0,1
void Graph::MatrixToTable() {
    int n = numberVertices;//构造图会确定numberVertices
    int i, j;
    Node *s;
    //由n个头指针组成的数组
    for (i = 0; i < n; i++)
        AdjTable[i] = NULL;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            //Edge[i][j]==1有边  i---j
            if (Edge[i][j] > 0 && Edge[i][j] < MaxValue) {
                s = new Node(j);
                s->next = AdjTable[i];
                AdjTable[i] = s;
            }
        }

}

//例7.3不带权图G邻接表转换成邻接矩阵
void Graph::TableToMatrix() {
    int n = numberVertices;//结点总数
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            Edge[i][j] = 0;//初始化邻接矩阵
    Node *p;
    for (i = 0; i < n; i++)//对邻接表n行遍历
    {
        p = AdjTable[i];//头指针
        while (p != NULL) {
            Edge[i][p->data] = 1;
            p = p->next;
        }
    }

}

//7.3.1 深度优先遍历算法
void Graph::dfsMatrix(int i, bool *visited) {     //从初始点vi出发深度优先搜索由邻接矩阵表示的图
    cout << i << ' ';
    //假定访问顶点vi以输出该顶点的序号代之
    visited[i] = true;        //标记vi已被访问过
    int n = numberVertices;
    for (int j = 0; j < n; j++)
        //依次搜索v的每个邻接点
        if (Edge[i][j] != 0 && Edge[i][j] != MaxValue && !visited[j])
            //若vi的一个有效邻接点vj未被访问过，则从vj出发进行递归调用
            dfsMatrix(j, visited);
}

//广度优先遍历算法
void Graph::bfsMatrix(int i, bool *visited) {    //从初始点vi出发广度优先搜索由邻接矩阵表示的图
//定义队列的最大长度
    int q[MaxSize] = {0};
//定义一个队列q，其元素类型应为整型
    int front = 0, rear = 0;    //定义队首和队尾指针
    cout << i << ' ';           //访问初始点vi
    visited[i] = true;        //标记初始点vi已访问过
    q[++rear] = i;            //将已访问过的初始点序号i入队
    while (front != rear) {    //当队列非空时进行循环处理
        front = (front + 1) % MaxSize;
        int k = q[front];
        //删除队首元素，第一次执行时k的值为i
        for (int j = 0; j < numberVertices; j++) {
            //依次搜索vk的每一个可能的邻接点
            if (Edge[k][j] != 0 && Edge[k][j] != MaxValue && !visited[j]) {
                cout << j << ' ';       //访问一个未被访问过的邻接点vj
                visited[j] = true;    //标记vj已访问过
                rear = (rear + 1) % MaxSize;
                q[rear] = j;          //顶点序号j入队
            }//if end
        }//for end
    }//while end
}//end
void Graph::dfsTraverse() { //深度优先求图的连通分量
    bool visited[MaxVertices];//设置访问标志数组
    int v;
    for (v = 0; v < numberVertices; v++)
        visited[v] = 0;
    //初始化访问标志数组
    for (v = 0; v < numberVertices; v++)
        if (!visited[v])
            dfsMatrix(v, visited);
    //每次从尚未访问过的顶点中选取一个顶点v，从顶点v出发进行调用dfsMatrix（）
}

/*例7.4 利用深度优先遍历算法
*判断图G中从顶点u到顶点v是否存在简单路径
*如果只有邻接矩阵
*/
bool Graph::ExistPath(int u, int v) {
    Node *p;
    int j;
    int i;
    int n = numberVertices;
    bool visited[MaxVertices];//设置访问标志数组
    bool flag;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    visited[u] = 1; // 置为已经访问标记
    if (u == v)
        return true;
    p = AdjTable[u]; // p指向顶点u的第一个相邻点
    while (p != NULL) {
        j = p->data; // j为u的相邻顶点
        if (visited[j] == 0) {
            //  j--------v
            //u-j
            flag = ExistPath(j, v);
            if (flag == true)
                return true;
        }
        p = p->next; // p指向u的下一个相邻点
    }
    return false;
}

//例7.5 基于广度优先遍历的应用
//求无权 无向图G从u到v的最短路径
//G采用邻接表存储
typedef struct vn {
    DataType data;//当前结点的编号
    DataType parentNode;//父结点的编号
} VistedNode;//被访问结点的数据结构
void Graph::ShortPath(int u, int v) {
    if (u == v)
        return;
    int n = numberVertices;
    Node *p;
    int i;
    bool visited[MaxVertices];//设置访问标志数组
    for (i = 0; i < n; i++)
        visited[i] = false;
    visited[u] = true; // 置为已经访问标记
    int front = 0;
    int rear = 0;
    VistedNode queue[MaxVertices];
    VistedNode vnode;
    vnode.data = u;
    vnode.parentNode = -1;
    queue[rear++] = vnode;
    DataType w;
    i = 0;
    while (rear < n) {
        vnode = queue[i++];//出队
        w = vnode.data;
        p = AdjTable[w];
        while (p != NULL) {
            if (p->data == v) {//找到了路径,打印路径
                //w-v有边
                string path = to_string(w) + "-->" + to_string(v);
                while (i >= 1 && w != u) {
                    i--;
                    if (queue[i].data != w)
                        continue;
                    w = queue[i].parentNode;
                    path = to_string(w) + path;
                }
                path = to_string(u) + path;
                cout << path;
                //u---->v
                return;
            } else {
                if (visited[p->data] == 0) {
                    visited[p->data] = 1;
                    vnode.data = p->data;
                    vnode.parentNode = w;
                    queue[rear++] = vnode;
                }
            }
            p = p->next;
        }
    }
    return;
}

/*
 * 7.4.1 Prim 算法
 * 是一种构造性算法
 * */
void Graph::Prim(int v) {
    int lowcost[MaxVertices];            //建立数组lowcost
    int closest[MaxVertices];            //建立数组closest
    int min, k, i, j;
    int n = numberVertices;
    for (i = 0; i < n; i++)                    //给lowcost[]和closest[]置初值
    {
        lowcost[i] = Edge[v][i];
        closest[i] = v;
    }

    //v已经在U这个集合里面了
    //n-1次
    //0....n-1
    for (i = 1; i < n; i++)                    //找出最小生成树的n-1条边
    {
        min = MaxValue;
        k = -1;
        for (j = 0; j < n; j++)                //在(V-U)中找出离U最近的顶点k
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;                        //k记录最小顶点的编号
            }
        cout << closest[k] << "," << k << endl; //输出最小生成树的边
        lowcost[k] = 0;                        //将顶点k加入U中
        //k=2
        for (j = 0; j < n; j++)                //修改数组lowcost和closest
            if (lowcost[j] != 0 && Edge[k][j] < lowcost[j]) {
                lowcost[j] = Edge[k][j];
                closest[j] = k;
            }
    }
}

/*
 * Kruskal克鲁斯卡尔算法
 * */
typedef struct EdgeSet {
    int u;//边的起始点
    int v;//终点
    int w;//边的权重

} EDGE;

void Graph::Kruskal() {
    int vset[MaxVertices];//建立数组vset
    //连通分量数组
    /*
     * 设置一个辅助数组vset[0..n-1]，
     * 其元素vset[i]代表顶点i所属的连通分量的编号
     * （同一个连通分量中所有顶点的vset值相同）
     * */
    EDGE E[MaxEdge];      //建立存放所有边的数组E
    int k = 0;            //E数组下标从0开始
    int i, j;
    EDGE temp;
    int u, v;
    int n = numberVertices;
    for (i = 0; i < n; i++)                        //由邻接矩阵g产生的边集数组E
        for (j = 0; j < i; j++)                    //对于无向图仅考虑下三角部分的边
            if (Edge[i][j] != 0 && Edge[i][j] != MaxValue) {
                E[k].u = j;
                E[k].v = i;
                E[k].w = Edge[i][j];
                k++;
            }
    //n个连通分量
    for (i = 0; i < n; i++)
        vset[i] = i;
    //排序,按照权重 从小到大排序
    for (i = 0; i < k - 1; i++)
        for (j = 0; j < k - i - 1; j++) {
            if (E[j].w > E[j + 1].w) {
                temp = E[j];
                E[j] = E[j + 1];
                E[j + 1] = temp;
            }
        }
    u = E[0].u;
    v = E[0].v;
    vset[v] = u;
    //最小生成树有n-1条边
    //有n个顶点
    //u,v已经被选中,还需要选择n-2个顶点
    //n-2条边需要加进来
    int count = n - 2;
    int su, sv;
    j = 1;
    //每次加入1个顶点
    while (count > 0) {
        u = E[j].u;
        v = E[j].v;
        su = vset[u];
        sv = vset[v];
        if (su != sv) {
            cout << u << "," << v << endl;
            count--;
            for (i = 0; i < n; i++)
                if (vset[i] == sv)
                    vset[v] = su;//合并u,v


        }
        j++;
    }
}

/*
 *迪杰斯特拉算法是典型的单源最短路径算法,
 * 用于计算一个节点到其他所有节点的最短路径
 * */
void Graph::Dijkstra(int i) {
    int j, k, w, m, n = numberVertices;
    bool *s = new bool[n];
    //dist[n]记录每一个结点到起始点i的最短距离
    int dist[MaxVertices];
    //记录每一个点j最短路径的前一个点
    int path[MaxVertices];
    for (j = 0; j < n; j++) {
        if (j == i)
            s[j] = true;//j在S这个集合里面
        else
            s[j] = false;//j在U,  V-S集合里面
        dist[j] = Edge[i][j];
        if (dist[j] < MaxValue && j != i)
            path[j] = i;
        else
            path[j] = -1;
    }
    for (k = 1; k <= n - 1; k++) {
        w = MaxValue;//对短距离
        m = i;
        for (j = 0; j < n; j++)
            if (s[j] == false && dist[j] < w) {
                w = dist[j];
                m = j;
            }
        if (m != i)
            s[m] = true;
        else
            break;
        for (j = 0; j < n; j++)
            if (s[j] == false && dist[m] + Edge[m][j] < dist[j]) {
                //dist[
                dist[j] = dist[m] + Edge[m][j];
                Edge[i][j] = dist[j];
                path[j] = m;
            }
    }
}

void Graph::Floyd() {
    int i, j, k, n = numberVertices;
    //最短路径矩阵
    //i-->j当前的最短路径长度
    int A[MaxVertices][MaxVertices];
    int path[MaxVertices][MaxVertices];
    //path[i][j]记录从i到j的最短路径上
    // 最靠近j前一个结点的编号
    //
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            A[i][j] = Edge[i][j];
            if (i == j || Edge[i][j] == MaxValue)
                path[i][j] = -1;
            else
                path[i][j] = i;
        }
    //对n个结点做循环
    //每次加入一个结点到S集合
    for (k = 0; k < n; k++) {
        //对A矩阵的遍历，更新
        //A[i][j]
        //i-->k    k-->j
        //k刚刚加入S这个顶点
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                if (i == k || j == k || i == j)
                    continue;
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
    }
}

void Graph::TopSort(int SortArray[]) {
    int InDegree[MaxVertices] = {0};
    int n = numberVertices;
    stack<int> s;
    int i, j, k;
    k = 0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++)
            if (i != j && Edge[i][j] < MaxValue)
                InDegree[j]++;
    }
    for (i = 0; i < n; i++)
        if (InDegree[i] == 0)
            s.push(i);
    while (!s.empty()) {
        i = s.top();
        s.pop();
        cout << i << endl;
        SortArray[k++] = i;
        for (j = 0; j < n; j++)
            if (i != j && Edge[i][j] < MaxValue) {
                InDegree[j]--;
                if (InDegree[j] == 0)
                    s.push(j);
            }
    }
}

//关键路径
void Graph::CriticalPath() {
    int n = numberVertices;
    int *v = new int[n];
    int *ve = new int[n];
    int *vl = new int[n];
    int i, j, k;
    TopSort(v);
    for (i = 0; i < n; i++)
        ve[i] = 0;
    for (i = 0; i < n; i++) {
        j = v[i];//拓扑排序的结果
        for (k = 0; k < n; k++) {
            if (k != j && Edge[j][k] < MaxValue
                && ve[k] < ve[j] + Edge[j][k])
                ve[k] = ve[j] + Edge[j][k];
        }
    }
    for (i = 0; i < n; i++)
        vl[i] = ve[n - 1];
    for (i = n - 1; i >= 0; i--) {
        j = v[i];
        for (k = 0; k < n; k++) {
            if (k != j && Edge[k][j] < MaxValue
                && vl[j] > vl[k] - Edge[k][j])
                vl[j] = vl[k] - Edge[k][j];
        }
    }

}

#endif //CHAPTER07_GRAPH_H
