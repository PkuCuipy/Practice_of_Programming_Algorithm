#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;


char maze[300][300];
int m, n, H;
bool pushed[300][300][10];
int dx[] = {0,1,-1,0};
int dy[] = {-1,0,0,1};


struct Node{
    int x;
    int y;
    int h;
    int steps;
    Node(int x, int y, int h, int steps):x(x), y(y), h(h), steps(steps){}
};


int main(){
    int T;
    cin >> T;
    while(T--){
        memset(pushed, false, sizeof(pushed));
        memset(maze, '#', sizeof(maze));
        cin >> m >> n >> H;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                cin >> maze[i][j];
            }
        }
        


        int min_steps = 1 << 30;

        queue<Node> q;
        q.push(Node(1, 1, H, 0));
        pushed[1][1][H] = true;

        while(!q.empty()){
            const Node current = q.front();
            q.pop();
            int x = current.x;
            int y = current.y;
            int h = current.h;
            int steps = current.steps;

            if(x == m && y == n){ //到达终点了
                min_steps = steps;
                break;
            }

            //继续向四周探索
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(maze[nx][ny] == '.' && !pushed[nx][ny][h]){
                    q.push(Node(nx, ny, h, steps + 1));
                    pushed[nx][ny][h] = true;
                }
                if(maze[nx][ny] == '*' && h > 1 && !pushed[nx][ny][h - 1]){
                    q.push(Node(nx, ny, h - 1, steps + 1));
                    pushed[nx][ny][h - 1] = true;
                }
            }


        }

        cout << min_steps << endl;

    }



    return 0;
}
