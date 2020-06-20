#include<iostream>
#include<cstring>
using namespace std;

int m, n;
char lake[110][110];
int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {0,1,-1,-1,1,0,1,-1};

bool is_ice(int x, int y){
    if(x >= 0 && x < m && y >= 0 && y < n && lake[x][y] == '@'){
        return true;
    }
    return false;
}

void clear_ice(int x, int y){
    
    lake[x][y] = '#';
    for(int i = 0; i < 8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(is_ice(nx, ny)){
            clear_ice(nx, ny);
        }
    }
}

int main(){
    while(cin >> m >> n, m + n != 0){
        cin.get();
        int cnt = 0;
        for(int i = 0; i < m; i++){
            cin.getline(lake[i], 105);
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(lake[i][j] == '@'){
                    clear_ice(i, j);
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    
    return 0;
}
