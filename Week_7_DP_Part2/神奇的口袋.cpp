#include<iostream>
#include<cstring>
using namespace std;

int dp[25][45]; //dp[a][b]表示从前a个(包括第a个)物品中凑b单位容积的可能数
int volume[45]; //每个物品的体积,0弃用
int item_amount; //物品总数

int main(){
    memset(dp, 0, sizeof(dp));
    
    cin >> item_amount;
    for(int i = 1; i <= item_amount; i++){
        cin >> volume[i];
    }
    
    for(int a = 0; a <= item_amount; a++){
        dp[a][0] = 1;
    }
    
    for(int b = 1; b <= 41; b++){
        for(int a = 1; a <= item_amount; a++){
            dp[a][b] += dp[a-1][b];
            if(b - volume[a] >= 0){
                dp[a][b] += dp[a-1][b-volume[a]];
            }
        }
    }
    cout << dp[item_amount][40];
    
    return 0;
}
