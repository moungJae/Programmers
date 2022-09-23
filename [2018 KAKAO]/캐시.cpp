#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

priority_queue<pair<int, string>> PQ;
map<string, bool> m;

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
    
    if(cacheSize == 0) return cities.size() * 5;

	for (int i = 0; i < cities.size(); i++) {
		for (int j = 0; j < cities[i].size(); j++) {
			if (cities[i][j] >= 'A' && cities[i][j] <= 'Z')
				cities[i][j] = cities[i][j] - 'A' + 'a';
		}
	}

	for (int i = 0; i < cities.size(); i++) {
		if (m[cities[i]]) {
            priority_queue<pair<int, string>> tmp_Q;
            while(!PQ.empty()){
                if(cities[i] != PQ.top().second)
                    tmp_Q.push({PQ.top().first, PQ.top().second});
                PQ.pop();
            }
            tmp_Q.push({-i, cities[i]});
            PQ = tmp_Q;
			answer += 1;
		}
		else {
			if (PQ.size() == cacheSize) {
				m[PQ.top().second] = false;
				PQ.pop();
			}
			m[cities[i]] = true;
			PQ.push({-i, cities[i]});
			answer += 5;
		}
	}

	return answer;
}