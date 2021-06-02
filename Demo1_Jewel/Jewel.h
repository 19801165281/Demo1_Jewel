#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

//The class of the Jewel
class Jewel :
	public Node
{
public:
	//��ʯ��λ��
	float pos_row;
	float pos_col;
	//��ʯ�ı��
	int pic_num;
	//��ʯ�Ŀ��ư�ť
	Button* jewel_btn;
	Sprite* border;
	//��ʯ�Ƿ�ѡ��
	bool isSelected;
	Jewel();
	Jewel(int pic_num);
	//ѡ��ʯ����
	void Select();
	//����������ʯ�Ķ���
	void static Exchange(Jewel* jewel1, Jewel* jewel2, double delay, bool ifReturn);
	////��ʯ����Ķ���
	//void static Fall(Jewel* jewel, double delay, int distance);

	void Fall(int fall_grids);
	void Break();
	////��ʯ��ʧ�Ķ���
	//void static Break(Jewel* jewel,double delay);
	~Jewel();
};

