#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include"time.h"
#include<vector>
#include "MahjongGB/MahjongGB.h"
using namespace std;

#define FUSHI
#define LUFU 1

//“值-权”对
template <class T1, class T2>
struct val_wei{
    T1 val;
    T2 wei;
};


//全局变量
vector<string> sys_request; //系统输入
vector<string> my_response; //我的历史回应
int myID; //座位号
int turn; //当前轮数
int fengquan; //风圈
int hua_amount[4]; //每个人手中花牌数(没用)
vector<string> hand; //自己手中的暗牌
vector<pair<string, pair<string, int> > > pack; //自己公开区的牌,包括暗杠(int=0)
int shoupai[77] = {0};  //我的手牌(hand)使用int编号进行统计(不包括装备区的牌!!)
int hand_and_pack[77] = {0}; //我的手牌(hand)和装备区(pack)的牌的统计
int paichi[77] = {0};   //牌池: 还可能摸到的牌的统计
void init_paichi();     //初始化牌池,每牌4张
int mingpai_cnt = 0; //决定是否开启全求人模式(如果装备区域明牌>=3个,开启模式)

//函数声明
int str2num(const string& card); //string牌转化为数字 1-9B 21-29T 41-49W 61.63.65.67F 71.73.75J
string num2str(int card_id); //数字转化为string牌 1-9B 21-29T 41-49W 61.63.65.67F 71.73.75J
void raise_error(){cout << "ERROR" << endl;} //报错函数
void myplay(const string card); //从hand中打出一张牌
void mydraw(const string card); //摸一张牌到hand
void mychi(const string card_from_others, const string card_chi_m, const string card_abandon); //吃card
void mypeng(const string card_peng_m, const string card_abandon); //碰card
void mygang(const string card_gang_m, bool from_others); //明暗杠card
void mybugang(const string card_bugang_m); //补杠


#ifdef FUSHI //复式
int pai_wall[4];
void init_pai_wall(){for(int i = 0; i <= 3; i++) pai_wall[i] = 34 - 13;}
//如果牌源玩家的下一家牌墙空了,则这张牌不能用于吃碰杠,只能用于HU
bool get_my_chipenggang_illegality(int playerid_of_paiSource){
    if(pai_wall[(playerid_of_paiSource+1) % 4] == 0){return false;}
    else {return true;}
}
#endif


//判断某个ID是否为自己(myID)的上家
bool is_my_shangjia(int his_id){
    return (his_id + 1) % 4 == myID;
}





const int Weights[4] = {12,10,-100,6};//顺子刻子单牌将牌权重
struct info{
    int shunzi = 0, kezi = 0, danpai = 0, jiangpai = 0;
    bool find_hu = false;
    vector<int> m_pai_of_shunzi;
    int evaluate_score() const{
        return Weights[0] * shunzi + Weights[1] * kezi + Weights[2] * danpai + Weights[3] * jiangpai;
    }
    bool operator < (const info& another){
        int score = evaluate_score();
        int another_score = another.evaluate_score();
        return (score < another_score);
    }
};

info best_info{0, 0, 20, 0, false}; //使用前请初始化best_info到当前状态

val_wei<int, int> not_sk_pai[77]; //cnt_skd的“返回值”
void cnt_skd(int shun_s, int ke_s, info& temp_info){
    for(int i = shun_s; i <= 49; i++){ //枚举可能的顺子
        if(shoupai[i] && shoupai[i+1] && shoupai[i+2]){
            temp_info.shunzi++;
            shoupai[i]--; shoupai[i+1]--; shoupai[i+2]--;
            temp_info.m_pai_of_shunzi.push_back(i+1);
            cnt_skd(i, 1, temp_info); //【递归】
            temp_info.m_pai_of_shunzi.pop_back();
            temp_info.shunzi--;
            shoupai[i]++; shoupai[i+1]++; shoupai[i+2]++;
        }
    }
    for(int i = ke_s; i <= 75; i++){ //枚举可能的刻子
        if(shoupai[i] == 3){
            temp_info.kezi++;
            shoupai[i] -= 3;
            cnt_skd(1, i + 1, temp_info); //【递归】
            temp_info.kezi--;
            shoupai[i] += 3;
        }
    }
    
    //如果走到这了,说明剩下的都是单牌或将牌了...(可能有2、5、8、11、14张)
    //那么加上单牌后,temp_info就是这一轮划分的结果,和best_info做比对,取最好值.
    for(int i = 1; i <= 75; i++){
        if(shoupai[i]){
            if(shoupai[i] == 1){
                temp_info.danpai++;
            }
            else if(shoupai[i] == 2){
                temp_info.jiangpai++;
            }
        }
    }
    //    cout << temp_info.evaluate_score() << endl;
    //评估分数与目前最优解进行比较
    if(best_info < temp_info){
        //当前是最优解
        best_info = temp_info;
        //修改best_info下的not_sk_pai[]
        for(int i = 0; i <= 75; i++){
            not_sk_pai[i].val = shoupai[i];
            not_sk_pai[i].wei = 0;
        }
    }
    //没有单牌,一对将牌,和了(当然,可能是错和)
    if(temp_info.danpai == 0 && temp_info.jiangpai == 1){
        temp_info.find_hu = true;
        best_info.find_hu = true;
    }
    
    temp_info.danpai = 0;
    temp_info.jiangpai = 0;
}




string decide_abondon_card(){
    //先调用cnt_skd(),它会给出最佳的手牌分割,以及这种分割对应的手中的单牌的集合
    info temp_info{0,0,0,0,false};
    best_info = {0,0,20,0,false};
    cnt_skd(1, 1, temp_info);
    //接下来按照 **一系列标准** 改变 not_sk_pai 中value非0的牌的权值, 挑出权值[最低]的打出
    // **(奖励好性质,不惩罚差性质,差的自然分数低)标准**
    //1.BTW牌是将牌!         权值升高  +250/将牌对数
    //1.1. FJ牌是将牌!         权值升高  +350/将牌对数
    //2.BTW牌周围2格内牌的数量    紧挨着:1张+100; 隔一个:1张+50   (注:这里的“张”指不同“类型”)
    //3.BTW牌所在type的总张数    张数k越少,权重越高,但不是重点  +50-k*10
    //4.BTW牌在paichi中剩余量    剩余量越高,权值越高   + 5 * 剩余张数
    //5.FJ牌在paichi中剩余量     剩余量越高,权值越高   + 10 * 剩余张数
    
    //6.[特判].如果只剩两张[单牌],且其中一张在牌池里已经没有了,那就给他非常低的权重,以此打出这一张!
    
    
    //1.BTW牌是将牌!         权值升高  +250/将牌对数
    int jiang_dui_cnt = 0;
    for(int i = 1; i <= 49; i++){
        if(not_sk_pai[i].val == 2){
            jiang_dui_cnt++;
        }
    }
    for(int i = 1; i <= 49; i++){
        if(not_sk_pai[i].val == 2){
            not_sk_pai[i].wei += 250 / jiang_dui_cnt;
        }
    }
    //1.1. FJ牌是将牌!         权值升高  +350/将牌对数
    jiang_dui_cnt = 0;
    for(int i = 61; i <= 75; i++){
        if(not_sk_pai[i].val == 2){
            jiang_dui_cnt++;
        }
    }
    for(int i = 61; i <= 75; i++){
        if(not_sk_pai[i].val == 2){
            not_sk_pai[i].wei += 350 / jiang_dui_cnt;
        }
    }
    //2.BTW牌周围2格内牌的数量    紧挨着:1张+100; 隔一个:1张+50  (注:这里的“张”指不同“类型”)
    for(int i = 1; i <= 49; i++){
        if(not_sk_pai[i].val == 0) {continue;}
        not_sk_pai[i].wei += bool(not_sk_pai[i-1].val) * 100;
        not_sk_pai[i].wei += bool(not_sk_pai[i+1].val) * 100;
        if(i != 1){not_sk_pai[i].wei += bool(not_sk_pai[i-2].val) * 50;}
        not_sk_pai[i].wei += bool(not_sk_pai[i+2].val) * 50;
    }
    //3.BTW牌所在type的总张数    张数k越少,权重越高,但不是重点  +50-k*10
    for(int i = 1; i <= 49; i++){
        if(not_sk_pai[i].val == 0) {continue;}
        int type = i / 10 * 10 + 1;
        int k = 0;
        for(int j = type; j <= type + 8; j++){
            k += shoupai[j];
        }
        not_sk_pai[i].wei += (50 - 10 * k);
    }
    //4.BTW牌在paichi中剩余量    剩余量越高,权值越高   + 5 * 剩余张数
    for(int i = 1; i <= 49; i++){
        if(not_sk_pai[i].val == 0) {continue;}
        not_sk_pai[i].wei += 5 * paichi[i];
    }
    //5.FJ牌在paichi中剩余量     剩余量越高,权值越高   + 10 * 剩余张数
    for(int i = 61; i <= 75; i++){
        if(not_sk_pai[i].val == 0) {continue;}
        not_sk_pai[i].wei += 10 * paichi[i];
    }
    //6.[特判].如果只剩两张[单牌],且其中一张在牌池里已经没有了,那就打出这一张!
    if(best_info.danpai == 2 && best_info.jiangpai == 0){
        for(int i = 1; i <= 75; i++){
            if(not_sk_pai[i].val && paichi[i] == 0){
                not_sk_pai[i].wei = -9999; //这张牌在牌池里没有了,丢掉吧.
            }
        }
    }
    //找出权值最低的
    int min_weight = 999999;
    int min_weight_pai = '?';
    for(int i = 1; i <= 75; i++){
        if(not_sk_pai[i].val == 0) {continue;}
        if(not_sk_pai[i].wei < min_weight){
            min_weight = not_sk_pai[i].wei;
            min_weight_pai = i;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    //返回这张牌,在主函数中用于打出
    return num2str(min_weight_pai);
}









int main(){
    
#ifndef _BOTZONE_ONLINE
    freopen("in.txt", "r", stdin);
    auto start_time = clock();
#endif
    
#ifdef FUSHI
    init_pai_wall(); //初始化牌墙计数
#endif
    MahjongInit(); //初始化算番器
    init_paichi(); //初始化牌池
    istringstream sin; //string流对象
    cin >> turn;
    string temp_str;
    getline(cin, temp_str); //吃掉回车
    sys_request.push_back("======");
    my_response.push_back("======");
    int read_lines = 2 * turn - 1; //还需读入2*n-1条字符串
    for(int i = 1; i <= read_lines; i++){
        getline(cin, temp_str);
        if(i % 2) sys_request.push_back(temp_str);
        else my_response.push_back(temp_str);
    }
    
    //此时sys_request[turn]是当前这一局的最新request
    //约定这一轮的response要push到my_response的最后,最后 cout << (my_response[turn]) 即可
    
    //开始场景复原(不包含最后一个request!)
    for(auto req = sys_request.begin() + 1; req != sys_request.end() - 1; ++req){
        if((*req)[0] == '3'){
            sin.str(*req); sin.clear();
            int player_id; string event;
            sin >> player_id >> player_id >> event;
            //有七种可能的事件event:
            //BUHUA Card1; DRAW; PLAY Card1; PENG Card1; CHI Card1 Card2; GANG; BUGANG Card1
            //其中GANG需要通过上一盘来判断明暗杠情况(若上一回合为摸牌，表示进行暗杠，否则杠上回合打出的牌)
            if(event == "BUHUA"){}
            else if(event == "DRAW"){
#ifdef FUSHI
                pai_wall[player_id]--;
#endif
            }
            else if(event == "PLAY"){
                string card_play;
                sin >> card_play;
                if(player_id == myID){ //自己打出
                    myplay(card_play);
                }
                else{ //别人打出
                    paichi[str2num(card_play)]--;
                }
            }
            else if(event == "PENG"){
                string card_abondon;
                sin >> card_abondon;
                string card_peng_m = "??"; //碰的什么牌取决于上一条信息的最后两个字母!
                string last_event = *(req-1);
                card_peng_m[0] = last_event[last_event.length() - 2];
                card_peng_m[1] = last_event[last_event.length() - 1];
                if(player_id == myID){
                    mypeng(card_peng_m, card_abondon);
                }
                else{ //别人碰牌
                    //!注意: 不要重复统计碰的那张牌! 之前那张牌已经被统计过了!!!!!!
                    paichi[str2num(card_peng_m)] -= 2;
                    paichi[str2num(card_abondon)] -= 1;
                }
            }
            else if(event == "CHI"){
                string card_from_others = "??"; //吃了别人的哪张牌?
                string last_event = *(req-1);
                card_from_others[0] = last_event[last_event.length() - 2];
                card_from_others[1] = last_event[last_event.length() - 1];
                string card_chi_m; //形成的顺子的中间(middle)牌?
                string card_abondon; //吃牌后丢弃了哪张牌?
                sin >> card_chi_m >> card_abondon;
                if(player_id == myID){
                    mychi(card_from_others, card_chi_m, card_abondon);
                }
                else{ //别人吃牌
                    //!注意: 不要重复统计from_others的那张牌! 之前那张牌已经被统计过了!!!!!!
                    char card_l[3] = {0}, card_r[3] = {0};
                    card_l[0] = card_r[0] = card_chi_m[0];
                    card_l[1] = card_chi_m[1] - 1;
                    card_r[1] = card_chi_m[1] + 1;
                    paichi[str2num(card_abondon)]--;
                    paichi[str2num(card_l)] --;
                    paichi[str2num(card_r)] --;
                    paichi[str2num(card_chi_m)] --;
                    paichi[str2num(card_from_others)]++; //多减了一次,补回去
                }
            }
            else if(event == "GANG"){
                bool is_minggang = true; //是否为明杠,明杠意味着牌来自别人
                if((player_id == myID && '\0' == (*(req-1))[4]) || (player_id != myID && 'D' == (*(req-1))[4])){ //上一回合是摸牌,暗杠
                    is_minggang = false;
                }
                if(player_id == myID){ //自己杠牌
                    string card_gang_m = "??";
                    //因为是自己杠牌,所以无论明暗,杠的牌是已知的,
                    //如果是明杠,它取决于上一条信息的最后两个字母
                    //如果是暗杠,它取决于上一条 ** my_response ** 的最后两个字母!
                    if(is_minggang){
                        string last_event = *(req-1);
                        card_gang_m[0] = last_event[last_event.length() - 2];
                        card_gang_m[1] = last_event[last_event.length() - 1];
                        mygang(card_gang_m, is_minggang);
                    }
                    else{
                        string my_last_response = my_response[req - sys_request.begin() - 1];
                        card_gang_m[0] = my_last_response[5];
                        card_gang_m[1] = my_last_response[6];
                        mygang(card_gang_m, is_minggang);
                    }
                }
                else if(is_minggang){ //别人杠的明杠
                    string card_gang_m = "??"; //杠的牌是已知的,它取决于上一条信息的最后两个字母!
                    string last_event = *(req-1);
                    card_gang_m[0] = last_event[last_event.length() - 2];
                    card_gang_m[1] = last_event[last_event.length() - 1];
                    paichi[str2num(card_gang_m)] -= 3;
                }
                else{} //别人杠的暗杠,(没有任何信息...)
            }
            else if(event == "BUGANG"){
                string Card_bugang;
                sin >> Card_bugang;
                if(player_id == myID){
                    mybugang(Card_bugang);
                }
                else{ //别人补杠
                    paichi[str2num(Card_bugang)]--;
                }
            }
            else{
                raise_error();
            }
        }
        else if((*req)[0] == '2'){ //自己摸了张牌
#ifdef FUSHI
            pai_wall[myID]--;
#endif
            sin.clear();
            sin.str(*req);
            string card_draw;
            sin >> card_draw >> card_draw;
            mydraw(card_draw);
        }
        else if((*req)[0] == '1'){ //初始花牌情况以及自己的初始手牌
            sin.clear();
            sin.str(*req);
            sin >> hua_amount[0] >> hua_amount[0] >> hua_amount[1] >> hua_amount[2] >> hua_amount[3];
            for(int i = 0; i < 13; i++){
                string card_draw;
                sin >> card_draw;
                hand.push_back(card_draw);
                shoupai[str2num(card_draw)]++;
                paichi[str2num(card_draw)]--;
            }
        }
        else if((*req)[0] == '0'){ //自己的座位和本局游戏的风圈
            sin.clear();
            sin.str(*req);
            sin >> myID >> myID >> fengquan;
        }
        else{
            raise_error();
        }
    }
    
    
    
    
    //开始处理最后一个request!
    auto req = sys_request.end() - 1;
    if((*req)[0] == '3'){
        
        sin.str(*req); sin.clear();
        int player_id; string event;
        sin >> player_id >> player_id >> event;
        
        //有七种可能的事件event:
        //BUHUA Card1; DRAW; PLAY Card1; PENG Card1; CHI Card1 Card2; GANG; BUGANG Card1

        if(event == "BUHUA") {my_response.push_back("PASS");}
        else if(event == "DRAW") {
#ifdef FUSHI
            pai_wall[player_id]--;
#endif
            my_response.push_back("PASS");}
        else if(event == "PLAY"){
            string card_play;
            sin >> card_play;
            if(player_id == myID){ //自己打出
                my_response.push_back("PASS");
            }
            else{ //别人打出一张牌
                paichi[str2num(card_play)]--;
                
                //这里有以下可能的输出: PASS / PENG Card_abondon / CHI Card_m Card_abondon / GANG / HU   (针对别人play的那张)
                bool pushed = false; //确保最终只会push_response一次
                
                
                //1.看能不能HU
                if(!pushed){
                    int fan = 0;
                    if(pai_wall[(player_id+1)%4] == 0){
                        
                    }
                    try{
                        auto re = MahjongFanCalculator(pack,hand,card_play,0,0,paichi[str2num(card_play)] == 0,0,pai_wall[(player_id+1)%4] == 0,myID, fengquan);
                        for(auto i : re){
                            fan += i.first;
                        }
                    }
                    catch(const string& error){
                        fan = 0;
                    }
                    
                    if(fan >= 8){
                        if(fan >= 8){ //和了
                            my_response.push_back("HU");
                            pushed = true;
                        }
                    }
                }
                
#ifdef FUSHI
                if(get_my_chipenggang_illegality(player_id) == false){
                    my_response.push_back("PASS");
                    pushed = true;
                }
#endif
                //2.看能不能GANG
                if(!pushed){
                    if(shoupai[str2num(card_play)] == 3){
                        my_response.push_back("GANG");
                        pushed = true;
                    }
                }
                
                //3.看看F/J能不能PENG
                if(!pushed){
                    if(card_play[0] == 'F' || card_play[0] == 'J'){
                        if(shoupai[str2num(card_play)] == 2){ //自己手中恰好有2张这张F/J牌
                            //决定碰了,下面决策abondon哪张牌
                            shoupai[str2num(card_play)] = 0;
                            my_response.push_back("PENG " + decide_abondon_card());
                            pushed = true;
                        }
                    }
                }
                
                
                //4.看要不要CHI
                if(!pushed && is_my_shangjia(player_id) && str2num(card_play) <= 49 &&
                   ((shoupai[str2num(card_play)-2] && shoupai[str2num(card_play)-1]) ||  (shoupai[str2num(card_play)-1] && shoupai[str2num(card_play)+1]) ||
                    (shoupai[str2num(card_play)+1] && shoupai[str2num(card_play)+2]))){
                    //只能吃上家的牌
                    //这得是一张数字牌
                    //手牌中得有前后两张牌
                    //先调用cnt_skd()评估不吃时候的手牌价值
                    //再假设吃进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就CHI
                    //(要求严格是防止123吃成1 234,虽然事实上不会发生后者,因为后者的单牌会拉低分数)
                    
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){ //决定吃了,但记得确认高分来自新的顺子(比如有可能是因为将牌导致的分数升高),否则仍然PASS!
                        string print_card_m;
                        int card_from_other = str2num(card_play);
                        bool find_shunzi = false; //确保高分来自新的顺子,否则仍然PASS!
                        //找到新组成的顺子的中间牌
                        for(auto i = best_info.m_pai_of_shunzi.begin(); i != best_info.m_pai_of_shunzi.end(); i++){
                            if(*i - card_from_other <= 1 && *i - card_from_other >= -1){
                                print_card_m = num2str(*i);
                                find_shunzi = true;
                                break;
                            }
                        }
                        if(find_shunzi){
                            //去掉这个顺子
                            shoupai[str2num(print_card_m)]--;
                            shoupai[str2num(print_card_m)-1]--;
                            shoupai[str2num(print_card_m)+1]--;
                            //开始决策扔哪张
                            string print_card_abondon = decide_abondon_card();
                            //最终输出
                            my_response.push_back("CHI " + print_card_m + " " + print_card_abondon);
                            pushed = true;
                        }
                        else{
                            my_response.push_back("PASS");
                            pushed = true;
                        }
                    }
                    else{
                        shoupai[str2num(card_play)]--; //恢复
                    }
                }
                
                
                
                //5.看数字牌要不要PENG
                if(!pushed && shoupai[str2num(card_play)] >= 2 && str2num(card_play) < 60){
                    //手牌中得有两张和card_play相同的牌
                    //先调用cnt_skd()评估不PENG时候的手牌价值
                    //再假设PENG进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就PENG
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){
                        //决定PENG了
                        shoupai[str2num(card_play)] -= 3;
                        my_response.push_back("PENG " + decide_abondon_card());
                        pushed = true;
                    }
                }
                
                
                
                
                
                
                
                
                //终极保险
                if(!pushed){
                    my_response.push_back("PASS");
                }
                
            }
        }
        else if(event == "PENG"){
            string card_abondon;
            sin >> card_abondon;
            string card_peng_m = "??"; //碰的什么牌取决于上一条信息的最后两个字母!
            string last_event = *(req-1);
            card_peng_m[0] = last_event[last_event.length() - 2];
            card_peng_m[1] = last_event[last_event.length() - 1];
            
            if(player_id == myID){ //是自己成功碰牌的信息
                my_response.push_back("PASS");
            }
            else{ //是别人碰牌的信息
                //!注意: 不要重复统计碰的那张牌! 之前那张牌已经被统计过了!!!!!!
                paichi[str2num(card_peng_m)] -= 2;
                paichi[str2num(card_abondon)] -= 1;
                
                //这里有以下可能的输出: PASS / PENG Card_abondon / CHI Card_m Card_abondon / GANG / HU  (针对abondon的那张)
                bool pushed = false; //确保最终只会push_response一次
                
                
                //1.看能不能HU
                if(!pushed){
                    if(pai_wall[(player_id+1)%4] == 0){
                        
                    }
                    int fan = 0;
                    try{
                        auto re = MahjongFanCalculator(pack,hand,card_abondon,0,0,paichi[str2num(card_abondon)] == 0,0,pai_wall[(player_id+1)%4] == 0,myID, fengquan);
                        for(auto i : re){
                            fan += i.first;
                        }
                    }
                    catch(const string& error){
                        fan = 0;
                    }
                    if(fan >= 8){
                        if(fan >= 8){ //和了
                            my_response.push_back("HU");
                            pushed = true;
                        }
                    }
                }
#ifdef FUSHI
                if(get_my_chipenggang_illegality(player_id) == false){
                    my_response.push_back("PASS");
                    pushed = true;
                }
#endif
                
                //2.看能不能GANG
                if(!pushed){
                    if(shoupai[str2num(card_abondon)] == 3){
                        my_response.push_back("GANG");
                        pushed = true;
                    }
                }
                
                //3.看看F/J能不能PENG
                if(!pushed){
                    if(card_abondon[0] == 'F' || card_abondon[0] == 'J'){
                        if(shoupai[str2num(card_abondon)] == 2){ //自己手中恰好有2张这张F/J牌
                            //决定碰了,下面决策abondon哪张牌
                            shoupai[str2num(card_abondon)] = 0;
                            my_response.push_back("PENG " + decide_abondon_card());
                            pushed = true;
                        }
                    }
                }
                
                
                //4.看要不要CHI
                string card_play = card_abondon;
                if(!pushed && is_my_shangjia(player_id) && str2num(card_play) <= 49 &&
                   ((shoupai[str2num(card_play)-2] && shoupai[str2num(card_play)-1]) ||  (shoupai[str2num(card_play)-1] && shoupai[str2num(card_play)+1]) ||
                    (shoupai[str2num(card_play)+1] && shoupai[str2num(card_play)+2]))){
                    //只能吃上家的牌
                    //这得是一张数字牌
                    //手牌中得有前后两张牌
                    //先调用cnt_skd()评估不吃时候的手牌价值
                    //再假设吃进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就CHI
                    //(要求严格是防止123吃成1 234,虽然事实上不会发生后者,因为后者的单牌会拉低分数)
                    
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){ //决定吃了,但记得确认高分来自新的顺子(比如有可能是因为将牌导致的分数升高),否则仍然PASS!
                        string print_card_m;
                        int card_from_other = str2num(card_play);
                        bool find_shunzi = false; //确保高分来自新的顺子,否则仍然PASS!
                        //找到新组成的顺子的中间牌
                        for(auto i = best_info.m_pai_of_shunzi.begin(); i != best_info.m_pai_of_shunzi.end(); i++){
                            if(*i - card_from_other <= 1 && *i - card_from_other >= -1){
                                print_card_m = num2str(*i);
                                find_shunzi = true;
                                break;
                            }
                        }
                        if(find_shunzi){
                            //去掉这个顺子
                            shoupai[str2num(print_card_m)]--;
                            shoupai[str2num(print_card_m)-1]--;
                            shoupai[str2num(print_card_m)+1]--;
                            //开始决策扔哪张
                            string print_card_abondon = decide_abondon_card();
                            //最终输出
                            my_response.push_back("CHI " + print_card_m + " " + print_card_abondon);
                            pushed = true;
                        }
                        else{
                            my_response.push_back("PASS");
                            pushed = true;
                        }
                    }
                    else{
                        shoupai[str2num(card_play)]--; //恢复
                    }
                }
                
                
                
                //5.看数字牌要不要PENG
                if(!pushed && shoupai[str2num(card_play)] >= 2 && str2num(card_play) < 60){
                    //手牌中得有两张和card_play相同的牌
                    //先调用cnt_skd()评估不PENG时候的手牌价值
                    //再假设PENG进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就PENG
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){
                        //决定PENG了
                        shoupai[str2num(card_play)] -= 3;
                        my_response.push_back("PENG " + decide_abondon_card());
                        pushed = true;
                    }
                }
                
                
                
                
                
                
                
                
                
                
                
                //终极保险
                if(!pushed){
                    my_response.push_back("PASS");
                }
                
            }
        }
        else if(event == "CHI"){
            string card_from_others = "??"; //吃了别人的哪张牌?
            string last_event = *(req-1);
            card_from_others[0] = last_event[last_event.length() - 2];
            card_from_others[1] = last_event[last_event.length() - 1];
            string card_chi_m; //形成的顺子的中间(middle)牌?
            string card_abondon; //吃牌后丢弃了哪张牌?
            sin >> card_chi_m >> card_abondon;
            if(player_id == myID){ //是自己吃牌的信息
                my_response.push_back("PASS");
            }
            else{ //是别人吃牌的信息
                //!注意: 不要重复统计from_others的那张牌! 之前那张牌已经被统计过了!!!!!!
                char card_l[3] = {0}, card_r[3] = {0};
                card_l[0] = card_r[0] = card_chi_m[0];
                card_l[1] = card_chi_m[1] - 1;
                card_r[1] = card_chi_m[1] + 1;
                paichi[str2num(card_abondon)]--;
                paichi[str2num(card_l)] --;
                paichi[str2num(card_r)] --;
                paichi[str2num(card_chi_m)] --;
                paichi[str2num(card_from_others)]++; //多减了一次,补回去
                
                //这里有以下可能的输出: PASS / PENG Card_abondon / CHI Card_m Card_abondon / GANG / HU  (针对abandon的那张)
                bool pushed = false; //确保最终只会push_response一次
                
                
                //1.看能不能HU
                if(!pushed){
                    if(pai_wall[(player_id+1)%4] == 0){
                        
                    }
                    int fan = 0;
                    try{
                        auto re = MahjongFanCalculator(pack,hand,card_abondon,0,0,paichi[str2num(card_abondon)] == 0,0,pai_wall[(player_id+1)%4] == 0,myID, fengquan);
                        for(auto i : re){
                            fan += i.first;
                        }
                    }
                    catch(const string& error){
                        fan = 0;
                    }
                    if(fan >= 8){
                        if(fan >= 8){ //和了
                            my_response.push_back("HU");
                            pushed = true;
                        }
                    }
                }
#ifdef FUSHI
                if(get_my_chipenggang_illegality(player_id) == false){
                    my_response.push_back("PASS");
                    pushed = true;
                }
#endif
                
                //2.看能不能GANG
                if(!pushed){
                    if(shoupai[str2num(card_abondon)] == 3){
                        my_response.push_back("GANG");
                        pushed = true;
                    }
                }
                
                //3.看看F/J能不能PENG
                if(!pushed){
                    if(card_abondon[0] == 'F' || card_abondon[0] == 'J'){
                        if(shoupai[str2num(card_abondon)] == 2){ //自己手中恰好有2张这张F/J牌
                            //决定碰了,下面决策abondon哪张牌
                            shoupai[str2num(card_abondon)] = 0;
                            my_response.push_back("PENG " + decide_abondon_card());
                            pushed = true;
                        }
                    }
                }
                
                //4.看要不要CHI
                string card_play = card_abondon;
                if(!pushed && is_my_shangjia(player_id) && str2num(card_play) <= 49 &&
                   ((shoupai[str2num(card_play)-2] && shoupai[str2num(card_play)-1]) ||  (shoupai[str2num(card_play)-1] && shoupai[str2num(card_play)+1]) ||
                    (shoupai[str2num(card_play)+1] && shoupai[str2num(card_play)+2]))){
                    //只能吃上家的牌
                    //这得是一张数字牌
                    //手牌中得有前后两张牌
                    //先调用cnt_skd()评估不吃时候的手牌价值
                    //再假设吃进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就CHI
                    //(要求严格是防止123吃成1 234,虽然事实上不会发生后者,因为后者的单牌会拉低分数)
                    
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){ //决定吃了,但记得确认高分来自新的顺子(比如有可能是因为将牌导致的分数升高),否则仍然PASS!
                        string print_card_m;
                        int card_from_other = str2num(card_play);
                        bool find_shunzi = false; //确保高分来自新的顺子,否则仍然PASS!
                        //找到新组成的顺子的中间牌
                        for(auto i = best_info.m_pai_of_shunzi.begin(); i != best_info.m_pai_of_shunzi.end(); i++){
                            if(*i - card_from_other <= 1 && *i - card_from_other >= -1){
                                print_card_m = num2str(*i);
                                find_shunzi = true;
                                break;
                            }
                        }
                        if(find_shunzi){
                            //去掉这个顺子
                            shoupai[str2num(print_card_m)]--;
                            shoupai[str2num(print_card_m)-1]--;
                            shoupai[str2num(print_card_m)+1]--;
                            //开始决策扔哪张
                            string print_card_abondon = decide_abondon_card();
                            //最终输出
                            my_response.push_back("CHI " + print_card_m + " " + print_card_abondon);
                            pushed = true;
                        }
                        else{
                            my_response.push_back("PASS");
                            pushed = true;
                        }
                    }
                    else{
                        shoupai[str2num(card_play)]--; //恢复
                    }
                }
                
                //5.看数字牌要不要PENG
                if(!pushed && shoupai[str2num(card_play)] >= 2 && str2num(card_play) < 60){
                    //手牌中得有两张和card_play相同的牌
                    //先调用cnt_skd()评估不PENG时候的手牌价值
                    //再假设PENG进来,然后评估一下价值
                    //比较两次的价值..如果价值严格升高了,就PENG
                    
                    info temp_info_1{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_1);
                    
                    int score_before = best_info.evaluate_score();
                    
                    
                    
                    shoupai[str2num(card_play)]++;
                    info temp_info_2{0,0,0,0,false};
                    best_info = {0,0,20,0,false};
                    cnt_skd(1, 1, temp_info_2);
                    
                    int score_after = best_info.evaluate_score();
                    
                    
                    //                    cout << score_before << " >> " << score_after << endl;
                    
                    if(LUFU && (score_after > score_before || mingpai_cnt >= 1)){
                        //决定PENG了
                        shoupai[str2num(card_play)] -= 3;
                        my_response.push_back("PENG " + decide_abondon_card());
                        pushed = true;
                    }
                }
                
                
                
                
                
                
                
                
                
                
                
                //终极保险
                if(!pushed){
                    my_response.push_back("PASS");
                }
                
            }
        }
        else if(event == "GANG"){
            my_response.push_back("PASS");
        }
        else if(event == "BUGANG"){
            string Card_bugang;
            sin >> Card_bugang;
            if(player_id == myID){
                my_response.push_back("PASS");
            }
            else{ //别人补杠
                paichi[str2num(Card_bugang)]--;
                //这里有以下可能的输出: PASS / HU  (针对Card_bugang)
                //调用算番器,如果这张能和,和了一定8番+,就"HU"
                bool can_hu = true;
                try{
                    auto re = MahjongFanCalculator(pack,hand,Card_bugang,0,false,false,true,false,myID,fengquan);
                }catch(const string& error){
                    can_hu = false;
                }
                if(can_hu){ //和了
                    my_response.push_back("HU");
                }
                else{
                    my_response.push_back("PASS");
                }
            }
        }
        else{
            raise_error();
        }
    }
    else if((*req)[0] == '2'){ //自己摸了张牌
        sin.clear();
        sin.str(*req);
        string card_draw;
        sin >> card_draw >> card_draw;
        mydraw(card_draw);
        
        //这里有4种可能的输出: PLAY Card1 / GANG Card1 / BUGANG Card1 / HU
        //AI逻辑:
        //1.检查能否和牌
        //2.检查能否暗杠
        //3.检查能否补杠
        //4.调用 get_abondon_card(),它会给出弃牌建议
        bool pushed = false; //确保最终只会push_response一次
        
        //1.检查能否和牌
        if(!pushed){
            int fan = 0;
            try{
                hand.erase(find(hand.begin(),hand.end(),card_draw));
                auto re = MahjongFanCalculator(pack,hand,card_draw,0, true, paichi[str2num(card_draw)] == 0, false, pai_wall[(myID+1)%4] == 0, myID, fengquan);
                hand.push_back(card_draw);
                for(auto i : re){
                    fan += i.first;
                }
            }
            catch(const string& error){
                fan = 0;
                hand.push_back(card_draw);
            }
            if(fan >= 8){
                if(fan >= 8){ //和了
                    my_response.push_back("HU");
                    pushed = true;
                }
            }
        }
        //2.检查能否暗杠
        if(!pushed && pai_wall[myID] >= 2){
            for(int i = 1; i <= 75; i++){
                if(shoupai[i] == 4){
                    my_response.push_back("GANG " + num2str(i));
                    pushed = true;
                    break;
                }
            }
        }
        //3.检查能否补杠(似乎pai_wall必须有牌才行)
        if(!pushed && pai_wall[myID] >= 2){
            for(auto i = pack.begin(); i != pack.end(); i++){
                if(i->first == "PENG" && i->second.first == card_draw){
                    my_response.push_back("BUGANG " + card_draw);
                    pushed = true;
                    break;
                }
            }
        }
        //4.调用 get_abondon_card(),它会给出弃牌建议
        if(!pushed){
            my_response.push_back("PLAY " + decide_abondon_card());
        }
        
    }
    else if((*req)[0] == '1'){ //初始花牌情况以及自己的初始手牌
        my_response.push_back("PASS");
    }
    else if((*req)[0] == '0'){ //获取自己的座位和本局游戏的风圈
        my_response.push_back("PASS");
    }
    else{
        raise_error();
    }
    
    
    
    
    //最后就是输出my_response(turn)
    cout << my_response[turn];
    
    
#ifndef _BOTZONE_ONLINE
    auto end_time = clock();
    cout << endl << double(end_time - start_time) / CLOCKS_PER_SEC << endl;
#endif
    
    
    return 0;
}






//string牌转化为数字 1-9B 21-29T 41-49W 61.63.65.67F 71.73.75J
//!不检查传入参数是否合法
int str2num(const string& card){
    char type = card[0];
    int num = card[1] - '0';
    if(type == 'B') return num;
    else if(type == 'T') return 20 + num;
    else if(type == 'W') return 40 + num;
    else if(type == 'F') return 59 + 2 * num;
    else if(type == 'J') return 69 + 2 * num;
    else raise_error();
    return -1;
}

//数字转化为string牌 1-9B 21-29T 41-49W 61.63.65.67F 71.73.75J
//!不检查传入参数是否合法
string num2str(int card_id){
    char card_str[3] = {0};
    int type = card_id / 10;
    switch(type){
        case 0: card_str[0] = 'B'; card_str[1] = card_id % 10 + '0'; break;
        case 2: card_str[0] = 'T'; card_str[1] = card_id % 10 + '0'; break;
        case 4: card_str[0] = 'W'; card_str[1] = card_id % 10 + '0'; break;
        case 6: card_str[0] = 'F'; card_str[1] = card_id % 10 / 2 + '1'; break;
        case 7: card_str[0] = 'J'; card_str[1] = card_id % 10 / 2 + '1'; break;
        default: raise_error();
    }
    return card_str;
}

//我从hand中打出一张牌
void myplay(const string card){
    hand.erase(find(hand.begin(), hand.end(), card));
    shoupai[str2num(card)]--;
}

//我摸一张牌到hand
void mydraw(const string card){
    hand.push_back(card);
    shoupai[str2num(card)]++;
    paichi[str2num(card)]--;
}

//我吃card
void mychi(const string card_from_others, const string card_eat_m, const string card_abandon){
    mingpai_cnt++;
    char card_l[3] = {0}, card_r[3] = {0};
    card_l[0]= card_r[0] = card_eat_m[0];
    card_l[1] = card_eat_m[1] - 1;
    card_r[1] = card_eat_m[1] + 1;
    hand.push_back(card_from_others);
    hand.erase(find(hand.begin(), hand.end(), string(card_l)));
    hand.erase(find(hand.begin(), hand.end(), string(card_eat_m)));
    hand.erase(find(hand.begin(), hand.end(), string(card_r)));
    hand.erase(find(hand.begin(), hand.end(), card_abandon));
    shoupai[str2num(card_from_others)]++;
    shoupai[str2num(card_l)]--;
    shoupai[str2num(card_eat_m)]--;
    shoupai[str2num(card_r)]--;
    shoupai[str2num(card_abandon)]--;
    pack.push_back(make_pair("CHI", make_pair(card_eat_m, 1)));
}

//我碰card
void mypeng(const string card_peng_m, const string card_abandon){
    mingpai_cnt++;
    hand.erase(find(hand.begin(), hand.end(), card_peng_m));
    hand.erase(find(hand.begin(), hand.end(), card_peng_m));
    hand.erase(find(hand.begin(), hand.end(), card_abandon));
    shoupai[str2num(card_peng_m)] -= 2;
    shoupai[str2num(card_abandon)] -= 1;
    pack.push_back(make_pair("PENG", make_pair(card_peng_m, 1)));
}

//我明暗杠card
void mygang(const string card_gang_m, bool from_others){
    if(from_others){ //我的明杠
        mingpai_cnt++;
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        shoupai[str2num(card_gang_m)] -= 3;
        pack.push_back(make_pair("GANG", make_pair(card_gang_m, 1)));
    }
    else{ //我的暗杠,因为紧随发生在摸牌之后,所以(不同于明杠,)需要从手中移走4张牌
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        hand.erase(find(hand.begin(), hand.end(), card_gang_m));
        shoupai[str2num(card_gang_m)] -= 4;
        pack.push_back(make_pair("GANG", make_pair(card_gang_m, 0)));
    }
}

//我的补杠
void mybugang(const string card_bugang_m){
    hand.erase(find(hand.begin(), hand.end(), card_bugang_m));
    shoupai[str2num(card_bugang_m)] -= 1;
    pack.erase(find_if(pack.begin(), pack.end(), [&](auto p){
        if(p.first == "PENG" && p.second.first == card_bugang_m){
            return true;
        }
        return false;
    }));
    pack.push_back(make_pair("GANG", make_pair(card_bugang_m, 1)));
}

void init_paichi(){//初始化牌池
    for(int i = 1; i <= 9; i++) {paichi[i] = 4;}
    for(int i = 21; i <= 29; i++) {paichi[i] = 4;}
    for(int i = 41; i <= 49; i++) {paichi[i] = 4;}
    for(int i = 61; i <= 67; i+=2) {paichi[i] = 4;}
    for(int i = 71; i <= 75; i+=2) {paichi[i] = 4;}
};

