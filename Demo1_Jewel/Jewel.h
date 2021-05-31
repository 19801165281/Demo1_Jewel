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
	//��ʯ�Ŀ��ư�ť
	Button* jewel_btn;
	Sprite* border;
	//std::vector<std::vector<Jewel*>> map;
	//��ʯ�Ƿ�ѡ��
	bool isSelected;
	Jewel();
	//ѡ��ʯ����
	void Select();
	//����������ʯ�Ķ���
	void static Exchange(Jewel* jewel1, Jewel* jewel2);
	//��ʯ����Ķ���
	void Fall();
	//��ʯ��ʧ�Ķ���
	void Break();
	~Jewel();
};

