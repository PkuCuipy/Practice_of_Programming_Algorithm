#include<iostream>
using namespace std;

double notation(){ //这种写法可以先直接读如一个string 然后判断第0位, 是运算符就递归, 不是就用atof(str.c_str())
    
    if(cin.peek() == ' '){
        cin.get(); //吃掉空格
    }
    
    if(cin.peek() == '+'){
        cin.get(); //吃掉运算符
        return notation() + notation();
    }
    else if(cin.peek() == '-'){
        cin.get(); //吃掉运算符
        return notation() - notation();
    }
    else if(cin.peek() == '*'){
        cin.get(); //吃掉运算符
        return notation() * notation();
    }
    else if(cin.peek() == '/'){
        cin.get(); //吃掉运算符
        return notation() / notation();
    }
    else{
        double expr;
        cin >> expr;
        return expr;
    }
}

int main(){
    
    cout << notation();
    
    
    
    return 0;
}
