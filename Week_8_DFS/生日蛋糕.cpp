//#include<iostream>
//#include<vector>
//#include<cstring>
//#include<cmath>
//using namespace std;
//
///**
// 
// 剪枝:
// 1.最优性剪枝: 搭建过程中发现已建好的面积已经超过目前求得的最优表面积
//            或者“预见到”将会超过, 则停止搭建
// 2.可行性剪枝: 预见到再往上搭, 高度已经无法安排, 或者半径已经无法安排, 则停止搭建.
//            或者 还没搭建的那些层的体积一定会“超过”还缺的体积
//            或者 还没搭建的那些层的体积一定“无法达到”还缺的体积
// 
// [注]: 一个n层的蛋糕的“最大体积”、“最小体积”、“最大表面积”、“最小表面积”应该预先算好存在数组里, 避免重复计算.
// 
// */
//
//
//
//int N, M;
//int minArea = 1 << 30; //最优表面积
//int area = 0; //正在搭建中的蛋糕的表面积
//
//
////要用n层去凑体积为v,最底层半径不超过r,高度不超过h的蛋糕
////最小表面积放入minArea
//void dfs(int v, int n, int r, int h){
//    if(n == 0){
//        if(v == 0){
//            minArea = min(minArea, area);
//            return;
//        }
//        else{
//            return;
//        }
//    }
//    if(v <= 0){
//        return;
//    }
//    for(int rr = r; rr >= n; rr--){ //枚举“这个部分的”底层半径
//        if(n == M){
//            area = rr * rr; //如果枚举的是“整个蛋糕的”最底层,则从上面俯视的表面积为 rr * rr
//        }
//        for(int hh = h; hh >= n; hh--){ //枚举“这个部分的”底层高度
//            area += 2 * rr * hh;
//            dfs(v - rr * rr * hh, n - 1, rr - 1, hh - 1);
//            area -= 2 * rr * hh;
//        }
//    }
//    
//    
//}
//
//
//int main(){
//    
//    //数据读取也没写
//    //这里没有写,自行估计
//    int maxR;
//    int maxH;
//    dfs(N, M, maxR, maxH);
//    if(minArea == 1 << 30){
//        cout << 0 << endl;
//    }
//    else{
//        cout << minArea << endl;
//    }
//    
//    
//    return 0;
//}
