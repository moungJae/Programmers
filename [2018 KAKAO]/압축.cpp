#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> m;

vector<int> solution(string msg) {
    vector<int> answer;
    string tmp = "", before = "";
    
    int dic_cnt = 26;
    
    for(int i=0; i<26; i++){
        string s = "";
        s += ('A' + i);
        m[s] = i + 1;
    }
    
    for(int i=0; i<msg.size(); i++){
        before = tmp;
        if(m[(tmp += msg[i])]) continue;
        answer.push_back(m[before]);
        m[tmp] = ++dic_cnt;
        tmp = "";
        i--;
    }
    
    if(tmp.size()) answer.push_back(m[tmp]);
    
    return answer;
}