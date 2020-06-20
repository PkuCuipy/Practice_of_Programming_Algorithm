#define INF 0x3f3f3f3f
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

struct node{
    int x, y, t, key, snake;
    node() {}
    node(int x, int y, int t, int key, int snake) : x(x), y(y), t(t), key(key), snake(snake) {}
};

bool vis[105][105][10][40]; //保存某个状态是否到达过, 避免重复搜索
int N, M, sx, sy;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
char maze[105][105];

bool check(int x, int y){ //判断某个位置是否可达
    if(0 <= x && x < N && 0 <= y && y < N && maze[x][y] != '#'){
        return true;
    }
    return false;
}

void bfs(){
    int ans = INF;
    memset(vis, 0, sizeof(vis)); //初始化为任何状态都未搜索过
    queue<node> que;
    que.push(node(sx, sy, 0, 0, 0));
    
    while(!que.empty()) {
        const node top = que.front();
        que.pop();
        int x = top.x, y = top.y, key = top.key, snake = top.snake, t = top.t; //要处理的Node的信息
        if(key == M && maze[x][y] == 'T') { //这个Node已经是唐僧, 且钥匙齐了!
            ans = min(ans, t);
        }
        if(vis[x][y][key][snake]){ //曾经搜索过这个状态了,不再搜索
            continue;
        }
        vis[x][y][key][snake] = true; //记录:搜索过这个状态了
        for(int i = 0; i < 4; i++) { //向四个方向试图push下一层的节点
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(!check(nx, ny)){ //这个方向的节点不可达,看下一个方向
                continue;
            }
            node now = top;
            if('A' <= maze[nx][ny] && maze[nx][ny] <= 'G') { //上一层是蛇
                int s = maze[nx][ny] - 'A';
                if(!((1<<s) & now.snake)){ //如果这只蛇没被打
                    now.snake |= (1<<s);
                    now.t++;
                }
            }
            else if(maze[nx][ny] - '0' == now.key + 1) { //上一层是钥匙,而且是合法的钥匙(即编号==我已持有的数量+1)
                now.key++;
            }
            now.t++;
            que.push(node(nx, ny, now.t, now.key, now.snake));
        }
    }
    
    if(ans != INF){
        cout << ans << endl;
    }
    else{
       cout << "impossible" << endl;
    }
}

int main(){
    while(cin >> N >> M, N + M) {
        int cnt = 0;
        //读入迷宫
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++){
                cin >> maze[i][j];
            }
        }
        //找到孙悟空的初始位置,并且给每个蛇标记不同的编号A,B,C,...
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(maze[i][j] == 'K'){
                    sx = i;
                    sy = j;
                }
                if(maze[i][j] == 'S'){
                    maze[i][j] = cnt+'A';
                    cnt++;
                }
            }
        }
        bfs();
    }
    return 0;
}

/*
4 2
KS1.
2SS.
SSSS
STSS
0 0
*/
