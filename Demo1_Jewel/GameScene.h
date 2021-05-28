#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

class GameScene:
	public Scene
{
public:
	GameScene();
	void onUpdate() override;
	~GameScene();
	static int get_selected_jewels_numbers();
	static void add_selected_jewels_numbers();
	static void init_selected_jewels_numbers();
	static void minu_selected_jewels_numbers();
protected:
	static int selected_jewels_numbers;
};

