#include<iostream>
using namespace std;

int cnt(int apple, int plate){

    if(plate == 1 or apple == 1 or apple == 0){
        return 1;
    }

    if(apple < plate){
        return cnt(apple, apple);
    }

    //(以下必然有 apple >= plate)
    return cnt(apple, plate-1) + cnt(apple-plate, plate);
}


int main(){

    int T = 0;
    cin >> T;
    int M, N;
    for(int t = 1; t <= T; t++){
        cin >> M >> N;
        cout << cnt(M, N) << endl;
    }


    return 0;
}
