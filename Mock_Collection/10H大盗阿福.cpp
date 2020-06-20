#include<iostream>
#include<algorithm>
using namespace std;

int stores[100010];
int dp[100010]; //i为最右的盗窃店铺时, 抢钱最大值. dp[i] = max{dp[i-2], dp[i-3]}

int main(){
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        for(int i = 1; i <= N; i++){
            cin >> stores[i];
        }
        
        dp[1] = stores[1];
        dp[2] = stores[2];
        dp[3] = stores[1] + stores[3];
        for(int i = 4; i <= N; i++){
            dp[i] = stores[i] + max(dp[i-2], dp[i-3]);
        }
        
        int ans = max(dp[N], dp[N-1]);
        cout << ans << endl;
    }
    return 0;
}
