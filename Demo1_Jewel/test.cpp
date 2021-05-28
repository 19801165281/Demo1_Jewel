#include "Jewel.h"
#include "GameScene.h"
#include <vector>
using namespace std;
int main()
{
	if (Game::init(L"Demo1", 1200, 900))
	{
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);

		auto scene = gcnew GameScene();
		SceneManager::enter(scene);


		//auto jewel = gcnew Jewel();
		//jewel->setName(L"jewel");
		//auto jewel2 = gcnew Jewel();
		//jewel2->setName(L"jewel2");
		//auto jewel3 = gcnew Jewel();
		//jewel3->setName(L"jewel3");
		//auto jewel4 = gcnew Jewel();
		//jewel4->setName(L"jewel4");
		//白色背景
		auto background = gcnew RectShape(Size(Window::getWidth(), Window::getHeight()));
		background->setFillColor(Color::White);
		background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
		scene->addChild(background);
		//棋盘

		auto chessboard = gcnew Sprite(L"res/chessboard.png");
		chessboard->setPos(765, 433);
		chessboard->setScale(1.03f);
		scene->addChild(chessboard);

		//创建宝石
		vector<vector<Jewel*> >map(8, vector<Jewel*>(8));
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				auto jew = new Jewel();
				jew->pos_row = 500 + 75 * i;
				jew->pos_col = 170 + 75 * j;

				jew->setScale(0.8f);
				jew->setPos(500 + 75 * i, 170 + 75 * j);
				map.at(i).push_back(jew);

				jew->setVisible(true);
				scene->addChild(jew);
			}
		}
		////创建两个测试宝石
		//jewel->setPos(Window::getWidth() / 2 - 50, Window::getHeight() / 2 - 100);
		//jewel2->setPos(Window::getWidth() / 2 + 50, Window::getHeight() / 2 - 100);
		//jewel3->setPos(Window::getWidth() / 2 - 50, Window::getHeight() / 2 );
		//jewel4->setPos(Window::getWidth() / 2 + 50, Window::getHeight() / 2 );
		////触发消子按键
		//auto text_1 = gcnew Text(L"Break");
		//auto btn_1 = gcnew RectShape(Size(140, 50));
		//btn_1->setFillColor(Color::Red);
		//btn_1->addChild(text_1);
		//text_1->setPos(btn_1->getWidth() / 2, btn_1->getHeight() / 2);
		//auto scale_btn = gcnew Button(btn_1);
		//scale_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100);
		//scale_btn->setClickFunc(std::bind(&Jewel::Break, jewel));
		////触发下落按键
		//auto text_2 = gcnew Text(L"Fall");
		//auto btn_2 = gcnew RectShape(Size(140, 50));
		//btn_2->setFillColor(Color::Blue);
		//btn_2->addChild(text_2);
		//text_2->setPos(btn_2->getWidth() / 2, btn_2->getHeight() / 2);
		//auto fall_btn = gcnew Button(btn_2);
		//fall_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100 + 60);
		//fall_btn->setClickFunc(std::bind(&Jewel::Fall, jewel2));
		////触发左右交换按键
		//auto text_3 = gcnew Text(L"Exchange");
		//auto btn_3 = gcnew RectShape(Size(140, 50));
		//btn_3->setFillColor(Color::Yellow);
		//btn_3->addChild(text_3);
		//text_3->setPos(btn_3->getWidth() / 2, btn_3->getHeight() / 2);
		//auto ex_btn = gcnew Button(btn_3);
		//ex_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100 + 60 + 60);
		//ex_btn->setClickFunc(std::bind(&Jewel::Exchange, jewel, jewel2));

	
		//scene->addChild(jewel);
		//scene->addChild(jewel2);
		//scene->addChild(jewel3);
		//scene->addChild(jewel4);
		//scene->addChild(scale_btn);
		//scene->addChild(fall_btn);
		//scene->addChild(ex_btn);
		//
		Game::start();
	}
	Game::destroy();
	return 0;
}