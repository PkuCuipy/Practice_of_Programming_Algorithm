#include<iostream>
#include<cstring>
using namespace std;

char match[5][5];
int best_rank = 5;
int blank_amount;

bool is_symmetric(){
    for(int i = 1; i <= 3; i++){
        for(int j = i + 1; j <= 4; j++){
            if(match[i][j] == match[j][i]){
                return false;
            }
        }
    }
    return true;
}

void compare_and_set(){
    //calc_score, then rank;
    int rank = 4;
    int score[5] = {0};
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 4; j++){
            if(match[i][j] == 'W'){
                score[i]++;
            }
        }
    }
    for(int i = 2; i <= 4; i++){
        if(score[1] >= score[i]){
            rank--;
        }
    }
    if(rank < best_rank){
        best_rank = rank;
    }
}



void f(char* last_enum, int cnt){ //枚举,把 ? 都变成 W / L
    if(cnt == blank_amount && is_symmetric()){
        compare_and_set();
        return;
    }
    char* p = last_enum;
    while(p - *match <= 23){
        p++;
        if(*p == '?'){
            *p = 'W';
            f(p, cnt + 1);
            *p = 'L';
            f(p, cnt + 1);
            *p = '?';
        }
    }
}



int main(){
    int T;
    cin >> T;
    while(T--){
        blank_amount = 0;
        best_rank = 5;
        for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
                cin >> match[i][j];
                if(match[i][j] == '?'){
                    blank_amount++;
                }
            }
        }
        f(*match + 6, 0);
        cout << best_rank << endl;

    }

    return 0;
}
