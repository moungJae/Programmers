#include <string>
#include <vector>
#include <queue>

using namespace std;

int D[201][201];

int solution(int alp, int cop, vector<vector<int>> problems) {
	priority_queue<pair<int, pair<int, int>>> PQ;
	int max_alp = 0, max_cop = 0;

	for (vector<int> problem : problems) {
		max_alp = max(max_alp, problem[0]);
		max_cop = max(max_cop, problem[1]);
	}

	for (int i = 0; i <= 200; i++) {
		for (int j = 0; j <= 200; j++) {
			D[i][j] = 1e9;
		}
	}

	PQ.push({ 0, {-alp, -cop} });
	D[alp][cop] = 0;

	while (!PQ.empty()) {
		int cur_cost = -PQ.top().first;
		int cur_alp = -PQ.top().second.first;
		int cur_cop = -PQ.top().second.second;

		PQ.pop();
		if (cur_cost > D[cur_alp][cur_cop])
			continue;
		if (cur_alp == max_alp && cur_cop == max_cop) {
			return cur_cost;
		}

		for (vector<int> problem : problems) {
			int alp_req = problem[0], cop_req = problem[1];
			int alp_rwd = problem[2], cop_rwd = problem[3];
			int cost = problem[4];

			if (cur_alp >= alp_req && cur_cop >= cop_req) {
				int next_alp = min(max_alp, cur_alp + alp_rwd);
				int next_cop = min(max_cop, cur_cop + cop_rwd);
				int next_t = cur_cost + cost;

				if (next_t < D[next_alp][next_cop]) {
					D[next_alp][next_cop] = next_t;
					PQ.push({ -next_t, { -next_alp, -next_cop } });
				}
			}
			if (cur_alp < alp_req) {
				int next_alp = max(cur_alp, alp_req);
				int next_t = cur_cost + (next_alp - cur_alp);

				if (next_t < D[next_alp][cur_cop]) {
					D[next_alp][cur_cop] = next_t;
					PQ.push({ -next_t, {-next_alp, -cur_cop} });
				}
			}
			if (cur_cop < cop_req) {
				int next_cop = max(cur_cop, cop_req);
				int next_t = cur_cost + (next_cop - cur_cop);

				if (next_t < D[cur_alp][next_cop]) {
					D[cur_alp][next_cop] = next_t;
					PQ.push({ -next_t, {-cur_alp, -next_cop} });
				}
			}

		}
	}
}
