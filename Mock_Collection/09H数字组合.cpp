#include<iostream>
#include<cstring>
using namespace std;

int n, target;
int num[35];

int dp[25][1010];

int search(int s, int t){ //计算 用后s个(包括第s个)(从1开始数)数字 凑t的总方式数
    if(dp[s][t] != -1){
        return dp[s][t];
    }
    if(t > target || t < 0){
        return 0;
    }
    if(s == n){
        return t == 0 || t == num[n];
    }
    
    dp[s][t] = search(s + 1, t - num[s]) + search(s + 1, t);
    
    return dp[s][t];
}


int main(){
    cin >> n >> target;
    for(int i = 1; i <= n; i++){
        cin >> num[i];
    }
    memset(dp, -1, sizeof(dp));
    cout << search(1, target) << endl;
    
    return 0;
}



