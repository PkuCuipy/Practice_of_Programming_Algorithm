#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int ex, ey;
int sx, sy;

struct Point{
    bool is_TP;
    int to_x;
    int to_y;
    Point(bool is_TP = false, int x = 0, int y = 0): is_TP(is_TP), to_x(x), to_y(y){}
};


struct Node{
    int x;
    int y;
    int t;
    Node(int x, int y, int t): x(x), y(y), t(t){}
};


int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};

char map[110][110];
int N, M;

bool arrived[110][110];
Point TP[110][110];



int main(){
    int T;
    cin >> T;
    while(T--){
        memset(map, '#', sizeof(map));
        memset(arrived, false, sizeof(arrived));
        memset(TP, 0, sizeof(TP));
        cin >> N >> M;
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                cin >> map[i][j];
            }
        }
        //找ex, ey的位置
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(map[i][j] == 'I'){
                    ex = i;
                    ey = j;
                    break;
                }
            }
        }
        //找sx, sy的位置
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(map[i][j] == 'B'){
                    sx = i;
                    sy = j;
                    break;
                }
            }
        }
        
        //匹配传送门
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(map[i][j] <= 'z' && map[i][j] >= 'a'){
                    char temp = map[i][j];
                    //找配对的传送门
                    for(int a = 1; a <= N; a++){
                        for(int b = 1; b <= N; b++){
                            if(map[a][b] == temp && i != a && j != b){
                                TP[a][b] = Point(true, i, j);
                                TP[i][j] = Point(true, a, b);
                            }
                        }
                    }
                }
            }
        }
        
        queue<Node> q;
        q.push(Node(sx, sy));
        int least = 1 << 30;
        while(!q.empty()){
            const Node current = q.front();
            q.pop();
            if(current.x == ex && current.y == ey){
                least = min(least, )
            }
        }
        
        
    }
    



    return 0;
}
