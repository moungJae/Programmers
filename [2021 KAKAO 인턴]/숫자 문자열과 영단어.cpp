#include <string>
#include <vector>

using namespace std;

int solution(string s) {
	int answer = 0;
	string result = "";

	for (int i = 0; i < s.size(); i++) {
		if (s.substr(i, 4) == "zero") result += "0", i += 3;
		else if (s.substr(i, 3) == "one") result += "1", i += 2;
		else if (s.substr(i, 3) == "two") result += "2", i += 2;
		else if (s.substr(i, 5) == "three") result += "3", i += 4;
		else if (s.substr(i, 4) == "four") result += "4", i += 3;
		else if (s.substr(i, 4) == "five") result += "5", i += 3;
		else if (s.substr(i, 3) == "six") result += "6", i += 2;
		else if (s.substr(i, 5) == "seven") result += "7", i += 4;
		else if (s.substr(i, 5) == "eight") result += "8", i += 4;
		else if (s.substr(i, 4) == "nine") result += "9", i += 3;
		else if (s[i] >= '0' && s[i] <= '9') result += s[i];
	}

	answer = stoi(result);

	return answer;
}