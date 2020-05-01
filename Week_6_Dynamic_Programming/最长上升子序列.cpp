#include<iostream>
using namespace std;


inline int max_(int a, int b){
    if(a > b) return a;
    else return b;
}

//寻找子问题: 以a_k为终点的最长子序列长度

int a[1010] = {0};
int max_len[1010] = {0}; //以a[k]为终点的最长子序列长度



int main(){
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }
    max_len[1] = 1;
    
    for(int i = 2; i <= N; i++){
        for(int j = 1; j <= i - 1; j++){
            if(a[i] > a[j]){ //说明可以连成一个长度+1的上升序列
                max_len[i] = max_(max_len[i], max_len[j] + 1);
            }
        }
        if(max_len[i] == 0){ //不能和任何构成上升序列,那就和自己构成长度为1的...
            max_len[i] = 1;
        }
    }
    
    int max_print = 0;
    for(int i = 1; i <= N; i++){
        if(max_len[i] > max_print){
            max_print = max_len[i];
        }
    }
    
    cout << max_print << endl;
    
    return 0;
}
