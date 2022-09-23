#include <string>
#include <math.h>

using namespace std;

int X[100000];
int power[100000];
int mul[100000];

int solution(string dartResult) {
    int answer = 0;
    
    for(int i=0; i<100000; i++) mul[i] = 1;
    
    int idx = -1;
    for(int i=0;i<dartResult.size(); i++){
        if(dartResult[i] >= '0' && dartResult[i] <= '9'){
            string num = "";
            num += dartResult[i];
            idx++, i++;
            while(dartResult[i] >= '0' && dartResult[i] <= '9') 
                num += dartResult[i++];
            i -= 1;
            X[idx] = stoi(num);
        }
        else if(dartResult[i] == 'S'){
            power[idx] = 1;
        }
        else if(dartResult[i] == 'D'){
            power[idx] = 2;
        }
        else if(dartResult[i] == 'T'){
            power[idx] = 3;
        }
        else if(dartResult[i] == '*'){
            if(idx == 0) mul[idx] *= 2;
            else mul[idx] *= 2, mul[idx - 1] *= 2;
        }
        else if(dartResult[i] == '#'){
            mul[idx] *= (-1);
        }
    }
    
    for(int i=0; i<=idx; i++){
        int tmp = pow(X[i], power[i]);
        answer += mul[i] * tmp;
    }
    
    return answer;
}