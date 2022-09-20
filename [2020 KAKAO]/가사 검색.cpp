#include <string>
#include <vector>

using namespace std;

typedef struct Trie {
	Trie* child[26];
	int cnt;
};

Trie* root[10001], * rev_root[10001];
Trie dummy[2020002];
int d_cnt;

Trie* get_trie() {
	dummy[d_cnt].cnt = 0;
	for (int i = 0; i < 26; i++) {
		dummy[d_cnt].child[i] = 0;
	}
	return &dummy[d_cnt++];
}

void set_root() {
	for (int i = 1; i <= 10000; i++) {
		root[i] = get_trie();
		rev_root[i] = get_trie();
	}
}

bool all_question(string s) {
	for (char c : s) {
		if (c != '?')
			return false;
	}
	return true;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;

	set_root();
	for (string word : words) {
		Trie* cur = root[word.size()];

		for (int i = 0; i < word.size(); i++) {
			char c = word[i];

			if (!cur->child[c - 'a'])
				cur->child[c - 'a'] = get_trie();
			cur->cnt++;
			cur = cur->child[c - 'a'];
		}

		cur = rev_root[word.size()];
		for (int i = word.size() - 1; i >= 0; i--) {
			char c = word[i];

			if (!cur->child[c - 'a'])
				cur->child[c - 'a'] = get_trie();
			cur->cnt++;
			cur = cur->child[c - 'a'];
		}
	}

	for (string query : queries) {
		if (all_question(query)) {
			answer.push_back(root[query.size()]->cnt);
		}
		else if (query[0] == '?') {
			Trie* cur = rev_root[query.size()];

			for (int i = query.size() - 1; i >= 0; i--) {
				char c = query[i];

				if (c == '?') {
					answer.push_back(cur->cnt);
					break;
				}
				else if (!cur->child[c - 'a']) {
					answer.push_back(0);
					break;
				}
				else cur = cur->child[c - 'a'];
			}
		}
		else if (query[query.size() - 1] == '?') {
			Trie* cur = root[query.size()];

			for (char c : query) {
				if (c == '?') {
					answer.push_back(cur->cnt);
					break;
				}
				else if (!cur->child[c - 'a']) {
					answer.push_back(0);
					break;
				}
				else cur = cur->child[c - 'a'];
			}
		}
	}

	return answer;
}