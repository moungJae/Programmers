#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int all_same(int N, int k)
{
	int ret = N;
	for (int i = 1; i < k; i++)
	{
		ret += N * pow(10, i);
	}
	return ret;
}

int solution(int N, int number) {
	vector<unordered_set<int>> dp(9);
	
	if (N == number)
		return 1;
	dp[1].insert(N);

	for (int k = 2; k <= 8; k++)
	{
		dp[k].insert(all_same(N, k));
		for (int i = 1; i < k; i++)
		{
			for (int j = 1; j < k; j++)
			{
				if (i + j == k)
				{
					for (int a : dp[i])
					{
						for (int b : dp[j])
						{
							dp[k].insert(a + b);
							if (a - b > 0) dp[k].insert(a - b);
							dp[k].insert(a * b);
							if (a / b > 0) dp[k].insert(a / b);
						}
					}
				}
			}
		}
		if (dp[k].count(number))
			return k;
	}

	return -1;
}