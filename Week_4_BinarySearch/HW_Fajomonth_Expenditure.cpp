#include<iostream>
using namespace std;


bool can(int day_spend[], int days, int max_fajo_spend, int max_fajo_amount){
    
    int temp = 0;
    int cnt_fajo = 1;
    
    for(int i = 1; i <= days; i++){
        if(day_spend[i] > max_fajo_spend){ //某一天的开销就超过了最大月上限, 肯定不行
            return false;
        }
        temp += day_spend[i];
        if(temp > max_fajo_spend){
            temp = day_spend[i];
            cnt_fajo++;
            if(cnt_fajo > max_fajo_amount){
                return false;
            }
        }
    }
    
    return true;
}


int main(){
    
    int N, M; // 一共N天, 最多分为M个fajo月
    cin >> N >> M;
    int spend[100010] = {0}; //spend[i] 表示第i天的开销
    
    
    for(int i = 1; i <= N; i++){
        cin >> spend[i];
    }
    
    
    
    
    
    //对每个fajo月的开销的最大值进行二分查找R
    int L = 0;
    int R = 100000 * 10000;
    int minof_MaxExpenditureofOneFajoMonth = R;
    while(L <= R){
        int mid = L + (R-L)/2;
        if(can(spend, N, mid, M)){
            minof_MaxExpenditureofOneFajoMonth = mid;
            R = mid - 1;
        }
        else{
            L = mid + 1;
        }
    }
    
    cout << minof_MaxExpenditureofOneFajoMonth << endl;
    
    
    
    
    return 0;
}
