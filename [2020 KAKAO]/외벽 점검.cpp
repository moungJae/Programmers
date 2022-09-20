#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Weak[30];

int get_answer(int start_idx, vector<int> weak, vector<int> dist) {
	int cnt = 0;
	int idx = start_idx;

	for (int i = 0; i < dist.size(); i++) {
		while (cnt != weak.size() && idx < 2 * weak.size()) {
			if (Weak[idx] - Weak[start_idx] <= dist[i]) {
                cnt++;
				idx++;
			}
			else break;
		}
		if (cnt == weak.size())
			return i + 1;
		start_idx = idx;
	}

	return 1e9;
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 1e9;

	for (int i = 0; i < 2 * weak.size(); i++) {
		if (i < weak.size())
			Weak[i] = weak[i];
		else
			Weak[i] = weak[i - weak.size()] + n;
    }

	do {
		for (int i = 0; i < weak.size(); i++) {
			answer = min(answer, get_answer(i, weak, dist));
        }
	} while (next_permutation(dist.begin(), dist.end()));

	return (answer == 1e9 ? -1 : answer);
}