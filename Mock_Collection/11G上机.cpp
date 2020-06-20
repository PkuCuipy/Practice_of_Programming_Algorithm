#include<iostream>
#include<algorithm>
using namespace std;

int a[10010];
int b[10010];
int c[10010];
int dp[10010][4];
//dp[i][j]表示 在第i个座位的状态为j时,前i个座位的最大能力值总和.
//其中j=0,1,2,3分别代表:在第i个人坐下的前一瞬间,
//0左右都空, 1左有右空, 2右有左空, 3左右都有

int main(){
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= N; i++){
        cin >> b[i];
    }
    for(int i = 1; i <= N; i++){
        cin >> c[i];
    }
    dp[1][0] = a[1];
    dp[1][1] = -(1<<30);
    dp[1][2] = b[1];
    dp[1][3] = -(1<<30);
    for(int i = 2; i <= N; i++){
        dp[i][0] = max(dp[i-1][2], dp[i-1][3]) + a[i];
        dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + b[i];
        dp[i][2] = max(dp[i-1][2], dp[i-1][3]) + b[i];
        dp[i][3] = max(dp[i-1][0], dp[i-1][1]) + c[i];
    }
    
    
    cout << max(dp[N][0], dp[N][1]) << endl;
    
    return 0;
}
