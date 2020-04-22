//#include<iostream>
//using namespace std;
//
//int main(){
//    
//    int N;
//    cin >> N;
//    int min_stickers = N * N * N;
//    
//    //枚举长宽高abc
//    for(int i = 1; i <= N; i++){
//        for(int j = 1; j <= N/i; j++){
//            int k = N / i / j;
//            if(i * j * k != N){
//                continue;
//            }
//            else{
//                int temp_stickers = i*j + j*k + i*k;
//                temp_stickers *= 2;
//                if(temp_stickers < min_stickers){
//                    min_stickers = temp_stickers;
//                }
//            }
//            
//        }
//    }
//    
//    cout << min_stickers << endl;
//    
//    
//    
//    return 0;
//}
