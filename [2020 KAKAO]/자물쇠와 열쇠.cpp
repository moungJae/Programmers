#include <string>
#include <vector>

using namespace std;

int Key[21][21], Lock[21][21];
int N, M;

void map_copy(int dst[][21], int src[][21]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            dst[i][j] = src[i][j];
        }
    }   
}

void rotate() {
    int tmp[21][21];
    
    map_copy(tmp, Key);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            Key[i][j] = tmp[M - j - 1][i];
        }
    }
}

void init(int arr[][21]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = 0;
        }
    }
}

void set_key(int arr[][21], int row, int col) {
    for (int x = 0, i = row; x < N; x++, i++) {
        for (int y = 0, j = col; y < N; y++, j++) {
            if (i >= 0 && i < M && j >= 0 && j < M) 
                arr[x][y] = Key[i][j];
            else
                arr[x][y] = 0;
        }
    }
}

bool is_match(int arr[][21]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((Lock[i][j] && !arr[i][j]) 
                || (!Lock[i][j] && arr[i][j]))
                continue;
            return false;
        }
    }
    return true;
}

bool check_lock() {
    int tmp[21][21];
    
    for (int i = -(N - 1); i < M; i++) {
        for (int j = -(N - 1); j < M; j++) {
            init(tmp);
            set_key(tmp, i, j);
            if (is_match(tmp))
                return true;
        }
    }
    return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {      
    M = key.size(), N = lock.size();
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            Key[i][j] = key[i][j];   
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Lock[i][j] = lock[i][j];   
        }
    }
    for (int i = 0; i < 4; i++) {
        if (check_lock())
            return true;
        rotate();
    }
    
    return false;
}