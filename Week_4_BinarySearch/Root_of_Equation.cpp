#include<iostream>
#include<cmath>
using namespace std;


inline double f(double x){
    return pow(x,3) - 5*pow(x,2) + 10*x - 80;
}

//求单调递增函数 f(x) = x^3 - 5x^2 + 10x - 80 = 0 的根,精确到10^(-6)
//注意到 f(0) < 0, f(100) > 0
//使用二分查找

double get_root(){
    double L = 0.0;
    double R = 100.0;
    int tryTimes = 0;
    while(R-L > 10e-7){
        tryTimes++;
        double mid = L + (R-L) / 2;
        if(f(mid) < 0){
            L = mid;
        }
        else{
            R = mid;
        }
    }
    cout << "尝试次数:" << tryTimes << endl;
    return L;
}



int main(){

    cout << get_root() << endl;
    cout << scientific;
    cout << f(get_root() - 10e-6) << endl;
    cout << f(get_root()) << endl;
    cout << f(get_root() + 10e-6) << endl;


    return 0;
}
