#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, pair<int, int>> x, pair<int, pair<int, int>> y)
{
    return x.first < y.first;
}

int get_parent(int x, int parent[])
{
    if (x == parent[x])
        return x;
    return parent[x] = get_parent(parent[x], parent);
}

void go_union(int x, int y, int parent[])
{
    x = get_parent(x, parent), y = get_parent(y, parent);
    if (x > y)
        parent[x] = y;
    else
        parent[y] = x;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int parent[100];
    vector<pair<int, pair<int, int>>> v;

    for (int i = 0; i < n; i++)
        parent[i] = i;

    for (int i = 0; i < costs.size(); i++)
    {
        int x = costs[i][0], y = costs[i][1];
        int dist = costs[i][2];
        v.push_back({ dist, {x, y} });
    }
    sort(v.begin(), v.end(), compare);

    for (int i = 0; i < v.size(); i++)
    {
        int x = v[i].second.first, y = v[i].second.second;
        int dist = v[i].first;
        if (get_parent(x, parent) != get_parent(y, parent))
        {
            go_union(x, y, parent);
            answer += dist;
        }
    }

    return answer;
}