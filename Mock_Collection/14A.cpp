#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int map[110][110];
int n;


int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> map[i][j];
        }
    }
    //统计错误点
    int wrong_x_cnt = 0;
    int wrong_y_cnt = 0;
    int wrong_x;
    int wrong_y;
    
    for(int row = 1; row <= n; row++){
        int one_cnt = 0;
        for(int i = 1; i <= n; i++){
            if(map[row][i] == 1){
                one_cnt++;
            }
        }
        if(one_cnt % 2 != 0){
            wrong_x_cnt++;
            wrong_x = row;
        }
    }
    
    for(int column = 1; column <= n; column++){
        int one_cnt = 0;
        for(int i = 1; i <= n; i++){
            if(map[i][column] == 1){
                one_cnt++;
            }
        }
        if(one_cnt % 2 != 0){
            wrong_y_cnt++;
            wrong_y = column;
        }
    }
    
    if(wrong_x_cnt == 1 && wrong_y_cnt == 1){
        cout << wrong_x << " " << wrong_y << endl;
    }
    else if(wrong_x_cnt == 0 && wrong_y_cnt == 0){
        cout << "OK" << endl;
    }
    else{
        cout << "Corrupt" << endl;
    }
    
    return 0;
}
