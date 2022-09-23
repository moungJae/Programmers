#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string make_n(int x, int n){
    if(x == 0) 
        return "0";
    
    vector<int> v;
    while(x != 0){
        v.push_back(x % n);
        x /= n;
    }
    reverse(v.begin(), v.end());
    
    string tmp = "";
    for(int i=0;i<v.size(); i++){
        if(v[i] >= 10) tmp += (v[i] - 10 + 'A');
        else tmp += (v[i] + '0');
    }
    return tmp;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string tmp = "";
    for(int i=0; i<1000000; i++){
        tmp += make_n(i, n);    
    }
    
    int cnt = 0;
    for(int i = p - 1; i < 1000000; i += m){
        answer += tmp[i];
        cnt++;
        if(cnt == t) break;
    }
    
    return answer;
}