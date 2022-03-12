#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

vector<int> v[17890];
map<int, bool> m[17890];

int f(string s)
{
    int ret = 0;
    ret += 26 * 26 * (s[0] - 'A');
    ret += 26 * (s[1] - 'A');
    ret += (s[2] - 'A');
    return ret;
}

string g(int x)
{
    string ret;
    char c;
    c = (x % 26 + 'A'), ret += c, x /= 26;
    c = (x % 26 + 'A'), ret += c, x /= 26;
    c = (x % 26 + 'A'), ret += c;
    reverse(ret.begin(), ret.end());
    return ret;
}

bool dfs(int n, int fin, string s, vector<int> v[], 
    map<int, bool> m[], vector<string> &ans)
{
    int x;
    if (n == fin)
    {
        ans.push_back(s);
        return true;
    }
    x = f(s);
    for (int i = 0; i < v[x].size(); i++)
    {
        int next = v[x][i];
        if (m[x][i])
            continue;
        m[x][i] = true;
        if (dfs(n + 1, fin, g(next), v, m, ans))
        {
            ans.push_back(s);
            return true;
        }
        m[x][i] = false;
    }
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    string from, to;
    int start, end;

    for (int i = 0; i < tickets.size(); i++)
    {
        from = tickets[i][0], to = tickets[i][1];
        v[f(from)].push_back(f(to));
    }
    start = f("AAA"), end = f("ZZZ");
    for (int i = start; i < end; i++)
    {
        if (v[i].size())
            sort(v[i].begin(), v[i].end());
    }
    dfs(1, tickets.size() + 1, "ICN", v, m, answer);
    reverse(answer.begin(), answer.end());
    
    return answer;
}