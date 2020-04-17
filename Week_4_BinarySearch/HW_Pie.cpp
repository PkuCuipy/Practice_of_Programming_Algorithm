#include<iostream>
#include<iomanip>
using namespace std;
#define PI 3.14159265358979323846
#define DIFF 0.000001

bool can(const double pies[], int pie_amount, int people, double pie_per_person){
    int cnt = 0;
    for(int i = 1; i <= pie_amount; i++){
        //榨干这块pie
        double temp_volume = pies[i];
        while(temp_volume >= pie_per_person){
            cnt++;
            temp_volume -= pie_per_person;
        }
        if(cnt >= people){
            return true;
        }
    }
    
    return false;
}


int main(){

    double pies[10010] = {0};
    int pie_amount;
    int people;
    cin >> pie_amount >> people;
    people++; //包括自己
    
    
    for(int i = 1; i <= pie_amount; i++){
        cin >> pies[i];
        pies[i] *= (pies[i] * PI);
    }
    
    
    //查找每个人分到的pie的大小的最大可能值
    double L = 0;
    double R = 10000 * 10000 * PI;
    
    while(R - L > DIFF){
        double mid = L + (R-L)/2;
        if(can(pies, pie_amount, people, mid)){
            L = mid;
        }
        else{
            R = mid;
        }
    }
    
    cout << setprecision(3) << fixed << R << endl;
    
    return 0;
}
