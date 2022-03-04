#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    bool op = false;
    priority_queue<pair<int, string>> Q;

    for (string s : words)
    {
        if (s == target)
            op = true;
    }
    if (!op) return 0;

    Q.push({ 0, begin });
    while (!Q.empty())
    {
        int cnt = -Q.top().first;
        string s = Q.top().second;
        Q.pop();

        if (s == target)
            return cnt;

        for (string word : words)
        {
            int check = 0;
            for (int i = 0; i < word.size(); i++)
            {
                if (word[i] == s[i]) check++;
            }
            if (check == word.size() - 1)
            {
                Q.push({ -(cnt + 1), word });
            }
        }
    }
}