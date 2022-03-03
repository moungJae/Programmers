#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool compare(vector<int> x, vector<int> y)
{
    return x[0] < y[0];
}

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    priority_queue<pair<int, int>> pq;
    
    sort(jobs.begin(), jobs.end(), compare);
    int task_cnt = 0, cur_time = 0;
    while (task_cnt < jobs.size() || !pq.empty())
    {
        if (task_cnt < jobs.size() && jobs[task_cnt][0] <= cur_time)
        {
            pq.push({-jobs[task_cnt][1], -jobs[task_cnt][0]});
            task_cnt++;
            continue;
        }
        
        if (!pq.empty())
        {
            cur_time += (-pq.top().first);
            answer += (cur_time + pq.top().second);
            pq.pop();
        }
        else
            cur_time = jobs[task_cnt][0];
    }
    
    return answer / task_cnt;
}