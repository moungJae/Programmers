#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int tree[20][2];
bool visited[20];

// 이동 경로에 대한 순서 정하기
void set_order(int cur, vector<int>& v) {
	if (tree[cur][0]) {
		v.push_back(tree[cur][0]);
		set_order(tree[cur][0], v);
		if (tree[cur][1]) {
			v.push_back(tree[cur][1]);
			set_order(tree[cur][1], v);
		}
	}
}

// fin 위치로 이동할 수 있는지를 판단하는 함수
// 이때, cur 의 초깃값은 root 노드, fin 위치에는 양이 존재
bool tree_traversal(int cur, int fin, int& sheep, int& wolf,
	vector<int> info, deque<int> Dq) {
	if (cur == fin) {
		deque<int> tmp = Dq;
		while (!Dq.empty()) {
			int x = Dq.front();
			Dq.pop_front();
			if (!visited[x]) {
				if (info[x]) wolf++;
				else sheep++;
			}
			if (wolf == sheep) {
				return false;
			}
		}
		while (!tmp.empty()) {
			int x = tmp.front();
			tmp.pop_front();
			visited[x] = true;
		}
		return true;
	}
	bool ret = false;
	if (tree[cur][0]) {
		Dq.push_back(tree[cur][0]);
		ret |= tree_traversal(tree[cur][0], fin, sheep, wolf, info, Dq);
		Dq.pop_back();
		if (tree[cur][1]) {
			Dq.push_back(tree[cur][1]);
			ret |= tree_traversal(tree[cur][1], fin, sheep, wolf, info, Dq);
			Dq.pop_back();
		}
	}
	return ret;
}

// 역으로 방문을 해제해주는 함수
// 이때 양(해제) => 늑대(해제) => 늑대(해제) => 양(종료) 방법으로 진행
// 즉, 양을 한번 더 만날 경우 return  
void visited_restore(int cur, int fin, int& sheep, int& wolf,
	vector<int> info, deque<int> Dq) {
	if (cur == fin) {
		visited[Dq.back()] = false;
		Dq.pop_back();
		sheep--;
		while (!Dq.empty()) {
			int x = Dq.back();
			Dq.pop_back();
			if (info[x]) {
				wolf--;
				visited[x] = false;
			}
			else {
				break;
			}
		}
		return;
	}
	if (tree[cur][0]) {
		Dq.push_back(tree[cur][0]);
		visited_restore(tree[cur][0], fin, sheep, wolf, info, Dq);
		Dq.pop_back();
		if (tree[cur][1]) {
			Dq.push_back(tree[cur][1]);
			visited_restore(tree[cur][1], fin, sheep, wolf, info, Dq);
			Dq.pop_back();
		}
	}
}

// 재귀적으로 양을 최대로 모을 수 있도록 구하는 함수
int sheep_and_wolf(int sheep_cnt, int wolf_cnt, vector<int>& info, vector<int>& order) {
	int result = sheep_cnt;
	int tmp_sheep = sheep_cnt, tmp_wolf = wolf_cnt;
	bool op = false;
	deque<int> Dq;
	Dq.push_back(0);
	for (int i = 0; i < order.size(); i++) {
		int move = order[i];
		if (!info[move] && !visited[move]) {
			if (tree_traversal(0, move, sheep_cnt, wolf_cnt, info, Dq)) {
				result = max(result, sheep_cnt);
				result = max(result, sheep_and_wolf(sheep_cnt, wolf_cnt, info, order));
				visited_restore(0, move, sheep_cnt, wolf_cnt, info, Dq);
			}
			sheep_cnt = tmp_sheep;
			wolf_cnt = tmp_wolf;
		}
	}
	return result;
}

int solution(vector<int> info, vector<vector<int>> edges) {
	vector<int> order;
	int answer = 1, sheep_cnt = 1, wolf_cnt = 0;

	for (int i = 0; i < edges.size(); i++) {
		int cur = edges[i][0], next = edges[i][1];
		if (!tree[cur][0]) tree[cur][0] = next;
		else tree[cur][1] = next;
	}

	set_order(0, order);

	visited[0] = true;
	answer = sheep_and_wolf(1, 0, info, order);

	return answer;
}