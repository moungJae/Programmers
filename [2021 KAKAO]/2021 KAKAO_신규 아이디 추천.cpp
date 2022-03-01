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
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {
			while (i < new_id.size() && new_id[i] == '.') {
				i++;
			}
			answer += ".";
			i -= 1;
		}
		else
			answer += new_id[i];
	}

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
		answer = new_id.substr(0, 15);
		if (new_id[14] == '.')
			answer = new_id.substr(0, 14);
	}
	else answer = new_id;

	// 7단계
	if (answer.size() <= 2) {
		char c = answer[answer.size() - 1];
		if (answer.size() == 1) {
			for (int i = 0; i < 2; i++)
				answer += c;
		}
		else {
			answer += c;
		}
	}

	return answer;
}