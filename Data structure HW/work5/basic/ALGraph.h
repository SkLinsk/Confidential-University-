#include "total_def.h"
using namespace std;

typedef struct ArcNode // 边结点
{
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    bool visited = false;
    // OtherInfo info; // 和边相关的信息
} ArcNode;

typedef struct VNode
{
    VertexType data;             // 顶点信息
    ArcNode *firstarc = nullptr; // 指向第一条依附该顶点的边的指针
    vector<int> index_link = {-1};
} VNode; // AdjList表示邻接表类型

typedef struct ALGraph
{
    vector<VNode> vertices; // 邻接表
    int vexnum, arcnum;     // 图的当前顶点数和边数
} ALGraph;

int LocateVex(ALGraph G, VertexType u)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (u == G.vertices[i].data)
            return i;
    }
    return -1;
}

Status CreateUDG(ALGraph &G)
{
    VertexType v1, v2;
    ArcNode *p1 = new ArcNode, *p2 = new ArcNode;

    // 采用邻接表表示法，创建无向图G
    cin >> G.vexnum >> G.arcnum; // 输入总顶点数，总边数
    for (int i = 0; i < G.vexnum; ++i)
    {                              // 输入各点，构造表头结点表
        cin >> G.vertices[i].data; // 输入顶点值
    }
    VNode temp;
    G.vertices.push_back(temp);

    for (int k = 0; k < G.arcnum; ++k)
    {
        // 输入各边，构造邻接表
        cin >> v1 >> v2; // 输入一条边依附的两个顶点
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        if (i == -1 || j == -1)
        {
            cerr << "Locate error" << endl;
            return 0;
        }

        auto it1 = find(G.vertices[i].index_link.begin(), G.vertices[i].index_link.end(), j);
        auto it2 = find(G.vertices[j].index_link.begin(), G.vertices[j].index_link.end(), i);

        if (it1 != G.vertices[i].index_link.end() && it2 != G.vertices[i].index_link.end())
        {
            p1->adjvex = j; // 邻接点序号为j
            p1->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p1; // 将新结点*p1插入顶点vi的边表头部
            G.vertices[i].index_link.push_back(p1->adjvex);

            p2->adjvex = i; // 邻接点序号为i
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2; // 将新结点*p2插入顶点vj的边表头部
            G.vertices[i].index_link.push_back(p1->adjvex);
        }
    }
    return OK;
} // CreateUDG

Status CreateUDG(ALGraph &G, string filename)
{
    auto graphData = ReadGraphFile(filename);

    vector<string> vertices;
    vector<Edge> edges;
    int numVertices;
    int numEdges;
    tie(vertices, edges, numVertices, numEdges) = graphData;

    // 采用邻接表表示法，创建无向图G
    G.vexnum = numVertices;
    G.arcnum = numEdges;

    G.vertices.resize(G.vexnum);

    for (int i = 0; i < G.vexnum; ++i)
    {                                     // 输入各点，构造表头结点表
        G.vertices[i].data = vertices[i]; // 输入顶点值
    }

    for (int k = 0; k < G.arcnum; ++k)
    {
        ArcNode *p1 = new ArcNode, *p2 = new ArcNode;
        int i = LocateVex(G, edges[k].vex1);
        int j = LocateVex(G, edges[k].vex2);

        if (i == -1 || j == -1)
        {
            cerr << "Locate error" << endl;
            return 0;
        }

        auto it1 = find(G.vertices[i].index_link.begin(), G.vertices[i].index_link.end(), j);
        auto it2 = find(G.vertices[j].index_link.begin(), G.vertices[j].index_link.end(), i);

        if (it1 == G.vertices[i].index_link.end() && it2 == G.vertices[j].index_link.end())
        {
            p1->adjvex = j; // 邻接点序号为j
            p1->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p1; // 将新结点*p1插入顶点vi的边表头部
            G.vertices[i].index_link.push_back(p1->adjvex);

            p2->adjvex = i; // 邻接点序号为i
            p2->nextarc = G.vertices[j].firstarc;
            G.vertices[j].firstarc = p2; // 将新结点*p2插入顶点vj的边表头部
            G.vertices[j].index_link.push_back(p1->adjvex);
        }
    }
    return OK;
} // CreateUDG

void display_ALG(ALGraph G)
{
    cout << "display_ALG: " << endl;
    ArcNode *temp = nullptr;
    for (int i = 0; i < G.vexnum; i++)
    {
        temp = G.vertices[i].firstarc;
        cout << G.vertices[i].data << " -> ";
        while (temp)
        {
            cout << G.vertices[temp->adjvex].data << " -> ";
            temp = temp->nextarc;
        }
        cout << " ^ " << endl;
    }
    cout << endl;
}

void UDG_DFS(ALGraph G, int start_index = 0)
{
    if (!G.vertices.size())
    {
        cerr << "Graph is empty" << endl;
        return;
    }

    vector<bool> visited;
    visited.resize(G.vexnum);

    cout << "UDG_DFS: ";
    stack<int> index_of_vertices;
    index_of_vertices.push(start_index);

    cout << G.vertices[start_index].data << ", " << index_of_vertices.top() << "    ";
    visited[index_of_vertices.top()] = true;

    int temp_index = index_of_vertices.top();
    ArcNode *temp_AN_pointer = G.vertices[temp_index].firstarc;

    while (!index_of_vertices.empty())
    {
        bool flag = false;
        while (temp_AN_pointer)
        {
            if (!visited[temp_AN_pointer->adjvex])
            {
                index_of_vertices.push(temp_AN_pointer->adjvex);
                cout << G.vertices[temp_AN_pointer->adjvex].data << ", " << temp_AN_pointer->adjvex << "    ";

                visited[temp_AN_pointer->adjvex] = true;
                temp_AN_pointer = G.vertices[temp_AN_pointer->adjvex].firstarc;
            }
            else
            {
                temp_AN_pointer = temp_AN_pointer->nextarc;
            }
        }
        index_of_vertices.pop();
        if (!index_of_vertices.empty())
        {
            temp_index = index_of_vertices.top();
            temp_AN_pointer = G.vertices[temp_index].firstarc;
        }
    }

    cout << endl;
}

void UDG_BFS(ALGraph G, int start_index = 0)
{
    if (!G.vertices.size())
    {
        cerr << "Graph is empty" << endl;
        return;
    }

    vector<bool> visited;
    visited.resize(G.vexnum);

    cout << "UDG_BFS: ";
    queue<int> index_of_vertices;
    index_of_vertices.push(start_index);

    cout << G.vertices[start_index].data << ", " << index_of_vertices.front() << "    ";
    visited[index_of_vertices.front()] = true;

    while (!index_of_vertices.empty())
    {
        int temp_index = index_of_vertices.front();
        ArcNode *temp_VN_pointer = G.vertices[temp_index].firstarc;
        while (temp_VN_pointer)
        {
            temp_index = temp_VN_pointer->adjvex;
            if (!visited[temp_index])
            {
                index_of_vertices.push(temp_index);
                cout << G.vertices[temp_index].data << ", " << temp_index << "    ";

                visited[temp_index] = true;
                temp_VN_pointer = temp_VN_pointer->nextarc;
            }
            else
            {
                temp_VN_pointer = temp_VN_pointer->nextarc;
            }
        }

        if (!index_of_vertices.empty())
        {
            index_of_vertices.pop();
        }
    }
}