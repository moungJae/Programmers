#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    multiset<int> m;
    
    for (string query : operations)
    {
        if (query[0] == 'I')
        {
            m.insert(stoi(&query[2]));
        }
        else
        {
            if (m.size())
            {
                if (stoi(&query[2]) == 1)
                    m.erase(*(--m.end()));
                else
                    m.erase(*(m.begin()));
            }
        }
    }
    
    if (m.size())
    {
        answer.push_back(*(--m.end()));
        answer.push_back(*(m.begin()));
    }
    else
        answer.push_back(0), answer.push_back(0);
    
    return answer;
}