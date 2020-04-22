#include<iostream>
using namespace std;


//将数组a的局部[s,m]和[m+1,e]合并到temp[],保证temp有序,然后再拷贝回a[s,m]
void merge(int a[], int s, int m, int e, int temp[]){
    int pb = 0; //在temp[]中使用的“指针”
    int p1 = s; //在第一段[]中使用的“指针”
    int p2 = m + 1; //在第二段[]中使用的“指针”
    while(p1 <= m && p2 <= e){ //两个只要有一个走到尽头就跳出循环
        if(a[p1] < a[p2]){
            temp[pb++] = a[p1++];
        }
        else{
            temp[pb++] = a[p2++];
        }
    }
    
    while(p1 <= m){ //if: p1没走到头
        temp[pb++] = a[p1++];
    }
    while(p2 <= e){ //else: p2没走到头
        temp[pb++] = a[p2++];
    }
    
    //从temp[]拷贝回a[]
    memcpy(a + s, temp, (e-s+1) * sizeof(int));
    
}

//从a[s]到 [e]进行排序(包括这两个元素),会用到temp[]作为中间量
void merge_sort(int a[], int s, int e, int temp[]){
    if(s < e){
        int m = s + (e - s) / 2;
        merge_sort(a, s, m, temp); //前一半排序
        merge_sort(a, m + 1, e, temp); //后一半排序
        merge(a, s, m, e, temp); //前后两半进行归并
        
    }
    
    
}

int a[10] = {13, 27, 19, 2, 8, 12, 2, 8, 30, 89};
int b[10];

int main(){
    
    int size = sizeof(a)/sizeof(int);
    merge_sort(a, 0, size-1, b);
    for(int i = 0; i < size; i++){
        cout << a[i] << ", ";
    }
    cout << endl;
    
    return 0;
}
