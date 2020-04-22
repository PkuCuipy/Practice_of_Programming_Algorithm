#include<iostream>
using namespace std;

//思路:
// (1)将数组分成两半, 分别求出左半边的逆序数 和右半边的逆序数
// (2)再算有多少逆序是由左半边取一个数和右半边取一个数构成(要求在O(n)内完成!)

// 可以在归并排序程序中加入额外的代码来实现


int a[100010] = {0};
int temp[100010] = {0};
long long cnt_reverse = 0;

//对分别已经排序了的前后两部分合并成整个有序数组
void merge(int a[], int s1, int s2, int e, int temp[]){
    
    int p1 = s1;
    int p2 = s2;
    int P = 0;
    while(p1 < s2 && p2 <= e){ //p1和p2都没走到头
        if(a[p1] < a[p2]){
            temp[P++] = a[p1++];
        }
        else{
            temp[P++] = a[p2++];
        }
    }
    
    while(p1 < s2){
        temp[P++] = a[p1++];
    }
    while(p2 <= e){
        temp[P++] = a[p2++];
    }
    
    for(int i = 0; i < P; i++){
        a[s1 + i] = temp[i];
    }
    
}


void count(int a[], int s1, int s2, int e){
    
    int temp_cnt = 0; //统计这两个分别已经从小到大排序了的部分之间的逆序数
    int pL = s1, pR = s2;
    while(pL < s2 && pR < e+1){
        while(pR <= e && a[pR] < a[pL]){
            pR++;
            temp_cnt += (s2 - pL);
        }
        while(pL <= s2 && a[pL] < a[pR]){
            pL++;
        }
    }
    
    //跳出循环说明pLpR至少有一个指向了他所在区间的最后一个元素的下一个元素
    //似乎不需要进行任何补偿!
    
    cnt_reverse += temp_cnt; //统计到总体上去,(其实不用创建temp_cnt,直接加到全局cnt就行,不过为了调试时更方便.)
}


void merge_sort_and_count(int a[], int s, int e, int temp[]){
    
    if(s == e){ //已经排好序了,而且逆序数为0.直接返回~
        return;
    }
    
    merge_sort_and_count(a, s, s+(e-s)/2, temp); //排序并统计第一部分
    merge_sort_and_count(a, s+(e-s)/2+1, e, temp); //排序并统计第二部分
    
    count(a, s, s+(e-s)/2+1, e); //统计这两部分之间的逆序数
    
    merge(a, s, s+(e-s)/2+1, e, temp); //合并两部分
    
}


int main(){
    
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    merge_sort_and_count(a, 0, n - 1, temp);
    
    cout << cnt_reverse << endl;
    

    return 0;
}
