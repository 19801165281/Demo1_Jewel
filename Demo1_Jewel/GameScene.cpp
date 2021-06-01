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
	//	Jewel* temp = NULL;
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
			
			//while (this->gt->breakTask(pos) != nullptr) {

			//	int **o=this->gt->breakTask(pos)->map;
			//	//��ӡ���̣�����
			//	for (int n = 0; n < 8; n++)
			//	{
			//		for (int m = 0; m < 8; m++)
			//		{
			//			cout << o[n][m] << " ";
			//		}
			//		cout << endl;
			//	}
			//	cout << endl;
			//}
			
			//���Զ�ȡ��0�������ܶ���˵������������
			MatrixNode* p1 = new MatrixNode;
			p1 = this->gt->breakTask(pos);

			if (p1 != nullptr)//����������Բ�������
			{
				
				//�����ϵĽ���
				Jewel::Exchange(jew1, jew2, 0, false);//��������
				map[i][j] = jew1;
				map[a][b] = jew2;

				int record[8] = { 0 };//��¼ÿһ���������������±�(��)��
				int numOfFall[8] = { 0 };//��¼ÿһ����������ľ��룻

				//���ĳ��λ����0����λ�ò�����ʧ����
				for (j = 0; j < 8; j++) {//���б���
					for (i = 0; i < 8; i++) {

						if (p1->map[i][j]==0) {
							Jewel::Break(map[i][j],0.3);//������ʧ����
							
							if (record[j] < i) {
								record[j] = i;//���µ�ǰ��0���ڵĵ�����±�
							}
							numOfFall[j]++;//ÿһ�� ÿ��һ��0 �������+1
						}
					}
				}

				//��ʼ����һ��״̬������ �����ˢ������ ��ûд�꣩
				p1 = p1->next;

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						auto jew = new Jewel(p1->map[i][j]);//����map���ɲ�ͬͼ��ͼƬ
						jew->pos_row = 30.0f + 36.25f + 72.5f * (float)(i);
						jew->pos_col = 414.0f + 36.25f + 72.5f * (float)(j);
						jew->setScale(0.8f);
						jew->setPosX(jew->pos_col);
						jew->setPosY(jew->pos_row);
						jew->setVisible(true);
						scene->addChild(jew);
						GameScene::map[i][j] = jew;
					}
				}

				//�������䶯��
				for (j = 0; j < 8; j++) {//���б���
					for (i = 0; i <=record[i]; i++) {

						Jewel::Fall(map[i][j],2, numOfFall[j]);
					}
				}


			}else {
				//����������ܲ������ӣ����Ŷ���
				// ִ��˳�򶯻�
				// ִ��˳�򶯻�

				Jewel::Exchange(jew1, jew2, 0, true);//��������
				
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
