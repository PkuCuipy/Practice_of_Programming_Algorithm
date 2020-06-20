#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;


void study(int which, int* lesson, bool* learned, vector<int> next[], vector<int> before[]){
    
    learned[which] = true; //标记为已学习
    for(auto i = next[which].begin(); i != next[which].end(); i++){ //查找潜在的可能继续学习的课
        //如果这门课的全部先修都学过了,就可以学,否则不行
        bool can_study = true;
        for(auto j = before[*i].begin(); j != before[*i].end(); j++){
            if(!learned[*j]){ //有一门先修课没学过,完蛋!
                can_study = false;
                break;
            }
        }
        if(can_study){
            study(*i, lesson, learned, next, before);
        }
    }
}


int main(){
    int n, m;
    while(cin >> n >> m){
        int lesson[1010] = {0};
        bool learned[1010] = {false}; //标记是否学过这门课了
        vector<int> before[1010]; //before[i]存放修i前必修的课程
        vector<int> next[1010]; //next[i]存放修i之后便可以尝试修(因为还可能有别的先修约束呢!)的课程
        
        for(int i = 1; i <= m; i++){
            int then, bef;
            cin >> then >> bef;
            before[then].push_back(bef);
            next[bef].push_back(then);
        }
        
        for(int i = 0; i < n; i++){
            if(before[i].empty()){ //这门课没有先修要求, 从它开始往下学, 能学的都学了!
                study(i, lesson, learned, next, before);
            }
        }
        
        bool all_learned = true;
        for(int i = 0; i < n; i++){
            if(!learned[i]){
                all_learned = false;
                break;
            }
        }
        if(all_learned){
            cout << "True" << endl;
        }
        else{
            cout << "False" << endl;
        }
    }
    return 0;
}
