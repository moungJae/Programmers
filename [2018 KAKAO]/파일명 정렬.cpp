#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string get_head(string file, int &idx){
    string head = "";
    while(!(file[idx] >= '0' && file[idx] <= '9')) {
        if(file[idx] >= 'A' && file[idx] <= 'Z')
            head += (file[idx] - 'A' + 'a');
        else
            head += file[idx];
        idx++;
    }
    return head;
}

string get_number(string file, int &idx){
    string number = "";
    int cnt = 0;
    while((file[idx] >= '0' && file[idx] <= '9')) {
        number += file[idx++];
        cnt++;
        if(cnt == 5) break;
    }
    return number;
}

bool compare(pair<pair<string, int>, pair<int, string>> x, 
             pair<pair<string, int>, pair<int, string>> y) 
{
    if(x.first.first == y.first.first){
        if(x.first.second == y.first.second){
            return x.second.first < y.second.first;
        }
        return x.first.second < y.first.second;
    }
    return x.first.first < y.first.first;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    vector<pair<pair<string, int>, pair<int, string>>> v;
    
    string head = "", number = "", tail = "";
    for(int i=0;i<files.size();i++){
        int idx = 0;
        string file = files[i];
        head = get_head(file, idx);
        number = get_number(file, idx);
        v.push_back({{head, stoi(number)}, {i, file}});
    }
    
    sort(v.begin(), v.end(), compare);
    
    for(int i=0;i<v.size();i++){
        answer.push_back(v[i].second.second);
    }
    
    return answer;
}