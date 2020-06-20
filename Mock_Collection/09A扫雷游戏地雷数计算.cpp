#include<iostream>
#include<cstring>
using namespace std;

#define N 110

int cnt[N][N];
char map[N][N];
int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {1,0,-1,1,-1,1,0,-1};

int main(){
    memset(cnt, 0, sizeof(cnt));
    memset(map, 0, sizeof(map));
    
    //读入地图
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> map[i][j];
        }
    }
    
    //统计
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(map[i][j] != '*'){
                for(int d = 0; d < 8; d++){
                    cnt[i][j] += (map[i+dx[d]][j+dy[d]] == '*');
                }
            }
            else{
                cnt[i][j] = -1;
            }
        }
    }
    
    //输出
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(cnt[i][j] == -1){
                cout << "*";
            }
            else{
                cout << cnt[i][j];
            }
        }
        cout << endl;
    }
    
    
    return 0;
}
