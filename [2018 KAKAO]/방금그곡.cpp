#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string find_music(string musicinfo) {
	string ret = "";
	int i = 12;

	while (musicinfo[i] != ',') {
		ret += musicinfo[i];
		i++;
	}
	return ret;
}

string find_melody(string musicinfo) {
	string ret = "";
	int i = musicinfo.size() - 1;
	
	while (musicinfo[i] != ',') {
		ret += musicinfo[i];
		i--;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

int find_melody_time(string m, string melody) {
	int ret_time = 0;
    int t = 0;

	for (int i = 0; i < melody.size(); i++) {
		bool flag = true;

		ret_time = t;
		for (int j = i, idx = 0; idx < m.size();
			j = (j + 1) % melody.size(), idx++) {
			if (idx + 1 < m.size() && m[idx + 1] == '#') {
				int k = (j + 1) % melody.size();
				if (!(m[idx] == melody[j] && m[idx + 1] == melody[k])) {
					flag = false;
					break;
				}
				j = (j + 1) % melody.size(), idx++;
			}
			else {
				int k = (j + 1) % melody.size();
				if (!(m[idx] == melody[j] && melody[k] != '#')) {
					flag = false;
					break;
				}
			}
			ret_time++;
		}
		if (flag)
			return ret_time;
        if (i + 1 < melody.size() && melody[i + 1] == '#')
            i++;
        t++;
	}
	return 1e9;
}

int gap_time(string start, string end) {
	int start_hour = stoi(start.substr(0, 2));
	int start_min = stoi(start.substr(3, 2));
	int end_hour = stoi(end.substr(0, 2));
	int end_min = stoi(end.substr(3, 2));

	return (end_hour - start_hour) * 60 + (end_min - start_min);
}

bool compare(pair<pair<int, int>, string> x, pair<pair<int, int>, string> y) {
	if (x.first.first == y.first.first)
		return x.first.second < y.first.second;
	return x.first.first > y.first.first;
}

string solution(string m, vector<string> musicinfos) {
	string answer = "";
	vector<pair<pair<int, int>, string>> info;
	int idx = 0;

	for (string musicinfo : musicinfos) {
		string start = musicinfo.substr(0, 5);
		string end = musicinfo.substr(6, 5);
		string music = find_music(musicinfo);
		string melody = find_melody(musicinfo);
		int gaptime = gap_time(start, end);

		if (find_melody_time(m, melody) <= gaptime) {
			info.push_back({ {gap_time(start, end), idx}, music });
		}
		idx++;
	}

	sort(info.begin(), info.end(), compare);
	if (info.size())
		answer = info[0].second;
	else
		answer = "(None)";
	return answer;
}