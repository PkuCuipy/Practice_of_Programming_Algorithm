#include<iostream>
#include<string>
#include<cstring>
using namespace std;


//思路 每个指令只可能执行0,1,2,3次!
//枚举第一行 后面两行就被确定了! 然后在最后统一检测是否 "all_12"


struct Clock{
    int id; // 1-9
    int point_at; //0 or 3 or 6 or 9
    void rotate(){
        point_at = (point_at + 3) % 12;
    }
    Clock(char _id = 0, int _point_at = 0){
        id = _id;
        point_at = _point_at;
    }
    bool is_12(){
        return (point_at == 0);
    }
    int rotate_times_needed_to_be_12(){
        return ((12 - point_at) / 3) % 4;
    }
};

int min_len = 99999;

Clock ori_clocks[5][5];

string output;


int main(){
    
    for(int _ = 1; _ <= 3; _++){
        for(int __ = 1; __ <= 3; __++){
            int point_at;
            cin >> point_at;
            ori_clocks[_][__] = Clock(_, 3 * point_at);
        }
    }
    
    //枚举第一行,共64种情况~
    int cmds[10] = {0};
    for(int cmd1 = 0; cmd1 <= 3; cmd1++){
        cmds[1] = cmd1;
        for(int cmd2 = 0; cmd2 <= 3; cmd2++){
            cmds[2] = cmd2;
            for(int cmd3 = 0; cmd3 <= 3; cmd3++){
                
                cmds[3] = cmd3;
                Clock temp_clocks[5][5];
                memcpy(temp_clocks, ori_clocks, sizeof(ori_clocks));
                
                //将前3个指令应用于temp_clocks[][]
                for(int i = 1; i <= cmds[1]; i++){
                    temp_clocks[1][1].rotate();
                    temp_clocks[1][2].rotate();
                    temp_clocks[2][1].rotate();
                    temp_clocks[2][2].rotate();
                }
                for(int i = 1; i <= cmds[2]; i++){
                    temp_clocks[1][1].rotate();
                    temp_clocks[1][2].rotate();
                    temp_clocks[1][3].rotate();
                }
                for(int i = 1; i <= cmds[3]; i++){
                    temp_clocks[1][2].rotate();
                    temp_clocks[1][3].rotate();
                    temp_clocks[2][2].rotate();
                    temp_clocks[2][3].rotate();
                }
                
                //而cmd4,cmd5,cmd6被clock1,2,3的状态完全决定!
                cmds[4] = temp_clocks[1][1].rotate_times_needed_to_be_12();
                cmds[5] = temp_clocks[1][2].rotate_times_needed_to_be_12();
                cmds[6] = temp_clocks[1][3].rotate_times_needed_to_be_12();
                
                //cmd4,5,6应用于temp_clocks[][]
                for(int i = 1; i <= cmds[4]; i++){
                    temp_clocks[1][1].rotate();
                    temp_clocks[2][1].rotate();
                    temp_clocks[3][1].rotate();
                }
                for(int i = 1; i <= cmds[5]; i++){
                    temp_clocks[1][2].rotate();
                    temp_clocks[2][1].rotate();
                    temp_clocks[2][2].rotate();
                    temp_clocks[2][3].rotate();
                    temp_clocks[3][2].rotate();
                }
                for(int i = 1; i <= cmds[6]; i++){
                    temp_clocks[1][3].rotate();
                    temp_clocks[2][3].rotate();
                    temp_clocks[3][3].rotate();
                }
                
                //而cmd7,cmd9被clock4,6的状态完全决定!
                cmds[7] = temp_clocks[2][1].rotate_times_needed_to_be_12();
                cmds[9] = temp_clocks[2][3].rotate_times_needed_to_be_12();
                
                //cmd7,9应用于temp_clocks[][]
                for(int i = 1; i <= cmds[7]; i++){
                    temp_clocks[2][1].rotate();
                    temp_clocks[2][2].rotate();
                    temp_clocks[3][1].rotate();
                    temp_clocks[3][2].rotate();
                }
                for(int i = 1; i <= cmds[9]; i++){
                    temp_clocks[2][2].rotate();
                    temp_clocks[2][3].rotate();
                    temp_clocks[3][2].rotate();
                    temp_clocks[3][3].rotate();
                }
                
                //cmd8完全被7决定!
                cmds[8] = temp_clocks[3][1].rotate_times_needed_to_be_12();
                
                //cmd8应用于temp_clocks[][]
                for(int i = 1; i <= cmds[8]; i++){
                    temp_clocks[3][1].rotate();
                    temp_clocks[3][2].rotate();
                    temp_clocks[3][3].rotate();
                }
                
                
                //检查是否符合要求了(all_12?)
                bool all_12 = true;
                for(int i = 1; i <= 3; i++){
                    for(int j = 1; j <= 3; j++){
                        if(!temp_clocks[i][j].is_12()){
                            all_12 = false;
                        }
                    }
                }
                
                //符合要求了, 看一下指令长度
                if(all_12){
                    //统计指令长度
                    int temp_len = 0;
                    for(int i = 1; i <= 9; i++){
                        temp_len += cmds[i];
                    }
                    if(temp_len < min_len){ //当前这个指令是最短的!
                        min_len = temp_len;
                        output = "";
                        for(int i = 1; i <= 9; i++){
                            for(int j = 1; j <= cmds[i]; j++){
                                output += to_string(i);
                                output += " ";
                            }
                        }
                    }
                }
                
                
                
            }
        }
    }
   
    cout << output << endl;
    
    
    
    return 0;
}
