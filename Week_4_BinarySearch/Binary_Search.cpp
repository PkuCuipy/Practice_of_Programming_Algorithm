//#include<iostream>
//using namespace std;
//
////从包含size个元素“从小到大排序了的”int数组a[]中查找元素p,返回该元素的下标,如果找不到,返回-1
//int BinarySearch(int a[], int size, int p){
//    int L = 0; //查找区间的左端点
//    int R = size - 1; //查找区间的右端点
//    while(L <= R){
//        int mid = L + (R - L) / 2; //这个其实就是(L+R)/2 但前者可以防止(L+R)过大造成的溢出
//        if(a[mid] == p){
//            return mid;
//        }
//        else if(a[mid] < p){
//            L = mid + 1; //设置新的左端点
//        }
//        else{
//            R = mid - 1; //设置新的右端点
//        }
//    }
//    return -1;
//}
//
//
////在包含size个元素、从小到大排序了的、int数组a[]中查找比给定整数p小的、下标最大的元素,返回其下标, 找不到则返回-1
//int LowerBound(int a[], int size, int p){
//    int L = 0;
//    int R = size - 1;
//    int lastPos = -1; //到目前为止找到的最优解
//    while(L <= R){
//        int mid = L + (R - L) / 2;
//        if(a[mid] >= p){
//            R = mid - 1;
//        }
//        else{
//            lastPos = mid;
//            L = mid + 1;
//        }
//    }
//    return lastPos;
//}
//
//int main(){
//    
//    int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
//    cout << BinarySearch(a, 14, 8) << endl;
//    cout << LowerBound(a, 14, 8) << endl;
//    
//    
//    return 0;
//}
