#include<iostream>
using namespace std;

int main(){
    bool a[20] = {false};
    char* p = (char*)a;
    for(int i = 0; i < 10; i++){
        *(p + i) = i + 'a';
    }
   
    //1.
    cout << "以char形式输出a数组" << endl;
    for(int i = 0; i < 10; i++){
        cout << p[i] << " ";
    }
    cout << endl;
    
    //2.
    cout << "以bool形式输出a数组" << endl;                     static_cast<void>(a); //断点查看用
    for(int i = 0; i < 10; i++){
        if(a[i]){
            cout << "true" << " ";
        }
        else{
            cout << "false" << " ";
        }
    }
    
    // 结论: 在实际运行时, 只看最后一个bit, 1表示true, 0表示false
    // 但断点时, 似乎看了全部bit, 只有全0才false, 否则是true. (这有一点点误导性..)
    
    return 0;
}
