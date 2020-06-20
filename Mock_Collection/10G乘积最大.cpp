#include<iostream>
using namespace std;

int pow10(int n){
    int res = 1;
    for(int i = 0; i < n; i++){
        res *= 10;
    }
    return res;
}

int N;
int K;
int MAX;
int num[50];

int p2num(int* L, int* R){ // 计算 [L,R) 代表的整数
    long len = R - L;
    int res = 0;
    for(int i = 0; i < len; i++){
        R--;
        res += pow10(i) * (*R);
    }
    return res;
}


void dfs(int last_pos, int remain, int product){ //上个乘号的位置是last_pos, 剩下remain个乘号需要被枚举, 当前乘积为product
    if(remain == 0){ //没有乘号需要枚举了, 开始和max比较
        product *= p2num(num + last_pos + 1, num + N);
        if(product > MAX){
            MAX = product;
        }
        return;
    }
    for(int i = last_pos + 1; i <= N - 2; i++){
        dfs(i, remain - 1, product * p2num(num + last_pos + 1, num + i + 1));
    }

}


int main(){
    //N位数, K个乘号, 乘号的位置为i表示这个乘号放在第i个数字之后
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        char c;
        cin >> c;
        num[i] = c - '0';
    }
    dfs(-1, K, 1);
    cout << MAX << endl;


    return 0;
}
