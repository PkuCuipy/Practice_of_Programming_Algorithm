#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int num[100010];
int m;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> num[i];
    }
    sort(num + 1, num + n + 1);
    num[0] = -(1 << 30);
    cin >> m;
    int x;
    for(int i = 1; i <= m; i++){
        cin >> x;
        int L = 1, R = n;
        int last_pos = 0;
        while(L <= R){
            int m = L + (R-L)/2;
            if(num[m] <= x){
                L = m + 1;
                last_pos = m;
            }
            else{
                R = m - 1;
            }
        }
        //继续尝试向右挪动last_pos
        int diff = abs(num[last_pos] - x);
        if(abs(num[last_pos + 1] - x) < diff){
            last_pos++;
        }
        cout << num[last_pos] << endl;
    }
    
    return 0;
}
