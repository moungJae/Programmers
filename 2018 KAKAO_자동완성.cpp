#include <string>
#include <vector>
#include <malloc.h>

using namespace std;

struct Trie* getTrie();

struct Trie{
    Trie *next[26];
    int check;
    
    void clear() {
        check = 0;
        for(int i=0; i<26; i++)
            next[i] = NULL;
    }
};

Trie* getTrie(){
    Trie* ret;
    ret = (Trie*)malloc(sizeof(Trie));
    ret->clear();
    return ret;
}

Trie* root;

int solution(vector<string> words) {
    int answer = 0;
    Trie* tmp;
    
    root = getTrie();
    
    for(int i=0; i<words.size(); i++) {
        tmp = root;
        string S = words[i];
        int S_size = S.size();
        for(int j=0; j<S_size; j++){
            int c = S[j] - 'a';
            if(tmp->next[c] == NULL) {
                tmp->next[c] = getTrie();
            }
            tmp->next[c]->check++;
            tmp = tmp->next[c];
        }
    }
    
    for(int i=0; i<words.size(); i++) {
        tmp = root;
        string S = words[i];
        int S_size = S.size();
        for(int j=0; j<S_size; j++){
            int c = S[j] - 'a';
            if(tmp->next[c]->check == 1){
                answer += j + 1;
                break;
            }
            tmp = tmp->next[c];
            if(j == S.size() - 1)
                answer += S_size;
        }
    }
    
    return answer;
}