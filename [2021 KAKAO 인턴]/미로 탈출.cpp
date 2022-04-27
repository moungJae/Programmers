#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> v[1001][2];
int D[1001][1024];
int Trap[1001];

void dijkstra(int n, int start) {
	priority_queue<pair<pair<int, int>, int>> PQ;
	// { { distance, node }, trap_bit } }
	// trap_bit = 0 0 0 0 0 0 0 0 0 0 

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 1024; j++) {
			D[i][j] = 1e9;
		}
	}
	PQ.push({ {0, start}, 0 });
	D[start][0] = 0;
	while (!PQ.empty()) {
		int dist = -PQ.top().first.first, cur = PQ.top().first.second;
		int trap_bit = PQ.top().second;
		PQ.pop();

		if (dist > D[cur][trap_bit])
			continue;
		if (Trap[cur]) {
			if (trap_bit & Trap[cur]) trap_bit -= Trap[cur];
			else trap_bit += Trap[cur];
		}

		for (pair<int, int> p : v[cur][0]) {
			int next = p.first, next_dist = dist + p.second;
			if (((trap_bit & Trap[cur]) && (trap_bit & Trap[next]))
				|| (!(trap_bit & Trap[cur]) && !(trap_bit & Trap[next]))) {
				if (next_dist < D[next][trap_bit]) {
					D[next][trap_bit] = next_dist;
					PQ.push({ {-next_dist, next}, trap_bit });
				}
			}
		}
		for (pair<int, int> p : v[cur][1]) {
			int next = p.first, next_dist = dist + p.second;
			if (((trap_bit & Trap[cur]) && !(trap_bit & Trap[next]))
				|| (!(trap_bit & Trap[cur]) && (trap_bit & Trap[next]))) {
				if (next_dist < D[next][trap_bit]) {
					D[next][trap_bit] = next_dist;
					PQ.push({ {-next_dist, next}, trap_bit });
				}
			}
		}
	}
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
	int answer = 1e9;

	for (int i = 0; i < roads.size(); i++) {
		int from = roads[i][0], to = roads[i][1];
		int dist = roads[i][2];
		v[from][0].push_back({ to, dist });
		v[to][1].push_back({ from,dist });
	}

	for (int i = 0; i < traps.size(); i++) {
		Trap[traps[i]] = 1 << i;
	}

	dijkstra(n, start);
	for (int i = 0; i < 1024; i++) {
		answer = min(answer, D[end][i]);
	}

	return answer;
}