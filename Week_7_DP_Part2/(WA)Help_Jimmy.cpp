//#include<iostream>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//
//struct Platform{
//    int left;
//    int right;
//    int height;
//};
//
//int min_(int a, int b){
//    if(a < b) return a;
//    return b;
//}
//
//int platform_amount, init_xy, init_h, max_not_die;
//int left_min_time(Platform pfs[], int pf_id);
//int right_min_time(Platform pfs[], int pf_id);
//
//
//int left_min_time_save[1010];
//int right_min_time_save[1010];
//
//
//
//int left_min_time(Platform pfs[], int pf_id){
//    //先找到从左端跳下第一次遇到的平台,或者可能是地面
//    bool finded = false;
//    int next_pf_id = -1;
//    for(int p = pf_id + 1; p <= platform_amount; p++){
//        if(pfs[p].height < pfs[pf_id].height && pfs[p].left <= pfs[pf_id].left && pfs[p].right >= pfs[pf_id].left && pfs[pf_id].height - pfs[p].height <= max_not_die){
//            finded = true;
//            next_pf_id = p;
//            break;
//        }
//    }
//    if(!finded){ //是地面
//        if(pfs[pf_id].height <= max_not_die){
//            return pfs[pf_id].height;
//        }
//        else{
//            return 999999999;
//        }
//    }
//    else{ //找到了
//        int l_min, r_min;
//        if(left_min_time_save[next_pf_id] == -1){
//            l_min = left_min_time(pfs, next_pf_id);
//            left_min_time_save[next_pf_id] = l_min;
//        }
//        else{
//            l_min = left_min_time_save[next_pf_id];
//        }
//        if(right_min_time_save[next_pf_id] == -1){
//            r_min = right_min_time(pfs, next_pf_id);
//            right_min_time_save[next_pf_id] = r_min;
//        }
//        else{
//            r_min = right_min_time_save[next_pf_id];
//        }
//        return pfs[pf_id].height - pfs[next_pf_id].height +
//            min_(l_min + pfs[pf_id].left - pfs[next_pf_id].left,
//                 r_min + pfs[next_pf_id].right - pfs[pf_id].left);
//    }
//}
//
//int right_min_time(Platform pfs[], int pf_id){
//    //先找到从右端跳下第一次遇到的平台,或者可能是地面
//    bool finded = false;
//    int next_pf_id = -1;
//    for(int p = pf_id + 1; p <= platform_amount; p++){
//        if(pfs[p].height < pfs[pf_id].height && pfs[p].left <= pfs[pf_id].right && pfs[p].right >= pfs[pf_id].right && pfs[pf_id].height - pfs[p].height <= max_not_die){
//            finded = true;
//            next_pf_id = p;
//            break;
//        }
//    }
//    if(!finded){ //是地面
//        if(pfs[pf_id].height <= max_not_die){
//            return pfs[pf_id].height;
//        }
//        else{
//            return 999999999;
//        }
//    }
//    else{ //找到了
//        int l_min, r_min;
//        if(left_min_time_save[next_pf_id] == -1){
//            l_min = left_min_time(pfs, next_pf_id);
//            left_min_time_save[next_pf_id] = l_min;
//        }
//        else{
//            l_min = left_min_time_save[next_pf_id];
//        }
//        if(right_min_time_save[next_pf_id] == -1){
//            r_min = right_min_time(pfs, next_pf_id);
//            right_min_time_save[next_pf_id] = r_min;
//        }
//        else{
//            r_min = right_min_time_save[next_pf_id];
//        }
//        return pfs[pf_id].height - pfs[next_pf_id].height +
//            min_(l_min + pfs[pf_id].right - pfs[next_pf_id].left,
//                 r_min + pfs[next_pf_id].right - pfs[pf_id].right);
//    }
//}
//
//
//int main(){
//    int T;
//    cin >> T;
//    for(int t = 1; t <= T; t++){
//        cin >> platform_amount >> init_xy >> init_h >> max_not_die;
//        Platform platforms[1010] = {0};
//        for(int i = 1; i <= platform_amount; i++){
//            cin >> platforms[i].left >> platforms[i].right >> platforms[i].height;
//        }
//        sort(platforms + 1, platforms + platform_amount, [](Platform A, Platform B){return A.height > B.height;});
//        platforms[0] = {init_xy, init_xy, init_h}; //初始位置假想一个平台
//        
//        memset(left_min_time_save, -1, sizeof(left_min_time_save));
//        memset(right_min_time_save, -1, sizeof(right_min_time_save));
//        
//        cout << right_min_time(platforms, 0) << endl;
//        
//        
//    
//        
//        
//    }
//    return 0;
//}
