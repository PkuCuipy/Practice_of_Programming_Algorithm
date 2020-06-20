//#include<iostream>
//#include<cstring>
//#include<queue>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//bool can[15][15]; //can[i][j]表示从i可以飞到j
//int N;
//bool finded;
//bool arrived[15];
//
//
//void dfs(int from){
//    
//    if(finded){ //已经找到了
//        return;
//    }
//    if(from == N){ //已经到了
//        finded = true;
//        return;
//    }
//    
//    if(arrived[from]){
//        return;
//    }
//    arrived[from] = true;
//    
//    
//    for(int i = 1; i <= N; i++){
//        if(can[from][i]){
//            dfs(i);
//        }
//    }
//}
//
//
//
//int main(){
//    int T;
//    cin >> T;
//    
//    while(T--){
//        cin >> N;
//        memset(arrived, false, sizeof(arrived));
//        for(int i = 1; i <= N; i++){
//            for(int j = 1; j <= N; j++){
//                int temp;
//                cin >> temp;
//                if(temp == -1 || temp == 0){
//                    can[i][j] = false;
//                }
//                else{
//                    can[i][j] = true;
//                }
//            }
//        }
//        finded = false;
//        dfs(1);
//        if(finded){
//            cout << "YES" << endl;
//        }
//        else{
//            cout << "NO" << endl;
//        }
//        
//        
//    }
//
//
//
//    return 0;
//}
