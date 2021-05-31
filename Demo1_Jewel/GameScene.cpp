#include "Jewel.h"
#include "GameScene.h"
#include <vector>
using namespace std;

int GameScene::selected_jewels_numbers = 0;
vector<vector<Jewel*> >map(8, vector<Jewel*>(8));

GameScene::GameScene()
{
}

void GameScene::onUpdate()
{
	if (this->selected_jewels_numbers == 2)
	{

		int a = 0, b = 0,flag=0;
		Jewel* jew1;
		Jewel* jew2;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {

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

		for (int i = a+1; i < 8; i++) {
			for (int j = b+1; j < 8; j++) {

				if (map[i][j]->isSelected) {
					jew2 = map[i][j];
				}
			}
		}

		Jewel::Exchange(jew1, jew2);
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
