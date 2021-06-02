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
	//宝石的编号
	int pic_num;
	//宝石的控制按钮
	Button* jewel_btn;
	Sprite* border;
	//宝石是否被选中
	bool isSelected;
	Jewel();
	Jewel(int pic_num);
	//选择宝石动画
	void Select();
	//交换两个宝石的动画
	void static Exchange(Jewel* jewel1, Jewel* jewel2, double delay, bool ifReturn);
	////宝石下落的动画
	//void static Fall(Jewel* jewel, double delay, int distance);

	void Fall(int fall_grids);
	void Break();
	////宝石消失的动画
	//void static Break(Jewel* jewel,double delay);
	~Jewel();
};

