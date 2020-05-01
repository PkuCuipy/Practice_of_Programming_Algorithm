#include<iostream>
#include<cstring>
using namespace std;

int height[110];
int max_up_len[110]; //以height[i]为终点的上升子序列的最大长度
int max_down_len[110]; //以height[i]为终点的下降子序列的最大长度

int main(){
    int K;
    cin >> K;
    
    for(int k = 1; k <= K; k++){
        memset(max_up_len, -1, sizeof(max_up_len));
        memset(max_down_len, -1, sizeof(max_down_len));
        int N;
        cin >> N;
        for(int building = 0; building < N; building++){
            cin >> height[building];
        }
        
        //先求最长上升序列长度
        max_up_len[0] = 1;
        for(int i = 1; i < N; i++){
            int temp;
            int temp_max = -1;
            for(int j = 0; j < i; j++){
                if(height[j] < height[i]){
                    temp = max_up_len[j] + 1;
                    if(temp > temp_max){
                        temp_max = temp;
                    }
                }
            }
            if(temp_max == -1){ //说明自己不比前面的任何一个大...只能自己作为起点自己作为终点,长度为1
                temp_max = 1;
            }
            max_up_len[i] = temp_max;
        }
        int max1 = -1;
        for(int i = 0; i < N; i++){
            if(max_up_len[i] > max1){
                max1 = max_up_len[i];
            }
        }
        
        
        
        
        //再求最长下降序列长度
        max_down_len[0] = 1;
        for(int i = 1; i < N; i++){
            int temp;
            int temp_max = -1;
            for(int j = 0; j < i; j++){
                if(height[j] > height[i]){
                    temp = max_down_len[j] + 1;
                    if(temp > temp_max){
                        temp_max = temp;
                    }
                }
            }
            if(temp_max == -1){ //说明自己不比前面的任何一个小...只能自己作为起点自己作为终点,长度为1
                temp_max = 1;
            }
            max_down_len[i] = temp_max;
        }
        
        for(int i = 0; i < N; i++){
            if(max_down_len[i] > max1){
                max1 = max_down_len[i];
            }
        }
        
        cout << max1 << endl;
        
    }
    
    
    
    return 0;
}
