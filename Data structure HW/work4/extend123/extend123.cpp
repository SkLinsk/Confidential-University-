#include <iostream>
#include "SqStack.h"

using namespace std;

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
    else
        return 1;
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

void PreOrderTraversal(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }

    cout << p_root->data << " ";
    PreOrderTraversal(p_root->lchild);
    PreOrderTraversal(p_root->rchild);
}

void InOrderTraversal(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }

    InOrderTraversal(p_root->lchild);
    cout << p_root->data << " ";
    InOrderTraversal(p_root->rchild);
}

void PostOrderTraversal(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }

    PostOrderTraversal(p_root->lchild);
    PostOrderTraversal(p_root->rchild);
    cout << p_root->data << " ";
}

void PreOrderTraversal_Stack(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }
    else
    {
        Sqstack s;
        InitStack(s);
        while (p_root || !empty(s))
        {
            if (p_root)
            {
                cout << p_root->data << " ";
                Push(s, p_root);
                p_root = p_root->lchild;
            }
            else
            {
                Pop(s, p_root);
                p_root = p_root->rchild;
            }
        }
        cout << endl;
    }
}

void InOrderTraversal_Stack(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }
    else
    {
        Sqstack s;
        InitStack(s);
        while(p_root || !empty(s))
        {
            if (p_root)
            {
                Push(s, p_root);
                p_root = p_root->lchild;
            }
            else
            {
                Pop(s, p_root);
                cout << p_root->data << " ";
                p_root = p_root->rchild;
            }
        }
        cout << endl;
    }
}

void PostOrderTraversal_Stack(BinaryTree p_root)
{
    if (!p_root)
    {
        return;
    }
    else
    {
        Sqstack s1, s2;
        InitStack(s1);
        InitStack(s2);
        Push(s1, p_root);
        while (!empty(s1))
        {
            BinaryTree temp;
            Pop(s1, temp);
            Push(s2, temp);
            if (temp->lchild)
                Push(s1, temp->lchild);
            if (temp->rchild)
                Push(s1, temp->rchild);
        }

        do
        {
            BinaryTree temp;
            Pop(s2, temp);
            cout << temp->data << " ";
        }while(!empty(s2));
        cout << endl;
    }
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

    cout << "Pre Order Traversal: ";
    PreOrderTraversal(p_root);
    cout << endl;

    cout << "In Order Traversal: ";
    InOrderTraversal(p_root);
    cout << endl;

    cout << "Post Order Traversal: ";
    PostOrderTraversal(p_root);
    cout << endl;

    cout << "Pre Order Traversal in stack: ";
    PreOrderTraversal_Stack(p_root);

    cout << "In Order Traversal in stack: ";
    InOrderTraversal_Stack(p_root);

    cout << "Post Order Traversal in stack: ";
    PostOrderTraversal_Stack(p_root);

    freeTree(p_root);

    return 0;
}