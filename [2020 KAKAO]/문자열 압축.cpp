#include <string>
#include <vector>
#define INF 1000000000

using namespace std;

string S;

string getString(int left, int right) {
	string ret = "";
	for (int i = left; i < right; i++) ret += S[i];
	return ret;
}

int min(int x, int y) {
	if (x > y) return y;
	return x;
}

int solution(string s) {
	int answer = s.size();
	S = s;

	for (int i = 1; i <= s.size() / 2; i++) {
		int cnt = 1, x;
		string cmp1 = getString(0, i), res = "";

		for (x = i; x < s.size(); x++) {
			if (x + i > s.size()) break;

			string cmp2 = getString(x, x + i);

			if (cmp1 == cmp2) {
				cnt += 1;
				x += (i - 1);
			}
			else {
				if (cnt > 1) res += to_string(cnt) + cmp1;
				else res += cmp1;
				cnt = 1;
				cmp1 = getString(x, x + i);
				x += (i - 1);
			}
		}

		if (cnt > 1) {
			res += to_string(cnt) + cmp1;
			for (int i = x; i < s.size(); i++) res += s[i];
		}
		else {
			res += cmp1;
			for (int i = x; i < s.size(); i++) res += s[i];
		}

		answer = min(answer, res.size());
	}

	return answer;
}