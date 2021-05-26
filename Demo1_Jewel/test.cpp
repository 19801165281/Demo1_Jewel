#include "Jewel.h"

int main()
{
	if (Game::init(L"Demo1", 288, 512))
	{
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);

		auto scene = gcnew Scene();
		
		auto background = gcnew RectShape(Size(Window::getWidth(), Window::getHeight()));
		background->setFillColor(Color::White);
		background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);

		auto jewel = gcnew Jewel();
		jewel->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
		

		scene->addChild(background);
		scene->addChild(jewel);

		SceneManager::enter(scene);

		Game::start();
	}
	Game::destroy();
	return 0;
}