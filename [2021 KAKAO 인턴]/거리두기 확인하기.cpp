#include <string>
#include <vector>
#include <queue>

using namespace std;

bool visited[5][5];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void convert(vector<string> place, char Map[][5]) {
	for (int i = 0; i < place.size(); i++) {
		for (int j = 0; j < place[i].size(); j++) {
			Map[i][j] = place[i][j];
		}
	}
}

void init() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			visited[i][j] = false;
		}
	}
}

bool check(int start_x, int start_y, char Map[][5]) {
	queue<pair<pair<int, int>, int>> Q;

	Q.push({ {start_x, start_y}, 0 });
	visited[start_x][start_y] = true;
	while (!Q.empty()) {
		int x = Q.front().first.first, y = Q.front().first.second;
		int t = Q.front().second;
		Q.pop();

		if (t != 0 && Map[x][y] == 'P')
			return false;
		if (t == 2)
			continue;

		for (int i = 0; i < 4; i++) {
			int next_x = x + dx[i], next_y = y + dy[i];
			if (next_x >= 0 && next_x < 5 && next_y >= 0 && next_y < 5) {
				if (Map[next_x][next_y] != 'X' && !visited[next_x][next_y]) {
					Q.push({ {next_x, next_y}, t + 1 });
					visited[next_x][next_y] = true;
				}
			}
		}
	}
	return true;
}

int go(char Map[][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (Map[i][j] == 'P') {
				init();
				if (!check(i, j, Map))
					return 0;
			}
		}
	}
	return 1;
}

vector<int> solution(vector<vector<string>> places) {
	vector<int> answer;
	char Map[5][5];

	for (int i = 0; i < places.size(); i++) {
		convert(places[i], Map);
		answer.push_back(go(Map));
	}

	return answer;
}