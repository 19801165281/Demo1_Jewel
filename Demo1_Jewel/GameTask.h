#include"GameLogic.h"
#include"MatrixNode.h"
using namespace std;
class GameTask {
public:
	GameTask(int l);//参数为当前关卡数
	~GameTask();
	MatrixNode* breakTask(int* pos);//用于对用户的消子操作进行循环，返回达到目标时所用步数。
	int** initState();//返回棋盘的初始状态
	bool getWin();//返回是否已达到目标分值
	bool getDeadlock();//返回当前是否是死局
	int** getNewState();//返回新的棋盘状态
	int getScore();//返回当前分值
	int* getHint();//返回提示中两个宝石的坐标信息
	GameLogic* getLogic();//返回GameLogic对象
	static void mapcpy(int** dist, int** src);
private:
	int level = 0;//当前关卡数，范围为1-6
	int step = 0;//用户当前所走步数
	int goal = 0;//此关卡目标分数
	int curGrade = 0;//次关卡当前分数，在过程中根据消子个数更新
	GameLogic* gl;//游戏逻辑对象
	MatrixNode* head = nullptr;//矩阵链表头结点

};
