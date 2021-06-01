#include "Jewel.h"
#include "GameScene.h"
#include "GameLogic.h"
#include <vector>
using namespace std;


int main()
{
	if (Game::init(L"Demo1", 1024, 640))
	{
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultAnchor(0.5f, 0.5f);
		//动画界面（默认为第一关）
		auto scene = new GameScene();
		SceneManager::enter(scene);

		//游戏背景
		auto background = gcnew Sprite(L"res/BG03.png");

		background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
		scene->addChild(background);
		//棋盘

		auto chessboard = gcnew Sprite(L"res/chessboard.png");
		chessboard->setAnchor(0.0f, 0.0f);
		chessboard->setPos(414, 30);
		scene->addChild(chessboard);

		//创建宝石

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				auto jew = new Jewel(scene->gt->initState()[i][j]);//根据map生成不同图像图片
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
		Game::start();
	}
	Game::destroy();
	return 0;
}