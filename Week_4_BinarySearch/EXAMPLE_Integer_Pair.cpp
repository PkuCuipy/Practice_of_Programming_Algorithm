#include<iostream>
using namespace std;

struct int_pair{
    int a;
    int b;
};

int BinarySearch(int a[], int size, int p){
    int L = 0; //查找区间的左端点
    int R = size - 1; //查找区间的右端点
    while(L <= R){
        int mid = L + (R - L) / 2; //这个其实就是(L+R)/2 但前者可以防止(L+R)过大造成的溢出
        if(a[mid] == p){
            return mid;
        }
        else if(a[mid] < p){
            L = mid + 1; //设置新的左端点
        }
        else{
            R = mid - 1; //设置新的右端点
        }
    }
    return -1;
}


int_pair find_pair(int m, int* a, int size){
    for(int i = 0; i < size; i++){
        if(BinarySearch(a, size-i-1, m-a[i]) != -1){
            return int_pair{a[i],m-a[i]};
        }
    }
    return int_pair{-1,-1};
}




int main(){
    
    freopen("in.txt","r",stdin);
    
    int n, m;
    cin >> n >> m;
    
    int* a = new int[n+10];
    for(int i = 0; i <= n - 1; i++){
        cin >> a[i];
    }
    
    sort(a, a+n);
    
    int_pair ip = find_pair(m, a, n);
    
    cout << ip.a << endl;
    cout << ip.b << endl;
    
    
    
    return 0;
}
