#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

char maze[15][15];
int T;
int size;
int sx, sy, ex, ey;
int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};

struct Node{
    int x;
    int y;
    int arrive_time;
    Node(int x, int y, int a_t): x(x), y(y), arrive_time(a_t){}
};


bool check(int x, int y){
    if(x >= 0 && x < size && y >= 0 && y < size && maze[x][y] != '#'){
        return true;
    }return false;
}

bool arrived[15][15];

int main(){
    int K;
    cin >> K;
    while(K--){
        memset(maze, 0, sizeof(maze));
        memset(arrived, 0, sizeof(arrived));
        cin >> size >> T;
        for(int i = 0; i < size; i++){
            cin >> maze[i];
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(maze[i][j] == 'S'){
                    sx = i; sy = j;
                }
                if(maze[i][j] == 'E'){
                    ex = i; ey = j;
                }
            }
        }
        
        queue<Node> q;
        q.push(Node(sx, sy, 0));
        bool finded = false;
        while(!q.empty()){
            const Node current = q.front();
            q.pop();
            int x = current.x;
            int y = current.y;
            int a_t = current.arrive_time;
            
            //如果找到了
            if(x == ex && y == ey){
                finded = true;
                break;
            }
            //继续向四周探索
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(check(nx, ny) && a_t + 1 <= T && !arrived[nx][ny]){
                    arrived[nx][ny] = true;
                    q.push(Node(nx, ny, a_t + 1));
                }
            }
        }
        
        if(finded){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        
        
    }
    
    
    return 0;
}
