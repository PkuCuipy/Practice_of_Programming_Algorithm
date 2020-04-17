#include<iostream>
#include<string>
#include<cstring>
using namespace std;


char oriLights[5]; //原始
char lights[5]; //变化中
char result[5]; //结果


int get_bit(char c, int i){
    return (c >> i) & 1;
}


void set_bit(char& c, int i, int v){
    if(v){
        c |= (1 << i);
    }
    else{
        c &= ~(1 << i);
    }
}


void flip_bit(char& c, int i){
    c ^= (1 << i);
}


void print_result(int test, char result[]){
    cout << "PUZZLE #" << test << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            cout << get_bit(result[i], j);
            if(j != 5){
                cout << " ";
            }
        }
        cout << endl;
    }
}


int main(){
    
    int T;
    cin >> T;
    for(int t = 1; t <= T; ++t){
        
        //读入原始状态
        for(int i = 0; i <= 4; ++i){
            for(int j = 0; j <= 5; ++j){
                int s;
                cin >> s;
                set_bit(oriLights[i], j, s);
            }
        }
        
        //枚举第一行的01组合
        for(int n = 0; n < 64; ++n){
            int switches = n;
            memcpy(lights, oriLights, sizeof(oriLights)); //先拷贝一份到lights
            for(int i = 0; i <= 4; ++i){ //对于每一行
                result[i] = switches;
                //先处理本行
                for(int j = 0; j <= 5; j++){ //第j个开关
                    if(get_bit(switches, j)){
                        if(j > 0){
                            flip_bit(lights[i], j - 1);
                        }
                        if(j < 5){
                            flip_bit(lights[i], j + 1);
                        }
                        flip_bit(lights[i], j);
                    }
                }
                //再处理下一行
                if(i != 4){
                    lights[i + 1] ^= switches;
                }
                
                //现在这一行亮着的灯的正下方那行的开关应该开着
                switches = lights[i];
            }
            
            //下面看第五行,如果也都灭了,就成功
            if(lights[4] == 0){
                print_result(t, result);
                break;
            }
            
            
            
        }
        
        
    }
    
    
    
    
    return 0;
}
