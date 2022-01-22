#include <string>
#include <vector>

using namespace std;

int lion[11], peach[11];
int gap;

void shot_Lion(int shot, int idx, vector<int>& answer) {
	if (shot == 0) {
		int lion_point, peach_point;
		lion_point = peach_point = 0;
		for (int i = 0; i < 11; i++) {
			if (peach[i] && peach[i] == lion[i])
				peach_point += (10 - i);
			if (peach[i] > lion[i]) peach_point += (10 - i);
			else if (peach[i] < lion[i]) lion_point += (10 - i);
		}
		if (lion_point > peach_point) {
			if (lion_point - peach_point > gap) {
				gap = lion_point - peach_point;
				answer.clear();
				for (int i = 0; i < 11; i++) answer.push_back(lion[i]);
			}
			else if (lion_point - peach_point == gap) {
				for (int i = 10; i >= 0; i--) {
					if (lion[i] != answer[i]) {
						if (lion[i] > answer[i]) {
							answer.clear();
						}
						break;
					}
				}
				if (answer.size() == 0) {
					for (int i = 0; i < 11; i++) answer.push_back(lion[i]);
				}
			}
		}
		return;
	}
	if (idx == 11) return;

	if (shot - (peach[idx] + 1) < 0) {
		lion[idx] = shot;
		shot_Lion(0, idx + 1, answer);
	}
	else {
		lion[idx] = peach[idx] + 1;
		shot_Lion(shot - lion[idx], idx + 1, answer);
	}
	lion[idx] = 0;
	shot_Lion(shot, idx + 1, answer);
}

vector<int> solution(int n, vector<int> info) {
	vector<int> answer;
	for (int i = 0; i < 11; i++) peach[i] = info[i];
	shot_Lion(n, 0, answer);
	if (gap == 0) answer.push_back(-1);

	return answer;
}