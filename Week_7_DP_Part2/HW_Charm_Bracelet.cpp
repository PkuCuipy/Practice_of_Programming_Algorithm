#include<iostream>
#include<cstring>
using namespace std;

int N, MaxW;
int value[3412];
int weight[3412];
int dp[12890];
inline int max_(int a, int b){
    if(a > b) return a;
    return b;
}

//dp[i][j]表示前i个物品中,挑选不超过j重量的最大价值
//dp[i][j] = MAX{ dp[i-1][j-weight[i]] + value[i], dp[i-1][j] }


int main(){
    cin >> N >> MaxW;
    for(int i = 1; i <= N; i++){
        cin >> weight[i] >> value[i];
    }
    
    memset(dp, 0, sizeof(dp));
    for(int j = 0; j <= MaxW; j++){
        if(j >= weight[1]){
            dp[j] = value[1];
        }
    }
    
    for(int i = 2; i <= N; i++){
        for(int j = MaxW; j >= 1; j--){
            if(j - weight[i] < 0){
                dp[j] = dp[j];
            }
            else{
                dp[j] = max_(dp[j-weight[i]] + value[i], dp[j]);
            }
        }
    }
    
  
    
    cout << dp[MaxW] << endl;
    
    return 0;
}

