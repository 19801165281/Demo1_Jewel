#include "GameLogic.h"
#include "GameTask.h"

//������
GameLogic::GameLogic()
{
    this->game_running = true;
    this->map = new int* [MAPCOLNUM];
    for (int i = 0; i < MAPCOLNUM; i++)
        map[i] = new int[MAPROWNUM];
    //��ʼ�����̣�ȷ����������
    this->BuildMap();
    int loc[4];
    memcpy(loc, this->hint(), sizeof(loc));
    while (loc[0] == 99)
    {
        this->BuildMap();
        memcpy(loc, this->hint(), sizeof(loc));
    }
}

//�������ùؿ������༸�ֱ�ʯ��������species
void GameLogic::setSpeices(int n)
{
    this->species = n;
}

//������Ϸ����״̬
void GameLogic::setGameState(bool state)
{
    this->game_running = state;
}

//������Ϸ����״̬
bool GameLogic::ifGameRunning()
{
    return this->game_running;
}

//���ɲ�������ͼ�Σ����ڵ�������ʼ����ͼ,����8*8��������󴫵ݸ�map��ά������
void GameLogic::BuildMap()
{
    int gemnum;//��ʯ��ţ���1-8
    srand((int)time(0));

    //��ʼ����8*8�����־���
    for (int n = 0; n < MAPROWNUM; n++) {
        for (int m = 0; m < MAPCOLNUM; m++) {
            gemnum = rand() % this->species + 1; //����1-species�������
            map[n][m] = gemnum;
        }
    }

    //��飬ȷ����ʼ��������һ�����
    while (checkmap())
    {
        //�жϺ����Ƿ������ڵ�������ʯ��ͬ,���޸�
        for (int j = 0; j < MAPROWNUM; j++) {
            for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
                int check[3]; //���ڼ�鱦ʯ�Ƿ���ͬ
                for (int n = 0; n < 3; n++) {
                    check[n] = map[j][i + n];
                }
                if (check[0] == check[1] && check[1] == check[2]) {
                    //�޸��м�һ�ŵı�ʯ����
                    while (check[1] == check[0]) {
                        check[1] = rand() % species + 1;
                        map[j][i + 1] = check[1];
                    }
                }
            }
        }

        //�ж������Ƿ������ڵ�������ʯ��ͬ�����޸�
        for (int j = 0; j < MAPCOLNUM; j++) {
            for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
                int check[3]; //���ڼ�鱦ʯ�Ƿ���ͬ
                for (int n = 0; n < 3; n++) {
                    check[n] = map[i + n][j];
                }
                if (check[0] == check[1] && check[1] == check[2]) {
                    //�޸��м�һ�ű�ʯ����
                    while (check[1] == check[0]) {
                        check[1] = rand() % species + 1;
                        map[i + 1][j] = check[1];
                    }
                }
            }
        }
    }

    //��ӡ���̣�����
    this->printMap();
}


//�жϵ�ͼ���Ƿ������ڵ�������ʯ��ͬ
bool GameLogic::checkmap() {
    //�жϺ����Ƿ������ڵ�������ʯ��ͬ
    for (int j = 0; j < MAPROWNUM; j++) {
        for (int i = 0; i < MAPCOLNUM - 3 + 1; i++) {
            int check[3]; //���ڼ�鱦ʯ�Ƿ���ͬ
            for (int n = 0; n < 3; n++) {
                check[n] = map[j][i + n];
            }
            if (check[0] == check[1] && check[1] == check[2]) {
                return true;
            }
        }
    }

    //�ж������Ƿ������ڵ�������ʯ��ͬ
    for (int j = 0; j < MAPCOLNUM; j++) {
        for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
            int check[3]; //���ڼ�鱦ʯ�Ƿ���ͬ
            for (int n = 0; n < 3; n++) {
                check[n] = map[i + n][j];
            }
            if (check[0] == check[1] && check[1] == check[2]) {
                return true;
            }
        }
    }
    return false;
}


//�ж��ܷ񽻻��������ڻ��޷����ӣ�����false��������Ҫ��eliminate
bool GameLogic::swap(int a, int b, int m, int n)
{
    //�����Ϸ������ͣ��ֱ�ӷ���false
    if (!game_running)
        return false;
    int temp;
    //ֻ��ѡ�е�������ͬһ�л�ͬһ�У������ڣ����ܽ���
    if (a == m) //ͬ�����
    {
        //������ڣ����������ܲ�������
        if ((b - n) == 1 || (b - n) == -1)//����
        {
            //����
            temp = map[a][b];
            map[a][b] = map[m][n];
            map[m][n] = temp;
            //�����󣬼����û���γ�����
            if (checkmap())
                return true;
            else //���������û���γ����ӣ�����ȥ
            {
                temp = map[a][b];
                map[a][b] = map[m][n];
                map[m][n] = temp;

                return false;
            }
        }
        //��������ڣ�ֱ�ӷ��ز��ܻ�
        else
            return false;
    }
    //������ͬһ�е����
    else if (b == n)
    {
        //������ڣ����������ܲ�������
        if ((a - m) == 1 || (a - m) == -1)
        {
            temp = map[a][b];
            map[a][b] = map[m][n];
            map[m][n] = temp;
            //�����󣬼����û���γ�����
            if (checkmap())
                return true;
            else //���������û���γ����ӣ�����ȥ
            {
                temp = map[a][b];
                map[a][b] = map[m][n];
                map[m][n] = temp;

                return false;
            }
        }
        //��������ڣ�ֱ�ӷ��ز��ܻ�
        else
            return false;
    } //end of if (b==n)
    else //��������Ӳ���ͬһ�л�ͬ��
        return false;
}



//���ӣ������ص÷�
int GameLogic::eliminate()
{
    int **temp; //����һ�ݵ�ͼ�����ڲ���
    temp = (int**)malloc(sizeof(int*) * MAPROWNUM);
    if (!temp) exit(0);
    for (int i = 0; i < MAPCOLNUM; i++)
    {
        temp[i] = (int*)malloc(sizeof(int) * MAPCOLNUM);
        if (!temp[i]) exit(0);
    }
    int score = 0; //�ӷ֣���ʼ0
    int current = 0; //��ǰ���ӻ�ɫ
    //����ͼ���Ƶ�temp
    
    GameTask::mapcpy(temp, map);

    //���ͬһ�е�����
    for (int j = 0; j < MAPCOLNUM; j++)
    {
        for (int i = 0; i < MAPROWNUM - 2; i++)
        {
            current = map[i][j];
            //�����ͬһ�е�����
            if (current == map[i + 1][j] && current == map[i + 2][j])
            {
                //ע��ĵ���temp
                temp[i][j] = 0;
                temp[i + 1][j] = 0;
                temp[i + 2][j] = 0;
            }
        }
    }

    //���ͬһ�е�����
    for (int j = 0; j < MAPROWNUM; j++)
    {
        for (int i = 0; i < MAPCOLNUM - 2; i++)
        {
            current = map[j][i]; //��ǰ��
            if (current == map[j][i + 1] && current == map[j][i + 2])
            {
                temp[j][i] = 0;
                temp[j][i + 1] = 0;
                temp[j][i + 2] = 0;
            }
        }
    }

    //�����ֵ����Ҫ��������0Ԫ�صĸ���
    for (int i = 0; i < MAPROWNUM; i++)
    {
        for (int j = 0; j < MAPCOLNUM; j++)
        {
            if (temp[i][j] == 0)
                score += 50; //һ��0����ʮ
        }
    }

    //�޸�map
    GameTask::mapcpy(map, temp);
    this->printMap();//test
    //���ص÷�
    return score;
}


//�������ƣ���������
void GameLogic::down()
{
    //�������������
    srand((int)time(0));
    //��Ϊ0������������Ӳ��ϣ�������ȱ�����������
    for (int i = 0; i < 8; i++)
    {
        //�����һ��������
        for (int j = 7; j >= 0; j--)
        {
            //�������Ӷ���һ����ʱ��Ҫ�������ü���
            while (map[j][i] == 0)
            {
                //�����������������������һ��
                for (int k = j; k > 0; k--)
                {
                    map[k][i] = map[k - 1][i];
                }
                //���ϵ�һ�еĿ�
                map[0][i] = rand() % species + 1;
            }
        }
    }
}


//��hint�������ã����ж���Ӧ���ӽ������ܷ��������
bool GameLogic::exchange(int a, int b, int m, int n)
{
    bool flag = false; //�����γ��������true
    //�Ƚ����ӽ��������Ҫ����ȥ
    int temp = map[a][b];
    map[a][b] = map[m][n];
    map[m][n] = temp;
    //���ú�������齻�����Ƿ��γ�����
    if (checkmap())
        flag = true;

    //�����ӻ���ȥ
    temp = map[a][b];
    map[a][b] = map[m][n];
    map[m][n] = temp;

    return flag;
}

void GameLogic::printMap()
{
    //��ӡ���̣�����
    for (int n = 0; n < 8; n++)
    {
        for (int m = 0; m < 8; m++)
        {
            cout << map[n][m] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//��ʾ
int* GameLogic::hint()
{
    int* location;
    //û���ҵ��ɽ���ʱ��location[0] = 99
    location = new int[4]{ 99 };
    //����ͬһ�������ӻ���
    for (int i = 0; i < MAPROWNUM; i++)
        for (int j = 0; j < MAPCOLNUM - 1; j++)
        {
            if (exchange(i, j, i, j + 1))
            {
                location[0] = i;
                location[1] = j;
                location[2] = i;
                location[3] = j + 1;

                return location;
            }
        }

    //����ͬһ�������ӻ���
    for (int j = 0; j < MAPCOLNUM; j++)
        for (int i = 0; i < MAPROWNUM - 1; i++)
        {
            if (exchange(i, j, i + 1, j))
            {
                location[0] = i;
                location[1] = j;
                location[2] = i + 1;
                location[3] = j;

                return location;
            }
        }

    return location;
}
