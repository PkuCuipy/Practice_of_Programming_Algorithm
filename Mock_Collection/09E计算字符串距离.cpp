#include<iostream>
#include<cstring>
#include<string>
using namespace std;

#define LEN 1010

int dp[LEN][LEN];
/**
 * dp[endpos(从1开始数) of string_A][endpos of string_B]: minimal difference between A and B
 * dp[i][j] = dp[i-1][j-1] if A[i] == A[j]
 *                         else
 *                              min
 *                              {
 *                                  dp[i-1][j],      去掉a的结尾
 *                                  dp[i][j-1],      去掉b的结尾
 *                                  dp[i-1][j-1]    修改a和b的结尾使之一致
 *                              }
 *                              + 1
 *
 */

int main(){
    int T;
    cin >> T;
    while(T--){
        string A, B;
        cin >> A >> B;
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 0;
        for(int k = 1; k <= B.size(); k++){ //第0行单独处理
            dp[0][k] = k;
        }
        for(int k = 1; k <= A.size(); k++){ //第0列单独处理
            dp[k][0] = k;
        }

        for(int i = 1; i <= A.size(); i++){
            for(int j = 1; j <= B.size(); j++){
                if(A[i-1] == B[j-1]){ //第i个字母的索引值是i-1
                    dp[i][j] = dp[i-1][j-1];
                }
                else{
                    dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
                }
            }
        }

        cout << dp[A.size()][B.size()] << endl;


    }

    return 0;
}
