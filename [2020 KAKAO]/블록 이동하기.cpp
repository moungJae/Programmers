#include <string>
#include <vector>
#include <queue>

using namespace std;

int Map[101][101];
bool visited[101][101][101][101];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N;

bool is_in(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= N;
}

int bfs() {
	queue<pair<pair<pair<int, int>, pair<int, int>>, int>> Q;

	Q.push({ {{1, 1}, {1, 2}}, 0 });
	visited[1][1][1][2] = true;
	while (!Q.empty()) {
		int left_x = Q.front().first.first.first;
		int left_y = Q.front().first.first.second;
		int right_x = Q.front().first.second.first;
		int right_y = Q.front().first.second.second;
		int cnt = Q.front().second;

		if ((left_x == N && left_y == N) ||
			(right_x == N && right_y == N))
			return cnt;
		Q.pop();
		// 둘 다 이동시키기
		for (int i = 0; i < 4; i++) {
			int next_left_x = left_x + dx[i];
			int next_left_y = left_y + dy[i];
			int next_right_x = right_x + dx[i];
			int next_right_y = right_y + dy[i];

			if (is_in(next_left_x, next_left_y) &&
				is_in(next_right_x, next_right_y) &&
				!Map[next_left_x][next_left_y] &&
				!Map[next_right_x][next_right_y] &&
				!visited[next_left_x][next_left_y][next_right_x][next_right_y]) {
				Q.push({ {{next_left_x, next_left_y}, {next_right_x, next_right_y}}, cnt + 1 });
                visited[next_left_x][next_left_y][next_right_x][next_right_y] = true;
			}
		}
		// 수평 90도 회전
		if (left_x == right_x) {
			for (int i = 0; i < 4; i += 2) {
				int next_x, next_y;

				// 왼쪽부분이 이동
				next_x = right_x + dx[i], next_y = right_y + dy[i];
				if (is_in(next_x, next_y) && !Map[next_x][next_y]
					&& !Map[left_x + dx[i]][left_y + dy[i]]
					&& !visited[right_x][right_y][next_x][next_y]) {
					Q.push({ {{right_x, right_y}, {next_x, next_y}}, cnt + 1 });
					visited[right_x][right_y][next_x][next_y] = true;
				}
				// 오른쪽부분이 이동
				next_x = left_x + dx[i], next_y = left_y + dy[i];
				if (is_in(next_x, next_y) && !Map[next_x][next_y]
					&& !Map[right_x + dx[i]][right_y + dy[i]]
					&& !visited[left_x][left_y][next_x][next_y]) {
					Q.push({ {{left_x, left_y}, {next_x, next_y}}, cnt + 1 });
					visited[left_x][left_y][next_x][next_y] = true;
				}
			}
		}
		// 수직 90도 회전
		if (left_y == right_y) {
			for (int i = 1; i < 4; i += 2) {
				int next_x, next_y;

				// 왼쪽부분이 이동
				next_x = right_x + dx[i], next_y = right_y + dy[i];
				if (is_in(next_x, next_y) && !Map[next_x][next_y]
					&& !Map[left_x + dx[i]][left_y + dy[i]]
					&& !visited[right_x][right_y][next_x][next_y]) {
					Q.push({ {{right_x, right_y}, {next_x, next_y}}, cnt + 1 });
					visited[right_x][right_y][next_x][next_y] = true;
				}
				// 오른쪽부분이 이동
				next_x = left_x + dx[i], next_y = left_y + dy[i];
				if (is_in(next_x, next_y) && !Map[next_x][next_y]
					&& !Map[right_x + dx[i]][right_y + dy[i]]
					&& !visited[left_x][left_y][next_x][next_y]) {
					Q.push({ {{left_x, left_y}, {next_x, next_y}}, cnt + 1 });
					visited[left_x][left_y][next_x][next_y] = true;
				}
			}
		}
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;

	N = board.size();
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			Map[i + 1][j + 1] = board[i][j];
		}
	}

	return bfs();
}