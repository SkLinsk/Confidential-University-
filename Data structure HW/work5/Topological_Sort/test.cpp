#include "AMGraph.h"
#include "Topological_Sort.h"
using namespace std;

int main()
{
    string filename = "Topological_Sort.txt";
    AMGraph M;

    CreateUDN(M, filename);
    display_AMG(M);

    UDN_DFS(M, 0);

    Topological_Sort(M);
}