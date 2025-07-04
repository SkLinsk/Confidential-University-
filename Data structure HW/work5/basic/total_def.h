#ifndef TOTAL_DEF_H
#define TOTAL_DEF_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;

// 用两个数组分别存储顶点表和邻接矩阵
#define MaxInt 32767 // 表示极大值，即∞
#define OK 1
#define ERROR 0
#define Status int

typedef string VertexType; // 假设顶点的数据类型为字符型
typedef int ArcType;       // 假设边的权值类型为整型
typedef double Weight;

using namespace std;

typedef struct Edge
{
    VertexType vex1, vex2;
    ArcType weight;
} Edge;

tuple<vector<string>, vector<Edge>, int, int> ReadGraphFile(const string &filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        throw runtime_error("File open failed");
    }

    vector<string> vertices;
    vector<Edge> edges;
    int numVertices = 0;
    int numEdges = 0;
    string line;

    // 读取第一行，获取顶点数和边数
    getline(infile, line);
    stringstream ss(line);
    if (!(ss >> numVertices >> numEdges))
    {
        throw runtime_error("Error parsing vertex and edge count");
    }

    // 读取第二行，顶点列表
    getline(infile, line);
    stringstream vertexSS(line);
    string vertex;
    while (vertexSS >> vertex)
    {
        vertices.push_back(vertex);
    }

    // 验证顶点数是否与文件中提供的相匹配（可选）
    if (vertices.size() != numVertices)
    {
        cerr << "Mismatch in number of vertices provided and read from file." << endl;
        // throw runtime_error("Mismatch in number of vertices");
        numVertices = vertices.size();
    }

    // 读取剩余行，边列表
    Edge edge;
    while (getline(infile, line))
    {
        stringstream lineSS(line);
        if (lineSS >> edge.vex1 >> edge.vex2 >> edge.weight)
        {
            edges.push_back(edge);
        }
        else
        {
            cerr << "Error parsing edge data: " << line << endl;
            throw runtime_error("Error parsing edge data");
        }
    }

    // 验证边数是否与文件中提供的相匹配
    if (edges.size() != numEdges)
    {
        cerr << "Mismatch in number of edges provided and read from file." << endl;
        // throw runtime_error("Mismatch in number of edges");
        numEdges = edges.size();
    }

    infile.close();

    return make_tuple(vertices, edges, numVertices, numEdges);
}
#endif