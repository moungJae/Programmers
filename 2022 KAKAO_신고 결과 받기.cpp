#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    map<string ,int> m1, m2;
    map<string, bool> check1, check2;
    
    for(int i=0;i<report.size();i++){
        string s="";
        int t=0;
        for(int j=0;j<report[i].size(); j++){
            if(report[i][j] == ' ') {
                t = j + 1;
                break;
            }
        }
        for(int j=t; j<report[i].size(); j++) 
            s += report[i][j];
        if(!check1[report[i]]){
            check1[report[i]] = true;
            m1[s]++;
        } 
    }
    
    for(int i=0;i<report.size();i++){
        string s1="", s2="";
        int t=0;
        for(int j=0;j<report[i].size(); j++){
            if(report[i][j] == ' ') {
                t = j + 1;
                break;
            }
            s1 += report[i][j];
        }
        for(int j=t; j<report[i].size(); j++) 
            s2 += report[i][j];
        if(!check2[report[i]]){
            check2[report[i]] = true;
            if(m1[s2] >= k) 
                m2[s1]++;   
        }
    }
    
    for(int i=0;i<id_list.size();i++){
        string S = id_list[i];
        answer.push_back(m2[S]);
    }
    
    return answer;
}