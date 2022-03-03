#include <string>
#include <vector>

using namespace std;

bool visited[201];

void dfs(int cur, vector<int> v[])
{
    if (visited[cur])
        return;
    visited[cur] = true;
    for(int next : v[cur])
    {
        dfs(next, v);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<int> v[201];
    
    for (int i=0; i<n; i++)
    {
        int x = i + 1;
        for (int j=0; j<computers[i].size(); j++)
        {
            int y = j + 1;
            if (x == y)
                continue;
            if (computers[i][j])
            {
                v[x].push_back(y);
                v[y].push_back(x);
            }
        }
    }
    
    for (int i=1; i<=n; i++)
    {
        if (!visited[i])
            dfs(i, v), answer++;
    }
    
    return answer;
}