#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int maze[10][10];
int min_len = 1 << 30;

struct point{
    int x;
    int y;
    point(int x, int y): x(x), y(y){}
};

vector<point> best_way;
vector<point> way;

void dfs(int x, int y, int steps){
    way.push_back(point(x, y));
    if(x == 5 && y == 5){
        if(steps < min_len){
            min_len = steps;
            best_way.assign(way.begin(), way.end());
        }
        way.pop_back();
        return;
    }
    if(maze[x-1][y] == 0){
        maze[x-1][y] = 1;
        dfs(x-1, y, steps+1);
        maze[x-1][y] = 0;
    }
    if(maze[x+1][y] == 0){
        maze[x+1][y] = 1;
        dfs(x+1, y, steps+1);
        maze[x+1][y] = 0;
    }
    if(maze[x][y-1] == 0){
        maze[x][y-1] = 1;
        dfs(x, y-1, steps+1);
        maze[x][y-1] = 0;
    }
    if(maze[x][y+1] == 0){
        maze[x][y+1] = 1;
        dfs(x, y+1, steps+1);
        maze[x][y+1] = 0;
    }
    way.pop_back();
}


int main(){
    memset(maze, -1, sizeof(maze));
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 5; j++){
            cin >> maze[i][j];
        }
    }

    dfs(1, 1, 0);

    for(int i = 0; i < best_way.size(); i++){
        cout << "(";
        cout << best_way[i].x - 1 << ", " << best_way[i].y - 1;
        cout << ")\n";
    }



    return 0;
}
