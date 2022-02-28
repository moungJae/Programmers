#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long sum[360002];

int get_time(string time, int idx)
{
    return (3600 * stoi(&time[idx]) + 60 * stoi(&time[idx + 3]) + stoi(&time[idx + 6]));
}

string make_time(int time)
{
    int hour, minute, second;
    string ret = "";
    
    second = time % 60;
    time /= 60;
    minute = time % 60;
    time /= 60;
    hour = time;
    
    if (hour < 10) ret += "0" + to_string(hour);
    else ret += to_string(hour);
    ret += ":";
    if (minute < 10) ret += "0" + to_string(minute);
    else ret += to_string(minute);
    ret += ":";
    if (second < 10) ret += "0" + to_string(second);
    else ret += to_string(second);
    
    return ret;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";

    int play = get_time(play_time, 0);
    int adv = get_time(adv_time, 0);
    
    for (int i=0; i<logs.size(); i++)
    {
        int log_s = get_time(logs[i], 0);
        int log_e = get_time(logs[i], 9);
        sum[log_s] += 1, sum[log_e] -= 1;
    }
    
    for (int i=1; i<=360000; i++)
        sum[i] += sum[i-1];
    
    int start = 0, end = adv;
    long long max_time = 0, time = 0;
    
    answer = make_time(0);
    for (int i=0; i<end; i++)
    {
        time += sum[i];
    }
    max_time = time;
    start++, end++;
    while (end <= play)
    {
        time += (sum[end - 1] - sum[start - 1]);
        if (time > max_time)
        {
            max_time = time;
            answer = make_time(start);
        }
        start++, end++;
    }
    
    return answer;
}