#include<string>
using namespace std;
class User {
private:
	int number;//用户编号，根据注册顺序决定，方便管理排行榜等信息
	string name;//用户姓名
	string password;//用户密码
	int* taskGrade;//分别存放闯关模式6关的分数，每关结束时更新，存入数据库/文件
	//在注册时创建用户对象初始化 taskGrade = new int[6]，每个元素为0
	//或登录时从数据库/文件中读取玩家信息，读取每个元素值
	int limTimeGrade;//竞速模式下玩家分数


public:
	//返回用户编号
	int getNumber() { return number; };

};