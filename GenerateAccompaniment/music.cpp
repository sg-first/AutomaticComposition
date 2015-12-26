#include "music.h"

//音符生成器
void note_p::setnote(int a)
{
    this->a[0]=a;
    this->a[1]=a+(rand()%3-1)*2;
    if(this->a[1]<0)
        this->a[1]=this->a[1]+7;
    else
    {
        if(this->a[1]>7)
            this->a[1]=this->a[1]-7;
    }
}

int note_p::get_p()
{
    a[0]=a[1];
    int sum,i;
    int q=rand()%10000;
    for(sum=0,i=0;sum<q;i++)
        sum+=(int)(10000*p[a[0]][i]);
    if(i-1==0)
        a[i]=7;
    else
        a[1]=i-1;
    if(a[0]==7||a[0]==4)
    {
        a[0]=1;
        a[1]=1;
    }
    if(a[1]>7 ||a[1]<0)
        a[1]=a[0];
    return a[1];
}

note_p::note_p()
{
    FILE *fp;
    if((fp=fopen("note.txt","r"))!=NULL)//这个文件中记录着对袅袅文件的分析结果
    {
        for(int i=0;i<7;i++)
        {
            for(int j=0;j<7;j++)
            {fscanf(fp,"%f",&p[i][j]);}
        }
        fclose(fp);
    }
    else
    {
        cout<<"系统文件\"note.txt\"缺失，请找回文件再启动本程序！"<<endl;
        getchar();
        exit(0);
    }
}

//和弦走向控制器
void note_c::setnote_c()
{
    FILE *fp;
    lenth=0;
    if((fp=fopen("chord.txt","r"))!=NULL)
    {
        int f=0;
        for(int i=0;i<16;i++)
        {
            if(fscanf(fp,"%d",&c[i])==EOF)
            {
                f=-1;
                break;
            }
            lenth++;
            /*if(f==-1)//这块逻辑有问题，先搞掉
                break;*/
        }
        fclose(fp);
    }
    else
    {
        cout<<"系统文件\"chord.txt\"缺失，请找回文件再启动本程序！"<<endl;
        getchar();
        exit(0);
    }
}

int note_c::get_c(int i)
{
	cout<<"chord="<<c[i%lenth]<<endl;
	return c[i%lenth];
}

//节奏型控制器
int note_t::get_t(int timer)
{return t[timer/16%4][timer%16];}

void note_t::setnote_t()
{
    notef=1;
    noteX=2;
    min=1;
    srand(time(0));
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<16;j++)
        {
            t[i][j]=0;
        }
    }
    cout<<"计算机产生的节奏型："<<endl;
    const int lenth=64;
    int sum;
    for(int j=0;j<4;j++)
    {
        sum=0;
        for(int i=0;sum<lenth && i<16;i++)
        {
            t[j][i]=2*(rand()%noteX+min+(i/(lenth/(2*notef)))%2);
            if(sum+t[j][i]>=64)t[j][i]=64-sum;
            cout<<t[j][i]<<"\t";
            sum+=t[j][i];
        }
        cout<<"\n";
    }
    getchar();
}

//音乐生成模块
int music::play(int n)
{
    int num=0;
    char v[20]="";//地址容器
    char m[3];//音符容器
    struct musicnote{
        int h;//音高
        int t;//时值
        int c;//和弦
        int p;
    }mn;
    int tj=0,f=0;
    srand(time(0));
    chord.setnote_c();
    timer.setnote_t();
    FILE *fp;
    fp=fopen("temp.txt","w");
    t=0;
    for(int i=0;i<n;i++)//一首音乐
    {
        for(int j=0;j<4;j++,tj++)//一个乐段
        {
            mn.c=chord.get_c(tj);//获取和弦
            mn.h=mn.c;
            for(int k=0;k<16;k++,t+=mn.t)//一个乐句
            {
                if(k%4==0)
                    producer.setnote(mn.c%10);
                //产生音符的音高
                mn.p=producer.get_p();
                cout<<mn.p<<endl;
                if(mn.p-mn.h%7>4)
                {mn.h=mn.p+mn.c/10*10-10;}
                else
                {
                    if(mn.p-mn.h%7<-4)
                        mn.h=mn.p+mn.c/10*10+10;
                    else
                        mn.h=mn.p+mn.c/10*10;
                }
                //产生音符的音长
                mn.t=timer.get_t(16*f+k);
                if(mn.t==0)
                {
                    //_sleep((64-t%64)*T);
                    t=(t/64+1)*64;
                    f++;
                    break;
                }
                cout<<"时钟："<<t<<"音高："<<mn.h<<"\t音长："<<mn.t<<endl;
                fprintf(fp,"%d %d %d\n",t,mn.t,mn.h);//写出
                v[0]='\0';
                m[0]=mn.h/10+48;
                m[1]=mn.h%10+48;
                m[2]='\0';
                strcat(v,src);
                strcat(v,m);
                strcat(v,wav);
                printf("%s\n",v);//把生成的配乐写入wav
                num++;
                //_sleep(T*mn.t);
            }
        }
    }
    fclose(fp);
    return num;
}
