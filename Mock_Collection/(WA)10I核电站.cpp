#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int N;
int M;
int dp[60];

int f(int n){ // n 个坑, 最多连续 M-1 个的情况下的方案数.
    if(n <= M - 1){
        return int(pow(2,n)+0.5);
    }
    if(n == M){
        return int(pow(2,n)+0.5) - 1;
    }
    if(dp[n] != -1){
        return dp[n];
    }
    
    int ans = 0;
    for(int i = 1; i <= M; i++){
        ans += f(n-i);
    }
    
    dp[n] = ans;
    return dp[n];
}

int main(){
    memset(dp, -1, sizeof(dp));
    cin >> N >> M;
    
    for(int i = 1; i <= 30; i++){
        cout << f(i) << endl;
    }
    cout << f(N) << endl;
    
    return 0;
}


/**
 2
 4
 7
 13
 24
 44
 81
 149
 274
 504
 927
 1705
 3136
 5768
 10609
 19513
 35890
 66012
 121415
 223317
 410744
 755476
 1389537
 2555757
 4700770
 8646064
 15902591
 29249425
 53798080
 98950096
 */
