#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;


struct huge_int{
    int arr[60] = {0};
    int calculated = false; //标记是否被计算过了,避免重复计算.
    huge_int(const string& num = "0"){
        for(int i = 0; i < num.length(); i++){
            arr[i] = num[num.length()-i-1] - '0';
        }
    }
    
    void show(){
        int i;
        for(i = 55; i >= 0; i--){
            if(arr[i] != 0){
                break;
            }
        }
        while(i >= 0){
            cout << arr[i];
            i--;
        }
        cout << endl;
    }
    
    huge_int operator + (huge_int another){
        huge_int result(*this);
        for(int i = 0; i <= 55; i++){ //加
            result.arr[i] += another.arr[i];
        }
        for(int i = 0; i <= 55; i++){ //进位
            if(result.arr[i] >= 10){
                result.arr[i] -= 10;
                result.arr[i+1]++;
            }
        }
        return result;
    }
    
    bool operator < (huge_int another){
        for(int i = 55; i >= 0; i--){
            if(arr[i] > another.arr[i]){
                return false;
            }
            if(arr[i] < another.arr[i]){
                return true;
            }
        }
        return false;
    }
    
    
};

const huge_int inf("9999999999999999999999999999999999999999999999999999999");


huge_int dp[60][60]; //dp[n][m]表示前n个数字中插入m个的最小值


//在前n个数字中插入m个加号的表达式的最小值 如n=3,m=2,num="123456" 即1+2+3最小
huge_int best(const string& num, int n, int m){
    if(dp[n][m].calculated){
        return dp[n][m];
    }
    if(m == 0){
        dp[n][m] = huge_int(num.substr(0, n));
        dp[n][m].calculated = true;
        return dp[n][m];
    }
    if(m >= n){
        dp[n][m] = inf;
        dp[n][m].calculated = true;
        return inf;
    }
    
    huge_int temp;
    huge_int temp_min = inf;
    //枚举最右边加号的位置(pos表示加号右边的数字个数)
    for(int pos = 1; pos <= n - m; pos++){
        temp = huge_int(num.substr(n-pos, pos)) + best(num, n - pos, m - 1);
        if(temp < temp_min){
            temp_min = temp;
        }
    }
    
    dp[n][m] = temp_min;
    dp[n][m].calculated = true;
    return temp_min;
}

int main(){
    int m;
    while(cin >> m){
        for(int i = 0; i <= 59; i++){
            for(int j = 0; j <= 59; j++){
                dp[i][j].calculated = false;
            }
        }
        string str_num;
        cin >> str_num;
        
        huge_int b = best(str_num, (int)str_num.length(), m);
        
        b.show();
    }
    
    return 0;
}
