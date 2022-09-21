#include <string>
#include <vector>
#include <map>

using namespace std;

int Map[51][51];
int N;

bool check_up(int x, int y) {
	while (x >= 0) {
		if (Map[x][y])
			return false;
		x--;
	}
	return true;
}

bool check_rectangle(int x, int y) {
	int num = Map[x][y];

	if (x + 1 < N && y + 2 < N && Map[x + 1][y] == num
		&& Map[x + 1][y + 1] == num && Map[x + 1][y + 2] == num
		&& !Map[x][y + 1] && !Map[x][y + 2]
		&& check_up(x, y + 1) && check_up(x, y + 2)) {
		for (int i = x; i <= x + 1; i++) {
			for (int j = y; j <= y + 2; j++) {
				Map[i][j] = 0;
			}
		}
		return true;
	}
	else if (x + 1 < N && y - 2 >= 0 && Map[x + 1][y] == num
		&& Map[x + 1][y - 1] == num && Map[x + 1][y - 2] == num
		&& !Map[x][y - 1] && !Map[x][y - 2]
		&& check_up(x, y - 1) && check_up(x, y - 2)) {
		for (int i = x; i <= x + 1; i++) {
			for (int j = y - 2; j <= y; j++) {
				Map[i][j] = 0;
			}
		}
		return true;
	}
	else if (x + 2 < N && y + 1 < N && Map[x + 1][y] == num
		&& Map[x + 2][y] == num && Map[x + 2][y + 1] == num
		&& !Map[x][y + 1] && !Map[x + 1][y + 1] && check_up(x, y + 1)) {
		for (int i = x; i <= x + 2; i++) {
			for (int j = y; j <= y + 1; j++) {
				Map[i][j] = 0;
			}
		}
		return true;
	}
	else if (x + 2 < N && y - 1 >= 0 && Map[x + 1][y] == num
		&& Map[x + 2][y] == num && Map[x + 2][y - 1] == num
		&& !Map[x][y - 1] && !Map[x + 1][y - 1] && check_up(x, y - 1)) {
		for (int i = x; i <= x + 2; i++) {
			for (int j = y - 1; j <= y; j++) {
				Map[i][j] = 0;
			}
		}
		return true;
	}
	else if (x + 1 < N && y - 1 >= 0 && y + 1 < N && Map[x + 1][y] == num
		&& Map[x + 1][y - 1] == num && Map[x + 1][y + 1] == num
		&& !Map[x][y - 1] && !Map[x][y + 1]
		&& check_up(x, y - 1) && check_up(x, y + 1)) {
		for (int i = x; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				Map[i][j] = 0;
			}
		}
		return true;
	}

	return false;
}

bool is_remove() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] >= 1 && Map[i][j] <= 200
				&& check_rectangle(i, j))
				return true;
		}
	}
	return false;
}


int solution(vector<vector<int>> board) {
	int answer = 0;

	N = board.size();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Map[i][j] = board[i][j];
		}
	}

	while (is_remove())
		answer++;
	return answer;
}