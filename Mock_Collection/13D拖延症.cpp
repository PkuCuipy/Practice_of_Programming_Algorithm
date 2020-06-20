#include<iostream>
#include<cstring>
using namespace std;

int spirit[16];
int wage[16];
bool choice[16];
int S;
int max_money = -1;

void arrange(int day, int qian10, int hou5, int spirit_left, int money_get){
    if(day == 16){
        if(qian10 > hou5){
            return;
        }
        if(money_get > max_money){
            max_money = money_get;
        }
        return;
    }
    //安排这一天
    if(spirit_left >= spirit[day]){ //1.这一天(还可以)尝试做工作
        arrange(day + 1, qian10 + (day <= 10), hou5 + (day >= 11), spirit_left - spirit[day], money_get + wage[day]);
    }
    arrange(day + 1, qian10, hou5, spirit_left, money_get);//2.这一天不做工作
}

int main(){
    memset(choice, false, sizeof(choice));
    memset(wage, 0, sizeof(wage));
    memset(spirit, 0, sizeof(spirit));
    cin >> S;
    for(int i = 1; i <= 15; i++){
        cin >> wage[i] >> spirit[i];
    }
    arrange(1, 0, 0, S, 0);
    cout << max_money << endl;

    return 0;
}
