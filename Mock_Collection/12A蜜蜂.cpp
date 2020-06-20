#include<iostream>
#include<cstring>
using namespace std;

long long dp[60][60];

long long f(int a, int b){
    if(b - a == 1){
        return 1;
    }
    if(b - a == 2){
        return 2;
    }
    if(dp[a][b] != -1){
        return dp[a][b];
    }
    dp[a][b] = f(a + 1, b) + f(a + 2, b);
    return dp[a][b];
}

int main(){
    int N;
    cin >> N;
    while(N--){
        memset(dp, -1, sizeof(dp));
        int a, b;
        cin >> a >> b;
        cout << f(a, b) << endl;
    }
    
    return 0;
}
