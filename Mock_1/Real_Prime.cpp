#include<iostream>
#include<cmath>
using namespace std;

bool is_prime[100050];
void set_prime(){
    for(int i = 0; i <= 100049; i++){
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;
    
    for(int i = 2; i <= 100040; i++){
        if(is_prime[i]){
            for(int num = 2 * i; num <= 100030; num += i){
                is_prime[num] = false;
            }
        }
    }
}


int get_reverse(const int x){
    
    int len = 1;
    int temp = x;
    int result = 0;
    
    //确定位数
    while((temp /= 10) != 0){
        len++;
    }
    
    for(int i = len; i >= 1; i--){
        result += (x / (int)pow(10, i - 1) % 10) * (int)pow(10, len - i);
    }
    
    return result;
}


int main(){
    
    set_prime();
    
    int M, N;
    cin >> M >> N;
    
    bool is_first = true;
    for(int i = M; i <= N; i++){
        if(is_prime[i] && is_prime[get_reverse(i)]){
            if(!is_first){
                cout << ",";
            }
            is_first = false;
            cout << i;
        }
    }
    
    if(is_first){
        cout << "No" << endl;
    }
    
    
    return 0;
}
