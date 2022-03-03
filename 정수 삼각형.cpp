#include <string>
#include <vector>

using namespace std;

int dp[501][501];

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int t_size = triangle.size();
    
    // base step
    dp[0][0] = triangle[0][0];
    for (int i=1; i<t_size; i++)
    {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }
    
    // dynamic programming
    for (int i=2; i<t_size; i++)
    {
        for (int j=1; j<i; j++)
        {
            dp[i][j] = max(dp[i - 1][j - 1] + triangle[i][j],
                    dp[i - 1][j] + triangle[i][j]);
        }
    }
    
    for (int i = 0; i < t_size; i++)
    {
        answer = max(answer, dp[t_size - 1][i]);
    }
    
    return answer;
}