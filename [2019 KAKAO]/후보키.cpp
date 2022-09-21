#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, bool> check[300];
vector<vector<int>> candidate;
bool visited[8];
int c_cnt;

bool check_candidate() {
	for (vector<int> v : candidate) {
		int cnt = 0;

		for (int x : v) {
			if (visited[x]) cnt++;
		}
		if (cnt == v.size())
			return true;
	}
	return false;
}

int dfs(int idx, int cnt, int n, vector<vector<string>> &relation) {
	if (cnt == n) {
		vector<int> v;
		bool is_candidate = true;

		if (check_candidate()) 
			return 0;

		c_cnt++;
		for (int i = 0; i < relation.size(); i++) {
			string s = "";

			for (int j = 0; j < relation[i].size(); j++) {
				if (visited[j])
					s += relation[i][j];
			}
			if (check[c_cnt][s]) 
				return 0;
			check[c_cnt][s] = true;
		}

		for (int i = 0; i < relation[0].size(); i++) {
			if (visited[i])
				v.push_back(i);
		}
		candidate.push_back(v);

		return 1;
	}
	if (idx == relation[0].size())
		return 0;
	int ans = 0;

	visited[idx] = true;
	ans += dfs(idx + 1, cnt + 1, n, relation);
	visited[idx] = false;
	ans += dfs(idx + 1, cnt, n, relation);
	return ans;
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	
	for (int i = 1; i <= relation[0].size(); i++) {
		answer += dfs(0, 0, i, relation);
	}
	return answer;
}