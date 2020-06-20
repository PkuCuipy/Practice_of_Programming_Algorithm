#include<iostream>
#include<cstring>
using namespace std;

int dx[] = {1,0,0,-1};
int dy[] = {0,1,-1,0};
int M, N;
char map[510][510];
bool margin[510][510];

void write_margin_set_X(int x, int y){
    margin[x][y] = true;
    map[x][y] = 'X';
    for(int i = 0; i < 4; i++){
        if(map[x+dx[i]][y+dy[i]] == 'O'){
            write_margin_set_X(x + dx[i], y + dy[i]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        cin >> M >> N;
        memset(margin, false, sizeof(margin));
        memset(map, 'X', sizeof(map));

        for(int i = 1; i <= M; i++){
            for(int j = 1; j <= N; j++){
                cin >> map[i][j];
            }
        }

        //第一行
        for(int i = 1; i <= N; i++){
            if(map[1][i] == 'O')
                write_margin_set_X(1, i);
        }
        //最后一行
        for(int i = 1; i <= N; i++){
            if(map[M][i] == 'O')
                write_margin_set_X(M, i);
        }
        //第一列
        for(int i = 1; i <= M; i++){
            if(map[i][1] == 'O')
                write_margin_set_X(i, 1);
        }
        //最后一列
        for(int i = 1; i <= M; i++){
            if(map[i][N] == 'O')
                write_margin_set_X(i, N);
        }

        //输出
        for(int i = 1; i <= M; i++){
            for(int j = 1; j <= N; j++){
                if(margin[i][j]){
                    cout << "O";
                }
                else{
                    cout << "X";
                }
            }
            cout << endl;
        }
        if(T != 0){
            cout << endl;
        }
    }



    return 0;
}
