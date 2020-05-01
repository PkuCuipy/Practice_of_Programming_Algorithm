#include<iostream>
#include<cstring>
using namespace std;

int R;
int C;
int area[110][110];
int len_max[110][110];

int get_max_len(int i, int j){
    if(len_max[i][j]){
        return len_max[i][j];
    }

    int temp;
    int temp_max = 1;

    if(area[i-1][j] < area[i][j]){
        temp = get_max_len(i-1,j) + 1;
        if(temp > temp_max){
            temp_max = temp;
        }
    }

    if(area[i+1][j] < area[i][j]){
        temp = get_max_len(i+1,j) + 1;
        if(temp > temp_max){
            temp_max = temp;
        }
    }
    if(area[i][j+1] < area[i][j]){
        temp = get_max_len(i,j+1) + 1;
        if(temp > temp_max){
            temp_max = temp;
        }
    }
    if(area[i][j-1] < area[i][j]){
        temp = get_max_len(i,j-1) + 1;
        if(temp > temp_max){
            temp_max = temp;
        }
    }

    len_max[i][j] = temp_max;
    return temp_max;
}

int main(){
    //初始化高墙 和 len_max
    for(int i = 0; i <= 109; i++){
        for(int j = 0; j <= 109; j++){
            area[i][j] = 66666;
            len_max[i][j] = 0;
        }
    }

    cin >> R >> C;

    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cin >> area[i][j];
        }
    }


    int max_len = 0;
    int temp_len;
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            temp_len = get_max_len(i, j);
            if(temp_len > max_len){
                max_len = temp_len;
            }
        }
    }

    cout << max_len << endl;

    return 0;
}
