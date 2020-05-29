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
//int minL[110][10010]; //minL[i][j]表示恰好剩余j元的条件下, 起点到城市i最优路径的长度.
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
//    
//    //剪枝(2)
//    
//    if(total_length >= minL[current_city][money_left]){
//        return;
//    }
//    else{
//        minL[current_city][money_left] = total_length;
//    }
//    
//    if(total_length >= shortest_length){ //剪枝(1)
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
//    
//    for(int i = 0; i < 110; i++){
//        for(int j = 0; j < 10010; j++){
//            minL[i][j] = 1 << 30;
//        }
//    }
//    
//    cin >> spend_max >> city_amount >> roads_amount;
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
