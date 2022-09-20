#include <string>
#include <vector>
#include <stack>

using namespace std;

bool is_correct(string u) {
    stack<char> S, tmpS;
    
    for (char c : u) {
        S.push(c);
    }
    
    while (!S.empty()) {
        char c = S.top();
        S.pop();
        if (c == ')')
            tmpS.push(c);
        else if (c == '(') {
            if (tmpS.empty())
                return false;
            char cc = tmpS.top();
            tmpS.pop();
            if (cc == '()')
                return false;
        }
    }
    
    return true;
}

string recursion(string w) {
    if (w == "")
        return "";
    
    string u = "", v = "";
    int cnt1 = 0, cnt2 = 0;
    int i;
    
    for (i = 0; i < w.size(); i++) {
        if (cnt1 && cnt2 && (cnt1 == cnt2))
            break;
        if (w[i] == '(')
            cnt1++;
        else if (w[i] == ')')
            cnt2++;
        u += w[i];
    }
    v = w.substr(i, w.size() - i);
    
    if (is_correct(u)) {
        return u + recursion(v);
    }
    else {
        string new_s = "";
        
        for (int i = 1; i < u.size() - 1; i++) {
            if (u[i] == '(')
                new_s += ')';
            else if (u[i] == ')')
                new_s += '(';
        }
        return "(" + recursion(v) + ")" + new_s;    
    }
}

string solution(string p) {
    string answer = "";
    
    answer = recursion(p);
    return answer;
}