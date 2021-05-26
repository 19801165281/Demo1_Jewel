#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

//The class of the Jewel
class Jewel :
	public Node
{
public:
	Button* jewel_btn;
	Sprite* border;
	bool isSelected;
	Jewel();
	void Select();
	~Jewel();
};

