#include<iostream>
#include<cstring>
using namespace std;

int R;
int N;
int L, T, W, H;
long long S[1000010]; //S[i]表示[i,i+1]的面积
long long Sum[1000010]; //Sum[i]表示[0,i]的总面积


int main(){
    cin >> R >> N;
    for(int t = 1; t <= N; t++){
        cin >> L >> T >> W >> H;
        for(int i = L; i <= L + W - 1; i++){
            S[i] += H;
        }
    }
    long long temp = 0;
    Sum[0] = 0;
    for(int i = 0; i < R; i++){
        temp += S[i];
        Sum[i+1] = temp;
    }
    //ok,现在[a,b]的面积 = Sum[b] - Sum[a]
    //[0,b]的面积 = Sum[b]
    //[a,R]的面积 = Sum[R] - Sum[a]
    //下面从{0,1,2,...,R-1}中寻找一个i使得 2 * Sum[i] - Sum[R] >= 0
    int l = 0, r = R, m = 0;
    while(r != l){
        m = l + (r-l)/2;
        if(2 * Sum[m] - Sum[R] >= 0){
            r = m;
//            r = m - 1; //这里m是符合题意的!不能轻易-1,否则就WA了
        }
        else{
            l = m + 1; //此时的m不符合题意,才要+1
        }
    }
    //然后尝试右移i找到最大的那个
    long long diff = 2 * Sum[l] - Sum[R];
    int i;
    for(i = m; i <= R; i++){
        if(2 * Sum[i+1] - Sum[R] != diff){
            break;
        }
    }
    cout << i << endl;
    
    return 0;
}
