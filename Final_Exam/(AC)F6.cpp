//#include<iostream>
//#include<cstring>
//#include<queue>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//inline int ceil(int x, int y){
//    if(x % y == 0){
//        return x / y;
//    }
//    return x / y + 1;
//}
//
//
//int N, M;
//int w[10010];
//
//int check(int x){
//    int ans = 0;
//    for(int i = 1; i <= N; i++){
//        ans += ceil(w[i], x);
//    }
//    return ans;
//}
//
//
//
//
//
//int main(){
//
//    cin >> N >> M;
//    for(int i = 1; i <= N; i++){
//        cin >> w[i];
//    }
//        
//    int L = 1;
//    int R = 10000010;
//    
//    int last = R;
//    
//    while(L <= R){
//        int m = L + (R-L)/2;
//        if(check(m) <= M){
//            R = m - 1;
//            last = m;
//        }
//        else{
//            L = m + 1;
//        }
//    }
//    while(check(last) > M && L < N){
//        last++;
//    }
//    while(check(last - 1) <= M && last - 1 >= 1){
//        last--;
//    }
//    cout << last << endl;
//    
//
//    return 0;
//}
