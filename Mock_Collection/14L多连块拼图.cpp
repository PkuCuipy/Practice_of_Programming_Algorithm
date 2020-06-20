#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int m, n;
char big[25][25];
char small[25][25];
int zsx, zsy; //small[][]的“最上一行的最左元素”(zs:左上)

bool fill(int x, int y){ //fill,并返回是否失败

    //small的第一行
    for(int j = zsy; j < m; j++){
        if(small[zsx][j] == '*'){
            if(big[x][y + j-zsy] != '*'){
                return false;
            }
            big[x][y + j-zsy] = '.';
        }
    }

    //small的其余行
    for(int i = zsx+1; i < m; i++){
        for(int j = 0; j < m; j++){
            if(small[i][j] == '*'){
                if(x + i-zsx < 0 || x + i-zsx >= n || y + j-zsy < 0 || y + j-zsy >= n){ //越界
                    return false;
                }
                if(big[x + i-zsx][y + j-zsy] != '*'){
                    return false;
                }
                big[x + i-zsx][y + j-zsy] = '.';
            }
        }
    }

    return true;
}


int main(){
    ios::sync_with_stdio(false);
    while(cin >> n >> m, m != 0){
        memset(big, 0, sizeof(big));
        memset(small, 0, sizeof(small));
        for(int i = 0; i < n; i++){
            cin >> big[i];
        }
        for(int i = 0; i < m; i++){
            cin >> small[i];
        }

        //寻找small[][]的“最上一行的最左元素”
        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if(small[i][j] == '*'){
                    zsx = i;
                    zsy = j;
                    goto lable0;
                }
            }
        }
        lable0:

        //寻找big[][]的“最上一行的最左元素”,显然它对应于small[][]的“最上一行的最左元素”;
        //找到后尝试填入,如果填不进去,就说明不可能.
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(big[i][j] == '*'){ //找到了,这是当前big的“最上一行的最左元素”
                    bool b = fill(i, j);
                    if(!b){
                        goto lable1;
                    }
                }
            }
        }

        cout << "1" << endl;
        continue;

    lable1:
        cout << "0" << endl;

    }

    return 0;
}
