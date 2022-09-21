#include <string>
#include <vector>
#include <map>

using namespace std;

string query[100000][3];
int querySize;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    querySize = record.size();
    
    for(int i=0; i<record.size(); i++){
        string s = "";
        int idx = 0;
        for(int j=0; j<record[i].size(); j++){
            if(record[i][j] != ' ') s += record[i][j];
            else{ 
                query[i][idx++] = s;
                s = "";
            }
        }
        query[i][idx] = s;
    }
    
    map<string, string> m;
    for(int i=0; i<querySize; i++){
        if(query[i][0] == "Enter" || query[i][0] == "Change"){
            m[query[i][1]] = query[i][2];
        }
    }
    
    for(int i=0; i<querySize; i++){
        if(query[i][0] == "Enter"){
            answer.push_back(m[query[i][1]]+"님이 들어왔습니다.");
        }
        else if(query[i][0] == "Leave"){
            answer.push_back(m[query[i][1]]+"님이 나갔습니다.");
        }
    }
    
    return answer;
}