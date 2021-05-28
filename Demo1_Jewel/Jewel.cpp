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

void Jewel::Exchange(Jewel* jewel1, Jewel* jewel2)
{
	//�������ƶ���
	auto moveRight = gcnew MoveBy(0.2f, Vector2(100, 0));
	
	//�������ƶ���
	auto moveLeft = gcnew MoveBy(0.2f, Vector2(-100, 0));

	//ִ�ж���
	jewel1->runAction(moveRight);
	jewel2->runAction(moveLeft);
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
