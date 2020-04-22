#include<iostream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;
int N=0,M_red=0,M_blue=0,K=0,T=0,R=0;
int hour=0,minute=0;
int ld=0,ln=0,li=0,ll=0,lw=0,ad=0,an=0,ai=0,al=0,aw=0;
//ofstream cout("D:\\out.txt",ios::out);
class weapon
{
    public:
        bool available;
        int ID;
        int num;
        int weapon_atk;
        double abrasion;
        string name;
        virtual void attack(int atk,int &EnemyLife,int &SelfLife)=0;
        virtual void change_atk_num(int atk)
        {
        }
        weapon():available(true),abrasion(1)
        {
        }
};
class sword:public weapon
{
    public:
        virtual void attack(int atk,int &EnemyLife,int &SelfLife)
        {
            EnemyLife=EnemyLife-weapon_atk;
            abrasion*=1.0*0.8;
            weapon_atk=weapon_atk*0.8;
            if(weapon_atk==0)
                available=false;
            return;
        }
        sword(int atk):weapon()
        {
            ID=0;
            name="sword";
            weapon_atk=0.2*atk;
        }
        virtual void channge_atk_num(int atk)
        {
            weapon_atk=0.2*atk*abrasion;
        }
};
class bomb:public weapon
{
    public:
        virtual void attack(int atk,int &EnemyLife,int &SelfLife)
        {
            EnemyLife=0;
            SelfLife=0;
            available=false;
        }
        bomb():weapon()
        {
            ID=1;
            name="bomb";
        }
};
class arrow:public weapon
{
    public:
        virtual void attack(int atk,int &EnemyLife,int &SelfLife)
        {
            EnemyLife-=R;
            num--;
            if(!num)
                available=false;
        }
        arrow():weapon()
        {
            ID=2;
            name="arrow";
            num=3;
        }
};
class warrior
{
    public:
        int id;
        int atk,loyalty;
        string side;
        weapon *wq[3];
        int city_num;
        string name;
        int life;
        double morale;
        int step;
        warrior(int make,int ZhenYing,int life,int atk):id(make+1),life(life),atk(atk),step(0)
        {
			for(int i=0;i<=9;i++)
                wq[i]=NULL;
            if(ZhenYing==0)
            {
                side="red";
                city_num=0;
            }
            else
            {
                side="blue";
                city_num=N+1;
            }
        }
        virtual void march()
        {
            if(side=="red")
                city_num++;
            else if(side=="blue")
                city_num--;
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" marched to city "<<city_num<<" with "<<life<<" elements and force "<<atk<<endl;
        }
        void report()
        {
            if(wq[0]!=NULL&&wq[1]!=NULL&&wq[2]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has arrow("<<wq[2]->num<<"),bomb,sword("<<wq[0]->weapon_atk<<")"<<endl;
            else if(wq[0]!=NULL&&wq[1]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has bomb,sword("<<wq[0]->weapon_atk<<")"<<endl;
            else if(wq[0]!=NULL&&wq[2]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has arrow("<<wq[2]->num<<"),sword("<<wq[0]->weapon_atk<<")"<<endl;
            else if(wq[1]!=NULL&&wq[2]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has arrow("<<wq[2]->num<<"),bomb"<<endl;
            else if(wq[0]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has sword("<<wq[0]->weapon_atk<<")"<<endl;
            else if(wq[1]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has bomb"<<endl;
            else if(wq[2]!=NULL)
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has arrow("<<wq[2]->num<<")"<<endl;
            else
                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" has no weapon"<<endl;
        }
        virtual void howl()
        {
        }
        virtual void rob_weapon(warrior *enemy)
        {
        }
        virtual void fight_back(warrior *enemy)
        {
            enemy->life-=atk/2;
            if(wq[0]!=NULL)
                wq[0]->attack(atk,enemy->life,life);
            return;
        }
};
class dragon:public warrior
{
    public:
        dragon(int make,int ZhenYing,int life,int atk):warrior(make,ZhenYing,life,atk)
        {
            name="dragon";
            if(ZhenYing==0)
                morale=1.0*(M_red-ld)/ld;
            else
                morale=1.0*(M_blue-ld)/ld;
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" born"<<endl;
            cout<<"Its morale is "<<setiosflags(ios::fixed)<<setprecision(2)<<morale<<endl;
            switch(id%3)
            {
                case 0:
                    wq[0]=new sword(atk);
                    if(wq[0]->weapon_atk==0)
                    {
                        wq[0]=NULL;
                    }
                    break;
                case 1:
                    wq[1]=new bomb;
                    break;
                case 2:
                    wq[2]=new arrow;
                    break;
            }
        }
        virtual void howl()
        {
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" dragon "<<id<<" yelled in city "<<city_num<<endl;
        }
};
class ninja:public warrior
{
    public:
        ninja(int make,int ZhenYing,int life,int atk):warrior(make,ZhenYing,life,atk)
        {
            name="ninja";
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" born"<<endl;
            switch(id%3)
            {
                case 0:
                    wq[0]=new sword(atk);
                    if(wq[0]->weapon_atk==0)
                    {
                        wq[0]=NULL;
                    }
                    break;
                case 1:
                    wq[1]=new bomb;
                    break;
                case 2:
                    wq[2]=new arrow;
                    break;
            }
            switch((id+1)%3)
            {
                case 0:
                    wq[0]=new sword(atk);
                    if(wq[0]->weapon_atk==0)
                    {
                        wq[0]=NULL;
                    }
                    break;
                case 1:
                    wq[1]=new bomb;
                    break;
                case 2:
                    wq[2]=new arrow;
                    break;
            }
        }
        virtual void fight_back(warrior *enemy)
        {
        }
};
class iceman:public warrior
{
    public:
        iceman(int make,int ZhenYing,int life,int atk):warrior(make,ZhenYing,life,atk)
        {
			name="iceman";
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" born"<<endl;
            switch(id%3)
            {
                case 0:
                   wq[0]=new sword(atk);
                    if(wq[0]->weapon_atk==0)
                    {
                        wq[0]=NULL;
                    }
                    break;
                case 1:
                    wq[1]=new bomb;
                    break;
                case 2:
                    wq[2]=new arrow;
                    break;
            }
        }
        virtual void march()
        {
            if(side=="red")
                city_num++;
            else if(side=="blue")
                city_num--;
            step++;
            if(step==2)
            {
                step=0;
                life-=9;
                atk+=20;
                if(life<=0)
                    life=1;
            }
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" marched to city "<<city_num<<" with "<<life<<" elements and force "<<atk<<endl;
        }
};
class lion:public warrior
{
    public:
        lion(int make,int ZhenYing,int life,int atk):warrior(make,ZhenYing,life,atk)
        {
            name="lion";
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" born"<<endl;
            if(side=="red")
                loyalty=M_red-ll;
            else if(side=="blue")
                loyalty=M_blue-ll;
            cout<<"Its loyalty is "<<loyalty<<endl;
        }
        virtual void march()
        {
            if(side=="red")
                city_num++;
            else if(side=="blue")
                city_num--;
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" marched to city "<<city_num<<" with "<<life<<" elements and force "<<atk<<endl;
        }
};
class wolf:public warrior
{
    public:
        wolf(int make,int ZhenYing,int life,int atk):warrior(make,ZhenYing,life,atk)
        {
            name="wolf";
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<side<<" "<<name<<" "<<id<<" born"<<endl;
        }
        virtual void rob_weapon(warrior *enemy)
        {
            if(wq[0]==NULL&&enemy->wq[0]!=NULL)
            {
                wq[0]=enemy->wq[0];
                enemy->wq[0]=NULL;
                wq[0]->change_atk_num(atk);
                if(wq[0]->weapon_atk==0)
                {
                    wq[0]=NULL;
                }
            }
            if(wq[1]==NULL&&enemy->wq[1]!=NULL)
            {
                wq[1]=enemy->wq[1];
                enemy->wq[1]=NULL;
            }
            if(wq[2]==NULL&&enemy->wq[2]!=NULL)
            {
                wq[2]=enemy->wq[2];
                enemy->wq[2]=NULL;
            }
        }
};
class battlefield
{
    public:
        warrior *RedWarrier=NULL;
        warrior *BlueWarrier=NULL;
        warrior *extraRedWarrier=NULL;
        warrior *extraBlueWarrier=NULL;
        int flag;
        int last_winner;
        int life_point;
        battlefield():flag(0),last_winner(0),life_point(0)
        {
		}
};
int fight(warrior *red,warrior *blue,battlefield *city,int city_id)
{
    int ori_red_life=red->life,ori_blue_life=blue->life;
    if(red->life>0&&blue->life>0)
    {
        if(city->flag==1||(city->flag==0&&city_id%2==1))
        {
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<red->name<<" "<<red->id<<" attacked blue "<<blue->name<<" "<<blue->id<<" in city "<<city_id<<" with "<<red->life<<" elements and force "<<red->atk<<endl;
            blue->life-=red->atk;
            if(red->wq[0]!=NULL)
               red->wq[0]->attack(red->atk,blue->life,red->life);
            if(red->wq[0]!=NULL&&red->wq[0]->available==false)
            {
                red->wq[0]=NULL;
            }
            if(blue->life>0)
            {
                if(blue->name!="ninja")
                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<blue->name<<" "<<blue->id<<" fought back against red "<<red->name<<" "<<red->id<<" in city "<<city_id<<endl;
                blue->fight_back(red);
                if(blue->wq[0]!=NULL&&blue->wq[0]->available==false)
                {
                    blue->wq[0]=NULL;
                }
            }
            if(red->name=="dragon")
            {
                if(blue->life>=0)
                    red->morale-=0.2;
                else
                    red->morale+=0.2;
            }
            if(blue->name=="dragon")
            {
                 if(red->life>=0)
                    blue->morale-=0.2;
                else
                    blue->morale+=0.2;
            }
        }
        else if(city->flag==2||(city->flag==0&&city_id%2==0))
        {
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<blue->name<<" "<<blue->id<<" attacked red "<<red->name<<" "<<red->id<<" in city "<<city_id<<" with "<<blue->life<<" elements and force "<<blue->atk<<endl;
            red->life-=blue->atk;
            if(blue->wq[0]!=NULL)
            {
                blue->wq[0]->attack(blue->atk,red->life,blue->life);
                if(blue->wq[0]!=NULL&&blue->wq[0]->available==false)
                {
                    blue->wq[0]=NULL;
                }
            }
            if(red->life>0)
            {
                if(red->name!="ninja")
                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<red->name<<" "<<red->id<<" fought back against blue "<<blue->name<<" "<<blue->id<<" in city "<<city_id<<endl;
                red->fight_back(blue);
                if(red->wq[0]!=NULL&&red->wq[0]->available==false)
                {
                    red->wq[0]=NULL;
                }
            }
            if(red->name=="dragon")
            {
                if(blue->life>=0)
                    red->morale-=0.2;
                else
                    red->morale+=0.2;   
            }
            if(blue->name=="dragon")
            {
                if(red->life>=0)
                    blue->morale-=0.2;
                else
                    blue->morale+=0.2;
            }
        }
    }
    if(red->life>0&&blue->life<=0)
    {
        red->rob_weapon(blue);
        if(ori_blue_life>0)
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<blue->name<<" "<<blue->id<<" was killed in city "<<city_id<<endl;
        if(blue->name=="lion")
        {
            if(ori_blue_life<0)
                ori_blue_life=0;
            red->life+=ori_blue_life;
        }
        return 0;
    }
    else if(red->life<=0&&blue->life>0)
    {
        blue->rob_weapon(red);
        if(ori_red_life>0)
            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<red->name<<" "<<red->id<<" was killed in city "<<city_id<<endl;
        if(red->name=="lion")
        {
            if(ori_red_life<0)
                ori_red_life=0;
            blue->life+=ori_red_life;
        }
        return 2;
    }
    else if(red->life>0&&blue->life>0)
    {
        if(red->name=="lion")
            red->loyalty-=K;
        if(blue->name=="lion")
            blue->loyalty-=K;
        return 1;
    }
    else
        return 3;
}
int main()
{
    int all=0;
    cin>>all;
    int remain=all;
    while(remain)
    {
        remain--;
        hour=0;
        minute=0;
        cin>>M_red>>N>>R>>K>>T>>ld>>ln>>li>>ll>>lw>>ad>>an>>ai>>al>>aw;
        M_blue=M_red;
        cout<<"Case "<<all-remain<<":"<<endl;
        battlefield *field[N+2];
        for(int i=0;i<=N+1;i++)
            field[i]=new battlefield;
        bool war=true,red_headquater_1=false,blue_headquater_1=false;
        int RedMake=0,BlueMake=0;
        while(60*hour+minute<=T)
        {
			if(war)
            {
                if(minute==0)
                {
					switch(RedMake%5)
                    {
                        case 0:
                            if(M_red>=li)
                            {
								field[0]->RedWarrier=new iceman(RedMake,0,li,ai);
                                M_red-=li;
                                ++RedMake;
                            }
                            break;
                        case 1:
                            if(M_red>=ll)
                            {
                                field[0]->RedWarrier=new lion(RedMake,0,ll,al);
                                M_red-=ll;
                                ++RedMake;
                            }
                            break;
                        case 2:
                            if(M_red>=lw)
                            {
                                field[0]->RedWarrier=new wolf(RedMake,0,lw,aw);
                                M_red-=lw;
                                ++RedMake;
                            }
                            break;
                        case 3:
                            if(M_red>=ln)
                            {
                                field[0]->RedWarrier=new ninja(RedMake,0,ln,an);
                                M_red-=ln;
                                ++RedMake;
                            }
                            break;
                        case 4:
                            if(M_red>=ld)
                            {
                                field[0]->RedWarrier=new dragon(RedMake,0,ld,ad);
                                M_red-=ld;
                                ++RedMake;
                            }
                            break;
                    }
                    switch(BlueMake%5)
                    {
                        case 0:
                            if(M_blue>=ll)
                            {
                                field[N+1]->BlueWarrier=new lion(BlueMake,1,ll,al);
                                M_blue-=ll;
                                ++BlueMake;
                            }
                            break;
                        case 1:
                            if(M_blue>=ld)
                            {
                                field[N+1]->BlueWarrier=new dragon(BlueMake,1,ld,ad);
                                M_blue-=ld;
                                ++BlueMake;
                            }
                            break;
                        case 2:
                            if(M_blue>=ln)
                            {
                                field[N+1]->BlueWarrier=new ninja(BlueMake,1,ln,an);
                                M_blue-=ln;
                                ++BlueMake;
                            }
                            break;
                        case 3:
                            if(M_blue>=li)
                            {
                                field[N+1]->BlueWarrier=new iceman(BlueMake,1,li,ai);
                                M_blue-=li;
                                ++BlueMake;
                            }
                            break;
                        case 4:
                            if(M_blue>=lw)
                            {
                                field[N+1]->BlueWarrier=new wolf(BlueMake,1,lw,aw);
                                M_blue-=lw;
                                ++BlueMake;
                            }
                            break;
                    }
                    minute=5;
                }
                else if(minute==5)
                {
                    if(field[0]->RedWarrier!=NULL)
                    {
                        if(field[0]->RedWarrier->name=="lion"&&field[0]->RedWarrier->loyalty<=0)
                        {
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<field[0]->RedWarrier->side<<" lion "<<field[0]->RedWarrier->id<<" ran away"<<endl;
                            field[0]->RedWarrier=NULL;
                        }
                    }
                    for(int i=1;i<=N;i++)
                    {
                        if(field[i]->RedWarrier!=NULL)
                        {
                            if(field[i]->RedWarrier->name=="lion"&&field[i]->RedWarrier->loyalty<=0)
                            {
                                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<field[i]->RedWarrier->side<<" lion "<<field[i]->RedWarrier->id<<" ran away"<<endl;
                                field[i]->RedWarrier=NULL;
                            }
                        }
                        if(field[i]->BlueWarrier!=NULL)
                        {
                            if(field[i]->BlueWarrier->name=="lion"&&field[i]->BlueWarrier->loyalty<=0)
                            {
                                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<field[i]->BlueWarrier->side<<" lion "<<field[i]->BlueWarrier->id<<" ran away"<<endl;
                                field[i]->BlueWarrier=NULL;
                            }
                        }
                    }
                    if(field[N+1]->BlueWarrier!=NULL)
                    {
                        if(field[N+1]->BlueWarrier->name=="lion"&&field[N+1]->BlueWarrier->loyalty<=0)
                        {
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<field[N+1]->BlueWarrier->side<<" lion "<<field[N+1]->BlueWarrier->id<<" ran away"<<endl;
                            field[N+1]->BlueWarrier=NULL;
                        }
                    }
                    minute=10;
                }
                else if(minute==10)
                {
                    for(int i=N+1;i>=1;i--)
                    {
                        if(i==N+1)
                        {
                            if(field[0]->BlueWarrier==NULL)
                                field[0]->BlueWarrier=field[1]->BlueWarrier;
                            else
                                field[0]->extraBlueWarrier=field[1]->BlueWarrier;
                            if(field[N+1]->RedWarrier==NULL)
                                field[N+1]->RedWarrier=field[N]->RedWarrier;
                            else
                                field[N+1]->extraRedWarrier=field[N]->RedWarrier;
                        }
                        else
                        {
                            field[i]->RedWarrier=field[i-1]->RedWarrier;
                            field[N+1-i]->BlueWarrier=field[N+1-i+1]->BlueWarrier;
                        }
                    }
                    field[0]->RedWarrier=NULL;
                    field[N+1]->BlueWarrier=NULL;
                    if(field[0]->BlueWarrier!=NULL)
                    {
                        if(!blue_headquater_1)
                        {
                            blue_headquater_1=true;
                            if(field[0]->BlueWarrier->name=="iceman")
                            {
                                ++field[0]->BlueWarrier->step;
                                if(field[0]->BlueWarrier->step==2)
                                {
                                    field[0]->BlueWarrier->life-=9;
                                    if(field[0]->BlueWarrier->life<=0)
                                        field[0]->BlueWarrier->life=1;
                                    field[0]->BlueWarrier->atk+=20;
                                }
                            }
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[0]->BlueWarrier->name<<" "<<field[0]->BlueWarrier->id<<" reached red headquarter with "<<field[0]->BlueWarrier->life<<" elements and force "<<field[0]->BlueWarrier->atk<<endl;
                        }
                    }
                    if(field[0]->extraBlueWarrier!=NULL)
                    {
                        if(field[0]->extraBlueWarrier->name=="iceman")
                        {
                            ++field[0]->extraBlueWarrier->step;
                            if(field[0]->extraBlueWarrier->step==2)
                            {
                                field[0]->extraBlueWarrier->life-=9;
                                if(field[0]->extraBlueWarrier->life<=0)
                                    field[0]->extraBlueWarrier->life=1;
                                field[0]->extraBlueWarrier->atk+=20;
                            }
                        }
                        cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[0]->extraBlueWarrier->name<<" "<<field[0]->extraBlueWarrier->id<<" reached red headquarter with "<<field[0]->extraBlueWarrier->life<<" elements and force "<<field[0]->extraBlueWarrier->atk<<endl;
                        cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red headquarter was taken"<<endl;
                        war=false;
                    }
                    for(int i=1;i<=N;i++)
                    {
                        if(field[i]->RedWarrier!=NULL)
                            field[i]->RedWarrier->march();
                        if(field[i]->BlueWarrier!=NULL)
                            field[i]->BlueWarrier->march();
                    }
                    if(field[N+1]->RedWarrier!=NULL)
                    {
                        if(!red_headquater_1)
                        {
                            red_headquater_1=true;
                            if(field[N+1]->RedWarrier->name=="iceman")
                            {
                                ++field[N+1]->RedWarrier->step;
                                if(field[N+1]->RedWarrier->step==2)
                                {
                                    field[N+1]->RedWarrier->life-=9;
                                    if(field[N+1]->RedWarrier->life<=0)
                                        field[N+1]->RedWarrier->life=1;
                                    field[N+1]->RedWarrier->atk+=20;
                                }
                            }
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[N+1]->RedWarrier->name<<" "<<field[N+1]->RedWarrier->id<<" reached blue headquarter with "<<field[N+1]->RedWarrier->life<<" elements and force "<<field[N+1]->RedWarrier->atk<<endl;
                        }
                        else if(field[N+1]->extraRedWarrier!=NULL)
                        {
                            if(field[N+1]->extraRedWarrier->name=="iceman")
                            {
                                ++field[N+1]->extraRedWarrier->step;
                                if(field[N+1]->extraRedWarrier->step==2)
                                {
                                    field[N+1]->extraRedWarrier->life-=9;
                                    if(field[N+1]->extraRedWarrier->life<=0)
                                        field[N+1]->extraRedWarrier->life=1;
                                    field[N+1]->extraRedWarrier->atk+=20;
                                }
                            }
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[N+1]->extraRedWarrier->name<<" "<<field[N+1]->extraRedWarrier->id<<" reached blue headquarter with "<<field[N+1]->extraRedWarrier->life<<" elements and force "<<field[N+1]->extraRedWarrier->atk<<endl;
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue headquarter was taken"<<endl;
                            war=false;
                        }
                    }
                    minute=20;
                }
                else if(minute==20)
                {
                    for(int i=1;i<=N;++i)
                        field[i]->life_point+=10;
                    minute=30;
                }
                else if(minute==30)
                {
                    for(int i=1;i<=N;++i)
                    {
                        if(field[i]->RedWarrier!=NULL&&field[i]->BlueWarrier==NULL)
                        {
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<" earned "<<field[i]->life_point<<" elements for his headquarter"<<endl;
                            M_red+=field[i]->life_point;
                            field[i]->life_point=0;
                        }
                        else if(field[i]->RedWarrier==NULL&&field[i]->BlueWarrier!=NULL)
                        {
                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<" earned "<<field[i]->life_point<<" elements for his headquarter"<<endl;
                            M_blue+=field[i]->life_point;
                            field[i]->life_point=0;
                        }
                    }
                    minute=35;
                }
                else if(minute==35)
                {
                    if(field[0]->RedWarrier!=NULL&&field[1]->BlueWarrier!=NULL)
                    {
                        if(field[0]->RedWarrier->wq[2]!=NULL)
                        {
                            field[0]->RedWarrier->wq[2]->attack(0,field[1]->BlueWarrier->life,field[0]->RedWarrier->life);
                            if(!field[0]->RedWarrier->wq[2]->available)
                            { 
                                field[0]->RedWarrier->wq[2]=NULL;
                            }
                            if(field[1]->BlueWarrier->life<=0)
                                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[0]->RedWarrier->name<<" "<<field[0]->RedWarrier->id<<" shot and killed blue "<<field[1]->BlueWarrier->name<<" "<<field[1]->BlueWarrier->id<<endl;
                            else
                                cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[0]->RedWarrier->name<<" "<<field[0]->RedWarrier->id<<" shot"<<endl;
                        }
                    }
                    for(int i=1;i<=N;i++)
                    {
                        if(field[i]->RedWarrier!=NULL&&field[i+1]->BlueWarrier!=NULL)
                        {
                            if(field[i]->RedWarrier->wq[2]!=NULL)
                            {
                                field[i]->RedWarrier->wq[2]->attack(0,field[i+1]->BlueWarrier->life,field[i]->RedWarrier->life);
                                if(!field[i]->RedWarrier->wq[2]->available)
                                {
                                    field[i]->RedWarrier->wq[2]=NULL;
                                }
                                if(field[i+1]->BlueWarrier->life<=0)
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<" shot and killed blue "<<field[i+1]->BlueWarrier->name<<" "<<field[i+1]->BlueWarrier->id<<endl;
                                else
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<" shot"<<endl;
                            }
                        }
                        if(field[i]->BlueWarrier!=NULL&&field[i-1]->RedWarrier!=NULL)
                        {
                            if(field[i]->BlueWarrier->wq[2]!=NULL)
                            {
                                field[i]->BlueWarrier->wq[2]->attack(0,field[i-1]->RedWarrier->life,field[i]->BlueWarrier->life);
                                if(!field[i]->BlueWarrier->wq[2]->available)
                                {
                                    field[i]->BlueWarrier->wq[2]=NULL;
                                }
                                if(field[i-1]->RedWarrier->life<=0)
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<" shot and killed red "<<field[i-1]->RedWarrier->name<<" "<<field[i-1]->RedWarrier->id<<endl;
                                else
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<" shot"<<endl;
                            }
                        }
                    }
                    if(field[N+1]->BlueWarrier!=NULL&&field[N]->RedWarrier!=NULL)
                        {
                            if(field[N+1]->BlueWarrier->wq[2]!=NULL)
                            {
                                field[N+1]->BlueWarrier->wq[2]->attack(0,field[N]->RedWarrier->life,field[N+1]->BlueWarrier->life);
                                if(!field[N+1]->BlueWarrier->wq[2]->available)
                                {
                                    field[N+1]->BlueWarrier->wq[2]=NULL;
                                }
                                if(field[N]->RedWarrier->life<=0)
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[N+1]->BlueWarrier->name<<" "<<field[N+1]->BlueWarrier->id<<" shot and killed red "<<field[N]->RedWarrier->name<<" "<<field[N]->RedWarrier->id<<endl;
                                else
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[N+1]->BlueWarrier->name<<" "<<field[N+1]->BlueWarrier->id<<" shot"<<endl;
                            }
                        }
                    for(int i=1;i<=N;++i)
                    {
                        if(field[i]->BlueWarrier!=NULL&&field[i]->RedWarrier==NULL&&field[i]->BlueWarrier->life<=0)
                        {
                            field[i]->BlueWarrier=NULL;
                        }
                        else if(field[i]->RedWarrier!=NULL&&field[i]->BlueWarrier==NULL&&field[i]->RedWarrier->life<=0)
                        {
                            field[i]->RedWarrier=NULL;
                        }
                    }
                    minute=38;
                }
                else if(minute==38)
                {
                    for(int i=1;i<=N;++i)
                    {
                        if(field[i]->RedWarrier!=NULL&&field[i]->BlueWarrier!=NULL&&field[i]->RedWarrier->life>0&&field[i]->BlueWarrier->life>0)
                        {
                            if(field[i]->RedWarrier->wq[1]!=NULL||field[i]->BlueWarrier->wq[1]!=NULL)
                            {
                                int temp_blue=field[i]->BlueWarrier->life,temp_red=field[i]->RedWarrier->life;
                                if(field[i]->flag==1||(field[i]->flag==0&&i%2==1))
                                {
                                    temp_blue-=field[i]->RedWarrier->atk;
                                    if(field[i]->RedWarrier->wq[0]!=NULL)
                                        temp_blue-=field[i]->RedWarrier->wq[0]->weapon_atk;
                                    if(temp_blue>0&&field[i]->BlueWarrier->name!="ninja")
                                    {
                                        temp_red-=field[i]->BlueWarrier->atk/2;
                                        if(field[i]->BlueWarrier->wq[0]!=NULL)
                                            temp_red-=field[i]->BlueWarrier->wq[0]->weapon_atk;
                                    }
                                }
                                else
                                {
                                    temp_red-=field[i]->BlueWarrier->atk;
                                    if(field[i]->BlueWarrier->wq[0]!=NULL)
                                        temp_red-=field[i]->BlueWarrier->wq[0]->weapon_atk;
                                    if(temp_red>0&&field[i]->RedWarrier->name!="ninja")
                                    {
                                        temp_blue-=field[i]->RedWarrier->atk/2;
                                        if(field[i]->RedWarrier->wq[0]!=NULL)
                                            temp_blue-=field[i]->RedWarrier->wq[0]->weapon_atk;
                                    }
                                }
                                if(temp_blue<=0&&field[i]->BlueWarrier->wq[1]!=NULL)
                                {
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<" used a bomb and killed red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<endl;
                                    field[i]->BlueWarrier=NULL;
                                    field[i]->RedWarrier=NULL;
                                }
                                else if(temp_red<=0&&field[i]->RedWarrier->wq[1]!=NULL)
                                {
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<" used a bomb and killed blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<endl;
                                    field[i]->BlueWarrier=NULL;
                                    field[i]->RedWarrier=NULL;
                                }
                            }
                        }
                    }
                    minute=40;
                }
                else if(minute==40)
                {
                    int ori_m_red=M_red,ori_m_blue=M_blue;
                    int give_life[N+1];
                    memset(give_life,0,sizeof(give_life));
                    for(int i=1;i<=N;i++)
                    {
                        if(field[i]->RedWarrier!=NULL&&field[i]->BlueWarrier!=NULL)
                        {
                            switch(fight(field[i]->RedWarrier,field[i]->BlueWarrier,field[i],i))
                            {
                                case 0:
                                    if(field[i]->RedWarrier->name=="dragon"&&(field[i]->flag==1||(field[i]->flag==0&&i%2==1))&&field[i]->RedWarrier->morale>0.8)
                                        field[i]->RedWarrier->howl();
                                    M_red+=field[i]->life_point;
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red "<<field[i]->RedWarrier->name<<" "<<field[i]->RedWarrier->id<<" earned "<<field[i]->life_point<<" elements for his headquarter"<<endl;
                                    field[i]->life_point=0;
                                    give_life[i]=1;
                                    field[i]->BlueWarrier=NULL;
                                    if(field[i]->flag!=1)
                                    {
                                        if(field[i]->last_winner!=1)
                                            field[i]->last_winner=1;
                                        else
                                        {
                                            field[i]->flag=1;
                                            field[i]->last_winner=0;
                                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" red flag raised in city "<<i<<endl;
                                        }
                                    }
                                    else if(field[i]->last_winner==2)
                                        field[i]->last_winner=1;
                                    break;
                                case 1:
                                    if(field[i]->RedWarrier->name=="dragon"&&(field[i]->flag==1||(field[i]->flag==0&&i%2==1))&&field[i]->RedWarrier->morale>0.8)
                                        field[i]->RedWarrier->howl();
                                    if(field[i]->BlueWarrier->name=="dragon"&&(field[i]->flag==2||(field[i]->flag==0&&i%2==0))&&field[i]->BlueWarrier->morale>0.8)
                                        field[i]->BlueWarrier->howl();
                                    field[i]->last_winner=0;
                                    break;
                                case 2:
                                    if(field[i]->BlueWarrier->name=="dragon"&&(field[i]->flag==2||(field[i]->flag==0&&i%2==0))&&field[i]->BlueWarrier->morale>0.8)
                                        field[i]->BlueWarrier->howl();
                                    M_blue+=field[i]->life_point;
                                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue "<<field[i]->BlueWarrier->name<<" "<<field[i]->BlueWarrier->id<<" earned "<<field[i]->life_point<<" elements for his headquarter"<<endl;
                                    field[i]->life_point=0;
                                    give_life[i]=2;
                                    field[i]->RedWarrier=NULL;
                                    if(field[i]->flag!=2)
                                    {
                                        if(field[i]->last_winner!=2)
                                            field[i]->last_winner=2;
                                        else
                                        {
                                            field[i]->flag=2;
                                            field[i]->last_winner=0;
                                            cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" blue flag raised in city "<<i<<endl;
                                        }
                                    }
                                    else if(field[i]->last_winner==1)
                                        field[i]->last_winner=2;
                                    break;
                                case 3:
                                    field[i]->RedWarrier=NULL;
                                    field[i]->BlueWarrier=NULL;
                                    break;
                            }
                        }
                    }
                    for(int i=N;i>=1;--i)
                    {
                        if(give_life[i]==1&&ori_m_red>=8)
                        {
                            ori_m_red-=8;
                            M_red-=8;
                            field[i]->RedWarrier->life+=8;
                        }
                        if(give_life[N-i+1]==2&&ori_m_blue>=8)
                        {
                            ori_m_blue-=8;
                            M_blue-=8;
                            field[N-i+1]->BlueWarrier->life+=8;
                        }
                    }
                    minute=50;
                }
                else if(minute==50)
                {
                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<M_red<<" elements in red headquarter"<<endl;
                    cout<<setw(3)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<" "<<M_blue<<" elements in blue headquarter"<<endl;
                    minute=55;
                }
                else if(minute==55)
                {
                    for(int i=0;i<=N+1;i++)
                    {
                        if(field[i]->RedWarrier!=NULL)
                            field[i]->RedWarrier->report();
                    }
                    for(int i=0;i<=N+1;i++)
                    {
                        if(field[i]->BlueWarrier!=NULL)
                            field[i]->BlueWarrier->report();
                    }
                    hour++;
                    minute=0;
                }
            }
            else
            {
                break;
            }
        }
    }
    system("pause");
    return 0;
}
