#include "Jewel.h"

Jewel::Jewel()
{
	isSelected = false;
	jewel_btn = gcnew Button(gcnew Sprite(L"res\\1_01.png"));
	jewel_btn->setClickFunc(std::bind(&Jewel::Select, this));
	this->addChild(jewel_btn);
	border = gcnew Sprite(L"res\\onChoosing.png");
	border->setScale(0.5f);
	border->setPosX(jewel_btn->getWidth() / 2);
	border->setPosY(jewel_btn->getHeight() / 2);
	//printf("\n%f, %f", jewel_btn->getPosX(), jewel_btn->getPosY());
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
	}
	else
	{
		isSelected = false;
		border->setVisible(isSelected);
	}
	// ������Ϣ���ļ�
	Data::saveBool(L"isSelected", isSelected);
}

Jewel::~Jewel()
{
}
