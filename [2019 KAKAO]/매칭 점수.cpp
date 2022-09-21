#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int external_link[21];
int base_point[21];
vector<int> web_node[21];
map<string, int> web;

string get_web_name(string page) {
	string find = "<meta property=\"og:url\" content=\"";
	string web_name = "";
	int j;

	for (int i = 0; i < page.size(); i++) {
		if (page.substr(i, find.size()) == find) {
			j = i + find.size();
			while (page[j] != '\"') {
				web_name += page[j++];
			}
			return web_name;
		}
	}
}

bool is_alphabet(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void set_base_point(int idx, string word, string page) {
	int cnt = 0;

	for (int i = 0; i < page.size(); i++) {
		string get_word = page.substr(i, word.size());
		string real_word = "";

		for (int j = 0; j < word.size(); j++) {
			if (word[j] >= 'a' && word[j] <= 'z') {
				if (get_word[j] >= 'a' && get_word[j] <= 'z')
					real_word += get_word[j];
				else
					real_word += (get_word[j] - 'A' + 'a');
			}
			else if (word[j] >= 'A' && word[j] <= 'Z') {
				if (get_word[j] >= 'A' && get_word[j] <= 'Z')
					real_word += get_word[j];
				else
					real_word += (get_word[j] - 'a' + 'A');
			}
		}
		if (word == real_word) {
            if (i + real_word.size() == page.size())
                cnt++;
            else if (i == 0)
                cnt++;
            else if (!is_alphabet(page[i + real_word.size()])
                    && !is_alphabet(page[i - 1]))
			    cnt++;
		}
	}

	base_point[idx] = cnt;
}

void set_external_link(int idx, string page) {
	string find = "<a href=\"";
	int j;

	for (int i = 0; i < page.size(); i++) {
		if (page.substr(i, find.size()) == find) {
			string web_name = "";

			j = i + find.size();
			while (page[j] != '\"') {
				web_name += page[j++];
			}
			external_link[idx]++;
			if (web[web_name])
				web_node[web[web_name]].push_back(idx);
		}
	}
}

bool compare(pair<double, int> x, pair<double, int> y) {
	if (x.first == y.first)
		return x.second < y.second;
	return x.first > y.first;
}

int solution(string word, vector<string> pages) {
	int answer = 0;
	vector<pair<double, int>> info;

	for (int i = 0; i < pages.size(); i++) {
		string page = pages[i];
		string web_name = get_web_name(page);

		web[web_name] = i + 1;
		set_base_point(i + 1, word, page);
	}
	for (int i = 0; i < pages.size(); i++) {
		string page = pages[i];
		set_external_link(i + 1, page);
	}
	for (int i = 0; i < pages.size(); i++) {
		double total_point = base_point[i + 1];

		for (int next : web_node[i + 1]) {
			total_point += (double)base_point[next] / (double)external_link[next];
		}
		info.push_back({ total_point, i });
	}
	sort(info.begin(), info.end(), compare);

	answer = info[0].second;
	return answer;
}