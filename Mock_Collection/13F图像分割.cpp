#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

#define MAX 0x3f3f3f3f
int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};

int H, W, M;
int photo[60][60];

void setMAX(int x, int y){
    int save = photo[x][y];
    photo[x][y] = MAX;
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(abs(photo[nx][ny] - save) <= M){
            setMAX(nx, ny);
        }
    }
}

int main(){
    while(cin >> H >> W >> M, W + H + M != 0){
        memset(photo, 0x3f, sizeof(photo));
        for(int i = 1; i <= H; i++){
            for(int j = 1; j <= W; j++){
                cin >> photo[i][j];
            }
        }
        int cnt = 0;
        for(int i = 1; i <= H; i++){
            for(int j = 1; j <= W; j++){
                if(photo[i][j] != MAX){
                    setMAX(i, j);
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    
    
    return 0;
}
