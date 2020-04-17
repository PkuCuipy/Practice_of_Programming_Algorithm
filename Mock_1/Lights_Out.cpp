#include<iostream>
#include<cstring>
using namespace std;


int lights[10][10];

inline void press(int& light){
    light = !light;
}

int first_line[10] = {0,1,1,1,1,1,1,0,0,0};

void next(){
    first_line[1]++;
    for(int i = 1; i <= 6; i++){
        if(first_line[i] == 2){
            first_line[i] = 0;
            first_line[i+1]++;
        }
    }
}




int main(){
    
    memset(lights, 0, sizeof(lights));
    
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 6; j++){
            cin >> lights[i][j];
        }
    }

    //枚举第一行按下的情况
    for(int _ = 1; _ <= 64; _++){
        next(); //下一个枚举
        
        //复制一份灯泡图
        int temp[10][10];
        memcpy(temp, lights, sizeof(lights));
        
        //操作temp的第一行
        for(int j = 1; j <= 6; j++){
            if(first_line[j]){
                press(temp[1][j]);
                press(temp[1][j-1]);
                press(temp[1][j+1]);
                press(temp[2][j]);
            }
        }
        
        //操作temp的其余行
        for(int i = 2; i <= 5; i++){ //第i行
            for(int j = 1; j <= 6; j++){ //第j个
                if(temp[i-1][j]){
                    press(temp[i][j]);
                    press(temp[i][j-1]);
                    press(temp[i][j+1]);
                    press(temp[i+1][j]);
                    press(temp[i-1][j]);
                }
            }
        }
        
        
        //检查temp最后一行是否全部灭掉了
        bool all_0 = true;
        for(int j = 1; j <= 6; j++){ //第j个
            if(temp[5][j]){
                all_0 = false;
                break;
            }
        }
        
        
        if(all_0){ //成功了, 输出每一行的操作
            int manip[10][10];
            memset(manip, 0, sizeof(manip));
            
            //复制一份灯泡图
            int temp[10][10];
            memcpy(temp, lights, sizeof(lights));
            
            //操作temp的第一行
            for(int j = 1; j <= 6; j++){
                if(first_line[j]){
                    press(temp[1][j]);
                    press(temp[1][j-1]);
                    press(temp[1][j+1]);
                    press(temp[2][j]);
                    manip[1][j] = 1;
                }
            }
            
            //操作temp的其余行
            for(int i = 2; i <= 5; i++){ //第i行
                for(int j = 1; j <= 6; j++){ //第j个
                    if(temp[i-1][j]){
                        press(temp[i][j]);
                        press(temp[i][j-1]);
                        press(temp[i][j+1]);
                        press(temp[i+1][j]);
                        press(temp[i-1][j]);
                        manip[i][j] = 1;
                    }
                }
            }
            
            //输出manip
            for(int i = 1; i <= 5; i++){
                for(int j = 1; j <= 6; j++){
                    cout << manip[i][j] << " ";
                }
                cout << "\n";
            }
            
        }
        
    }
    
    
    
    
    
    return 0;
}
