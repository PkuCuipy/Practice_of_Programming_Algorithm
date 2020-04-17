#include<iostream>
#include<cmath>
using namespace std;

int N;
int queenPos[100]; //第i行的皇后放在哪一列


void NQueen(int k){ //在0~k-1行皇后已经摆好的情况下, 摆放第k行及其后的皇后
    
    if(k == N){ //N个皇后都已经摆好
        for(int i = 0; i <= N - 1; i++){
            cout << queenPos[i] + 1 << " ";
        }
        cout << endl;
        return;
    }
    
    for(int i = 0; i < N; i++){ //逐个尝试第k行的皇后的位置
        int j;
        for(j = 0; j < k; j++){ //第k行的皇后和之前的k个皇后进行比较
            if(queenPos[j] == i || abs(queenPos[j] - i) == abs(k - j)){ //如果在同一列(不可能在同一行~)或对角线,则不行.
                break; //冲突, 测试下一位置
            }
        }
        if(j == k){ //说明没有被break, 这个位置是可行的
            queenPos[k] = i; //第k个皇后摆放在位置i
            NQueen(k+1);
        }
    }
    
    
}


int main(){
    //用递归代替多重循环
    //输入整数n, 要求n个国际象棋的皇后, 摆在n*n的棋盘上, 互相不能攻击, 输出全部方案.
    
    cin >> N;
    NQueen(0);
    
    
    return 0;
}
