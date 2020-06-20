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
    
    memset(dp, 0, sizeof(dp));
    
    for(int i = 0; i <= n; i++){
        dp[i][0] = true; //前i个硬币凑0元
    }
    for(int j = 1; j <= 10000; j++){
        dp[0][j] = false; //前0个硬币凑j>=1元
    }
    dp[0][0] = true; //前0个硬币凑0元
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 10000; j++){
            bool bool_1 = dp[i-1][j], bool_2 = false;
            if(j-coins[i] >= 0){
                bool_2 = dp[i-1][j-coins[i]];
            }
            dp[i][j] = bool_1 || bool_2;
        }
    }
    
    
    for(int coin = 1; coin <= n; coin++){
        if(price + coins[coin] > 10000 || dp[n][price + coins[coin]] == false){
            //说明全部的硬币凑不出(目标钱数+这个硬币)这么多钱数,也就是说,如果凑出price,这个硬币必然已被使用!
            //比如:如果100元的硬币不一定用得上,且目标钱数为2333,那么就一定可以凑出2433;
            //从而如果凑不出2433,说明100一定(在任何能凑出2333的时候都)被使用了
            
            
            错了!!!!!!!
            如果X+value[i]能被表出,但是X-value[i]不能被表出, 说明这个硬币也是必须的, 这没问题
            但是!!!
            X+value[i]即使能被被表出,这个硬币也可能是必须的,!!! 比如3,5,7,22凑15, 很明显7是必须的,但15+7能被表出!
            
            
            
            output.push_back(coins[coin]);
        }
    }
    
    cout << output.size() << endl;
    for(auto i = output.begin(); i != output.end(); i++){
        cout << *i << " ";
    }
    cout << endl;
    
//    for(int money = 0; money <= 200; money++){
//        cout << money << ": " << (dp[n][money]?"True":"False") << endl;
//    }
    
    return 0;
}
