#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int N, X;
int enemy[15];
bool used[15] = {false}; //标记枚举的时候是否已经用过这匹马
int sequence[15]; //记录枚举情况

void dfs(int which, int win_cnt){
    if(which == N + 1){ //已经枚举好了
        if(2 * win_cnt > N){ //胜利
            for(int i = 1; i <= N; i++){
                cout << sequence[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    
    //枚举which位置选哪匹马
    for(int i = 1; i <= N; i++){
        if(!used[i]){
            used[i] = true;
            sequence[which] = i;
            
            dfs(which + 1, win_cnt + (i - enemy[which] >= X));
            
            used[i] = false;
        }
    }
    
}


int main(){
    cin >> N >> X;
    for(int i = 1; i <= N; i++){
        cin >> enemy[i];
    }
    dfs(1, 0);
    

    return 0;
}
