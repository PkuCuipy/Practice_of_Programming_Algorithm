#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
    char s[10];
    cin >> s;
    int len = (int)strlen(s);
    
    do{
        cout << s << endl;
    }
    while(next_permutation(s, s + len));

    return 0;
}
