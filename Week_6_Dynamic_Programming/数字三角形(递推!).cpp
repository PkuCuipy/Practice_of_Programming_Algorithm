#include<iostream>
#include<cstring>
using namespace std;

inline int max_(int a, int b){
    if(a > b) return a;
    else return b;
}


int row;
int triangle[110][110];
int dp[110][110];




int main(){
    memset(triangle, 0, sizeof(triangle));
    memset(dp, -1, sizeof(dp));
    cin >> row;
    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= i; j++){
            cin >> triangle[i][j];
        }
    }
    
    for(int i = 1; i <= row; i++){
        dp[row][i] = triangle[row][i];
    }
    
    for(int i = row - 1; i >= 1; i--){
        for(int j = 1; j <= i; j++){
            dp[i][j] = triangle[i][j] + max_(dp[i+1][j], dp[i+1][j+1]);
        }
    }
    
    cout << dp[1][1] << endl;
    
    return 0;
}
