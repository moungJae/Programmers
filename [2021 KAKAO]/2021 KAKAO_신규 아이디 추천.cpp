#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
	string answer = "";

	// 1단계
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
			char c = (new_id[i] - 'A' + 97);
			answer += c;
		}
		else answer += new_id[i];
	}

	// 2단계
	new_id = answer;
	answer = "";
	for (int i = 0; i < new_id.size(); i++) {
		if ((new_id[i] >= 'a' && new_id[i] <= 'z') || (new_id[i] >= '0' && new_id[i] <= '9')
			|| new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')
			answer += new_id[i];
	}

	// 3단계
	new_id = answer;
	answer = "";
	int cnt = 0;
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {
			cnt++;
		}
		else {
			if (cnt >= 1) answer += ".";
			cnt = 0;
			answer += new_id[i];
		}
	}
	if (cnt >= 1) answer += ".";

	// 4단계
	new_id = answer;
	answer = "";
	for (int i = 0; i < new_id.size(); i++) {
		if (i == 0 && new_id[i] == '.') continue;
		if (i == new_id.size() - 1 && new_id[i] == '.') continue;
		answer += new_id[i];
	}

	// 5단계
	new_id = answer;
	if (new_id.size() == 0) new_id += "a";

	// 6단계
	answer = "";
	if (new_id.size() >= 16) {
		for (int i = 0; i < 15; i++) {
			answer += new_id[i];
		}
		if (answer[14] == '.') {
			answer = "";
			for (int i = 0; i < 14; i++) {
				answer += new_id[i];
			}
		}
	}
	else answer = new_id;

	// 7단계
	if (answer.size() <= 2) {
		char c = answer[answer.size() - 1];
		if (answer.size() == 1) {
			for (int i = 0; i < 2; i++) {
				answer += c;
			}
		}
		else {
			answer += c;
		}
	}

	return answer;
}