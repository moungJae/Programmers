#include <string>
#include <vector>

using namespace std;

bool Square[61][61];

void init(int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			Square[i][j] = false;
		}
	}
}

bool is_2x2(int m, int n, vector<string> board) {
	bool op = false;
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			char cmp = board[i][j];
			if (cmp != '@' && board[i][j] == cmp && board[i][j + 1] == cmp
				&& board[i + 1][j] == cmp && board[i + 1][j + 1] == cmp)
				op = Square[i][j] = true;
		}
	}
	return op;
}

void remove_2x2(int m, int n, vector<string>& board, int& result) {
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (Square[i][j]) {
				if (board[i][j] != '@') board[i][j] = '@', result++;
				if (board[i + 1][j] != '@') board[i + 1][j] = '@', result++;
				if (board[i][j + 1] != '@') board[i][j + 1] = '@', result++;
				if (board[i + 1][j + 1] != '@') board[i + 1][j + 1] = '@', result++;
			}
		}
	}
}

void down_2x2(int m, int n, vector<string>& board, int& result) {
	for (int i = 0; i < n; i++) {
		for (int j = m - 1; j >= 0; j--) {
			if (board[j][i] == '@') {
				int cnt = 1;
				j--;
				while (j >= 0 && board[j][i] == '@') j--, cnt++;
				if (j == -1) {
					break;
				}
				if (j != -1) {
					while (j >= 0 && board[j][i] != '@') {
						board[j + cnt][i] = board[j][i];
						board[j][i] = '@';
						j--;
					}
				}
				j = m;
			}
		}
	}
}

int solution(int m, int n, vector<string> board) {
	int answer = 0;

	while (1) {
		init(m, n);
		if (!is_2x2(m, n, board)) break;
		remove_2x2(m, n, board, answer);
		down_2x2(m, n, board, answer);
	}

	return answer;
}