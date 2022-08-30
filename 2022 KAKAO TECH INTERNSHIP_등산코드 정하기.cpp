#include <string>
#include <vector>
#include <queue>

#define ll long long

using namespace std;

int D[50001], DD[50001];
int trace[50001];
bool dest[50001];
vector<pair<int, int>> p[50001];
const int START = 0;

void dijkstra(int n) {
	priority_queue<pair<int, int>> PQ;

	for (int i = 0; i <= n; i++)
		D[i] = 1e9;
	PQ.push({ 0, START });
	while (!PQ.empty()) {
		int dist = -PQ.top().first;
		int cur = PQ.top().second;

		PQ.pop();
		if (dist > D[cur])
			continue;
		for (int i = 0; i < p[cur].size(); i++) {
			int next = p[cur][i].first;
			int next_dist = max(dist, p[cur][i].second);
			
			if (next_dist < D[next]) {
				trace[next] = cur;
				D[next] = next_dist;
				PQ.push({ -next_dist, next });
			}
		}
	}
}

void check_dijkstra(int n, vector<int> summits, vector<int> &answer) {
	priority_queue<pair<pair<ll, int>, bool>> PQ;
	int intensity = 1e9;
	int ans_cur = n;

	for (int summit : summits) {
		intensity = min(intensity, D[summit]);
	}

	for (int i = 0; i <= n; i++)
		DD[i] = 1e9;
	PQ.push({ { 0, START }, false });
	while (!PQ.empty()) {
		int dist = -PQ.top().first.first;
		int cur = PQ.top().first.second;
		bool op = PQ.top().second;

		PQ.pop();
		if (dest[cur] && intensity == dist && !op) {
			ans_cur = min(ans_cur, cur);
			op = true;
		}
		if (dist > DD[cur])
			continue;
		for (int i = 0; i < p[cur].size(); i++) {
			int next = p[cur][i].first;
			int next_dist = max(dist, p[cur][i].second);

			if (next_dist < DD[next]) {
				trace[next] = cur;
				DD[next] = next_dist;
				PQ.push({ { -next_dist, next }, op });
			}
		}
	}

	answer.push_back(ans_cur);
	answer.push_back(intensity);
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
	vector<int> answer;

	for (vector<int> path : paths) {
		int from = path[0], to = path[1];
		int dist = path[2];

		p[from].push_back({ to, dist });
		p[to].push_back({ from,dist });
	}

	for (int gate : gates) {
		p[START].push_back({ gate,0 });
		p[gate].push_back({ START,0 });
	}

	for (int summit : summits) {
		dest[summit] = true;
	}

	dijkstra(n);
	check_dijkstra(n, summits, answer);

	return answer;
}
