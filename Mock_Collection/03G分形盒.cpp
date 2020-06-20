#include<iostream>
#include<cstring>
using namespace std;

int pow3(int n){
    int res = 1;
    for(int i = 1; i <= n; i++){
        res *= 3;
    }
    return res;
}

char canvas[800][800];

void draw(int x, int y, int n){
    if(n == 1){
        canvas[x][y] = 'X';
        return;
    }
    int pow = pow3(n-2);
    draw(x, y, n-1);
    draw(x + 2 * pow, y, n-1);
    draw(x, y + 2 * pow, n-1);
    draw(x + pow, y + pow, n-1);
    draw(x + 2 * pow, y + 2 * pow, n-1);
}

int main(){
    ios::sync_with_stdio(false);
    memset(canvas, ' ', sizeof(canvas));

    //预先绘制
    draw(0, 0, 7);
    while(true){
        int N;
        cin >> N;
        if(N == -1){
            break;
        }
        int limit = pow3(N-1);
        for(int i = 0; i < limit; i++){
            for(int j = 0; j < limit; j++){
                cout << canvas[i][j];
            }
            cout << endl;
        }
        cout << "-" << endl;
    }

    return 0;
}
