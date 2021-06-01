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
	// ��ȡ��ť״̬
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
	// ������Ϣ���ļ�
	Data::saveBool(L"isSelected", isSelected);
}

void Jewel::Exchange(Jewel* jewel1, Jewel* jewel2,double delay)
{
	//�������ƶ���
	auto moveRight = gcnew MoveBy(0.2f, Vector2(GRID_LENGTH, 0));

	//�������ƶ���
	auto moveLeft = gcnew MoveBy(0.2f, Vector2(-GRID_LENGTH, 0));

	//�������ƶ���
	auto moveup = gcnew MoveBy(0.2f, Vector2(0, GRID_LENGTH));

	//�������ƶ���
	auto movedown = gcnew MoveBy(0.2f, Vector2(0, -GRID_LENGTH));

	auto animation1 =  gcnew MoveBy(0.0f, Vector2(0, 0));
	auto animation2=  gcnew MoveBy(0.0f, Vector2(0, 0));
	
	//ִ�ж���
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

	jewel1->runAction(sequence1);
	jewel2->runAction(sequence2);

	jewel1->border->setVisible(false);
	jewel2->border->setVisible(false);
}

void Jewel::Fall()
{
	//����һ�����䶯��
	auto fallTo = gcnew MoveBy(0.2f, Vector2(0, 80));
	this->runAction(fallTo);
}

void Jewel::Break()
{
	// ����һ�����Ŷ�����1 ������ŵ�ԭʼ��С�� 0.5 ��
	auto scaleTo = gcnew ScaleTo(0.3f, 0.0f);
	this->runAction(scaleTo);
}

Jewel::~Jewel()
{
}
