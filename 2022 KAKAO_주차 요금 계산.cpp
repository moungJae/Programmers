#include <string>
#include <vector>
#include <math.h>

using namespace std;

int get_Time(string S) {
	string hour, min;
	hour = S.substr(0, 2);
	min = S.substr(3, 5);
	return stoi(hour) * 60 + stoi(min);
}

int get_Number(string S) {
	string number;
	number = S.substr(6, 10);
	return stoi(number);
}

vector<int> car[10000];

vector<int> solution(vector<int> fees, vector<string> records) {
	vector<int> answer;
	for (int i = 0; i < records.size(); i++) {
		int time, number;
		time = get_Time(records[i]);
		number = get_Number(records[i]);
		car[number].push_back(time);
	}

	for (int number = 0; number < 10000; number++) {
		if (car[number].size() == 0) continue;
		if (car[number].size() % 2)
			car[number].push_back(1439);
		int time = 0;
		for (int i = 0; i < car[number].size(); i += 2) {
			time += (car[number][i + 1] - car[number][i]);
		}
		if (time > fees[0]) {
			int cul_time = time - fees[0];
			if (cul_time % fees[2]) cul_time = cul_time / fees[2] + 1;
			else cul_time = cul_time / fees[2];
			answer.push_back(fees[1] + cul_time * fees[3]);
		}
		else {
			answer.push_back(fees[1]);
		}
	}

	return answer;
}