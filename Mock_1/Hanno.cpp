#include<iostream>
#include<vector>
using namespace std;


char name[3];


vector<int> tower[3];


void move(int amount, int from, int by, int to){
    if(amount == 1){
        cout << name[from] << "->" << tower[from].back() << "->" << name[to] << endl;
        tower[to].push_back(tower[from].back());
        tower[from].pop_back();
        return;
    }
    move(amount-1, from, to, by);
    move(1, from, by, to);
    move(amount-1, by, from, to);
}

int main(){
    int plate_amount;
    cin >> plate_amount >> name[0] >> name[1] >> name[2];
    for(int i = plate_amount; i >= 1; i--){
        tower[0].push_back(i);
    }
    move(plate_amount, 0,2,1);
    return 0;
}
