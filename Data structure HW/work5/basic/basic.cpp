#include "ALGraph.h"
#include "AMGraph.h"
using namespace std;

int main()
{
    string filename = "Graph.txt";
    AMGraph M; ALGraph L;
    
    CreateUDN(M, filename);
    display_AMG(M);
    CreateUDG(L, filename);
    display_ALG(L);

    UDN_DFS(M, 0);
    UDN_BFS(M, 0);
    UDG_DFS(L, 0);
    UDG_BFS(L, 0);
    // 两种存储方式的遍历检录顺序不同，导致输出顺序略有不同

    return 0;
}