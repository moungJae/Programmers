#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

bool visited[10];

void init()
{
    for (int i=0; i<10; i++)
        visited[i] = false;
}

void dfs(int idx, int fin, string order,
         vector<pair<string, int>> &v, map<string, int> &m)
{
    if (idx == order.size())
    {
        string tmp = "";
        for (int i=0; i<order.size(); i++)
        {
            if (visited[i])
                tmp += order[i];
        }
        if (fin != tmp.size())
            return;
        if (!m[tmp])
            v.push_back({tmp, 1});
        m[tmp]++;
        return ;
    }
    visited[idx] = false;
    dfs(idx + 1, fin, order, v, m);
    visited[idx] = true;
    dfs(idx + 1, fin, order, v, m);
}

bool compare1(pair<string, int> x, pair<string, int> y)
{
    return (x.second > y.second);
}

bool compare2(string x, string y)
{
    return (x < y);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    for (int i=0; i<orders.size(); i++)
        sort(orders[i].begin(), orders[i].end());
    for (int i=0; i<course.size(); i++)
    {
        vector<pair<string, int>> v;
        map<string, int> m;
        for (int j=0; j<orders.size(); j++)
        {
            if (orders[j].size() < course[i])
                continue;
            init();
            dfs(0, course[i], orders[j], v, m);
        }
        if (v.size())
        {
            for (int j=0; j<v.size(); j++)
            {
                v[j].second = m[v[j].first];
            }
            sort(v.begin(), v.end(), compare1);
            int max_order = v[0].second;
            if (max_order > 1)
            {
                for (int j=0; j<v.size(); j++)
                {
                    if (v[j].second != max_order)
                        break;
                    answer.push_back(v[j].first);
                }    
            }  
        }
    }
    sort(answer.begin(), answer.end(), compare2);
    
    return answer;
}