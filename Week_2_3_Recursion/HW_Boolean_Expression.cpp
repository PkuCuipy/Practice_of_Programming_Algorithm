#include<iostream>
using namespace std;

//使cin.peek()到的东西属于{&,|,!,F,V,(,)} 不吃回车和EOF!
void eat(){
    char peek = cin.peek();
    while(peek != EOF && peek != '\n' && peek != '&' && peek != '|' && peek != '!' && peek != 'F' && peek != 'V' && peek != '(' && peek != ')'){
        cin.get();
        peek = cin.peek();
    }
//    cout << (char)cin.peek();
    
}

bool get_expression();
bool get_term();
bool get_factor();

bool get_expression(){
    eat();
    bool result = get_term();
    while(true){
        eat();
        if(cin.peek() == '|'){
            cin.get();
            bool _ = get_term();
            result = result || _;
        }
        else{
            break;
        }
    }
    return result;
}

bool get_term(){
    eat();
    bool result = get_factor();
    
    while(true){
        eat();
        if(cin.peek() == '&'){
            cin.get();
            bool _ = get_factor();
            result = result && _;
        }
        else{
            break;
        }
    }
    return result;
}

bool get_factor(){
    eat();
    bool result;
    char peek = cin.peek();
    if(peek == '!'){
        cin.get();
        result = !get_factor();
    }
    else if(peek == '('){
        cin.get();
        result = get_expression();
        eat();
        cin.get();
    }
    else{
        cin.get();
        switch(peek){
            case 'V': result = true; break;
            case 'F': result = false; break;
            default: result = true; cout << "error" << endl; break;
        }
    }
    return result;
}



int main(){
    int test = 0;
    char temp;
    while(true){
        temp = cin.get();
        if(temp == EOF){
            break;
        }
        cin.putback(temp);
        
        test++;
        bool result = get_expression();
        cout << "Expression " << test << ": ";
        if(result){
            cout << "V\n";
        }
        else{
            cout << "F\n";
        }
        
        cin.get();
    }
    
    return 0;
}
