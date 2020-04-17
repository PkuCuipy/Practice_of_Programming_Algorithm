#include<iostream>
#include<cstring>
using namespace std;

int delta_in[20]; //上车人数, 均>=0
int delta_out[20]; //下车人数, 均>=0
int after_delta_amount[20]; //上下车之后的人数

int main(){
    
    int init_people;
    int station_amount;
    int final_people;
    int station_inquire;
    cin >> init_people >> station_amount >> final_people >> station_inquire;
    
    
    for(int y = 0; y <= 999999; y++){ //枚举第二站上车和下车的人数y
        
        memset(delta_in, 0, sizeof(delta_in));
        memset(delta_out, 0, sizeof(delta_out));
        memset(after_delta_amount, 0, sizeof(after_delta_amount));
        
        delta_in[1] = init_people;
        delta_out[1] = 0;
        after_delta_amount[1] = init_people;
        delta_in[2] = y;
        delta_out[2] = y;
        after_delta_amount[2] = init_people;
        
        for(int station =  3; station <= station_amount - 1; station ++){
            delta_in[station] = delta_in[station-1] + delta_in[station-2];
            delta_out[station] = delta_in[station-1];
            after_delta_amount[station] = after_delta_amount[station-1] + delta_in[station] - delta_out[station];
        }
        
        delta_in[station_amount] = 0;
        delta_out[station_amount] = after_delta_amount[station_amount - 1];
        after_delta_amount[station_amount] = 0;
        
        if(delta_out[station_amount] == final_people){
            cout << after_delta_amount[station_inquire];
        }
        
    }
    
    
    
    
    return 0;
}
