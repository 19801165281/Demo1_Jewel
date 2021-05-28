#include "Jewel.h"
#include "GameScene.h"

int GameScene::selected_jewels_numbers = 0;

GameScene::GameScene()
{
}

void GameScene::onUpdate()
{
	if (this->selected_jewels_numbers == 2)
	{
		Jewel::Exchange((Jewel*)this->getChild(L"jewel"), (Jewel*)this->getChild(L"jewel2"));
		((Jewel*)(this->getChild(L"jewel")))->isSelected = false;
		((Jewel*)(this->getChild(L"jewel2")))->isSelected = false;
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
