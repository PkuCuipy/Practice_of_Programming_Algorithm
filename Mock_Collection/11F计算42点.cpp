#include<iostream>
#include<vector>
using namespace std;

bool finded = false;

inline bool can_divide(int a, int b){
    if(b && !(a % b)){
        return true;
    }
    else{
        return false;
    }
}

void find42(const vector<int>& num){
    if(num.size() == 1){ //最后一层
        if(num[0] == 42){
            finded = true;
        }
        return;
    }
    if(finded){
        return;
    }
    //继续枚举
    for(int i = 0; i < num.size(); i++){
        for(int j = 0; j < num.size(); j++){
            
            //保证枚举的是不同的两个数
            if(i == j){
                continue;
            }

            //枚举出的a,b
            int a = num[i], b = num[j];
            vector<int> next(num);
            
            //删除next中的a,b
            if(j > i){
                next.erase(next.begin() + j);
                next.erase(next.begin() + i);
            }
            else{
                next.erase(next.begin() + i);
                next.erase(next.begin() + j);
            }
            
            //枚举加减乘除,将结果push到next中去
            //注意+和*是可交换的,重复计算会超时
            int res;
            //a + b
            if(i < j){
                res = a + b;
                next.push_back(res);
                find42(next);
                next.pop_back();
            }
            
            //a - b
            res = a - b;
            next.push_back(res);
            find42(next);
            next.pop_back();
            
            //a * b
            if(i < j){
                res = a * b;
                next.push_back(res);
                find42(next);
                next.pop_back();
            }
            
            //a / b
            if(can_divide(a, b)){
                res = a / b;
                next.push_back(res);
                find42(next);
                next.pop_back();
            }
            
        }
    }
}


int main(){
    vector<int> num;
    int n;
    cin >> n;
    int temp;
    for(int i = 1; i <= n; i++){
        cin >> temp;
        num.push_back(temp);
    }
    
    find42(num);
    
    if(finded){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    
    return 0;
}
