#include<iostream>
#include<cstring>
using namespace std;

int f_xor(int a, int b){
    if(a == b){
        return -1;
    }
    return 1;
}

char init[40] = {-1};
char target[40] = {-1};
char diff[40] = {-1};


int output = 666;


int main(){
    cin.getline(init + 1, 40);
    cin.getline(target + 1, 40);
    for(int i = 1; i <= 40; i++){
        diff[i] = f_xor(init[i], target[i]);
    }
    
    //长度
    int n = (int)strlen(init) - 1;
    
    //第一个按钮分两种情况讨论
    
    char temp[40];
    
    
    //case1: 按第一个按钮
    memcpy(temp, diff, sizeof(diff));
    temp[1] *= -1;
    temp[2] *= -1;
    int cnt = 1;
    for(int i = 2; i <= n; i++){
        if(temp[i-1] == 1){ //如果左边是1
            //则需要按下当前的按钮
            cnt++;
            temp[i-1] *= -1;
            temp[i] *= -1;
            temp[i+1] *= -1;
        }
    }
    bool all_minus_1 = true;
    for(int i = 1; i <= n; i++){
        if(temp[i] == 1){
            all_minus_1 = false;
        }
    }
    if(all_minus_1){
        output = cnt;
    }
    
    
    
    
    //case2: 不按第一个按钮
    memcpy(temp, diff, sizeof(diff));
    int cnt2 = 0;
    for(int i = 2; i <= n; i++){
        if(temp[i-1] == 1){ //如果左边是1
            //则需要按下当前的按钮
            cnt2++;
            temp[i-1] *= -1;
            temp[i] *= -1;
            temp[i+1] *= -1;
        }
    }
    
    all_minus_1 = true;
    for(int i = 1; i <= n; i++){
        if(temp[i] == 1){
            all_minus_1 = false;
        }
    }
    if(all_minus_1 && cnt2 < cnt){
        output = cnt2;
    }
    
    if(output != 666){
        cout << output;
    }
    else{
        cout << "impossible" << endl;
    }
    
    
    
    
    
    return 0;
}
