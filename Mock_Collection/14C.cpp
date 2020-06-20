#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int mission[1010];
int dpL[1010]; //dpL[i]: [0,i]最长下降子序列长度
int dpR[1010]; //dpR[i]: [i,N]最长下降子序列长度

int main(){

    int N;
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> mission[i];
    }

    //计算dpL[]
    //dpL[i] = 1 + max{dpL[<i && mission[<i] >= mission[i]]}
    dpL[1] = 1;
    for(int i = 2; i <= N; i++){
        int tempMax = 0;
        for(int j = 1; j < i; j++){
            if(mission[j] >= mission[i]){
                tempMax = max(tempMax, dpL[j]);
            }
        }
        dpL[i] = 1 + tempMax;
    }

    //计算dpR[]
    //dpR[i] = 1 + max{dp[>i && mission[>i] <= mission[i]]}
    dpR[N] = 1;
    for(int i = N-1; i >= 1; i--){
        int tempMax = 0;
        for(int j = N; j > i; j--){
            if(mission[j] <= mission[i]){
                tempMax = max(tempMax, dpR[j]);
            }
        }
        dpR[i] = 1 + tempMax;
    }

    int MAX = -1;
    //枚举重启点R, 此时, 最大处理量 = max{dpL[<R]} + max{dpR[>=R]}
    for(int R = 1; R <= N; R++){
        int tempMAXL = -1;
        int tempMAXR = -1;
        for(int i = 1; i < R; i++){
            tempMAXL = max(tempMAXL, dpL[i]);
        }
        for(int i = R; i <= N; i++){
            tempMAXR = max(tempMAXR, dpR[i]);
        }
        MAX = max(MAX, tempMAXL + tempMAXR);
    }
    cout << MAX << endl;


    return 0;
}
