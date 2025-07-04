#include "AMGraph.h"
using namespace std;

void display_Topological_Sort (vector<VertexType> TS_vertices)
{
    for (int i = 0; i < TS_vertices.size(); i++)
    {
        cout << TS_vertices[i] << "---->";
    }
    cout << " ^ " << endl;
}

void Topological_Sort (AMGraph M, vector<VertexType> &TS_vertices, vector<bool> &visited)
{

    for (int j = 0; j < M.vexnum; j++)
    {
        if (!visited[j])
        {
            bool flag = false;
            for (int i = 0; i < M.vexnum; i++)
            {
                if (M.arcs[i][j] != MaxInt)
                {
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                TS_vertices.push_back(M.vexs[j]);
                visited[j] = true;

                for (int k = 0; k < M.vexnum; k ++)
                {
                    M.arcs[j][k] = MaxInt;
                }
            }
        }
    }

    if (TS_vertices.size() != M.vexnum)
    {
        Topological_Sort(M, TS_vertices, visited);
    }
}

void Topological_Sort(AMGraph M)
{
    vector<bool> visited;
    visited.resize(M.vexnum);
    for (int k = 0; k < M.vexnum; k++)
    {
        visited[k] = false;
    }
    vector<VertexType> TS_vertices;
    Topological_Sort(M, TS_vertices, visited);
    display_Topological_Sort(TS_vertices);
}