#include "Jewel.h"
#include "GameScene.h"
#include <vector>
#include<windows.h>
using namespace std;

int GameScene::selected_jewels_numbers = 0;
Jewel* GameScene::map[8][8];

GameScene::GameScene()
{
	gt = new GameTask(1);//Ĭ��Ϊ��һ��
}

GameScene::GameScene(int l)
{
	gt = new GameTask(l);
}

void GameScene::onUpdate(){

	//if (����ͣ)
	if (GameScene::selected_jewels_numbers == 2)// ���ѡ��2������
	{
		int a = 0, b = 0, flag=0;
		int i, j;
		Jewel* jew1 = NULL;
		Jewel* jew2 = NULL;

		//�Ӳ���

		//step++


		//�ҵ�������ѡ�еı�ʯ
		for (i = 0; i < 8; i++) {//��һ����ʯ
			for (j = 0; j < 8; j++) {

				if (map[i][j]->isSelected) {
					a = i;
					b = j;
					jew1 = map[i][j];
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}

		flag = 0;

		for (i = 0; i < 8; i++) {//�ڶ�����ʯ
			for (j = 0; j < 8; j++) {
				if (i == a && j == b) continue;
				if (map[i][j]->isSelected) {
					jew2 = map[i][j];
					flag = 1;
					break;
				}
			}
			if (flag == 1) break;
		}

		//��������������
		if (((a == i) && ((b == j + 1) || (b == j - 1)) || ( (b == j) && ((a == i + 1) || (a == i - 1))))){

			int pos[4] = { a, b, i, j };
			if (this->gt->breakTask(pos) != nullptr)//����������Բ�������
			{
				//�����ϵĽ���
				Jewel::Exchange(jew1, jew2,1);//��������
				map[i][j] = jew1;
				map[a][b] = jew2;


			}else {//����������ܲ������ӣ����Ŷ���
				// ִ��˳�򶯻�
				// ִ��˳�򶯻�

				Jewel::Exchange(jew1, jew2,0);//��������
		
				Jewel::Exchange(jew1, jew2,2);//��������
			}

		}

		
		jew1->Select();
		jew2->Select();
		jew1->isSelected = false;
		jew2->isSelected = false;
		init_selected_jewels_numbers();
	}
}

GameScene::~GameScene()
{

}

int GameScene::get_selected_jewels_numbers()
{
	return selected_jewels_numbers;
}

void GameScene::add_selected_jewels_numbers()
{
	selected_jewels_numbers++;
}

void GameScene::init_selected_jewels_numbers()
{
	selected_jewels_numbers = 0;
}

void GameScene::minu_selected_jewels_numbers()
{
	selected_jewels_numbers--;
}
