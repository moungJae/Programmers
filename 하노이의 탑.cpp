#include <string>
#include <vector>

using namespace std;

void hanoi(vector<vector<int>> &ans, int n, int from, int by, int to)
{
    vector<int> v;
    if (n == 1)
    {
        v.push_back(from), v.push_back(to);
        ans.push_back(v);
        return;
    }
    hanoi(ans, n - 1, from, to, by);
    v.push_back(from), v.push_back(to);
    ans.push_back(v);
    hanoi(ans, n - 1, by, from, to);
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    
    hanoi(answer, n, 1, 2, 3);
    return answer;
}