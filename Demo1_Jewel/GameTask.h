#include"GameLogic.h"
#include"MatrixNode.h"
using namespace std;
class GameTask {
public:
	GameTask(int l);//����Ϊ��ǰ�ؿ���
	~GameTask();
	MatrixNode* breakTask(int* pos);//���ڶ��û������Ӳ�������ѭ�������شﵽĿ��ʱ���ò�����
	int** initState();//�������̵ĳ�ʼ״̬
	bool getWin();//�����Ƿ��ѴﵽĿ���ֵ
	bool getDeadlock();//���ص�ǰ�Ƿ�������
	int** getNewState();//�����µ�����״̬
	int getScore();//���ص�ǰ��ֵ
	int* getHint();//������ʾ��������ʯ��������Ϣ
	GameLogic* getLogic();//����GameLogic����
	static void mapcpy(int** dist, int** src);
private:
	int level = 0;//��ǰ�ؿ�������ΧΪ1-6
	int step = 0;//�û���ǰ���߲���
	int goal = 0;//�˹ؿ�Ŀ�����
	int curGrade = 0;//�ιؿ���ǰ�������ڹ����и������Ӹ�������
	GameLogic* gl;//��Ϸ�߼�����
	MatrixNode* head = nullptr;//��������ͷ���

};
