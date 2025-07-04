#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
const int cheese = 8;            // 八行八列的棋盘
int Seq = 0;                       // 遍历的次数
int Visited[cheese][cheese] = {0}; // 已走过的点设为1
typedef struct p
{
    int x, y;
} Point; // 点

vector<Point> Points; // 存储走过的点

bool Out_range(const Point &pos)
{
    if (0 <= pos.x && pos.x < cheese && 0 <= pos.y && pos.y < cheese)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool DFS(const Point &spot)
{
    Points.push_back(spot);
    Seq++;
    if (Seq == 64)
    {
        return true;
    }
    const int dir[8][2] = {{-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};
    for (int ind = 0; ind < 8; ind++)
    {
        Point next = spot;
        next.x += dir[ind][0];
        next.y += dir[ind][1];
        if (!Out_range(next) && !Visited[next.x][next.y])
        {
            Visited[next.x][next.y] = Seq + 1;

            if (DFS(next))
            {
                return true;
            }
            Visited[next.x][next.y] = 0;
        }
    }
    Points.pop_back();
    Seq--;
    return false;
}

int main()
{
    int Zero_X = 0, Zero_Y = 0;

    Point point;
    point.x = Zero_X;
    point.y = Zero_Y;

    Visited[Zero_X][Zero_Y] = 1; // 标记起点
    DFS(point);

    cout << "Trace: " << endl;
    for (int i = 0; i < cheese; i++)
    {
        for (int j = 0; j < cheese; j++)
        {
            cout << setw(5) << Visited[i][j];
        }
        cout << endl;
    }
    return 0;
}
