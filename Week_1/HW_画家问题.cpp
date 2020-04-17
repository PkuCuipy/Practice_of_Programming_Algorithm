#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int origin_wall[20][20];
int paint_result[20][20];
int permutation[20]; //第一行的枚举

void set_next(int permutation[20], int size){
    permutation[1]++;
    for(int i = 1; i <= size; i++){
        if(permutation[i] == 2){
            permutation[i] = 0;
            permutation[i + 1] += 1;
        }
    }
}


int main(){

    int wall_size;
    cin >> wall_size;

    for(int i = 1; i <= wall_size; i++){
        for(int j = 1; j <= wall_size; j++){
            char color;
            cin >> color;
            if(color == 'w'){
                origin_wall[i][j] = -1;
            }
            else{
                origin_wall[i][j] = 1;
            }
        }
    }

    memset(permutation, 0, sizeof(permutation)); //初始化枚举为0000000000
    int times = int(pow(2, wall_size) + 0.5); //枚举次数
    
    for(int t = 1; t <= times; t++){
        
        //记录次数
        int draw_times = 0;
        
        //复制出一份新的墙
        int temp_wall[20][20];
        memcpy(temp_wall, origin_wall, sizeof(origin_wall));
        
        //复制出一份numeration
        int numeration[20];
        memcpy(numeration, permutation, sizeof(permutation));
        
        //按照枚举方案更改第一行
        for(int j = 1; j <= wall_size; j++){
            if(numeration[j]){ //如果枚举中这里是1,则画一笔
                draw_times++;
                temp_wall[1][j-1] *= -1;
                temp_wall[1][j] *= -1;
                temp_wall[1][j+1] *= -1;
                temp_wall[2][j] *= -1;
            }
        }
        //其余各行
        for(int i = 2; i <= wall_size; i++){
            for(int j = 1; j <= wall_size; j++){
                if(temp_wall[i-1][j] == -1){ //上一行这个位置是-1,则这一行这个位置必然要画一笔!
                    draw_times++;
                    temp_wall[i][j-1] *= -1;
                    temp_wall[i][j] *= -1;
                    temp_wall[i][j+1] *= -1;
                    temp_wall[i+1][j] *= -1;
                }
            }
        }
        
        //检查最后一行是否全是1
        bool all_one = true;
        for(int i = 1; i <= wall_size; i++){
            if(temp_wall[wall_size][i] != 1){
                all_one = false;
            }
        }
        if(all_one){
            cout << draw_times << endl;
            return 0;
        }
        
        //更改枚举到下一次
        set_next(permutation, wall_size);
    }
    
    cout << "inf" << endl;
    
    return 0;
}
