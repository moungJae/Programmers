#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int stage_cnt[501];

bool compare(pair<double, int> x, pair<double, int> y) { 
    if (x.first == y.first)
        return x.second < y.second;
    return x.first > y.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<double, int>> v;
    int cnt = stages.size();
    
    for (int stage : stages) {
        stage_cnt[stage]++;
    }
    
    for (int stage = 1; stage <= N; stage++) {
        if (cnt) {
            double error = (double)stage_cnt[stage] / (double)cnt;

            v.push_back({error, stage});
            cnt -= stage_cnt[stage];
        }
        else {
            v.push_back({0.0, stage});
        }
    }
    
    sort(v.begin(), v.end(), compare);
    for (int i = 0; i < v.size(); i++) {
        answer.push_back(v[i].second);
    }
    
    return answer;
}