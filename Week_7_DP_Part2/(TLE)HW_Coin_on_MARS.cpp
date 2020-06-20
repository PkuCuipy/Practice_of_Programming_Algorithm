#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int coins[210] = {0}; //coins[0]弃用
bool dp[210][10010]; //dp[i][j] 表示 coins[]的前i个(从1开始,且含第i个)硬币能否凑出j元;
//dp[i][j] = dp[i-1][j] || dp[i-1][j-coins[i]]
//             bool_1   ||      bool_2

int main(){
    vector<int> output;
    int n, price;
    cin >> n >> price;
    for(int i = 1; i <= n; i++){
        cin >> coins[i];
    }
    //思路: 去掉某个coin,看能不能凑出price, 如果不能, 说明这个coin是必要的!
    for(int coin = 1; coin <= n; coin++){
        int save = coins[coin];
        coins[coin] = 0;
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i <= n; i++){
            dp[i][0] = true; //前i个硬币凑0元
        }
        for(int j = 1; j <= n; j++){
            dp[0][j] = false; //前0个硬币凑j>=1元
        }
        dp[0][0] = true; //前0个硬币凑0元
        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= price; j++){
                bool bool_1 = dp[i-1][j], bool_2 = false;
                if(j-coins[i] >= 0){
                    bool_2 = dp[i-1][j-coins[i]];
                }
                dp[i][j] = bool_1 || bool_2;
            }
        }
        
        if(dp[n][price] == false){
            output.push_back(save);
        }
        coins[coin] = save; //恢复
    }
    
    cout << output.size() << endl;
    for(auto i = output.begin(); i != output.end(); i++){
        cout << *i << " ";
    }
    cout << endl;
    
    return 0;
}
