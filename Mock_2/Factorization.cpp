#include<iostream>
using namespace std;


int f(int x, int lower){
    if(x == 1){
        return 1;
    }
    int cnt = 0;
    for(int i = lower; i <= x; i++){
        if(x % i == 0){
            cnt += f(x/i, i);
        }
    }
    return cnt;
}


int main(){
    int N;
    cin >> N;
    for(int n = 1; n <= N; n++){
        int a;
        cin >> a;
        cout << f(a, 2) << endl;
    }
    
    return 0;
}
