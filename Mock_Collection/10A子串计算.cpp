#include<iostream>
#include<cstring>
#include<string>
#include<map>
using namespace std;

string str;
map<string,int> subs;

int main(){
    cin >> str;
    int len = (int)str.size();
    for(int i = 1; i <= len; i++){
        for(int j = 0; j + i <= len; j++){
            subs[str.substr(j, i)] += 1;
        }
    }
    for(auto i = subs.begin(); i != subs.end(); i++){
        if(i->second <= 1){
            continue;
        }
        cout << i->first << " " << i->second << endl;
    }
    
    return 0;
}
