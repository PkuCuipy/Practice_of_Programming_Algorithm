#include<iostream>
using namespace std;


int main(){
    
    long long N;
    cin >> N;
    
    for(long long peach = N + 1; ; peach += N){
        long long temp = peach;
        bool can_divide = true;
        for(int i = 1; i <= N; i++){
            if((temp - 1) % N != 0 || (temp-1) <= 0){
                can_divide = false;
                break;
            }
            else{
                temp = (temp - 1) * (N-1) / N;
            }
        }
        if(can_divide){
            cout << peach << endl;
            break;
        }
    }
    return 0;
}
