#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void print_front(int layer){
    for(int i = 1; i <= layer; i++){
        cout << "|     ";
    }
}

int t; //第几轮测试

void print_layer(int layer){ //传入层级, 先输出这一层的文件夹, 再输出这一层的文件
    if(layer == 0 && cin.peek() != '#'){
        cout << "DATA SET " << t << ":\nROOT\n";
    }
    if(cin.peek() == '#'){
        exit(0);
    }
    char name[40];
    vector<string> files;
    while(true){
        cin.getline(name, 35);
        if(name[0] == 'f'){
            files.push_back(string(name));
        }
        else if(name[0] == 'd'){
            print_front(layer + 1);
            cout << name << endl;
            print_layer(layer + 1);
        }
        else if(name[0] == ']' || name[0] == '*'){
            break;
        }
        
    }
    
    if(!files.empty()){
        sort(files.begin(), files.end(), [](string a, string b){return a < b;});
    }
    while(!files.empty()){
        print_front(layer);
        cout << files.front() << endl;
        files.erase(files.begin());
    }
    
    
}



int main(){
    for(t = 1; ; t++){
        print_layer(0);
        cout << endl;
    }
    return 0;
}
