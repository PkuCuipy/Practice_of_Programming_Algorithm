#include<iostream>
#include<vector>
using namespace std;

struct Info{
    int destination;
    int length;
    int toll;
    Info(int d = 1, int l = 1, int t = (1 << 30)): destination(d), length(l), toll(t){}
};

int spend_max;
int city_amount;
int roads_amount;

vector<vector<Info> > cities(1);

int shortest_length = (1 << 30);


void search(int current_city, int money_left, int total_length, int from){
    if(money_left < 0){
        return;
    }
    if(current_city == city_amount){
        if(total_length < shortest_length){
            shortest_length = total_length;
        }
        return;
    }
    for(auto i = cities[current_city].begin(); i != cities[current_city].end(); i++){
        if(i->destination == from){
            continue;
        }
        search(i->destination, money_left - i->toll, total_length + i->length, current_city);
    }
}


int main(){
    cin >> spend_max >> city_amount >> roads_amount;
    for(int i = 1; i <= city_amount; i++){
        cities.push_back(vector<Info>());
    }
    for(int i = 1; i <= roads_amount; i++){
        int source, destination, length, toll;
        cin >> source >> destination >> length >> toll;
        cities[source].push_back(Info(destination, length, toll));
    }
    search(1, spend_max, 0, 0);
    
    if(shortest_length == (1 << 30)){
        cout << "-1" << endl;
    }
    else{
        cout << shortest_length << endl;
    }
    
    
    return 0;
}
