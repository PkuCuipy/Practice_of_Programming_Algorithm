#include<iostream>
#include<cstring>
using namespace std;


struct Tree{
    int peach;
    int bee;
};
Tree forest[110];
int tree_amount;


int main(){
    int honey;
    while(static_cast<void>(cin >> honey), honey != -1){
        tree_amount = 0;
        int _b, _p;
        while(static_cast<void>(cin >> _p >> _b), _b + _p != -2){
            tree_amount++;
            forest[tree_amount].peach = _p;
            forest[tree_amount].bee = _b;
        }
        forest[tree_amount+1].bee = 1 << 30; //防止枚举越界

        int max_get = -1;
        //枚举空降的树
        for(int i = 1; i <= tree_amount; i++){
            //尝试向右行走,直到蜂蜜用尽(或者走到尽头)
            int peach_get = 0;
            int honey_left = honey;
            int pos = i;
            while(honey_left >= forest[pos].bee){
                honey_left -= forest[pos].bee;
                peach_get += forest[pos].peach;
                pos++;
            }
            if(peach_get > max_get){
                max_get = peach_get;
            }
        }
        cout << max_get << endl;


    }

    return 0;
}
