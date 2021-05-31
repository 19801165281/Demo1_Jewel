#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

//The class of the Jewel
class Jewel :
	public Node
{
public:
	//宝石的位置
	float pos_row;
	float pos_col;
	//宝石的控制按钮
	Button* jewel_btn;
	Sprite* border;
	//std::vector<std::vector<Jewel*>> map;
	//宝石是否被选中
	bool isSelected;
	Jewel();
	//选择宝石动画
	void Select();
	//交换两个宝石的动画
	void static Exchange(Jewel* jewel1, Jewel* jewel2);
	//宝石下落的动画
	void Fall();
	//宝石消失的动画
	void Break();
	~Jewel();
};

