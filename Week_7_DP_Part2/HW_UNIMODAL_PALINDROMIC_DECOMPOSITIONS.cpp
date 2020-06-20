#include<iostream>
#include<cstring>
using namespace std;

//dp[i][j]表示“总和为i,最小值>=j”的对称串数量
long long dp[300][300];

long long f(long long sum, long long min_){
    if(sum == 0){
        return 1;
    }
    if(sum == min_){
        return 1;
    }a
    if(sum < min_){
        return 0;
    }
    if(dp[sum][min_] != -1){
        return dp[sum][min_];
    }
    
    long long as_return = 0;
    if(sum >= min_){
        as_return += 1; //自己单独
    }
    for(long long side = min_; side <= sum/3; side++){
        //枚举左右护法(比如12需要枚举 1_1; 2_2; 3_3; 4_4; 但5_5就不行了,因为中间只剩下2,无论如何也做不到)
        as_return += f(sum - 2 * side, side);
    }
    if(sum % 2 == 0 && sum / 2 >= min_){
        as_return += 1; //自己可以拆成两份
    }
    
    dp[sum][min_] = as_return;
//    cout << "dp[" << sum << "][" << min_ << "] = " << as_return << endl;
    return as_return;
}


int main(){
    memset(dp, -1, sizeof(dp));
    while(true){
        long long n;
        cin >> n;
        if(n == 0){
            break;
        }
        else{
            cout << n << " " << f(n, 1) << endl;
        }
    }
    
    
    return 0;
}
