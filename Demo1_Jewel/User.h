#include<string>
using namespace std;
class User {
private:
	int number;//�û���ţ�����ע��˳�����������������а����Ϣ
	string name;//�û�����
	string password;//�û�����
	int* taskGrade;//�ֱ��Ŵ���ģʽ6�صķ�����ÿ�ؽ���ʱ���£��������ݿ�/�ļ�
	//��ע��ʱ�����û������ʼ�� taskGrade = new int[6]��ÿ��Ԫ��Ϊ0
	//���¼ʱ�����ݿ�/�ļ��ж�ȡ�����Ϣ����ȡÿ��Ԫ��ֵ
	int limTimeGrade;//����ģʽ����ҷ���


public:
	//�����û����
	int getNumber() { return number; };

};