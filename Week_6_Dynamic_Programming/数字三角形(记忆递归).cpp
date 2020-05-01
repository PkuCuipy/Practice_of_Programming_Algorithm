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


int max_sum(int i, int j){
    if(dp[i][j] != -1){ //如果算过了,就不用再算了
        return dp[i][j];
    }
    else if(i == row){
        return triangle[i][j];
    }
    else{
        int x = max_sum(i + 1, j);
        int y = max_sum(i + 1, j + 1);
        dp[i][j] = max_(x, y) + triangle[i][j];
        return dp[i][j];
    }
}


int main(){
    memset(triangle, 0, sizeof(triangle));
    memset(dp, -1, sizeof(dp));
    cin >> row;
    for(int i = 1; i <= row; i++){
        for(int j = 1; j <= i; j++){
            cin >> triangle[i][j];
        }
    }
    
    
    cout << max_sum(1,1) << endl;
    
    return 0;
}
