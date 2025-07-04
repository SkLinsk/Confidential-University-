#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "AMGraph.h"
using namespace std;

vector<int> parent_vector;

void display_Kruskal(vector<Edge> Kruskal_edges)
{
    cout << "display_Kruskal: " << endl;

    for (int i = 0; i < Kruskal_edges.size(); i++)
    {
        cout << Kruskal_edges[i].vex1 << " -- " << Kruskal_edges[i].weight << " --> " << Kruskal_edges[i].vex2 << endl;
    }
}

bool weight_cmp(struct Edge a, struct Edge b) // 比较边权大小的函数
{
    return a.weight < b.weight;
}

int parent_find(int a) // 寻找起始顶点，并且路径压缩
{
    while (a != parent_vector[a])
    {
        a = parent_vector[a];
    }
    return a;
}

Status Kruskal(AMGraph &M)
{

    if (M.vexs.size() != M.vexnum)
    {
        throw runtime_error("Bad Graph.");
    }

    vector<int> Kruskal_vertices;
    vector<Edge> edges; int count = 0;
    vector<Edge> Kruskal_edges;
    parent_vector.resize(M.vexnum);
    edges.resize(M.arcnum);
    for (int i = 0; i < M.vexnum; i++)
    {
        parent_vector[i] = i;
        for (int j = 0; j < i; j++)
        {
            if (M.arcs[i][j] != MaxInt)
            {
                edges[count].vex1 = M.vexs[i];
                edges[count].vex2 = M.vexs[j];
                edges[count].weight = M.arcs[i][j];
                count++;
            }
        }
    }

    sort(edges.begin(), edges.end(), weight_cmp);

    for (int i = 0; i < edges.size() && Kruskal_edges.size() < M.vexnum - 1; ++i)
    {
        VertexType vex1 = edges[i].vex1, vex2 = edges[i].vex2;
        ArcType weight = edges[i].weight;

        auto it1 = find(M.vexs.begin(), M.vexs.end(), vex1);
        int index1 = it1 - M.vexs.begin();
        auto it2 = find(M.vexs.begin(), M.vexs.end(), vex2);
        int index2 = it2 - M.vexs.begin();

        if (parent_find(index1) != parent_find(index2)) // 判断父节点是否相同
        {
            Edge temp;
            temp.vex1 = vex1; temp.vex2 = vex2;
            temp.weight = weight;
            Kruskal_edges.push_back(temp);
            parent_vector[parent_find(index1)] = parent_vector[parent_find(index2)]; // 将两点并入一个集合中
        }
    }
    if (Kruskal_edges.size() != M.vexnum - 1)
    {
        cout << Kruskal_edges.size() << "Disconnected graph" << endl;
    }
    else
    {
        display_Kruskal(Kruskal_edges);
    }

    return OK;
}

Status Kruskal(string filename)
{
    AMGraph M;
    CreateUDN(M, filename);

    Kruskal(M);
    return OK;
}

#endif