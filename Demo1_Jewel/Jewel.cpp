#include "Jewel.h"
#include "GameScene.h"
#include <string>

#define GRID_LENGTH 72.5
Jewel::Jewel()
{
	this->pic_num = 0;
	this->pos_col = 0;
	this->pos_row = 0;
	isSelected = false;
	jewel_btn = gcnew Button(gcnew Sprite(L"res\\1_01.png"));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	jewel_btn->addChild(border);
	border->setVisible(isSelected);
}

Jewel::Jewel(int pic_num)
{
	this->pic_num = pic_num;
	this->pos_col = 0;
	this->pos_row = 0;
	isSelected = false;
	std::string path = "res\\1_0" + std::to_string(this->pic_num) + ".png";
	String widename = NarrowToWide(path);
	jewel_btn = gcnew Button(gcnew Sprite(widename));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	jewel_btn->addChild(border);
	border->setVisible(isSelected);
}

void Jewel::Select()
{
	// 获取按钮状态
	if (!isSelected)
	{
		isSelected = true;
		border->setVisible(isSelected);
		GameScene::add_selected_jewels_numbers();
	}
	else 
	{
		isSelected = false;
		border->setVisible(isSelected);
		GameScene::minu_selected_jewels_numbers();
	}
	// 保存信息到文件
	Data::saveBool(L"isSelected", isSelected);
}

void Jewel::Exchange(Jewel* jewel1, Jewel* jewel2,double delay,bool ifReturn)
{
	//创建右移动画
	auto moveRight = gcnew MoveBy(0.2f, Vector2(GRID_LENGTH, 0));

	//创建左移动画
	auto moveLeft = gcnew MoveBy(0.2f, Vector2(-GRID_LENGTH, 0));

	//创建上移动画
	auto moveup = gcnew MoveBy(0.2f, Vector2(0, GRID_LENGTH));

	//创建下移动画
	auto movedown = gcnew MoveBy(0.2f, Vector2(0, -GRID_LENGTH));

	auto animation1 =  gcnew MoveBy(0.0f, Vector2(0, 0));
	auto animation2=  gcnew MoveBy(0.0f, Vector2(0, 0));
	
	//执行动画
	if (jewel1->getPosX() > jewel2->getPosX())
	{
		 animation1=moveLeft->clone();
		 animation2=moveRight->clone();
	}
	else if (jewel1->getPosX() < jewel2->getPosX())
	{
		 animation1 = moveRight->clone();
		 animation2 = moveLeft->clone();
	}
	else if (jewel1->getPosY() < jewel2->getPosY()){

		 animation1 = moveup->clone();
		 animation2 = movedown->clone();
    }else{
		 animation1 = movedown->clone();
		 animation2 = moveup->clone();

	}

	auto delay1 = gcnew Delay(delay);
	auto sequence1 = gcnew Sequence({ delay1->clone(),animation1 });
	auto sequence2= gcnew Sequence({ delay1->clone(),animation2 });

	if(!ifReturn)
	{
		jewel1->runAction(sequence1->clone());
		jewel2->runAction(sequence2->clone());
	}
	else
	{
		jewel1->runAction(gcnew Sequence({ sequence1->clone(), sequence2->clone() }));
		jewel2->runAction(gcnew Sequence({ sequence2->clone(), sequence1->clone() }));
	}

	jewel1->border->setVisible(false);
	jewel2->border->setVisible(false);
}

//void Jewel::Fall(Jewel* jewel, double delay,int distance)
//{
//	//创建一个下落动画
//	auto flash = gcnew MoveBy(0.0f, Vector2(0, -80.0 * distance));//向上瞬移
//	auto fallTo = gcnew MoveBy(0.2f, Vector2(0, 80.0*distance));//向下掉落
//	auto delay1 = gcnew Delay(delay);
//	auto sequence1 = gcnew Sequence({ flash->clone(),delay1->clone(),fallTo });
//	jewel->runAction(sequence1);
//}

void Jewel::Fall(int fall_grids)
{
	//创建一个下落动画
	auto fallTo = gcnew MoveBy(0.2f, Vector2(0, GRID_LENGTH * fall_grids));
	this->runAction(fallTo);
}
//
//void Jewel::Break(Jewel* jewel, double delay)
//{
//	// 创建一个缩放动画，1 秒后消失
//	auto scaleTo = gcnew ScaleTo(0.3f, 0.0f);
//	auto delay1 = gcnew Delay(delay);
//	auto sequence1 = gcnew Sequence({ delay1->clone(),scaleTo });
//	jewel->runAction(sequence1);
//}

void Jewel::Break(){

	auto scaleTo = gcnew ScaleTo(0.3f, 0.0f);

	this->runAction(scaleTo);
}

Jewel::~Jewel()
{
}
