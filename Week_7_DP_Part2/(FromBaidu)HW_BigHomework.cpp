//#include <algorithm>
//#include <cmath>
//#include <cstdio>
//#include <iostream>
//#include <string.h>
//#include <string>
//using namespace std;
//const int MAX = 1 << 16;
//int dp[MAX];  //表示把每一个状态中课程全部完成的最少罚时
//int t[20];    //表示每一门课程的完成时间
//int d[20];    //表示每一门课程的ddl
//int sum[MAX]; //表示某一状态的完成时间总和(很容易求出,加和就完了)
//string name[20];
//string ans[MAX];
//
//int calc(int a, int b){
//    return max(0, a - b);
//}
//
//int main(){
//    int T;
//    cin >> T;
//    while (T--){
//        int n;
//        cin >> n;
//        for (int i = 0; i < n; ++i){
//            cin >> name[i] >> d[i] >> t[i];
//            sum[1 << i] = t[i]; // 二进制第i位储存第i个任务花费时间
//        }
//        for (int i = 1; i < (1 << n); ++i){
//            for (int j = 0; j < n; ++j){
//                if (i & (1 << j)) // 此状态花费时间和，如果判断这一位有第j个任务，则应该加上
//                {
//                    sum[i] = sum[i ^ (1 << j)] + t[j]; // 没有第j个任务的时间+第j个任务的时间
//                    break;
//                }
//            }
//        }
//        dp[0] = 0;
//        for (int i = 0; i < (1 << n); ++i){
//            ans[i] = ""; //初始化
//        }
//
//        // 遍历所有组合，对于每个组合中的那些任务， 如果某个任务放在最后比之前罚时好，那么，答案更新为没有此任务的答案+该任务放在末尾
//        // 之前没有此任务的答案已经是那时候的最优——就是说，前i个任务排列 = max（将每一个试着放在最后），且拿出一个后，少一个的排列已经是最优。
//        for (int i = 1; i < (1 << n); ++i){
//            for (int j = 0; j < n; ++j){
//
//                // 如果 1.任务状态i中含有课程j,且把j排在最后面的罚时比之前的罚时少或者相等 OR 2.现在还没有答案
//                if (i & (1 << j) && (dp[i ^ (1 << j)] + calc(sum[i], d[j]) <= dp[i] || ans[i] == ""))
//                {
//                    // 如果 "比之前少" 或者 "相等但字典序小" 或者 "没有答案", 则放在最后一个 (这一判断仅仅是对上面判断的细化~)
//                    if (dp[i ^ (1 << j)] + calc(sum[i], d[j]) < dp[i]
//                        || ans[i ^ (1 << j)] + name[j] + "\n" < ans[i]
//                        || ans[i] == ""){
//                        ans[i] = ans[i ^ (1 << j)] + name[j] + "\n"; // 回车作为字符，就不用字符串数组了
//                    }
//                    // 这个状态记录下来（记录总罚时），下标的二进制表示含有那些任务
//                    dp[i] = dp[i ^ (1 << j)] + calc(sum[i], d[j]);
//                }
//            }
//        }
//
//
//        cout << dp[(1 << n) - 1] << endl;
//        cout << ans[(1 << n) - 1];
//    }
//
//    return 0;
//}
//
