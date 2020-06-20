#include<iostream>
using namespace std;

int N, K;
int cnt;
char cb[10][10];

bool row_used[10] = {false};
bool column_used[10] = {false};

void f(int chess_left, int from_x, int from_y){ //from_x from_y 表示之后的搜索要在这之后
    if(chess_left == 0){
        cnt++;
        return;
    }
    for(int i = 1; i <= N; i++){ if(row_used[i]) continue;
        for(int j = 1; j <= N; j++){ if(column_used[j]) continue;
            if(cb[i][j] != '#') continue;
            if(i < from_x) continue;
            if(i == from_x && j <= from_y) continue;
            
            row_used[i] = true;
            column_used[j] = true;
            
            f(chess_left - 1, i, j);
            
            row_used[i] = false;
            column_used[j] = false;
        }
    }
}

int main(){
    while(true){
        cin >> N >> K;
        if(N == -1 && K == -1) {break;}
        for(int i = 0; i <= 9; i++){
            for(int j = 0; j <= 9; j++){
                cb[i][j] = '.';
            }
        }
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                cin >> cb[i][j];
            }
        }
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(cb[i][j] == '#'){
                    cnt = 0;
                    f(K, i-1, j-1);
                    goto label;
                }
            }
        }
        label:
        cout << cnt << endl;
        
    }
    return 0;
}
