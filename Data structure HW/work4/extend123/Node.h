#include <iostream>
using namespace std;
#define Datatype int
typedef struct Node
{
    Datatype data;
    struct Node *lchild, *rchild;
    Node(): data(-1), lchild(nullptr), rchild(nullptr) {};
    Node(int val): data(val), lchild(nullptr), rchild(nullptr) {};
} *BinaryTree, *LinkNode;