#include<iostream>
using namespace std;

void f(int x, int layer){
    if(x == 1){
        if(layer == 0){
            cout << "2(0)";
        }
        if(layer == 1){
            cout << "2";
        }
        else{
            cout << "2(";
            f(layer, 0);
            cout << ")";
        }
        return;
    }
    
    f(x / 2, layer + 1);
    
    if(x % 2){
        if(layer == 0){
            cout << "+2(0)";
        }
        else if(layer == 1){
            cout << "+2";
        }
        else{
            cout << "+2(";
            f(layer, 0);
            cout << ")";
        }
    }
    
    
    
}

int main(){
    int n;
    cin >> n;
    f(n, 0);
    cout << endl;
    
    return 0;
}


