#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int cake[100010];
int n;
long long dp[100010];

int main(){

    int T;
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> cake[i];
        }
        //计算dp[]
        //dp[i] = max{dp[i-2], dp[i-3]} + max{0, cake[i]}
        dp[1] = max(0, cake[1]);
        dp[2] = max(0, cake[2]);
        dp[3] = max(0, cake[3]) + dp[1];
        for(int i = 4; i <= n; i++){
            dp[i] = max(dp[i-2], dp[i-3]) + max(0, cake[i]);
        }
        cout << max(dp[n], dp[n-1]) << endl;
    }
    
    
    
    return 0;
}
