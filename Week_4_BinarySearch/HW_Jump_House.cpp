#include<iostream>
using namespace std;

int rock_pos[50010] = {0};
int end_pos = 0;
int rock_amount = 0;
int remove_limit = 0;


bool can(int min_distance){
    int remove_cnt = 0;
    int min_next_pos = 0 + min_distance;
    for(int i = 1; i <= rock_amount; i++){
        if(rock_pos[i] >= min_next_pos){
            min_next_pos = rock_pos[i] + min_distance;
            continue;
        }
        else{
            remove_cnt++;
            continue;
        }
    }
    if(rock_pos[rock_amount + 1] < min_next_pos){
        remove_cnt++;
    }
    
    if(remove_cnt <= remove_limit){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    
    cin >> end_pos >> rock_amount >> remove_limit;
    
    rock_pos[0] = 0;
    for(int i = 1; i <= rock_amount; i++){
        cin >> rock_pos[i];
    }
    rock_pos[rock_amount + 1] = end_pos;
    
    
    int L = 0;
    int R = 1000000000;
    int result = 0;
    
    while(L <= R){
        int mid = L + (R-L)/2;
        if(can(mid)){
            result = mid;
            L = mid + 1;
        }
        else{
            R = mid - 1;
        }
    }
    cout << result << endl;
    
    
    
    return 0;
}
