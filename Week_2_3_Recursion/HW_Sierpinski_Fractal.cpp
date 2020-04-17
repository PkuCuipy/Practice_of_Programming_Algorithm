#include<iostream>
#include<cstring>
using namespace std;

inline int Pow(int e, int x){
    int result = 1;
    for(int i = 1; i <= x; i++){
        result *= e;
    }
    return result;
}


//save the 'image' of the sierpinski_triangle
char canvas[1100][2200];


void show_canvas(int max_size){
    for(int i = 0; i <= max_size; i++){
        for(int j = 0; j <= max_size * 2; j++){
            cout << canvas[i][j];
        }
        cout << endl;
    }
}



//size is the LEFT_side_length of THIS triangle
//pos(x,y) is the lower_left point of THIS triangle
void draw(int size, int posx, int posy){
    if(size == 1){
        return;
    }
    //left side
    for(int i = posx, j = posy; i > posx - size; i--, j++){
        canvas[i][j] = '/';
    }
    //lower side
    for(int i = posy + 1; i < posy + size * 2; i += 4){
        canvas[posx][i] = '_';
        canvas[posx][i+1] = '_';
    }
    //right side
    for(int i = posx - size + 1, j = posy + size; i <= posx; i++, j++){
        canvas[i][j] = '\\';
    }
    
    draw(size / 2, posx, posy); //left
    draw(size / 2, posx, posy + size); //right
    draw(size / 2, posx - size / 2, posy + size / 2); //up
    
}


int main(){
//    freopen("in.txt", "r", stdin);
    int x;
    while(cin >> x){
        if(x == 0){
            return 0;
        }
        memset(canvas, 0, sizeof(canvas));
        for(int i = 0; i <= 1050; i++){
            for(int j = 0; j <= 2100; j++){
                canvas[i][j] = ' ';
            }
        }
        draw(Pow(2, x), Pow(2, x) - 1, 0);
        show_canvas(Pow(2, x));
    }
    return 0;
}
