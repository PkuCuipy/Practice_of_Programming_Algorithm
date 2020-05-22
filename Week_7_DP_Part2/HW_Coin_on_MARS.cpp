#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int N, X;
int value[210]; //硬币价值
int dp[210][10010];
vector<int> ans;
//dp[i][j]表示前i个硬币凑j元的方案数
//dp[i][j] = dp[i-1][j-coins[i]] + dp[i-1][j]


int main(){
    cin >> N >> X;
    for (int i = 1; i <= N; i++){
        cin >> value[i];
    }
    memset(dp, 0, sizeof(dp));
    
    //计算前i个硬币凑j元的方案数:
    //1. j=0时, dp[i][0]=1
    for (int i = 0; i <= N; i++){
        dp[i][0] = 1;
    }
    //2. dp[i][j] = dp[i-1][j-coins[i]] + dp[i-1][j]
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= X; j++){
            dp[i][j] = dp[i-1][j];
            if(j-value[i] >= 0){
                dp[i][j] += dp[i-1][j-value[i]];
            }
        }
    }
    
    //如果必须用上coin_i,则不用coins_i的时候,凑出X的方案数为0!
    //而 不用coin_i凑出X的方案数 = 凑出X的方案数 - 用了coin_i凑出X的方案数 (1)
    //而 用了coin_i凑出X的方案数 = 不用coin_i凑出(X-value_i)的方案数 (2)
    
    //(2)代入(1),得:
    //不用coin_i凑出X的方案数 = 凑出X的方案数 - 不用coin_i凑出(X-value_i)的方案数
    //我们用数组g_i[j]表示不用coin_i凑出j的方案数
    //则有: g_i[X] = f[N][X] - g_i[X-coin_i]
    //     g_i[X-coin_i] = f[N][X-coin_i] - g_i[X-coin_i-coin_i]
    //      ... ...
    
    //枚举每一个coin_i,最后如果g_i[X] == 0, 说明这个coin_i是必不可少的
    for (int i = 1; i <= N; i++){
        int g_i[10010] = {0};
        g_i[0] = 1;
        for (int j = 1; j <= X; j++){
            if (j - value[i] >= 0){
                g_i[j] = dp[N][j] - g_i[j - value[i]];
            }
            else{ //这个硬币价值超过j了..所以凑j一定用不上它,所以 用/不用 它的时候的方案数都和总方案数相同
                g_i[j] = dp[N][j];
            }
        }
        
        if(g_i[X] == 0){ //不使用i时凑X的方案数为0!
            ans.push_back(value[i]);
        }
        
    }
    
    if(ans.size() == 0){
        cout << "0" << endl << endl;
    }
    else{
        cout << ans.size() << endl;
        for(auto i: ans){
            cout << i << " ";
        }
        cout << endl;
    }
    
    return 0;
}

