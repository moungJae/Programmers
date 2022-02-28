#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dist[201][201];
vector<pair<int, int>> info[201];

void init()
{
    for (int i=1; i<=200; i++)
        for (int j=1; j<=200; j++)
            dist[i][j] = 100000000;
}

void set_dijkstra(int s)
{
    priority_queue<pair<int, int>> pq;
    
    pq.push({0, s});
    dist[s][s] = 0;
    while (!pq.empty())
    {
        int d = -pq.top().first, cur = pq.top().second;
        pq.pop();
        
        if (d < dist[s][cur])
            continue;
        for (int i=0; i<info[cur].size(); i++)
        {
            int next = info[cur][i].first, next_d = d + info[cur][i].second;
            if (next_d < dist[s][next])
            {
                dist[s][next] = next_d;
                pq.push({-next_d, next});
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 100000000;
   
    for (int i=0; i<fares.size(); i++)
    {
        int u = fares[i][0], v = fares[i][1], d = fares[i][2];
        info[u].push_back({v, d});
        info[v].push_back({u, d});
    }
    
    init();
    for (int i=1; i<=n; i++)
        set_dijkstra(i);
    
    for (int e=1; e<=n; e++)
        answer = min(answer, dist[s][e] + dist[e][a] + dist[e][b]);
    
    return answer;
}