#include "Jewel.h"

int main()
{
	if (Game::init(L"Demo1", 288, 512))
	{
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultAnchor(0.5f, 0.5f);

		auto scene = gcnew Scene();
		SceneManager::enter(scene);
		
		auto background = gcnew RectShape(Size(Window::getWidth(), Window::getHeight()));
		background->setFillColor(Color::White);
		background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);

		auto jewel = gcnew Jewel();
		jewel->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
		
		auto btn_1 = gcnew RectShape(Size(20, 10));
		auto scale_btn = gcnew Button(btn_1);
		btn_1->setFillColor(Color::White);

		scene->addChild(background);
		scene->addChild(jewel);


		Game::start();
	}
	Game::destroy();
	return 0;
}