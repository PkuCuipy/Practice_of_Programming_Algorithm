#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

//给定一个很大很大的数组, 要求输出前m大的数(从小到大输出)
//思路: 把前m大的都弄到数组最右边, 然后对这最右边m个元素排序后输出
// (注: 如果全部排序再输出,复杂度是 nlogn,而上面的思路的复杂度是 n+mlogm, 当m比n小很多时速度明显更快)

//void arrange_right(k)
//(1)设 key = a[0] , 把key挪到适当位置, 使得比key小的元素都在key左边,比key大的都在key右边(同快速排序里的方法!O(n)的)
//(2)判断这之后key的位置, 记key和key右边的元素总个数为a,左边为b;
// 若 a < k, 说明key和key右边都可以, 但不够, 也就是左边还需要(k-b)个, 所以对左侧进行操作a_r(k-b);
// 若 a > k, 说明key右边太多了, 所以继续对右侧进行a_r(k)
// 若 a = k, 说明刚刚好! 结束~

inline void swap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}

void arrange_right(int a[], int s, int e, int k){
    
    if(s >= e){
        return;
    }
    
    int pL = s, pR = e;
    while(pL != pR){
        while(pR > pL && a[pR] >= a[pL]){
            pR--;
        }
        swap(a[pL], a[pR]);
        while(pR > pL && a[pL] <= a[pR]){
            pL++;
        }
        swap(a[pL], a[pR]);
    }
    
    if(e - pL + 1 == k || e - pL == k){
        return;
    }
    else if(e - pL + 1 < k){ //不够 还得从左边继续找
        arrange_right(a, s, pL - 1, k - (e-pL+1));
    }
    else{ //太多了 右边需要继续精细一些
        arrange_right(a, pL + 1, e, k);
    }
    
}


int main(){
    int n;
    cin >> n;
    int a[100010] = {0};
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int k;
    cin >> k;
    arrange_right(a, 0, n - 1, k);
    
    sort(a+n-k, a+n, greater<int>());
    
    for(int i = n-k; i < n; i++){
        cout << a[i] << endl;
    }
    
    return 0;
}
