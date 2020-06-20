#include<iostream>
#include<cstring>
using namespace std;

int maze[7][7];

struct Node{
    int x;
    int y;
    Node* from;
    int steps;
    Node(int x = 0, int y = 0, Node* from = NULL, int steps = 0):x(x),y(y),from(from),steps(steps){}
};

Node queue[30];
Node* head; //指向第一个元素
Node* tail; //指向最后一个元素自身
Node best(0,0,NULL,100);

void printr(Node* n){
    if(n->from != NULL){
        printr(n->from);
    }
    cout << "(" << n->x - 1 << ", " << n->y - 1 << ")\n";
}

int main(){
    memset(maze, -1, sizeof(maze));
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 5; j++){
            cin >> maze[i][j];
        }
    }
    head = queue;
    tail = queue;
    queue[0] = Node(1, 1, NULL, 0);
    while(head <= tail){
        if(head->x == 5 && head->y == 5){ //找到了
            if(head->steps < best.steps){
                best = *head;
            }
            head++;
        }
        else{ //这个节点向周围扩展
            maze[head->x][head->y] = 2; //标记为走过
            if(maze[head->x + 1][head->y] == 0){
                tail++;
                *tail = Node(head->x + 1, head->y, head, head->steps + 1);
            }
            if(maze[head->x - 1][head->y] == 0){
                tail++;
                *tail = Node(head->x - 1, head->y, head, head->steps + 1);
            }
            if(maze[head->x][head->y + 1] == 0){
                tail++;
                *tail = Node(head->x, head->y + 1, head, head->steps + 1);
            }
            if(maze[head->x][head->y - 1] == 0){
                tail++;
                *tail = Node(head->x, head->y - 1, head, head->steps + 1);
            }
            head++; //“删除”这个节点
        }
    }


    printr(&best);


    return 0;
}
