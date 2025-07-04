#include <iostream>
using namespace std;
#define Maxsize 100
#define TRUE 1
#define OK 1
#define FALSE 0
#define ERROR 0
typedef int status;
typedef int Selemtype;
typedef struct
{
    Selemtype* base;
    Selemtype* top;
    int stacksize;
} Sqstack;

status InitStack(Sqstack& s);
status Push(Sqstack& s, Selemtype e);
status Pop(Sqstack& s, Selemtype& e);
Selemtype GetTop(Sqstack s);

status InitStack(Sqstack& s)
{
    s.base = new Selemtype[Maxsize];
    s.top = s.base;
    s.stacksize = Maxsize;
    return OK;
}
status Push(Sqstack& s, Selemtype e)
{
    if (s.top - s.base >= s.stacksize)
    {
        return ERROR;
    }
    else
    {
        *s.top++ = e;
    }
    return OK;
}

status Pop(Sqstack& s, Selemtype& e)
{
    if (s.top == s.base)
    {
        return ERROR;
    }
    else
    {
        e = *(--s.top);
    }
    return OK;
}

Selemtype GetTop(Sqstack s)
{
    return *(s.top - 1);
}

int empty(Sqstack s)
{
    if (s.top == s.base)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void convert10to8(Sqstack s, int n)
{
    int reminder = 1;
    while (n != 0)
    {
        reminder = n % 8;
        n = n / 8;
        Push(s, reminder);
    }

    int re = 0;
    while (Pop(s, re))
    {
        cout << re;
    }
}

int main()
{
    Sqstack q;
    InitStack(q);
    convert10to8(q, 66);
    return 1;
}