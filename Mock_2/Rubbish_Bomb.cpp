#include<iostream>
#include<cmath>
using namespace std;


struct garbage{
    int x;
    int y;
    int amount;
    bool affected(int bomb_x, int bomb_y, int bomb_range, int& cnt){
        if(abs(bomb_x - x) <= bomb_range && abs(bomb_y - y) <= bomb_range){
            cnt += amount;
            return true;
        }
        else{
            return false;
        }
    }
    
};



int main(){
    int bomb_range;
    int garbage_amount;
    cin >> bomb_range;
    cin >> garbage_amount;
    
    garbage garbages[40];
    for(int i = 0; i < garbage_amount; i++){
        cin >> garbages[i].x;
        cin >> garbages[i].y;
        cin >> garbages[i].amount;
    }
    
    //遍历每一个可能的坐标
    int max_clear_garbage_amount = 0;
    int good_bomb_cnt = 0;
    
    for(int x = 0; x <= 1024; x++){
        for(int y = 0; y <= 1024; y++){
            int cnt = 0;
            for(int i = 0; i <= garbage_amount; i++){
                garbages[i].affected(x, y, bomb_range, cnt);
            }
            if(cnt > max_clear_garbage_amount){
                max_clear_garbage_amount = cnt;
                good_bomb_cnt = 1;
            }
            else if(cnt == max_clear_garbage_amount){
                good_bomb_cnt ++;
            }
        }
    }
    
    cout << good_bomb_cnt << " " << max_clear_garbage_amount << endl;
    
    
    return 0;
}
