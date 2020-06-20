#include<iostream>
using namespace std;

int main(){
    int r_0;
    int r_1;
    int r_2;
    int q;
    cin >> r_0 >> r_1;
    
    r_2 = r_0 % r_1;
//    q = r_0 / r_1;
    while(r_2 != 0){
        r_0 = r_1;
        r_1 = r_2;
//        q = r_0 / r_1;
        r_2 = r_0 % r_1;
    }
    
    cout << r_1 << endl;
    
    
    return 0;
}
