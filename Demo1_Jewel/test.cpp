#include "Jewel.h"


int main()
{
	if (Game::init(L"Demo1", 288, 512))
	{
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);

		auto scene = gcnew Scene();
		SceneManager::enter(scene);

		auto jewel = gcnew Jewel();
		auto jewel2 = gcnew Jewel();

		auto background = gcnew RectShape(Size(Window::getWidth(), Window::getHeight()));
		background->setFillColor(Color::White);
		background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);

		jewel->setPos(Window::getWidth() / 2 - 50, Window::getHeight() / 2 - 100);
		jewel2->setPos(Window::getWidth() / 2 + 50, Window::getHeight() / 2 - 100);
		auto text_1 = gcnew Text(L"Break");
		auto btn_1 = gcnew RectShape(Size(140, 50));
		btn_1->setFillColor(Color::Red);
		btn_1->addChild(text_1);
		text_1->setPos(btn_1->getWidth() / 2, btn_1->getHeight() / 2);
		auto scale_btn = gcnew Button(btn_1);
		scale_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100);
		scale_btn->setClickFunc(std::bind(&Jewel::Break, jewel));

		auto text_2 = gcnew Text(L"Fall");
		auto btn_2 = gcnew RectShape(Size(140, 50));
		btn_2->setFillColor(Color::Blue);
		btn_2->addChild(text_2);
		text_2->setPos(btn_2->getWidth() / 2, btn_2->getHeight() / 2);
		auto fall_btn = gcnew Button(btn_2);
		fall_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100 + 60);
		fall_btn->setClickFunc(std::bind(&Jewel::Fall, jewel2));

		auto text_3 = gcnew Text(L"Exchange");
		auto btn_3 = gcnew RectShape(Size(140, 50));
		btn_3->setFillColor(Color::Yellow);
		btn_3->addChild(text_3);
		text_3->setPos(btn_3->getWidth() / 2, btn_3->getHeight() / 2);
		auto ex_btn = gcnew Button(btn_3);
		ex_btn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 100 + 60 + 60);
		ex_btn->setClickFunc(std::bind(&Jewel::Exchange, jewel, jewel2));

		scene->addChild(background);
		scene->addChild(jewel);
		scene->addChild(jewel2);
		scene->addChild(scale_btn);
		scene->addChild(fall_btn);
		scene->addChild(ex_btn);
		Game::start();
	}
	Game::destroy();
	return 0;
}