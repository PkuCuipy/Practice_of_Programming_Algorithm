#include<iostream>
using namespace std;


int N, NA, NB;
int A_score = 0;
int B_score = 0;
char A_regular[110];
char B_regular[110];



inline char A_next(){
    static int p_A = 0;
    return A_regular[(p_A++) % NA];
}

inline char B_next(){
    static int p_B = 0;
    return B_regular[(p_B++) % NB];
}

inline void calc_score(char A, char B){
    if(A == B){
        return;
    }
    else if(A == '5'){
        if(B == '2'){
            B_score++;
            return;
        }
        else{
            A_score++;
            return;
        }
    }
    else if(A == '2'){
        if(B == '5'){
            A_score++;
        }
        else{
            B_score++;
        }
    }
    else if(A == '0'){
        if(B == '2'){
            A_score++;
        }
        else{
            B_score++;
        }
    }
    
}


int main(){
    cin >> N >> NA >> NB;
    
    for(int i = 0; i < NA; i++){
        cin >> A_regular[i];
    }
    
    for(int i = 0; i < NB; i++){
        cin >> B_regular[i];
    }
    
    for(int i = 1; i <= N; i++){
        calc_score(A_next(), B_next());
    }
    
    
    
    if(A_score > B_score){
        cout << "A\n";
    }
    else if( A_score < B_score){
        cout << "B\n";
    }
    else{
        cout << "draw\n";
    }
    
    return 0;
}

