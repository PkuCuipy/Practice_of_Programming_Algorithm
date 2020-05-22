#include<iostream>
#include<algorithm>
using namespace std;

int N; //课程数目
string name[15]; //课程名称
int ddl[15]; //每个大作业还有多少天就要扣分
int each_time[15]; //每个大作业所需时间
int dp[1 << 15]; //dp[i]表示把i写成二进制后,低N位代表的课程的所有排列中,最小的罚时.
string ans[1 << 15]; //ans[i]表示把i写成二进制后,低N位代表的课程的所有排列中,最小的罚时对应的课程排列(如:Math\nEnglish\nChinese).
int time_sum[1 << 15]; //time_sum[i]表示把i写成二进制后,低N位代表的全部课程的大作业所需的总时间.

int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> name[i] >> ddl[i] >> each_time[i];
        }
        //先计算time_sum[],注意此处可以(稍微?)省时间
        time_sum[0] = 0;
        for(int i = 1; i < (1 << N); i++){
            for(int j = 0; j < N; j++){
                if(i & (1 << j)){
                    time_sum[i] = time_sum[i ^ (1 << j)] + each_time[j];
                }
            }
        }
        //初始化ans[]
        for(int i = 0; i < (1 << N); i++){
            ans[i] = "";
        }
        
        /*
         分析: 假设一共6门课:语数英物化生
         如果对于<=4门课的任何课程排列,我们都已经获得了最优解
         那么,如果我们想知道某种5门课的排列i(用二进制视角来看i)的最优解,
         只需要枚举i中的这5门课,尝试把每一门课的作业放在最后来做,那么最优解一定就从这5种枚举中取得
         (证明:如果某个解是这5门课的最优解,那么这个解去掉最后一门课,则是相应4门课的排列的最优解;而这种4门的最优解我们全部枚举了!)
         */
        
        dp[0] = 0;
        for(int i = 1; i < (1 << N); i++){
            for(int j = 0; j < N; j++){ //枚举把第j门课放到最后去做
                if((i & (1 << j)) == 0){continue;} //当然首先排列i中得有j这门课,没有就枚举下一门课了
                
                /*
                 所谓更优解,
                 (0)要么是在还从未计算过罚时的情况下的任意解;
                 (1)要么是罚时更短了;
                 (注:由于枚举的是把这门课放在最后,所以罚时很容易计算:
                 假设是5门课的i’去掉一门课到4门课i“的情况,则: 罚时‘ = 罚时“ + max{time_sum[i‘] - ddl[i‘], 0})
                 (2)要么罚时一样,但字典序更低(这要求我们需要存储当前最优排列的字典序).
                 */
                
                if(ans[i] == ""){ // (1)
                    ans[i] = ans[i ^ (1 << j)] + name[j] + "\n";
                    dp[i] = dp[i ^ (1 << j)] + max(time_sum[i] - ddl[j], 0);
                }
                else if(dp[i ^ (1 << j)] + max(time_sum[i] - ddl[j], 0) < dp[i]){ // (2)
                    ans[i] = ans[i ^ (1 << j)] + name[j] + "\n";
                    dp[i] = dp[i ^ (1 << j)] + max(time_sum[i] - ddl[j], 0);
                }
                else if(dp[i ^ (1 << j)] + max(time_sum[i] - ddl[j], 0) == dp[i] && ans[i ^ (1 << j)] < ans[i]){ //(3)
                    ans[i] = ans[i ^ (1 << j)] + name[j] + "\n";
                    dp[i] = dp[i ^ (1 << j)] + max(time_sum[i] - ddl[j], 0);
                }
                
            }
        }
        
        //输出 11...111 对应的结果
        cout << dp[(1 << N) - 1] << endl;
        cout << ans[(1 << N) - 1];
        
        
        
    }
    
    return 0;
}
