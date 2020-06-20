#include<iostream>
#include<cstring>
using namespace std;



void Merge(int a[], int s, int m, int e, int temp[]){ //将两个有序片段[s,m]和[m+1,e]合并成整体有序的[s,e]
    int pt = 0; //temp[]中“指针“
    int p1 = s; //a的第一片段”指针“
    int p2 = m + 1; //a的第二片段”指针“
    
    while(p1 <= m && p2 <= e){ //p1,p2都没走到尽头
        if(a[p1] < a[p2]){
            temp[pt++] = a[p1++];
        }
        else{
            temp[pt++] = a[p2++];
        }
    }
    while(p1 <= m){ //如果p1还没走到尽头
        temp[pt++] = a[p1++];
    }
    while(p2 <= e){ //如果p2还没走到尽头
        temp[pt++] = a[p2++];
    }
    memcpy(a+s, temp, (e-s+1) * sizeof(int)); //将temp的[0, e - s]拷贝到a的[s, e]去
}

void MergeSort(int a[], int s, int e, int temp[]){ //排序a数组的[s,e]元素, 借用temp[]作为临时空间
    if(s == e){return;} //只有一个元素本来就“排好序了”
    else{
        int m = s + (e - s) / 2; //查找中间点
        MergeSort(a, s, m, temp); //前半段排序
        MergeSort(a, m + 1, e, temp); //后半段排序
        Merge(a, s, m, e, temp); //将两个有序片段[a,m]和[m+1,s]合并成整体有序的[a,s]
    }
}


int main(){
    
    
    return 0;
}
