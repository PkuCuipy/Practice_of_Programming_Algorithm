//#include<iostream>
//#include<cstring>
//#include<queue>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//struct Point{
//    int x;
//    int y;
//    Point(int x, int y) : x(x), y(y){}
//    Point(){}
//    bool operator < (const Point& another) const{
//        if(y > another.y){
//            return true;
//        }
//        if(y == another.y && x < another.x){
//            return true;
//        }
//        return false;
//    }
//};
//
//int n;
//
//bool check(const vector<Point>& points, int i, int j, int k, int m){
//    //先给四个点排序
//    Point p[4];
//    p[0] = points[i];
//    p[1] = points[j];
//    p[2] = points[k];
//    p[3] = points[m];
//    sort(p, p + 4);
//    
////    if(p[0].x == p[2].x && p[0].y > p[2].y && p[0].y == p[1].y && p[0].x < p[1].x){
////        if(p[3].y == p[2].y && p[3].x > p[2].x && p[3].x == p[1].x && p[3].y < p[1].y){
////            return true;
////        }
////    }
//    
//    if(p[0].y == p[1].y && p[0].x == p[2].x && p[2].y == p[3].y && p[1].x == p[3].x){
//        return true;
//    }
//    return false;
//}
//
//
//
//int main(){
//    int T;
//    cin >> T;
//    while(T--){
//        
//        vector<Point> points;
//        cin >> n;
//        
//        for(int i = 1; i <= n; i++){ //记得保证不重复添加点
//            int x, y;
//            cin >> x >> y;
//            int had = false;
//            for(auto i = points.begin(); i != points.end(); i++){
//                if(i->x == x && i->y == y){
//                    had = true;
//                    break;
//                }
//            }
//            if(!had){
//                points.push_back(Point(x, y));
//            }
//        }
//        
//        int size = (int)points.size();
//        int cnt = 0;
//        
//        for(int i = 0; i < size; i++){
//            for(int j = i + 1; j < size; j++){
//                for(int k = j + 1; k < size; k++){
//                    for(int m = k + 1; m < size; m++){
//                        if(check(points, i, j, k, m)){
//                            cnt++;
//                        }
//                    }
//                }
//            }
//        }
//    
//        cout << cnt << endl;
//        
//    }
//
//
//    return 0;
//}
