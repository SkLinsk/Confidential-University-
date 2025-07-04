#include "ALGraph.h"
#include "AMGraph.h"
#include "Prim.h"
#include "Kruskal.h"
using namespace std;

int main()
{
    string filename = "prim_kruskal.txt";
    AMGraph M;
    ALGraph L;

    CreateUDN(M, filename);
    display_AMG(M);
    CreateUDG(L, filename);
    display_ALG(L);

    // UDN_DFS(M, 0);
    // UDN_BFS(M, 0);
    // UDG_DFS(L, 0);
    // UDG_BFS(L, 0);
    cout << endl;
    // 两种存储方式的遍历检录顺序不同，导致输出顺序略有不同

    cout << endl;
    Prim(M);

    cout << endl;
    Kruskal(M);

    return 0;
}