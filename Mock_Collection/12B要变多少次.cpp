#include<iostream>
#include<cstring>
using namespace std;


int main(){
    int T;
    cin >> T;
    cin.get();
    while(T--){
        char arr[1010] = {0};
        cin.getline(arr, 1005);
        int len = strlen(arr);
        
        char comp[1010] = {0};
        for(int i = 0; i < len; i++){
            comp[i] = '1';
        }
        
        int min_diff = 1010;
        for(int _ = 0; _ <= len; _++){
            //计算comp和arr的差异值diff
            int diff = 0;
            for(int i = 0; i < len; i++){
                if(arr[i] != comp[i]){
                    diff++;
                }
            }
            if(diff < min_diff){
                min_diff = diff;
            }
            comp[_] = '0';
        }
        
        cout << min_diff << endl;
    }
    
    return 0;
}
