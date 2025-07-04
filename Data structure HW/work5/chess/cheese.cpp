#include <iostream>
#include <iomanip>
using namespace std;
int Seq = 0; 
int chess[8][8] =
{   
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

bool Out_range(int x, int y)
{
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Visited(int x, int y)
{
    if (chess[x][y])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DFS(int x, int y)
{
    if (Seq == 64)
    {
        return;
    }

    if (!Out_range(x, y) && !Visited(x, y))
    {
        chess[x][y] = ++Seq;
        DFS(x + 2, y + 1);
        DFS(x - 2, y - 1);
        DFS(x + 2, y - 1);
        DFS(x - 2, y + 1);
        DFS(x - 1, y - 2);
        DFS(x + 1, y - 2);
        DFS(x + 1, y + 2);
        DFS(x - 1, y + 2);
        return;
    }
    else
    {
        return;
    }
}

int main()
{
    int Zero_x, Zero_y;
    cout << "Position Zero: " << endl;
    while (1)
    {
        Zero_x = 3, Zero_y = 4;
        if (Zero_x > 7 || Zero_x < 0 || Zero_y > 7 || Zero_y < 0)
        {
            throw(runtime_error("Error revue."));
        }
        else
        {
            break;
        }
    }

    DFS(Zero_x, Zero_y);

    for (int i = 0; i < 8; i++) // 输出打印测试
    {
        for (int j = 0; j < 8; j++)
        {
            cout << setw(5) << chess[i][j] << "  ";
        }
        cout << endl;
    }
    return 0;
}
