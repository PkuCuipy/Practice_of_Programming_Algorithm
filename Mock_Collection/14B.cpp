#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int earn[110][2];
int T;
int M;

int dp[110][2]; //考虑前i个月,第i个月在j地工作时的利润最大值
//dp[i][j] = max(dp[i-1][!j] - M, dp[i-1][j]) + earn[i][j]

int main(){
    cin >> T >> M;
    for(int i = 1; i <= T; i++){
        cin >> earn[i][0] >> earn[i][1];
    }
    dp[1][0] = earn[1][0];
    dp[1][1] = earn[1][1];
    for(int i = 2; i <= T; i++){
        dp[i][0] = max(dp[i-1][1] - M, dp[i-1][0]) + earn[i][0];
        dp[i][1] = max(dp[i-1][0] - M, dp[i-1][1]) + earn[i][1];
    }
    cout << max(dp[T][0], dp[T][1]);
    
    return 0;
}
