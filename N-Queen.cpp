#include <string>
#include <vector>

using namespace std;

bool Map[13][13];

void init()
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            Map[i][j] = false;
}

int is_valid(int n, int cur, int idx)
{
    for (int i = cur - 1, t = 1; i >= 0; i--, t++)
    {
        if (Map[i][idx])
            return 0;
        if (idx - t >= 0 && Map[i][idx - t])
            return 0;
        if (idx + t < n && Map[i][idx + t])
            return 0;
    }
    return 1;
}

int back_tracking(int cur, int n)
{
    int ret = 0;

    if (cur == n)
        return 1;

    for (int i = 0; i < n; i++)
    {
        if (is_valid(n, cur, i))
        {
            Map[cur][i] = true;
            ret += back_tracking(cur + 1, n);
            Map[cur][i] = false;
        }
    }
    return ret;
}

int solution(int n) {
    int answer = 0;
    init();
    answer = back_tracking(0, n);
    return answer;
}