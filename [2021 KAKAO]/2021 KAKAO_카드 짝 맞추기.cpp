#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool is_finish(vector<vector<int>> &board)
{
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            if (board[i][j])
                return 0;
    return 1;
}

int is_in(int x, int y)
{
    if (x >= 0 && x <= 3 && y >= 0 && y <= 3)
        return 1;
    return 0;
}

int get_key(vector<vector<int>> &board, int s_x, int s_y, int e_x, int e_y)
{
    int dist[4][4];
    
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++)
            dist[i][j] = 10000;
    
    priority_queue<pair<int, pair<int, int>>> pq;
    dist[s_x][s_y] = 0;
    pq.push({0, {s_x, s_y}});
    while (!pq.empty())
    {
        int d = -pq.top().first;
        int x = pq.top().second.first, y = pq.top().second.second;
        pq.pop();
        if (dist[x][y] < d)
            continue;
        if (x == e_x && y == e_y)
            return d;
        for (int i=0; i<4; i++)
        {
            int next_x = x, next_y = y, next_d = d;
            while (is_in(next_x + dx[i], next_y + dy[i]))
            {
                next_x += dx[i], next_y += dy[i], next_d++;
                if (board[next_x][next_y])
                    break;
                if (next_d < dist[next_x][next_y])
                {
                    dist[next_x][next_y] = next_d;
                    pq.push({-(next_d), {next_x, next_y}});
                }
            }
            
            if (d + 1 < dist[next_x][next_y])
            {
                dist[next_x][next_y] = d + 1;
                pq.push({-(d + 1), {next_x, next_y}});
            }
        }
    }
}

int go(vector<vector<int>> &board, int r, int c)
{
    int ret = 10000;
    int enter = 2;
    
    if (is_finish(board))
        return 0;
    
    for (int card = 1; card <= 6; card++)
    {
        int x[2], y[2], idx = 0;
        for (int i=0; i<4; i++)
            for (int j=0; j<4; j++)
                if (board[i][j] == card)
                    x[idx] = i, y[idx] = j, idx++;
        if (idx == 0)
            continue;
        
        int dist1 = get_key(board, r, c, x[0], y[0]) + get_key(board, x[0], y[0], x[1], y[1]) + enter;
        int dist2 = get_key(board, r, c, x[1], y[1]) + get_key(board, x[1], y[1], x[0], y[0]) + enter;
        board[x[0]][y[0]] = board[x[1]][y[1]] = 0;
        ret = min({ret, dist1 + go(board, x[1], y[1]), dist2 + go(board, x[0], y[0])});
        board[x[0]][y[0]] = board[x[1]][y[1]] = card;
    }
    return ret;
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer;
    return (answer = go(board, r, c));
}