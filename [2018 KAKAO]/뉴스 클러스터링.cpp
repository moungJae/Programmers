#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<string> v;
map<string, int> m, m1, m2;

int solution(string str1, string str2) {
	int answer = 0;

	for (int i = 0; i < str1.size(); i++) {
		if (str1[i] >= 'A' && str1[i] <= 'Z')
			str1[i] = str1[i] - 'A' + 'a';
	}

	for (int i = 0; i < str2.size(); i++) {
		if (str2[i] >= 'A' && str2[i] <= 'Z')
			str2[i] = str2[i] - 'A' + 'a';
	}

	int union_cnt = 0, intersect_cnt = 0;

	for (int i = 0; i < str1.size() - 1; i++) {
		if (str1[i] >= 'a' && str1[i] <= 'z' && str1[i + 1] >= 'a' && str1[i + 1] <= 'z') {
			string tmp = "";
			tmp += str1[i];
			tmp += str1[i + 1];
			m1[tmp]++;
			if (m[tmp] == 0) {
				v.push_back(tmp);
				m[tmp] = 1;
			}
		}
	}

	for (int i = 0; i < str2.size() - 1; i++) {
		if (str2[i] >= 'a' && str2[i] <= 'z' && str2[i + 1] >= 'a' && str2[i + 1] <= 'z') {
			string tmp = "";
			tmp += str2[i];
			tmp += str2[i + 1];
			m2[tmp]++;
			if (m[tmp] == 0) {
				v.push_back(tmp);
				m[tmp] = 1;
			}
		}
	}

	for (int i = 0; i < v.size(); i++) {
		union_cnt += max(m1[v[i]], m2[v[i]]);
		intersect_cnt += min(m1[v[i]], m2[v[i]]);
	}

    if(union_cnt == 0) answer = 65536;
	else answer = intersect_cnt * 65536 / union_cnt;

	return answer;
}