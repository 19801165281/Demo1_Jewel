#pragma once
#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
//地图的行、列常量
const int MAPROWNUM = 8;
const int MAPCOLNUM = 8;

/* This class contains the basic logic of the game */
class GameLogic
{
public:
    int** map;//0代表空，1~n代表第n种宝石
    GameLogic();
    void BuildMap();//生成不三连的图形，用于调用来初始化地图，
                    //以下消子、交换、下移、产生新子等函数需要地图时只需调用 "map[8][8]"
    bool checkmap(); //判断地图中是否有相邻的三个宝石相同

    bool swap(int a, int b, int m, int n);//判断能否交换交换（不相邻或无法消子，返回false）后续需要用eliminate
    int eliminate();//消子,并返回得分
    void down();//消子之后下移
    void setSpeices(int n); //用于设置关卡有至多几种宝石，即设置species
    bool ifGameRunning(); //返回游戏状态

    void setGameState(bool state); //用于设置游戏是否暂停，写其他代码时可忽略本函数。
                                   //写消子、交换、下移、产生新子等函数时只用判断布尔变量 "game_running"是否为真

    int* hint();//提示（需要加步数）
    bool exchange(int a, int b, int m, int n); //由hint函数调用，来判断相应两子交换后能否产生连子


private:
    bool game_running; //游戏运行状态，该布尔变量默认为true,当在界面中点击“暂停游戏”按钮时该值为false。true时表示游戏处于运行状态
    //*******请在写 “交换函数（swap）” 时，务必判断该布尔变量game_running是否为true，只有为true是才能继续操作*********
    int species = 5;//初始宝石种类5种

};

#endif

