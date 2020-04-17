#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

int factor_value();
int term_value();
int expression_value();





//读入一个表达式, 返回其值
int expression_value(){
    int result = term_value(); //求第一项的值
    bool has_more = true;
    while(has_more){
        char op = cin.peek();
        if(op == '+' || op == '-'){
            cin.get();
            int value = term_value(); //求下一项的值
            if(op == '+'){
                result += value;
            }
            else{
                result -= value;
            }
        }
        else{
            has_more = false;
        }
    }
    return result;
}

//项
int term_value(){
    int result = factor_value(); //求第一个因子的值
    while(true){
        char op = cin.peek();
        if(op == '*' || op == '/'){
            cin.get();
            int value = factor_value();
            if(op == '*'){
                result *= value;
            }
            else{
                result /= value;
            }
        }
        else{
            break;
        }
    }
    return result;
}

//因子
int factor_value(){
    int result = 0;
    char c = cin.peek();
    if(c == '('){
        cin.get(); //吃掉 (
        result = expression_value();
        cin.get(); //吃掉 )
    }
    else{
        //读入一个多位整数
        while(isdigit(c)){
            result = 10 * result + (c - '0');
            cin.get();
            c = cin.peek();
        }
    }
    return result;
}



int main(){
    
    cout << expression_value() << endl;
    
    return 0;
}
