#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;


bool is_equal(double a, double b){
    return abs(b-a) < 0.00001;
}


bool f(double target, int amount, const vector<double> num){
    
    if(amount == 1){
        if(is_equal(target, num[0])){
            return true;
        }
    }
    
    //枚举两个不同的数
    for(int i = 0; i <= amount - 1; i++){
        for(int j = 0; j <= amount - 1; j++){
            if(j == i){
                continue;
            }
            
            //对这两个数枚举所有可能的操作
            // +
            {
                vector<double> v = num;
                double num_i = num[i];
                double num_j = num[j];
                double result = num_i + num_j;
                auto it = find(v.begin(), v.end(), num_i);
                v.erase(it);
                it = find(v.begin(), v.end(), num_j);
                v.erase(it);
                v.push_back(result);
                if(f(target, amount - 1, v)){
//                    cout << "+" << endl;
                    return true;
                }
            }
            
            // -
            {
                vector<double> v = num;
                double num_i = num[i];
                double num_j = num[j];
                double result = num_i - num_j;
                auto it = find(v.begin(), v.end(), num_i);
                v.erase(it);
                it = find(v.begin(), v.end(), num_j);
                v.erase(it);
                v.push_back(result);
                if(f(target, amount - 1, v)){
//                    cout << "-" << endl;
                    return true;
                }
            }
            
            // *
            {
                vector<double> v = num;
                double num_i = num[i];
                double num_j = num[j];
                double result = num_i * num_j;
                auto it = find(v.begin(), v.end(), num_i);
                v.erase(it);
                it = find(v.begin(), v.end(), num_j);
                v.erase(it);
                v.push_back(result);
                if(f(target, amount - 1, v)){
//                    cout << "*" << endl;
                    return true;
                }
            }
            
            // / 注意num[j]不等于0才能做!
            if(num[j] != 0)
            {
                vector<double> v = num;
                double num_i = num[i];
                double num_j = num[j];
                double result = num_i / num_j;
                auto it = find(v.begin(), v.end(), num_i);
                v.erase(it);
                it = find(v.begin(), v.end(), num_j);
                v.erase(it);
                v.push_back(result);
                if(f(target, amount - 1, v)){
//                    cout << "/" << endl;
                    return true;
                }
            }
            
        }
    }
    
    
    return false;
}


int main(){
    
    while(true){
        vector<double> vec;
        double x1, x2, x3, x4;
        cin >> x1 >> x2 >> x3 >> x4;
        if(x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0){
            break;
        }
        vec.push_back(x1);
        vec.push_back(x2);
        vec.push_back(x3);
        vec.push_back(x4);
        if(f(24.0, 4, vec)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
