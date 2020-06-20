#include<iostream>
#include<cstring>
using namespace std;

int dx[] = {-1,0,0,1};
int dy[] = {0,1,-1,0};
char maze[10][10];
bool arrived[10][10];
int m;
int T;
bool finded;
bool judge(int x, int y){
    if(x >= 0 && x < m && y >= 0 && y < m && maze[x][y] != '#' && !arrived[x][y]){
        return true;
    }
    return false;
}


void dfs(int x, int y, int t_spent){
    if(t_spent > T){
        return;
    }
    if(finded){
        return;
    }
    if(maze[x][y] == 'E'){
        finded = true;
        cout << "YES" << endl;
    }
    for(int i = 0; i < 4; i++){
        if(judge(x+dx[i], y+dy[i])){
            arrived[x+dx[i]][y+dy[i]] = true;
            dfs(x+dx[i], y+dy[i], t_spent + 1);
            arrived[x+dx[i]][y+dy[i]] = false;
        }
    }
}


int main(){
    int K;
    cin >> K;
    while(K--){
        cin >> m >> T;
        memset(arrived, false, sizeof(arrived));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                cin >> maze[i][j];
            }
        }
        finded = false;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if(maze[i][j] == 'S'){
                    arrived[i][j] == true;
                    dfs(i, j, 0);
                    break;
                }
            }
        }
        if(!finded){
            cout << "NO" << endl;
        }



    }


    return 0;
}
