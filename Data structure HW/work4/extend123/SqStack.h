#include <iostream>
#include "Node.h"
using namespace std;
#define Maxsize 100
typedef int status;
typedef BinaryTree Selemtype;

typedef struct
{
    Selemtype *base;
    Selemtype *top;
    int stacksize;
} Sqstack;

status InitStack(Sqstack &s)
{
    s.base = new Selemtype[Maxsize];
    s.top = s.base;
    s.stacksize = Maxsize;
    return 1;
}

status Push(Sqstack &s, Selemtype e)
{
    if (s.top - s.base >= s.stacksize)
    {
        return 0;
    }
    else
    {
        *s.top++ = e;
    }
    return 1;
}

status Pop(Sqstack &s, Selemtype &e)
{
    if (s.top == s.base)
    {
        return 0;
    }
    else
    {
        e = *(--s.top);
    }
    return 1;
}

Selemtype GetTop(Sqstack s)
{
    return *(s.top - 1);
}

int empty(Sqstack s)
{
    if (s.top == s.base)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void display(Sqstack &s)
{
    for (int i = 0; i < s.top - s.base; i++)
    {
        cout << s.base[i];
    }
    cout << endl;
}