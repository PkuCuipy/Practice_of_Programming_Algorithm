#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int N, target;
int stamps[110];

int least_need;

void dfs(int which, int need, int cnt){ //枚举第几种邮票,还差多少钱,已经多少张了
    if(need == 0){
        if(cnt < least_need){
            least_need = cnt;
        }
        return;
    }
    if(cnt > least_need){
        return;
    }
    if(need < 0){
        return;
    }
    if(which > N){
        return;
    }
    
    for(int i = need / stamps[which]; i >= 0; i--){
        dfs(which + 1, need - i * stamps[which], cnt + i);
    }
    
}



int main(){
    while(cin >> N >> target){
        if(N == 0 && target == 0){
            break;
        }
        for(int i = 1; i <= N; i++){
            cin >> stamps[i];
        }
        sort(stamps + 1, stamps + N + 1);
        reverse(stamps + 1, stamps + N + 1);
        
        
        least_need = 1 << 30;
        dfs(1, target, 0);
        
        if(least_need == (1 << 30)){
            cout << "-1" << endl;
        }
        else{
            cout << least_need << endl;
        }
        
        
    }



    return 0;
}
