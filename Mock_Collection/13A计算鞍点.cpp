#include<iostream>
#include<cstring>
using namespace std;

int matrix[5][5];
int cnt[5][5] = {0};

int main(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> matrix[i][j];
        }
    }
    for(int i = 0; i < 5; i++){
        int rowMax = matrix[i][0];
        int j_of_max = 0;
        for(int j = 1; j < 5; j++){
            if(matrix[i][j] > rowMax){
                rowMax = matrix[i][j];
                j_of_max = j;
            }
        }
        cnt[i][j_of_max]++;
    }
    
    for(int j = 0; j < 5; j++){
        int columnMin = matrix[0][j];
        int i_of_min = 0;
        for(int i = 1; i < 5; i++){
            if(matrix[i][j] < columnMin){
                columnMin = matrix[i][j];
                i_of_min = i;
            }
        }
        cnt[i_of_min][j]++;
    }
    
    bool finded = false;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(cnt[i][j] == 2){
                finded = true;
                cout << i + 1 << " " << j + 1 << " " << matrix[i][j] << endl;
                break;
            }
        }
    }
    if(!finded){
        cout << "not found\n";
    }
    return 0;
}
