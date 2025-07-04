#ifndef AMGRAPH_H
#define AMGRAPH_H

#include "total_def.h"
using namespace std;

typedef struct AMGraph
{
    int vexnum = 0, arcnum = 0;           // 图的当前点数和边数
    vector<VertexType> vexs;      // 顶点表
    vector<vector<ArcType>> arcs; // 邻接矩阵
} AMGraph;

int LocateVex(AMGraph G, VertexType u)
{
    // 存在则返回u在顶点表中的下标;否则返回-1
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (u == G.vexs[i])
            return i;
    }
    return -1;
}

Status CreateUDN(AMGraph &G)
{
    VertexType v1, v2;
    Weight w = 0;

    // 采用邻接矩阵表示法，创建无向网G
    cin >> G.vexnum >> G.arcnum; // 输入总顶点数，总边数
    G.vexs.resize(G.vexnum);
    G.arcs.resize(G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        G.arcs[i].resize(G.vexnum);
    }

    for (int i = 0; i < G.vexnum; ++i)
        cin >> G.vexs[i];              // 依次输入点的信息
    for (int i = 0; i < G.vexnum; ++i) // 初始化邻接矩阵，边的权值均置为极大值
        for (int j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = MaxInt;

    // 有向构造
    for (int k = 0; k < G.arcnum; ++k)
    {                         
        // 构造邻接矩阵
        cin >> v1 >> v2 >> w; // 输入边v1->v2及权值
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2); // 确定v1和v2在G中的位置

        if (i == -1 || j == -1)
        {
            cerr << "Locate error" << endl;
            return 0;
        }

        if (!G.arcs[i][j] && !G.arcs[j][i])
        {
            G.arcs[i][j] = w;            // 边<v1, v2>的权值置为w
            G.arcs[j][i] = G.arcs[i][j]; // 置<v1, v2>的对称边<v2, v1>的权值为w
        }
        else
        {
            k--;
        }
    }
    return OK;
} // CreateUDN

Status compose_Graph(vector<VertexType> vertices, vector<Edge> edges, int numVertices, int numEdges, AMGraph &G)
{
    G.vexnum = numVertices;
    G.arcnum = numEdges;

    G.vexs.resize(G.vexnum);
    G.arcs.resize(G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        G.arcs[i].resize(G.vexnum);
        G.vexs[i] = vertices[i];
    }

    for (int i = 0; i < G.vexnum; ++i) // 初始化邻接矩阵，边的权值均置为极大值
        for (int j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = MaxInt;

    // 有向构造
    for (int k = 0; k < G.arcnum; ++k)
    {
        // 构造邻接矩阵

        int i = LocateVex(G, edges[k].vex1);
        int j = LocateVex(G, edges[k].vex2); // 确定v1和v2在G中的位置

        if (i == -1 || j == -1)
        {
            cerr << "Locate error" << endl;
            return 0;
        }

        if (G.arcs[i][j] == MaxInt)
        {
            G.arcs[i][j] = edges[k].weight; // 边<v1, v2>的权值置为w
        }
    }
    return OK;
}


Status CreateUDN(AMGraph &G, string filename)
{
    auto graphData = ReadGraphFile(filename);

    vector<string> vertices;
    vector<Edge> edges;
    int numVertices;
    int numEdges;
    tie(vertices, edges, numVertices, numEdges) = graphData;

    compose_Graph(vertices, edges, numVertices, numEdges, G);
    return OK;
}

void display_AMG(AMGraph G)
{
    cout << "display_AMG: " << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[i][j] == MaxInt)
            {
                cout << setw(5) << "inf";
            }
            else
            {
                cout << setw(5) << G.arcs[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void UDN_DFS(AMGraph G, int start_index = 0)
{
    if (G.vexnum == 0)
    {
        cerr << "Graph is empty." << endl;
        return;
    }

    vector<bool> visited;
    visited.resize(G.vexnum);
    for ( int i = 0; i < G.vexnum; i++)
    {
        visited[i] = false;
    }

    cout << "UDN_DFS: ";
    stack<int> index_of_vexs;
    index_of_vexs.push(start_index);

    cout << G.vexs[start_index] << ", " << index_of_vexs.top() << "    ";
    visited[index_of_vexs.top()] = true;
    int temp_index = index_of_vexs.top();

    while (!index_of_vexs.empty())
    {
        bool flag = false;
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[temp_index][i] != MaxInt && !visited[i] && temp_index != i) // 不考虑自回路
            {
                index_of_vexs.push(i);
                cout << G.vexs[i] << ", " << i << "    ";
                visited[i] = true;
                temp_index = index_of_vexs.top();
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            index_of_vexs.pop();
            if (!index_of_vexs.empty())
            {
                temp_index = index_of_vexs.top();
            }
        }
    }
    cout << endl;
}

void UDN_BFS(AMGraph G, int start_index = 0)
{
    if (G.vexnum == 0)
    {
        cerr << "Graph is empty." << endl;
        return;
    }

    vector<bool> visited;
    visited.resize(G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = false;
    }

    cout << "UDN_BFS: ";
    queue<int> index_of_vexs;
    index_of_vexs.push(start_index);

    while (!index_of_vexs.empty())
    {
        int temp_index = index_of_vexs.front();

        if (!visited[temp_index])
        {
            cout << G.vexs[temp_index] << ", " << temp_index << "    ";
            visited[temp_index] = true;
        }

        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[temp_index][i] != MaxInt && !visited[i] && temp_index != i) // 不考虑自回路
            {
                index_of_vexs.push(i);
            }
        }
        index_of_vexs.pop();
    }
    cout << endl;
}

#endif