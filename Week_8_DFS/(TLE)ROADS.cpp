//#include<iostream>
//#include<vector>
//using namespace std;
//
//struct Road{
//    int destination;
//    int length;
//    int toll;
//    Road(int d = 1, int l = 1, int t = (1 << 30)): destination(d), length(l), toll(t){}
//} roads[10010];
//
//int spend_max;
//int city_amount;
//int roads_amount;
//
//vector<vector<Road> > cities(110);
//
//int shortest_length = (1 << 30);
//
//
//void search(int current_city, int money_left, int total_length, bool* visited){
//    if(money_left < 0){
//        return;
//    }
//    if(visited[current_city]){
//        return;
//    }
//    if(current_city == city_amount){
//        if(total_length < shortest_length){
//            shortest_length = total_length;
//        }
//        return;
//    }
//    for(int i = 0; i < cities[current_city].size(); i++){
//        Road r = cities[current_city][i];
//        visited[current_city] = true;
//        search(r.destination, money_left - r.toll, total_length + r.length, visited);
//        visited[current_city] = false;
//    }
//}
//
//
//int main(){
//    cin >> spend_max >> city_amount >> roads_amount;
//    
//    for(int i = 1; i <= roads_amount; i++){
//        int source, destination, length, toll;
//        cin >> source >> destination >> length >> toll;
//        if(source != city_amount){
//            cities[source].push_back(Road(destination, length, toll));
//        }
//    }
//    bool visited[110] = {false};
//    search(1, spend_max, 0, visited);
//
//    if(shortest_length == (1 << 30)){
//        cout << "-1" << endl;
//    }
//    else{
//        cout << shortest_length << endl;
//    }
//
//
//    return 0;
//}
