#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int N;
int site[1010];
int dpL[1010]; //以site[i]为结尾的最长上升子序列
int dpR[1010]; //以site[i]为起始的最长下降子序列

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> site[i];
    }

    //dpL[]
    dpL[0] = 0;
    for(int i = 1; i <= N; i++){
        int temp_max = 1;
        for(int j = 1; j < i; j++){
            if(site[i] > site[j]){
                if(temp_max < 1 + dpL[j]){
                    temp_max = 1 + dpL[j];
                }
            }
        }
        dpL[i] = temp_max;
    }

    //dpR[]
    dpR[N+1] = 0;
    for(int i = N; i >= 1; i--){
        int temp_max = 1;
        for(int j = N; j > i; j--){
            if(site[i] > site[j]){
                if(temp_max < 1 + dpR[j]){
                    temp_max = 1 + dpR[j];
                }
            }
        }
        dpR[i] = temp_max;
    }

    //Enumerate 路线中最高的景点i
    int max_cnt = -1;
    for(int i = 0; i <= N; i++){ //枚举i 0和N+1考虑在内是因为 有可能“一直上山”或“一直下山”.
        for(int j = i; j <= N + 1; j++){
            if(site[j] == site[i]){
                if(dpR[j] + dpL[i] - 1 > max_cnt){
                    max_cnt = dpR[j] + dpL[i] - 1;
                }
            }
            if(site[j] < site[i]){
                if(dpR[j] + dpL[i] > max_cnt){
                    max_cnt = dpR[j] + dpL[i];
                }
            }
        }
    }

    cout << max_cnt << endl;


    return 0;
}
