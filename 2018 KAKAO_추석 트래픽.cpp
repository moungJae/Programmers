#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// year / month / day / time 
vector<long long> v_start, v_end;

int getYear(string s) {
	string year = s.substr(0, 4);
	return stoi(year);
}

int getMonth(string s) {
	string month = s.substr(5, 2);
	return stoi(month);
}

int getDay(string s) {
	string day = s.substr(8, 2);
	return stoi(day);
}

int getTime(string s) {
	string h, m, t, mm;
	h = s.substr(11, 2), m = s.substr(14, 2);
	t = s.substr(17, 2), mm = s.substr(20, 3);
	return 1000 * (stoi(h) * 3600 + stoi(m) * 60 + stoi(t)) + stoi(mm);
}

int getGap(string s) {
	int mul_op[4] = { -1, 100, 10, 1 };
	string gap;
	gap = s.substr(24, s.size());
	gap = gap.substr(0, gap.size() - 1);
	if (gap.size() == 1) return 1000 * stoi(gap);
	else {
		string mm = gap.substr(2, gap.size());
		gap = gap.substr(0, 1);
		return 1000 * stoi(gap) + mul_op[mm.size()] * stoi(mm);
	}
}

long long getHash(int year, int month, int day, int time) {
	long long year_ = (long long)year * 1e12;
	long long month_ = (long long)month * 1e10;
	long long day_ = (long long)day * 1e8;
	return year_ + month_ + day_ + (long long)time;
}

bool compare(long long x, long long y) {
	return x < y;
}

bool isProcess(long long cur, long long next, long long start, long long end) {
	if (cur <= start && start <= next) return true;
	else if (start <= cur && next <= end) return true;
	else if (cur <= end && end <= next) return true;
	return false;
}

int solution(vector<string> lines) {
	int answer = 0;
	int year, month, day, time, gap, N;
	long long info;

	N = lines.size();
	for (int i = 0; i < N; i++) {
		string s = lines[i];
		year = getYear(s), month = getMonth(s), day = getDay(s);
		time = getTime(s), gap = getGap(s);
		v_end.push_back((info = getHash(year, month, day, time)));
		v_start.push_back(info - gap + 1);
	}

	sort(v_start.begin(), v_start.end());
	sort(v_end.begin(), v_end.end());

	// start 지점부터 전부 비교
	for (int i = 0; i < N; i++) {
		long long cur = v_start[i], next = v_start[i] + 999;
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (isProcess(cur, next, v_start[j], v_end[j])) cnt++;
		}
		answer = max(answer, cnt);
	}

	// end 지점부터 전부 비교
	for (int i = 0; i < N; i++) {
		long long cur = v_end[i], next = v_end[i] + 999;
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (isProcess(cur, next, v_start[j], v_end[j])) cnt++;
		}
		answer = max(answer, cnt);
	}

	return answer;
}