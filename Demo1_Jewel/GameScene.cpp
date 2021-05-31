#include "Jewel.h"
#include "GameScene.h"
#include <vector>
using namespace std;

int GameScene::selected_jewels_numbers = 0;
Jewel* GameScene::map[8][8];

GameScene::GameScene()
{
	gt = new GameTask(1);//默认为第一关
}

GameScene::GameScene(int l)
{
	gt = new GameTask(l);
}

void GameScene::onUpdate()
{
	if (GameScene::selected_jewels_numbers == 2)
	{
		int a = 0, b = 0, flag=0;
		int i, j;
		Jewel* jew1 = NULL;
		Jewel* jew2 = NULL;
		//找到两个被选中的宝石
		for (i = 0; i < 8; i++) {//第一个宝石
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

		for (i = 0; i < 8; i++) {//第二个宝石
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
		int pos[4] = { a, b, i, j };
		if (this->gt->breakTask(pos) != nullptr)
		{
			//动画上的交换
			Jewel::Exchange(jew1, jew2);//交换动画
			map[i][j] = jew1;
			map[a][b] = jew2;
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
