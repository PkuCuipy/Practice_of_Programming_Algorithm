//#include<iostream>
//#include<cstring>
//using namespace std;
//
//long long CNT = 0;
//int N;
//int dist[20][20];
//bool arrived[20] = {false};
//int best_total_time = 1 << 30;
//int state_best_time[18][1 << 17]; //这一状态的最优时间
//
//void dfs(int current, int time_sum, int island_cnt, int state){ //state的二进制形式表示已经走过的岛屿统计
//    CNT++;
//    if(island_cnt == N - 1){ //那就只剩下终点没去过了!
//        if(time_sum + dist[current][N] < best_total_time){
//            best_total_time = time_sum + dist[current][N];
//        }
//        return;
//    }
//        
//    //如果已经超过最好时间了,返回
//    if(time_sum > best_total_time){
//        return;
//    }
//    //如果这次搜索不是当前状态的最优时间,return;否则记录这个最优时间
//    if(state_best_time[current][state] < time_sum){
//        return;
//    }
//    else{
//        state_best_time[current][state] = time_sum;
//    }
//    
//    
//    for(int i = 2; i < N; i++){ //枚举每个没到过的除了起点终点的岛屿
//        if(arrived[i]) continue;
//        arrived[i] = true;
//        dfs(i, time_sum + dist[current][i], island_cnt + 1, (state | (1 << current)));
//        arrived[i] = false;
//    }
//}
//
//
//int main(){
//    freopen("in.txt","r",stdin);
//    cin >> N;
//    for(int i = 1; i <= N; i++){
//        for(int j = 1; j <= N; j++){
//            cin >> dist[i][j];
//        }
//    }
//    memset(state_best_time, 0x7f, sizeof(state_best_time));
//    
//    dfs(1, 0, 1, 1<<1);
//    cout << best_total_time << endl;
//    
//    cout << CNT << "!";
//    return 0;
//}
