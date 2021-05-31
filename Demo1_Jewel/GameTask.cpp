#include<iostream>
#include"GameTask.h"

using namespace std;

//�˺������ڳ�ʼ���ؿ���Ϣ
//����l����ǰΪ��l�ؿ�


GameTask::GameTask(int l) {
	int n = 5;//��ǰ�ؿ���ӵ�еı�ʯ����
	level = l;
	//���ݹؿ��ݽ����ӱ�ʯ������������Ϸ�Ѷ�
	if (l == 1 || l == 2) {
		n = 5;
	}
	if (l == 3 || l == 4) {
		n = 6;
	}
	if (l == 5 || l == 6) {
		n = 7;
	}
	//�����ؿ���Ŀ���ֵ
	if (level == 1 || level == 3 || level == 5) {
		goal = 2000;
	}
	//ż���ؿ���Ŀ���ֵ
	else {
		goal = 3000;
	}
	//��ʼ�������߼�����
	gl = new GameLogic();
	//���������б�ʯ����
	gl->setSpeices(n);



}

//�������̳�ʼ״̬������
int** GameTask::initState() {
	return gl->map;
}

//�˺������ڸ����û������Ϣ�������̱仯���
//����Ϊ���潻�����ӵĺ���λ�õ�����
//eg��pos={1,2,1,3},���������Ҫ������һ�еڶ����������һ�е���������
//����ֵΪ�洢�û��˴β���������һϵ�б仯�ľ������������������������
MatrixNode* GameTask::breakTask(int* pos) {
	int a, b, c, d;
	a = pos[0]; b = pos[1]; c = pos[2]; d = pos[3];
	//���ú����ж��ܷ�����
	bool swapsuc = gl->swap(a, b, c, d);
	//������ʯ�ɹ�ʱ
	if (swapsuc) {
		//���ú������ش˴����ӵ÷�
		int curStep = gl->eliminate();
		//���´˹ؿ���ǰ����
		curGrade += curStep;
		//ͷ����д�����Ӻ�0����
		head = new MatrixNode;
		//head->map = gl->map;
		mapcpy(head->map, gl->map);
		//�������ӣ���������
		gl->down();
		//�洢���º����״̬����������
		MatrixNode* afterRenew = new MatrixNode;
		//afterRenew->map = gl->map;
		mapcpy(afterRenew->map, gl->map);
		head->next = afterRenew;
		afterRenew->next = nullptr;

		//���������̺����������ʯ��ͬ��������������
		while (gl->checkmap()) {
			//���ú������ش˴����ӵ÷�
			int moreGrade = gl->eliminate();
			//���´˹ؿ���ǰ����
			curGrade += moreGrade;
			//����д�����Ӻ�0����
			MatrixNode* pre = new MatrixNode;
			//pre->map = gl->map;
			mapcpy(pre->map, gl->map);
			MatrixNode* q = head;
			//�ҵ�β���
			while (q->next != nullptr)
				q = q->next;
			q->next = pre;
			//�������ӣ���������
			gl->down();
			//�洢���º����״̬����������
			MatrixNode* afterRenew = new MatrixNode;
			//afterRenew->map = gl->map;
			mapcpy(afterRenew->map, gl->map);
			pre->next = afterRenew;
			afterRenew->next = nullptr;
		}
		return head;
	}

	//���û�������ʯ������ʱ�����ؿ�ָ��
	else {
		return nullptr;
		//����head
	}


}
//�˺��������ж�����Ƿ�ﵽĿ�����
//����ֵΪ����ֵ���ﵽΪ�棬����Ϊ��
bool GameTask::getWin() {
	if (curGrade >= goal)
		return true;
	else
		return false;
}
//�˺��������������жϵ�ǰ�Ƿ�Ϊ����
bool  GameTask::getDeadlock() {
	//��int�з�������
	int* idea = gl->hint();
	//������ĵ�һ��ֵΪ99����ǰΪ����
	if (idea[0] == 99)
		return true;
	else
		return false;
}

//�������ֺ���µ�������Ϣ
int** GameTask::getNewState() {
	//�������̣�ȷ����������
	gl->BuildMap();
	int loc[4];
	memcpy(loc, gl->hint(), sizeof(loc));
	while (loc[0] == 99)
	{
		gl->BuildMap();
		memcpy(loc, gl->hint(), sizeof(loc));
	}
	return gl->map;
}
//��ȡ��ǰ����
int GameTask::getScore() {
	return curGrade;
}
//��ȡ��ʾ����
int* GameTask::getHint() {
	int* idea = gl->hint();
	return idea;
}
GameLogic* GameTask::getLogic()
{
	return this->gl;
}
void GameTask::mapcpy(int** dist, int** src)
{
	for (int i = 0; i < MAPROWNUM; i++)
	{
		for (int j = 0; j < MAPCOLNUM; j++)
		{
			dist[i][j] = src[i][j];
		}
	}
}
//��������
GameTask::~GameTask() {
	delete gl;
	delete head;
}
