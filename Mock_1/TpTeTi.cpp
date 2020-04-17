#include<iostream>
#include<cstring>
using namespace std;

int T1 = 23;
int T2 = 28;
int T3 = 33;

int main(){
    
    int s1, s2 ,s3, d;
    cin >> s1 >> s2 >> s3 >> d;
    
    s1 = s1 % T1;
    s2 = s2 % T2;
    s3 = s3 % T3;
    
    for(int day = d + 1;; day++){ //枚举第一个高峰的日期
        if((day - s1) % T1 == 0 && (day - s2) % T2 == 0 && (day - s3) % T3 == 0){
            cout << day - d << endl;
            break;
        }
    }
    
    
    return 0;
}
