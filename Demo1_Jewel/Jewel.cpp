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
	// 获取按钮状态
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
	// 保存信息到文件
	Data::saveBool(L"isSelected", isSelected);
}

void Jewel::Break()
{
	// 创建一个缩放动画，1 秒后缩放到原始大小的 0.5 倍
	auto scaleTo = gcnew ScaleTo(1, 0.5f);

}

Jewel::~Jewel()
{
}
