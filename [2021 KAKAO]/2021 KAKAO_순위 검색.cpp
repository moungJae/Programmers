#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int scores[4][3][3][3][100001];
map<string, int> m;

void init()
{
    m["cpp"] = 0, m["java"] = 1, m["python"] = 2;
    m["backend"] = 0, m["frontend"] = 1;
    m["junior"] = 0, m["senior"] = 1;
    m["chicken"] = 0, m["pizza"] = 1;
    m["-"] = -1;
}

string get_info(string info, int *idx)
{
    string ret = "";
    
    while (info[*idx] != ' ')
    {
        ret += info[*idx];
        *idx += 1;
    }
    *idx += 1;
    return (ret);
}

void set_scores()
{
    for (int i=0; i<4; i++)
        for (int j=0; j<3; j++)
            for (int u=0; u<3; u++)
                for (int v=0; v<3; v++)
                    for(int k=99999; k>=1; k--)
                        scores[i][j][u][v][k] += scores[i][j][u][v][k+1];
}

void solve_query(vector<int> &answer, int language, int work, 
                 int level, int food, int score)
{
    if (language == -1) language = 3;
    if (work == -1) work = 2;
    if (level == -1) level = 2;
    if (food == -1) food = 2;
    answer.push_back(scores[language][work][level][food][score]);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    
    init();
    for (int i=0; i<info.size(); i++)
    {
        int idx = 0;
        string language = get_info(info[i], &idx);
        string work = get_info(info[i], &idx);
        string level = get_info(info[i], &idx);
        string food = get_info(info[i], &idx);
        int score = stoi(&info[i][idx]);
        scores[m[language]][m[work]][m[level]][m[food]][score]++;
        
        scores[3][m[work]][m[level]][m[food]][score]++; scores[m[language]][2][m[level]][m[food]][score]++;
        scores[m[language]][m[work]][2][m[food]][score]++; scores[m[language]][m[work]][m[level]][2][score]++;
        
        scores[3][2][m[level]][m[food]][score]++; scores[3][m[work]][2][m[food]][score]++;
        scores[3][m[work]][m[level]][2][score]++; scores[m[language]][2][2][m[food]][score]++;
        scores[m[language]][2][m[level]][2][score]++; scores[m[language]][m[work]][2][2][score]++;
        
        scores[3][2][2][m[food]][score]++; scores[3][2][m[level]][2][score]++;
        scores[3][m[work]][2][2][score]++; scores[m[language]][2][2][2][score]++;
        
        scores[3][2][2][2][score]++;
    }
    set_scores();
    for (int i=0; i<query.size(); i++)
    {
        int idx = 0;
        string language = get_info(query[i], &idx); 
        idx += 4;
        string work = get_info(query[i], &idx); 
        idx += 4;
        string level = get_info(query[i], &idx); 
        idx += 4;
        string food = get_info(query[i], &idx); 
        int score = stoi(&query[i][idx]);
        solve_query(answer, m[language], m[work], m[level], m[food], score);
    }
    
    return answer;
}