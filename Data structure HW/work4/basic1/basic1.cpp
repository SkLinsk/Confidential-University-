#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    struct Node *lchild, *rchild;
    Node(int val) : data(val), lchild(nullptr), rchild(nullptr) {};
} Node, *BinaryTree;

BinaryTree createBinaryTree(const int *arr, int &index)
{
    if (arr[index] == -1)
    {
        index++;
        return nullptr;
    }

    BinaryTree p_root = new Node(arr[index++]);
    p_root->lchild = createBinaryTree(arr, index);
    p_root->rchild = createBinaryTree(arr, index);

    return p_root;
}

int isempty(BinaryTree p_root)
{
    if (!p_root)
    {
        cerr << "Tree is empty." << endl;
        return 0;
    }
    else return 1;
}

int Depth(BinaryTree p_root)
{
    if (p_root == NULL)
        return 0;
    else
    {
        int i = Depth(p_root->lchild);
        int j = Depth(p_root->rchild);
        return i > j ? i + 1 : j + 1;
    }
}

void LevelOrderTraversal(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }

    cout << "Level Order Traversal: ";

    int maxDepth = Depth(p_root);

    BinaryTree *Binary_pointer_quene = new BinaryTree[maxDepth * 2];
    int front = 0, rear = 0;

    Binary_pointer_quene[rear++] = p_root;

    while (front < rear)
    {
        BinaryTree currentNode = Binary_pointer_quene[front++];
        cout << currentNode->data << " ";

        if (currentNode->lchild)
        {
            Binary_pointer_quene[rear++] = currentNode->lchild;
        }
        if (currentNode->rchild)
        {
            Binary_pointer_quene[rear++] = currentNode->rchild;
        }
    }

    delete[] Binary_pointer_quene;
}

void freeTree(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }
    freeTree(p_root->lchild);
    freeTree(p_root->rchild);
    delete p_root;
}

int main()
{
    const int arr[] = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
    int index = 0;

    BinaryTree p_root = createBinaryTree(arr, index);

    LevelOrderTraversal(p_root);
    cout << endl;

    freeTree(p_root);

    return 0;
}