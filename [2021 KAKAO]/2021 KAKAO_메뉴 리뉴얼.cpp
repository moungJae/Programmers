#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool visited[10];

void init()
{
	for (int i = 0; i < 10; i++)
		visited[i] = false;
}

void dfs(int idx, int fin, string order,
	vector<pair<string, int>>& menu, map<string, int>& m)
{
	if (idx == order.size())
	{
		string tmp = "";
		for (int i = 0; i < order.size(); i++)
		{
			if (visited[i])
				tmp += order[i];
		}
		if (fin != tmp.size())
			return;
		if (!m[tmp])
			menu.push_back({ tmp, 1 });
		m[tmp]++;
		return;
	}
	visited[idx] = false;
	dfs(idx + 1, fin, order, menu, m);
	visited[idx] = true;
	dfs(idx + 1, fin, order, menu, m);
}

bool compare(pair<string, int> x, pair<string, int> y)
{
	return (x.second > y.second);
}

vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;

	for (int i = 0; i < orders.size(); i++)
		sort(orders[i].begin(), orders[i].end());
	for (int i = 0; i < course.size(); i++)
	{
		vector<pair<string, int>> menu;
		map<string, int> m;
		for (int j = 0; j < orders.size(); j++)
		{
			if (orders[j].size() < course[i])
				continue;
			init();
			dfs(0, course[i], orders[j], menu, m);
		}
		if (menu.size())
		{
			for (int j = 0; j < menu.size(); j++)
				menu[j].second = m[menu[j].first];
			sort(menu.begin(), menu.end(), compare);
			int max_order = menu[0].second;
			if (max_order > 1)
			{
				for (int j = 0; j < menu.size(); j++)
				{
					if (menu[j].second != max_order)
						break;
					answer.push_back(menu[j].first);
				}
			}
		}
	}
	sort(answer.begin(), answer.end());

	return answer;
}