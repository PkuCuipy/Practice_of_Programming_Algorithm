#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

//模拟
int n, m;
char big[25][25];
char small[25][25];
struct coord {
    int x;
    int y;
    coord() :x(0), y(0) {}
    coord(int x, int y) :x(x), y(y) {}
}  box[505];

bool inmap(int x, int y)
{
    return (x >= 0 && y >= 0 && x < n && y < n);
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n >> m)
    {
        if (n == 0)  break;
        int cnt1 = 0;
        int cnt2 = 0;
        for (int i = 0; i < n; ++i)
        {
            cin >> big[i];
            for (int j = 0; j < n; ++j)
            {
                if (big[i][j] == '*')
                    cnt1++;
            }
        }
        bool flag = 0;//表明是左上角
        int i1, j1;
        for (int i = 0; i < m; ++i)
        {
            cin >> small[i];
            for (int j = 0; j < m; ++j)
            {
                if (small[i][j] == '*')
                {
                    if (!flag)
                    {
                        i1 = i;  j1 = j;
                        box[cnt2++] = coord(0, 0);
                        flag = 1;
                    }
                    else
                        box[cnt2++] = coord(i - i1, j - j1);
                }
            }
        }
        if (cnt1 % cnt2)
        {
            cout << 0 << endl;
            continue;
        }
        flag = 0;
        int cover = 0;
        //注意到对于一种合法的覆盖，大块的左上角一定也是某个小块的左上角
        for (int i = 0; i < n && !flag; ++i)
            for (int j = 0; j < n && !flag; ++j)
            {
                if (big[i][j] == '*')
                {
                    for (int k = 0; k < cnt2; ++k)
                    {
                        int nx = i + box[k].x;
                        int ny = j + box[k].y;
                        if (!inmap(nx, ny))
                        {
                            flag = 1;
                            break;
                        }
                        if (big[nx][ny] != '*')
                        {
                            flag = 1;
                            break;
                        }
                        big[nx][ny] = '.';
                        ++cover;
                    }
                }
            }
        if (cover == cnt1 && !flag)
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}
