#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int command[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},{0,1,1,0,1,1,0,0,0,0},{0,1,1,1,0,0,0,0,0,0},{0,0,1,1,0,1,1,0,0,0},{0,1,0,0,1,0,0,1,0,0},
    {0,0,1,0,1,1,1,0,1,0},{0,0,0,1,0,0,1,0,0,1},{0,0,0,0,1,1,0,1,1,0},{0,0,0,0,0,0,0,1,1,1},{0,0,0,0,0,1,1,0,1,1}
};




int temp_command[10] = {0}; //第i个元素的值代表第i个指令使用多少次

struct Clock{
    int id; // 1-9
    int point_at; //0 or 3 or 6 or 9
    void move(){
        point_at = (point_at + 3) % 12;
    }
    Clock(char _id = 0, int _point_at = 0){
        id = _id;
        point_at = _point_at;
    }
    bool is_12(){
        return (point_at == 0);
    }
};


Clock ori_clocks[10];


void multi_for(int this_layer, int total_layer){
    
    if(this_layer > total_layer){ //最后一层,检测temp_command对应的指令串是否符合要求
        //对temp_clocks[]按照指令操作
        Clock temp_clocks[10];
        memcpy(temp_clocks, ori_clocks, sizeof(ori_clocks));
        for(int cmd = 1; cmd <= 9; cmd++){ //temp_command[cmd]存放了第cmd条指令需要执行的次数
            for(int times = 1; times <= temp_command[cmd]; times++){
                //执行第cmd个指令于temp_clocks[]
                for(int c = 1; c <= 9; c++){
                    if(command[cmd][c]){
                        temp_clocks[c].move();
                    }
                }
            }
        }
        
        //检查这些clocks是不是都是12了?
        bool all_12 = true;
        for(int c = 1; c <= 9; c++){
            if(!temp_clocks[c].is_12()){
                all_12 = false;
                break;
            }
        }
        if(all_12){
            //开始输出 然后结束程序
            for(int cmd = 1; cmd <= 9; cmd++){
                for(int i = 1; i <= temp_command[cmd]; i++){
                    cout << cmd << " ";
                }
            }
            
            exit(0);
        }
        
        
        return;
    }
    for(int i = 1; i <= 9; i++){
        temp_command[i]++;
        multi_for(this_layer + 1, total_layer);
        temp_command[i]--;
    }
}


int main(){
    
    
    for(int _ = 1; _ <= 9; _++){
        int point_at;
        cin >> point_at;
        ori_clocks[_] = Clock(_, 3 * point_at);
    }
    
   
    for(int len = 1; ; len++){ //枚举指令长度
        memset(temp_command, 0, sizeof(temp_command));
        multi_for(1, len);
    }
    
    
    
    
    
    return 0;
}
