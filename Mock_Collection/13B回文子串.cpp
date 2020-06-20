#include<iostream>
#include<cstring>
using namespace std;


char word[110];
int dp[110][110];
bool judge(int i, int j){
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    if(i == j){
        dp[i][j] = 1;
        return true;
    }
    if(j - i == 1 || j - i == 2){
        dp[i][j] = (word[i] == word[j]);
        return dp[i][j];
    }
    if(word[i] == word[j]){
        dp[i][j] = judge(i+1, j-1);
        return dp[i][j];
    }
    dp[i][j] = false;
    return false;
}

int main(){
    int T;
    cin >> T;
    cin.get();
    while(T--){
        int MAX = -1;
        int best_i, best_j;
        memset(dp, -1, sizeof(dp));
        memset(word, 0, sizeof(word));
        cin.getline(word, 105);
        int len = (int)strlen(word);
        for(int i = 0; i < len; i++){
            for(int j = i; j < len; j++){
                if(judge(i, j)){
                    if(j - i > MAX){
                        MAX = j - i;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
        }
        for(int i = best_i; i <= best_j; i++){
            cout << word[i];
        }
        cout << endl;
    }

    return 0;
}
