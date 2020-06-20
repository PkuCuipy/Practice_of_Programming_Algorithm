#include<iostream>
#include<iomanip>
using namespace std;

double f(double x){
    return x*x*x*x*x - 15*x*x*x*x + 85*x*x*x - 225*x*x +274*x -121;
}

double diff = 0.0000001;

int main(){
    double L = 1.5, R = 2.4;
    while(R - L > diff){
        double m = L + (R-L)/2;
        if(f(m) < 0){
            R = m;
        }
        else{
            L = m;
        }
    }
    cout << setprecision(6) << fixed << L + (R-L)/2 << endl;
    return 0;
}
