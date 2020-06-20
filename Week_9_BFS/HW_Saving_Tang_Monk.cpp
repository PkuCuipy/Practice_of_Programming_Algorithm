#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

int ox[4] = {0,0,1,-1};
int oy[4] = {1,-1,0,0};

int M, N;
int sx, sy;
char maze[110][110];
bool arrived[110][110][32][10]; //[x][y][snake{binary}][key(int))]
struct Node{
    int x, y, snake, key, time;
    Node(){}
    Node(int x, int y, int snake, int key, int time): x(x), y(y), snake(snake), key(key), time(time){
        if(x == 110){
            
        }
    }
};


bool check(int x, int y){
    if(x >= 0 && y >= 0 && x < N && y < N && maze[x][y] != '#'){
        return true;
    }
    return false;
}



int main(){
    while(static_cast<void>(cin >> N >> M), N + M){
        //读入数据, 记录关键信息, 给每个蛇特殊编号A,B,C,... 编号最多到G
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> maze[i][j];
            }
        }
        int snake_cnt = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(maze[i][j] == 'S'){
                    maze[i][j] = 'A' + snake_cnt;
                    snake_cnt++;
                }
                else if(maze[i][j] == 'K'){
                    sx = i;
                    sy = j;
                }
            }
        }
        memset(arrived, 0, sizeof(arrived));
        
        //下面开始搜索最优解
        int ans = 1 << 30;
        queue<Node> q;
        q.push(Node(sx, sy, 0, 0, 0));
        
        while(!q.empty()){
            
            Node current = q.front();
            q.pop();
            if(arrived[current.x][current.y][current.snake][current.key]){continue;} //避免重复探索
            arrived[current.x][current.y][current.snake][current.key] = true; //标记已经来过
            if(maze[current.x][current.y] == 'T' && current.key == M){ans = min(ans, current.time); break;} //找到唐僧了,且一定是最快的.
            if(maze[current.x][current.y] >= 'A' && maze[current.x][current.y] <= 'G'){ //是蛇
                if((current.snake & (1 << (maze[current.x][current.y] - 'A'))) == 0){ //而且这条蛇还没打过
                    //那么这个节点的探索就将以打蛇告结
                    q.push(Node(current.x, current.y,
                                current.snake | (1 << (maze[current.x][current.y] - 'A')),
                                                                    current.key, current.time + 1));
                    continue; //告结
                }
            }
            if('1' <= maze[current.x][current.y] && maze[current.x][current.y] <= '9'){ //是钥匙
                if(maze[current.x][current.y] - '0' == current.key + 1){ //且正好是应该拿的
                    current.key++;
                }
            }
            //向四周搜索
            for(int o = 0; o < 4; o++){
                if(check(current.x + ox[o], current.y + oy[o])){ //位置可达
                    q.push(Node(current.x + ox[o], current.y + oy[o], current.snake, current.key, current.time + 1));
                }
            }

        }
        
        if(ans == 1 << 30){
            cout << "impossible" << endl;
        }
        else{
            cout << ans << endl;
        }
        
    }
    return 0;
}
