#ifndef PRIM_H
#define PRIM_H

#include "AMGraph.h"
using namespace std;

void display_Prim(AMGraph G, vector<Edge> edges)
{
    cout << "display_Prim: " << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[i][j] == MaxInt)
            {
                cout << "inf" << "    ";
            }
            else
            {
                cout << G.arcs[i][j] << "    ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < edges.size(); i++)
    {
        cout << edges[i].vex1 << " -- " << edges[i].weight << " --> ";
    }
    cout << (edges.back()).vex2 << endl;

}

Status Prim(AMGraph &M)
{

    if (M.vexs.size() != M.vexnum)
    {
        throw runtime_error("Bad Graph.");
    }

    vector<int> ori_vertices;
    ori_vertices.resize(M.vexnum);
    for (int i = 0; i < M.vexnum; i++)
    {
        ori_vertices[i] = i;
    }
    vector<int> Prim_vertices;
    vector<Edge> Prim_edges;
    Prim_vertices.push_back(0);
    auto it0 = find(ori_vertices.begin(), ori_vertices.end(), 0);
    ori_vertices.erase(it0);

    vector<vector<ArcType>> Vertices_matrix = M.arcs;
    while (ori_vertices.size())
    {
        int min = MaxInt;
        int ind_x = 0, ind_y = 0;
        for (int k = 0; k < Prim_vertices.size(); k++)
        {
            int i = Prim_vertices[k];
            int temp_min = MaxInt;
            int temp_ind_x = 0, temp_ind_y = 0;
            for (int j = 0; j < M.vexnum; j++)
            {
                (Vertices_matrix[i][j] < temp_min) ? (temp_min = Vertices_matrix[i][j], temp_ind_x = i, temp_ind_y = j) : (temp_min);
            }
            (min < temp_min) ? (min) : (min = temp_min, ind_x = temp_ind_x, ind_y = temp_ind_y);
        }
        Vertices_matrix[ind_x][ind_y] = MaxInt;
        Vertices_matrix[ind_y][ind_x] = MaxInt;
        Prim_vertices.push_back(ind_y);

        Edge temp_edge; 
        temp_edge.vex1 = M.vexs[ind_x];
        temp_edge.vex2 = M.vexs[ind_y];
        temp_edge.weight = min;

        Prim_edges.push_back(temp_edge);
        auto it = find(ori_vertices.begin(), ori_vertices.end(), ind_y);
        ori_vertices.erase(it);
    }

    AMGraph Prim_Graph;
    Prim_Graph.vexs = M.vexs;
    Prim_Graph.vexnum = M.vexnum;
    Prim_Graph.arcnum = M.vexnum - 1;
    compose_Graph(Prim_Graph.vexs, Prim_edges, Prim_Graph.vexnum, Prim_Graph.arcnum, Prim_Graph);

    display_Prim(Prim_Graph, Prim_edges);
    return OK;
}

Status Prim(string filename)
{
    AMGraph M;
    CreateUDN(M, filename);

    Prim(M);
    return OK;
}

#endif