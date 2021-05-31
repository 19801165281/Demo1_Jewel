#include<iostream>
#include"GameTask.h"

using namespace std;

//此函数用于初始化关卡信息
//参数l代表当前为第l关卡


GameTask::GameTask(int l) {
	int n = 5;//当前关卡所拥有的宝石种类
	level = l;
	//根据关卡递进增加宝石数量，增大游戏难度
	if (l == 1 || l == 2) {
		n = 5;
	}
	if (l == 3 || l == 4) {
		n = 6;
	}
	if (l == 5 || l == 6) {
		n = 7;
	}
	//奇数关卡的目标分值
	if (level == 1 || level == 3 || level == 5) {
		goal = 2000;
	}
	//偶数关卡的目标分值
	else {
		goal = 3000;
	}
	//初始化棋盘逻辑对象
	gl = new GameLogic();
	//设置棋盘中宝石个数
	gl->setSpeices(n);



}

//返回棋盘初始状态的数组
int** GameTask::initState() {
	return gl->map;
}

//此函数用于根据用户点击信息返回棋盘变化情况
//参数为保存交换棋子的横纵位置的数组
//eg：pos={1,2,1,3},代表玩家想要交换第一行第二列棋子与第一行第三列棋子
//返回值为存储用户此次操作后棋盘一系列变化的矩阵链表，用于主界面更新棋盘
MatrixNode* GameTask::breakTask(int* pos) {
	int a, b, c, d;
	a = pos[0]; b = pos[1]; c = pos[2]; d = pos[3];
	//调用函数判断能否消子
	bool swapsuc = gl->swap(a, b, c, d);
	//当消宝石成功时
	if (swapsuc) {
		//调用函数返回此次消子得分
		int curStep = gl->eliminate();
		//更新此关卡当前分数
		curGrade += curStep;
		//头结点中存放消子后含0矩阵
		head = new MatrixNode;
		//head->map = gl->map;
		mapcpy(head->map, gl->map);
		//下移棋子，更新棋盘
		gl->down();
		//存储更新后矩阵状态并加入链表
		MatrixNode* afterRenew = new MatrixNode;
		//afterRenew->map = gl->map;
		mapcpy(afterRenew->map, gl->map);
		head->next = afterRenew;
		afterRenew->next = nullptr;

		//当更新棋盘后出现三个宝石相同，则出现连消情况
		while (gl->checkmap()) {
			//调用函数返回此次消子得分
			int moreGrade = gl->eliminate();
			//更新此关卡当前分数
			curGrade += moreGrade;
			//结点中存放消子后含0矩阵
			MatrixNode* pre = new MatrixNode;
			//pre->map = gl->map;
			mapcpy(pre->map, gl->map);
			MatrixNode* q = head;
			//找到尾结点
			while (q->next != nullptr)
				q = q->next;
			q->next = pre;
			//下移棋子，更新棋盘
			gl->down();
			//存储更新后矩阵状态并加入链表
			MatrixNode* afterRenew = new MatrixNode;
			//afterRenew->map = gl->map;
			mapcpy(afterRenew->map, gl->map);
			pre->next = afterRenew;
			afterRenew->next = nullptr;
		}
		return head;
	}

	//当用户交换后宝石不可消时，返回空指针
	else {
		return nullptr;
		//发送head
	}


}
//此函数用于判断玩家是否达到目标分数
//返回值为布尔值，达到为真，否则为假
bool GameTask::getWin() {
	if (curGrade >= goal)
		return true;
	else
		return false;
}
//此函数用于主界面判断当前是否为死局
bool  GameTask::getDeadlock() {
	//从int中返回数组
	int* idea = gl->hint();
	//若数组的第一个值为99，则当前为死局
	if (idea[0] == 99)
		return true;
	else
		return false;
}

//返回死局后更新的棋盘信息
int** GameTask::getNewState() {
	//更新棋盘，确保不是死局
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
//获取当前分数
int GameTask::getScore() {
	return curGrade;
}
//获取提示数组
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
//析构函数
GameTask::~GameTask() {
	delete gl;
	delete head;
}
