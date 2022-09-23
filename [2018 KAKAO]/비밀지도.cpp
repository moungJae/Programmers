#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    
    for(int i=0;i<n;i++){
        string s = "";
        for(int j=0;j<n;j++){
            int op = 0;
            if(arr1[i] >= pow(2, n - j - 1)){
                arr1[i] -= pow(2, n - j - 1), op++;
            }  
            if(arr2[i] >= pow(2, n - j - 1)){ 
                arr2[i] -= pow(2, n - j - 1), op++;
            }
            if(op == 0) s += " ";
            else s += "#";
        }
        answer.push_back(s);
    }
    
    return answer;
}