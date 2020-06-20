#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

int dx[] = {1,0,0,-1};
int dy[] = {0,1,-1,0};
int R, C, K;
int Sx, Sy, Ex, Ey;
int min_time;
char map[110][110];
bool arrived[110][110][12]; //第三维度表示arrive_time % K

bool available(int x, int y, int arrive_time){ //检测是否可达
    if(x >= 0 && x < R && y >= 0 && y < C && ((map[x][y] != '#') || arrive_time % K == 0)){
        return true;
    }
    return false;
}

struct Node{
    int arrive_time;
    int x;
    int y;
    Node(int at, int x, int y): arrive_time(at), x(x), y(y){}
};


void bfs(){
    memset(arrived, false, sizeof(arrived));
    queue<Node> q;
    q.push(Node(0, Sx, Sy));

    while(!q.empty()){ //处理每个节点
        const Node current = q.front();
        q.pop();
        int nowtime = current.arrive_time;
        int x = current.x;
        int y = current.y;
        //如果已经到达终点,那就是最优解
        if(x == Ex && y == Ey){
            min_time = nowtime;
            break;
        }

        //尝试四周寻路
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            int at = nowtime + 1;
            if(available(nx, ny, at) && !arrived[nx][ny][at % K]){ //可以到达,而且没push过
                q.push(Node(at, nx, ny));
                arrived[nx][ny][at % K] = true; //标记已push过
            }

        }
    }

}



int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> R >> C >> K;
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                cin >> map[i][j];
                if(map[i][j] == 'S'){Sx = i; Sy = j;}
                if(map[i][j] == 'E'){Ex = i; Ey = j;}
            }
        }

        min_time = -1;
        bfs();
        if(min_time == -1){
            cout << "Oop!" << endl;
        }
        else{
            cout << min_time << endl;
        }
    }
    return 0;
}
