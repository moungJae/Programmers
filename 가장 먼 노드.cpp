#include <string>
#include <vector>
#include <queue>

using namespace std;

int ans[20001];
bool visited[20001];

void bfs(int start, vector<int> v[])
{
    queue<pair<int, int>> q;
    
    visited[start] = true;
    q.push({start, 0});
    while (!q.empty())
    {
        int cur = q.front().first, dist = q.front().second;
        q.pop();
        ans[dist]++;
        for (int next : v[cur])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push({next, dist + 1});
            }
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    vector<int> v[20001];
    
    for (int i=0; i<edge.size(); i++)
    {
        int x = edge[i][0], y = edge[i][1];
        v[x].push_back(y), v[y].push_back(x);
    }
    
    bfs(1, v);
    for (int i = 20000; i >= 0; i--)
    {
        if (ans[i])
            return ans[i];
    }
}