#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int N, W;
int weight[20]; //i道具重量

int remain[20]; //第i个背包剩余容量
int bag_use; //已经使用的最后一个背包的编号(编号从1开始数)
int least_use = 20; //最少使用数量


void dfs(int which){

    if(bag_use >= least_use){ //这种枚举已经没有意义了!!!
        return;
    }

    if(which > N){ //所有道具已经装完了
        if(bag_use < least_use){
            least_use = bag_use;
        }
        return;
    }
    //先枚举在已有的背包里放置
    for(int i = 1; i <= bag_use; i++){
        if(weight[which] <= remain[i]){ //可以放得下
            remain[i] -= weight[which];
            dfs(which + 1); //枚举下一个道具的放法
            remain[i] += weight[which];
        }
    }
    //再枚举新建一个背包的情况
    bag_use++;
    remain[bag_use] -= weight[which];
    dfs(which + 1);
    remain[bag_use] += weight[which];
    bag_use--;
}


int main(){
    cin >> N >> W;
    for(int i = 1; i <= N; i++){
        cin >> weight[i]; //读入道具重量
        remain[i] = W; //初始化背包容量
    }

    //先放第一个道具
    bag_use = 1;
    remain[1] -= weight[1];

    //枚举放置后面的道具, 每个道具的放法最多有 bag_use + 1 种
    dfs(2);

    cout << least_use << endl;

    return 0;
}
