#include<iostream>
#include<cstring>
using namespace std;

void f(int x){
    bool flag = false;
    for(int bit = 30; bit >= 0; bit--){
        if((1 << bit) & x){
            if(flag){
                cout << "+";
            }
            flag = true;
            
            if(bit == 0){
                cout << "2(0)";
            }
            else if(bit == 1){
                cout << "2";
            }
            else{
                cout << "2("; f(bit); cout << ")";
            }
        }
    }
}

int main(){
    int x;
    cin >> x;
    f(x);
    cout << endl;

    return 0;
}
