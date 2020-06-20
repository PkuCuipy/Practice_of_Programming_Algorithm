#include<iostream>
#include<cstring>
using namespace std;

bool isPrime[100010];

int pow10(int n){
    //返回10的n次方
    int temp = 1;
    for(int i = 1; i <= n; i++){
        temp *= 10;
    }
    return temp;
}

int reversed(int x){
    //先统计位数
    int digits;
    for(int i = 0; ; i++){
        if(x / pow10(i) == 0){
            digits = i;
            break;
        }
    }
    int ans = 0;
    for(int i = 0; i <= digits - 1; i++){
        ans += x / pow10(i) % 10 * pow10(digits - 1 - i);
    }
    return ans;
}

int main(){

    //Sieve Primes
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i = 2; i <= 100005; i++){
        if(isPrime[i]){
            for(int j = 2 * i; j <= 100005; j += i){
                isPrime[j] = false;
            }
        }
    }

    bool is_first = true;
    int M, N;
    cin >> M >> N;
    
    for(int i = M; i <= N; i++){
        if(isPrime[i] && isPrime[reversed(i)]){
            if(!is_first){
                cout << ",";
            }
            is_first = false;

            cout << i;
        }
    }
    if(is_first){
        cout << "No";
    }


    return 0;
}
