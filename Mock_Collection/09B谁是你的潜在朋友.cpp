#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int book_cnt[210];
vector<int> person_like;

int main(){
    int N, M;
    cin >> N >> M;
    
    //统计每本书有多少人喜欢
    while(N--){
        int temp;
        cin >> temp;
        person_like.push_back(temp);
        book_cnt[temp]++;
    }
    
    //输出: 某人喜欢的这本书 一共被多少人喜欢 (再-1)
    for(auto i = person_like.begin(); i != person_like.end(); i++){
        if(book_cnt[*i] == 1){
            cout << "BeiJu" << endl;
        }else{
            cout << book_cnt[*i] - 1 << endl;
        }
    }
    
    return 0;
}
