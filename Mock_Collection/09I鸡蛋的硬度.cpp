#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[110][15] = {0}; //dp[i][j]: i层高的楼,你有j个鸡蛋,对应的最优策略下的最坏情况的扔蛋次数
//dp[i][j] = min{ max{dp[k-1][j-1], dp[i-k][j]} : k=1,2,...,i-1 } + 1


int main(){
    for(int i = 1; i <= 10; i++){
        dp[1][i] = 1;
    }
    for(int i = 1; i <= 105; i++){
        dp[i][1] = i;
    }
    for(int i = 2; i <= 105; i++){
        for(int j = 2; j <= 10; j++){
            int min_ = 1 << 30;
            for(int k = 1; k < i; k++){
                min_ = min(min_, max(dp[k-1][j-1], dp[i-k][j]));
            }
            dp[i][j] = 1 + min_;
        }
    }
    
    int n, m;
    while(cin >> n >> m){
        cout << dp[n][m] << endl;
    }
    
    return 0;
}
