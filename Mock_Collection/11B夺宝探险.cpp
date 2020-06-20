#include<iostream>
#include<cstring>
using namespace std;

int dx[] = {1,0,0,-1};
int dy[] = {0,1,-1,0};
int M, N, K;
int map[30][30];
int got_max = -1;
bool have_got[110] = {false}; //是否已经拿到某个宝藏i

bool check(int x, int y){ //检查是否可以arrive
    if(!have_got[map[x][y]] && x >= 1 && x <= M && y >= 1 && y <= N){
        return true;
    }
    return false;
}

void dfs(int x, int y, int cnt){
    //拿宝藏map[x][y]
    have_got[map[x][y]] = true;

    //继续尝试四个方向搜索
    bool cant_continue = true;
    for(int i = 0; i < 4; i++){
        if(check(x + dx[i], y + dy[i])){
            dfs(x + dx[i], y + dy[i], cnt + 1);
        }
    }
    //搜索失败,无路可走了
    if(cant_continue){
        if(cnt > got_max){
            got_max = cnt;
        }
    }
    //回溯
    have_got[map[x][y]] = false;
}

int main(){
    cin >> M >> N >> K;
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            cin >> map[i][j];
        }
    }
    dfs(1, 1, 1);
    cout << got_max << endl;

    return 0;
}
