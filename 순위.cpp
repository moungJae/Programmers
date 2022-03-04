#include <string>
#include <vector>

using namespace std;

// res[x][y] = true <= x 번째 선수가 y 번째 선수를 이겼다!
bool res[101][101];

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    for (int i=0; i<results.size(); i++)
    {
        res[results[i][0]][results[i][1]] = true;    
    }
    
    for (int k=1; k<=n; k++)
    {
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=n; j++)
            {
                res[i][j] |= res[i][k] && res[k][j];
            }
        }
    }
    
    for (int i=1; i<=n; i++)
    {
        int cnt = 0;
        for (int j=1; j<=n; j++)
        {
            if (res[i][j] || res[j][i]) cnt++;
        }
        if (cnt == n - 1)
            answer++;
    }
    
    return answer;
}