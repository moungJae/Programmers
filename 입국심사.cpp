#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 1e18;
    long long low, high;
    
    sort(times.begin(), times.end());
    low = (long long)times[0], high = n * (long long)times[times.size() - 1];
    while (low <= high)
    {
        long long mid = (low + high) / 2;
        long long cnt = 0;
        bool op = false;
        for (int i=0; i<times.size(); i++)
        {
            if (mid % (long long)times[i] == 0)
                op = true;
            cnt += mid / (long long)times[i];
        }
        if (cnt < (long long)n)
            low = mid + 1;
        else
        {
            if (op)
                answer = min(answer, mid);
            high = mid - 1;   
        }
    }
    
    return answer;
}