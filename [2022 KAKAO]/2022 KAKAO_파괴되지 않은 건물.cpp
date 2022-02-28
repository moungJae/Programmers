#include <string>
#include <vector>

using namespace std;

int Map[1001][1001], imos[1001][1001];

void get_Imos(int r1, int c1, int r2, int c2, int degree) {
	imos[r1][c1] += degree;
	imos[r1][c2 + 1] += -degree;
	imos[r2 + 1][c1] += -degree;
	imos[r2 + 1][c2 + 1] += degree;
}

void sweep_Map(int R, int C) {
	int tmp = 0;
	// 1. 오른쪽으로 sweep
	for (int i = 0; i < R; i++) {
		for (int j = 1; j < C; j++) {
			imos[i][j] += imos[i][j - 1];
		}
	}

	// 2. 아래로 sweep
	for (int i = 0; i < C; i++) {
		for (int j = 1; j < R; j++) {
			imos[j][i] += imos[j - 1][i];
		}
	}

	// 3. imos 적용
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			Map[i][j] += imos[i][j];
		}
	}
}

int find_Destory(int R, int C) {
	int ret = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Map[i][j] <= 0) ret++;
		}
	}
	return ret;
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
	int answer = 0, row, col;

	row = board.size();
	for (int i = 0; i < board.size(); i++) {
		col = board[i].size();
		for (int j = 0; j < board[i].size(); j++) {
			Map[i][j] = board[i][j];
		}
	}

	for (int i = 0; i < skill.size(); i++) {
		int type, r1, c1, r2, c2, degree;
		type = skill[i][0];
		r1 = skill[i][1], c1 = skill[i][2];
		r2 = skill[i][3], c2 = skill[i][4];
		degree = skill[i][5];
		if (type == 1) degree = -degree;
		get_Imos(r1, c1, r2, c2, degree);
	}

	sweep_Map(row, col);
	answer = row * col - find_Destory(row, col);

	return answer;
}