#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int node_x[10001];
int child[10001][2];
int parent[10001];

bool compare(pair<pair<int, int>, int> x, pair<pair<int, int>, int> y) {
	if (x.first.second == y.first.second)
		return x.first.first < y.first.first;
	return x.first.second > y.first.second;
}

bool is_valid(int next_x, int cur, int next) {
	while (parent[cur]) {
		if ((child[parent[cur]][0] == cur && next_x > node_x[parent[cur]]) ||
			(child[parent[cur]][1] == cur && next_x < node_x[parent[cur]])) {
			return false;
		}
		cur = parent[cur];
	}
	return true;
}

void construct_tree(vector<pair<pair<int, int>, int>> info) {
	node_x[info[0].second] = info[0].first.first;

	for (int i = 0; i < info.size(); i++) {
		int cur_x = info[i].first.first;
		int cur_y = info[i].first.second;
		int cur_node = info[i].second;

		for (int j = i + 1; j < info.size(); j++) {
			int next_x = info[j].first.first;
			int next_y = info[j].first.second;
			int next_node = info[j].second;

			if (child[cur_node][0] && child[cur_node][1])
				break;
			if (!child[cur_node][0] && next_y < cur_y && next_x < cur_x
				&& !parent[next_node] && is_valid(next_x, cur_node, next_node)) {
				child[cur_node][0] = next_node;
				parent[next_node] = cur_node;
				node_x[next_node] = next_x;
			}
			if (!child[cur_node][1] && next_y < cur_y && next_x > cur_x
				&& !parent[next_node] && is_valid(next_x, cur_node, next_node)) {
                child[cur_node][1] = next_node;
				parent[next_node] = cur_node;
				node_x[next_node] = next_x;
			}
		}
	}
}

void pre_order(int cur, vector<int> &v) {
	if (child[cur][0] || child[cur][1]) {
		v.push_back(cur);
		if (child[cur][0])
			pre_order(child[cur][0], v);
		if (child[cur][1])
			pre_order(child[cur][1], v);
	}
    else
        v.push_back(cur);
}

void post_order(int cur, vector<int> &v) {
	if (child[cur][0] || child[cur][1]) {
		if (child[cur][0])
			post_order(child[cur][0], v);
		if (child[cur][1])
			post_order(child[cur][1], v);
		v.push_back(cur);
	}
    else
        v.push_back(cur);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;
	vector<int> pre_v, post_v;
	vector<pair<pair<int, int>, int>> info;
	int node = 1;

	for (vector<int> v : nodeinfo) {
		node_x[node] = v[0];
		info.push_back({ {v[0], v[1]}, node++ });
	}

	sort(info.begin(), info.end(), compare);
	construct_tree(info);

	pre_order(info[0].second, pre_v);
	post_order(info[0].second, post_v);
	answer = { pre_v, post_v };

	return answer;
}