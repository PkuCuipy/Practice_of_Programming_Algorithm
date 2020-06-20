#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> vec;
    cout << vec.capacity() << endl;
    vec.push_back(2);
    vec.pop_back();
    vec.pop_back();
    vec.push_back(3);
    vec.push_back(4);
    
    //初步结论: vector在已经empty的情况下, pop_back似乎并不报错, 但这个时候程序已经出问题了...
    
    return 0;
}
