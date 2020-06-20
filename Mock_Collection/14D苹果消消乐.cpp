#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int bananaPos[110];
int M;
bool magic[110];

int calcMax(){
    int MAX = 0;
    int temp = bananaPos[1] - 1;
    for(int i = 1; i <= N; i++){
        if(magic[i]){
            temp += bananaPos[i+1] - bananaPos[i];
            MAX = max(MAX, temp);
        }
        else{
            MAX = max(MAX, temp);
            temp = bananaPos[i+1] - bananaPos[i] - 1;
        }
    }
    MAX = max(MAX, temp);
    
    return MAX;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> N >> M;
        for(int i = 1; i <= N; i++){
            cin >> bananaPos[i];
        }
        bananaPos[N+1] = 101;
        
        int MAX = -1;
        //枚举施法, 再计算得分
        for(int i = 1; i <= N; i++){
            memset(magic, false, sizeof(magic));
            for(int j = i; j < i + M && j <= N; j++){
                magic[j] = true;
            }
            int tempMAX = calcMax();
            MAX = max(MAX, tempMAX);
        }
        
        cout << MAX << endl;
        
        
    }
    return 0;
}
