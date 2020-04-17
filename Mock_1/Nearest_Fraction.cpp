#include<iostream>
#include<cmath>
using namespace std;



int main(){
    
    int N;
    cin >> N;
    
    int A, B;
    cin >> A >> B;
    
    double nearest_value = A/B + 2000;
    int result_A, result_B;
    
    
    for(double i = 1; i <= N; i++){ //枚举分母
        for(double j = int(A * i / B) + 1; j >= 1; j--){ //枚举分子
            if(j/i < double(A)/double(B)){
                //看看是否是最接近的
                if(abs(j/i - double(A)/double(B)) < abs(nearest_value - double(A)/double(B))){
                    nearest_value = j/i;
                    result_A = j;
                    result_B = i;
                }
                break;
            }
        }
    }
    
    cout << result_A << " " << result_B << endl;
    
    return 0;
}
