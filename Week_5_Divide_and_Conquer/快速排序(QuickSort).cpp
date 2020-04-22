//#include<iostream>
//using namespace std;
//
////数组两端用i j指针, ... , 注意在过程中始终有一个指针指向最开始的a[0](记为k) 直到最后i和j碰到一块(都指向k)
//
//void swap(int& a, int& b){
//    int temp = a;
//    a = b;
//    b = temp;
//}
//
//
//void quick_sort(int a[], int s, int e){
//    if(s >= e){
//        return;
//    }
//    int k = a[s];
//    int i = s, j = e; //两个分别指向端点的指针
//    while(i != j){
//        
//        while(j > i && a[j] >= k){ //挪动右指针
//            --j;
//        }
//        swap(a[i], a[j]);
//        
//        while(i < j && a[i] <= k){ //挪动左指针
//            ++i;
//        }
//        swap(a[i], a[j]);
//    }
//    
//    //处理完毕, 此时数组依据k被分为两个部分, 分别快排这两个部分(中间那个就不用再排序了~, 否则长度为1时也会死循环)
//    quick_sort(a, s, i - 1);
//    quick_sort(a, i + 1, e);
//    
//}
//
//
//
//int main(){
//    int a[10] = {13, 27, 19, 2, 8, 12, 2, 8, 30, 89};
//    quick_sort(a, 0, 9);
//    for(int i = 0; i <= 9; i++){
//        cout << a[i] << ", ";
//    }
//    
//    return 0;
//}
