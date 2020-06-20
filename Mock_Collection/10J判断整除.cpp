#include<iostream>
#include<cstring>
using namespace std;

int num[10010];
int N;
int k;
bool dp[10010][110]; //dp[i][j]表示前i个数组成的序列 能否模k得到j
//dp[i][j] = dp[i-1][(j+num[i])%k] || dp[i-1][((j-num[i]) % k + k) % k]

int main(){
    memset(dp, false, sizeof(dp));
    cin >> N >> k;
    for(int i = 1; i <= N; i++){
        cin >> num[i];
    }
    dp[1][num[1] % k] = true;
    dp[1][((-num[1]) % k + k) % k] = true;
    
    for(int i = 2; i <= N; i++){
        for(int j = 0; j < k; j++){
            dp[i][j] = dp[i-1][(j+num[i])%k] || dp[i-1][((j-num[i]) % k + k) % k];
        }
    }
    
    if(dp[N][0]){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    
    return 0;
}
