#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;


int N; //股票数量
int price[100010]; //第i天的股票价格
int price_min[100010]; //1~i天股票最小价格     ( x~y 表示闭区间 [x,y] )
int price_max[100010]; //i~N天股票最大价格
int dpL[100010]; //1~i天买卖最大收益   dpL[i] = MAX{ dpL[i-1], price[i] - price_min[i] }
int dpR[100010]; //i~N天买卖最大收益   dpR[i] = MAX{ dpR[i+1], price_max[i] - price[i] }


int main(){
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 1; i <= N; i++){
            cin >> price[i];
        }
        //计算price_min[]
        int temp_min = 1 << 30;
        for(int i = 1; i <= N; i++){
            if(price[i] < temp_min){
                temp_min = price[i];
            }
            price_min[i] = temp_min;
        }
        //计算price_max[]
        int temp_max = - (1 << 30);
        for(int j = N; j >= 1; j--){
            if(price[j] > temp_max){
                temp_max = price[j];
            }
            price_max[j] = temp_max;
        }
        //计算dpL[]
        dpL[1] = 0;
        for(int i = 2; i <= N; i++){
            dpL[i] = max(dpL[i-1], price[i] - price_min[i]);
        }
        //计算dpR[]
        dpR[N] = 0;
        for(int j = N - 1; j >= 2; j--){
            dpR[j] = max(dpR[j+1], price_max[j] - price[j]);
        }
        //遍历分割线 寻求受益最大值
        int max_earn = -(1 << 30);
        for(int i = 1; i <= N; i++){
            if(dpL[i] + dpR[i] > max_earn){
                max_earn = dpL[i] + dpR[i];
            }
        }
        cout << max_earn << endl;
    }
    return 0;
}
