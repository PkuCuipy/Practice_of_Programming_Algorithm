#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int num[1010];
int maxS[1010] = {0};
//maxS[i]: 以第i个数字结尾的子序列的最大和
//maxS[i] = 1, 如果num[i]≤前面每个数字
//          = 1 + max{maxS[j]: num[j] < num[i]}


int main(){
    
    int N;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> num[i];
    }
    
    for(int i = 0; i < N; i++){
        
        maxS[i] = num[i];
        for(int j = i; j >= 0; j--){
            if(num[j] < num[i]){ //找到了可以组成更长的序列的j
                maxS[i] = max(maxS[j] + num[i], maxS[i]);
            }
        }
    }
    
    
    int output = 0;
    for(int i = 0; i < N; i++){
        output = max(output, maxS[i]);
    }
    cout << output << endl;
    
    
    
    return 0;
}
