#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#define ll long long

using namespace std;

void get_10_to_k(vector<int>& v, int n, int k) {
	while (n) {
		v.push_back(n % k);
		n /= k;
	}
	reverse(v.begin(), v.end());
}

bool is_prime(ll n) {
	if (n == 1) return false;
	ll tmp = sqrt(n);
	for (ll x = 2; x <= tmp; x++) {
		if (n % x == 0) return false;
	}
	return true;
}

// 0P0
int prime1(vector<int> v) {
	int x, y, ret = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 0) {
			string S = "";
			x = i, y = -1;
			for (int j = i + 1; j < v.size(); j++) {
				if (v[j] == 0) {
					y = j;
					break;
				}
			}
			for (int j = x + 1; j < y; j++) {
				S += to_string(v[j]);
			}
			if (S.size() != 0 && is_prime(stol(S))) ret++;
		}
	}
	return ret;
}

// P0
int prime2(vector<int> v) {
	if (v[0] == 0) return 0;
	int x = -1;
	string S = "";
	for (int i = 1; i < v.size(); i++) {
		if (v[i] == 0) {
			x = i;
			break;
		}
	}
	if (x == -1) return 0;
	for (int i = 0; i < x; i++) {
		S += to_string(v[i]);
	}
	if (is_prime(stol(S))) return 1;
	return 0;
}

// 0P
int prime3(vector<int> v) {
	if (v[v.size() - 1] == 0) return 0;
	int x = -1;
	string S = "";
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] == 0) {
			x = i;
			break;
		}
	}
	if (x == -1) return 0;
	for (int i = x + 1; i < v.size(); i++) {
		S += to_string(v[i]);
	}
	if (is_prime(stol(S))) return 1;
	return 0;
}

// P
int prime4(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 0) return 0;
	}
	string S = "";
	for (int i = 0; i < v.size(); i++) {
		S += to_string(v[i]);
	}
	if (is_prime(stol(S))) return 1;
	return 0;
}

int solution(int n, int k) {
	int answer = 0;

	vector<int> v;
	get_10_to_k(v, n, k);
	answer = prime1(v) + prime2(v) + prime3(v) + prime4(v);

	return answer;
}