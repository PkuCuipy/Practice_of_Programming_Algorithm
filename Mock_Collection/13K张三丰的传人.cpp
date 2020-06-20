#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;

const double diff = 1e-6;
int S;
bool finded;


void f(int last_time, double still_need, int time_left, vector<int>& ans){
    if(finded){ //已经找到过方案了
        return;
    }
    if(time_left == 0 && abs(still_need) <= diff){ //找到方案了!
        finded = true;
        cout << ans.size() << " ";
        for(auto i = ans.begin(); i != ans.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
        return;
    }
    //枚举
    for(int i = last_time; i <= time_left; i++){
        if(1.0 / i <= still_need + diff && time_left - i >= 0){
            ans.push_back(i);
            f(i, still_need - 1.0 / i, time_left - i, ans);
            ans.pop_back();
        }
    }
}

int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> S;
        if(S == 1){
            cout << "1 1" << endl;
            continue;
        }
        finded = false;
        vector<int> ans;
        f(2, 1, S, ans);
        if(!finded){
            cout << -1 << endl;
        }
    }
    
    
    return 0;
}
