#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;

class music;
const int T=75;
const char src[]="src\\";
const char wav[]=".wav";

//音符生成器
class note_p
{
private:
    friend music;
    float p[7][7];//音符生成概率表
    int a[2];//根据前一个音符，生成后一个音符

public:
    note_p();//载入数据
    void setnote(int a);//设定初始音符（和弦走向）
    int get_p();//生成音符并且输出
};

//和弦走向控制器
class note_c
{
private:
    friend music;
    int c[16];//和弦走向数据表
    int lenth;

public:
    void setnote_c();
    int get_c(int i){cout<<"chord="<<c[i%lenth]<<endl;return c[i%lenth];};//输出和弦
};

//节奏型控制器
class note_t
{
private:
    friend music;
    int t[4][16];//每一乐句最多16个音符，每个音符最少占n个单位时间，每一乐段四句
    int lenth;//乐句长度
    int min;//最小音符长度
    int notef;//节奏频率
    int noteX;//节奏幅度

public:
    void setnote_t();
    int get_t(int timer);//返回时值
};

//音乐生成模块
class music
{
private:
    int t;//节拍器
    note_t timer;
    note_c chord;
    note_p producer;

public:
    int play(int n);//播放n个乐段
};
