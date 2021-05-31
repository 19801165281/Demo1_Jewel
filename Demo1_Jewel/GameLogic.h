#pragma once
#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
//��ͼ���С��г���
const int MAPROWNUM = 8;
const int MAPCOLNUM = 8;

/* This class contains the basic logic of the game */
class GameLogic
{
public:
    int** map;//0����գ�1~n�����n�ֱ�ʯ
    GameLogic();
    void BuildMap();//���ɲ�������ͼ�Σ����ڵ�������ʼ����ͼ��
                    //�������ӡ����������ơ��������ӵȺ�����Ҫ��ͼʱֻ����� "map[8][8]"
    bool checkmap(); //�жϵ�ͼ���Ƿ������ڵ�������ʯ��ͬ

    bool swap(int a, int b, int m, int n);//�ж��ܷ񽻻������������ڻ��޷����ӣ�����false��������Ҫ��eliminate
    int eliminate();//����,�����ص÷�
    void down();//����֮������
    void setSpeices(int n); //�������ùؿ������༸�ֱ�ʯ��������species
    bool ifGameRunning(); //������Ϸ״̬

    void setGameState(bool state); //����������Ϸ�Ƿ���ͣ��д��������ʱ�ɺ��Ա�������
                                   //д���ӡ����������ơ��������ӵȺ���ʱֻ���жϲ������� "game_running"�Ƿ�Ϊ��

    int* hint();//��ʾ����Ҫ�Ӳ�����
    bool exchange(int a, int b, int m, int n); //��hint�������ã����ж���Ӧ���ӽ������ܷ��������

    void printMap();//����

private:
    bool game_running; //��Ϸ����״̬���ò�������Ĭ��Ϊtrue,���ڽ����е������ͣ��Ϸ����ťʱ��ֵΪfalse��trueʱ��ʾ��Ϸ��������״̬
    //*******����д ������������swap���� ʱ������жϸò�������game_running�Ƿ�Ϊtrue��ֻ��Ϊtrue�ǲ��ܼ�������*********
    int species = 5;//��ʼ��ʯ����5��

};

#endif

