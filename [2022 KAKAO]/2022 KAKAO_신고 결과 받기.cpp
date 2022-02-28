#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
	vector<int> answer;
	map<string, int> report_cnt, report_id;
	map<string, bool> report_check;

	for (int i = 0; i < report.size(); i++) {
		string s = "";
		int t = 0;

		for (int j = 0; j < report[i].size(); j++) {
			if (report[i][j] == ' ') {
				t = j + 1;
				break;
			}
		}

		// s는 신고당한 유저의 이름
		for (int j = t; j < report[i].size(); j++)
			s += report[i][j];

		if (!report_check[report[i]]) {
			report_check[report[i]] = true;
			report_cnt[s]++;
		}
	}

	report_check.clear();
	for (int i = 0; i < report.size(); i++) {
		string s1 = "", s2 = "";
		int t = 0;

		// s1는 신고한 유저의 이름
		for (int j = 0; j < report[i].size(); j++) {
			if (report[i][j] == ' ') {
				t = j + 1;
				break;
			}
			s1 += report[i][j];
		}

		// s2는 신고당한 유저의 이름
		for (int j = t; j < report[i].size(); j++)
			s2 += report[i][j];

		if (!report_check[report[i]]) {
			report_check[report[i]] = true;
			if (report_cnt[s2] >= k)
				report_id[s1]++;
		}
	}

	for (int i = 0; i < id_list.size(); i++) {
		string S = id_list[i];
		answer.push_back(report_id[S]);
	}

	return answer;
}