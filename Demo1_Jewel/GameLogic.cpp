#include "GameLogic.h"

//构造器
GameLogic::GameLogic()
{
    this->game_running = true;
    this->map = new int* [MAPCOLNUM];
    for (int i = 0; i < MAPCOLNUM; i++)
        map[i] = new int[MAPROWNUM];
    //初始化棋盘，确保不是死局
    this->BuildMap();
    int loc[4];
    memcpy(loc, this->hint(), sizeof(loc));
    while (loc[0] == 99)
    {
        this->BuildMap();
        memcpy(loc, this->hint(), sizeof(loc));
    }
}

//用于设置关卡有至多几种宝石，即设置species
void GameLogic::setSpeices(int n)
{
    this->species = n;
}

//设置游戏运行状态
void GameLogic::setGameState(bool state)
{
    this->game_running = state;
}

//返回游戏运行状态
bool GameLogic::ifGameRunning()
{
    return this->game_running;
}

//生成不三连的图形，用于调用来初始化地图,，将8*8随机数矩阵传递给map二维数组中
void GameLogic::BuildMap()
{
    int gemnum;//宝石编号，从1-8
    srand((int)time(0));

    //初始生成8*8的数字矩阵
    for (int n = 0; n < MAPROWNUM; n++) {
        for (int m = 0; m < MAPCOLNUM; m++) {
            gemnum = rand() % this->species + 1; //生成1-species的随机数
            map[n][m] = gemnum;
        }
    }

    //检查，确保初始棋盘无连一起的子
    while (checkmap())
    {
        //判断横向是否有相邻的三个宝石相同,并修改
        for (int j = 0; j < MAPROWNUM; j++) {
            for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
                int check[3]; //用于检查宝石是否相同
                for (int n = 0; n < 3; n++) {
                    check[n] = map[j][i + n];
                }
                if (check[0] == check[1] && check[1] == check[2]) {
                    //修改中间一颗的宝石种类
                    while (check[1] == check[0]) {
                        check[1] = rand() % species + 1;
                        map[j][i + 1] = check[1];
                    }
                }
            }
        }

        //判断纵向是否有相邻的三个宝石相同，并修改
        for (int j = 0; j < MAPCOLNUM; j++) {
            for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
                int check[3]; //用于检查宝石是否相同
                for (int n = 0; n < 3; n++) {
                    check[n] = map[i + n][j];
                }
                if (check[0] == check[1] && check[1] == check[2]) {
                    //修改中间一颗宝石种类
                    while (check[1] == check[0]) {
                        check[1] = rand() % species + 1;
                        map[i + 1][j] = check[1];
                    }
                }
            }
        }
    }

    //打印棋盘，测试
    for (int n = 0; n < 8; n++)
    {
        for (int m = 0; m < 8; m++)
        {
            cout << map[n][m] << " ";
        }
        cout << endl;

    }
}


//判断地图中是否有相邻的三个宝石相同
bool GameLogic::checkmap() {
    //判断横向是否有相邻的三个宝石相同
    for (int j = 0; j < MAPROWNUM; j++) {
        for (int i = 0; i < MAPCOLNUM - 3 + 1; i++) {
            int check[3]; //用于检查宝石是否相同
            for (int n = 0; n < 3; n++) {
                check[n] = map[j][i + n];
            }
            if (check[0] == check[1] && check[1] == check[2]) {
                return true;
            }
        }
    }

    //判断纵向是否有相邻的三个宝石相同
    for (int j = 0; j < MAPCOLNUM; j++) {
        for (int i = 0; i < MAPROWNUM - 3 + 1; i++) {
            int check[3]; //用于检查宝石是否相同
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


//判断能否交换（不相邻或无法消子，返回false）后续需要用eliminate
bool GameLogic::swap(int a, int b, int m, int n)
{
    //如果游戏处于暂停，直接返回false
    if (!game_running)
        return false;
    int temp;
    //只有选中的两子在同一行或同一列，且相邻，才能交换
    if (a == m) //同行情况
    {
        //如果相邻，交换看看能不能消子
        if ((b - n) == 1 || (b - n) == -1)//相邻
        {
            //交换
            temp = map[a][b];
            map[a][b] = map[m][n];
            map[m][n] = temp;
            //交换后，检查有没有形成连子
            if (checkmap())
                return true;
            else //如果交换后没有形成连子，换回去
            {
                temp = map[a][b];
                map[a][b] = map[m][n];
                map[m][n] = temp;

                return false;
            }
        }
        //如果不相邻，直接返回不能换
        else
            return false;
    }
    //俩子在同一列的情况
    else if (b == n)
    {
        //如果相邻，交换看看能不能消子
        if ((a - m) == 1 || (a - m) == -1)
        {
            temp = map[a][b];
            map[a][b] = map[m][n];
            map[m][n] = temp;
            //交换后，检查有没有形成连子
            if (checkmap())
                return true;
            else //如果交换后没有形成连子，换回去
            {
                temp = map[a][b];
                map[a][b] = map[m][n];
                map[m][n] = temp;

                return false;
            }
        }
        //如果不相邻，直接返回不能换
        else
            return false;
    } //end of if (b==n)
    else //如果两个子不在同一行或同列
        return false;
}



//消子，并返回得分
int GameLogic::eliminate()
{
    int temp[MAPROWNUM][MAPCOLNUM]; //复制一份地图，便于操作
    int score = 0; //加分，初始0
    int current = 0; //当前棋子花色
    //将地图复制到temp
    memcpy(temp, map, sizeof(map));

    //检查同一列的连子
    for (int j = 0; j < MAPCOLNUM; j++)
    {
        for (int i = 0; i < MAPROWNUM - 2; i++)
        {
            current = map[i][j];
            //如果有同一列的三连
            if (current == map[i + 1][j] && current == map[i + 2][j])
            {
                //注意改的是temp
                temp[i][j] = 0;
                temp[i + 1][j] = 0;
                temp[i + 2][j] = 0;
            }
        }
    }

    //检查同一行的连子
    for (int j = 0; j < MAPROWNUM; j++)
    {
        for (int i = 0; i < MAPCOLNUM - 2; i++)
        {
            current = map[j][i]; //当前子
            if (current == map[j][i + 1] && current == map[j][i + 2])
            {
                temp[j][i] = 0;
                temp[j][i + 1] = 0;
                temp[j][i + 2] = 0;
            }
        }
    }

    //计算分值，主要看矩阵中0元素的个数
    for (int i = 0; i < MAPROWNUM; i++)
    {
        for (int j = 0; j < MAPCOLNUM; j++)
        {
            if (temp[i][j] == 0)
                score += 50; //一个0加五十
        }
    }

    //修改map
    memcpy(map, temp, sizeof(map));

    //返回得分
    return score;
}


//棋子下移，更新棋盘
void GameLogic::down()
{
    //设置随机数种子
    srand((int)time(0));
    //将为0的子用上面的子补上，并将空缺处补上随机数
    for (int i = 0; i < 8; i++)
    {
        //从最后一行往上找
        for (int j = 7; j >= 0; j--)
        {
            //当消的子都在一列上时，要连续掉好几个
            while (map[j][i] == 0)
            {
                //这个棋子以上所有棋子下移一个
                for (int k = j; k > 0; k--)
                {
                    map[k][i] = map[k - 1][i];
                }
                //补上第一行的空
                map[0][i] = rand() % species + 1;
            }
        }
    }
}


//由hint函数调用，来判断相应两子交换后能否产生连子
bool GameLogic::exchange(int a, int b, int m, int n)
{
    bool flag = false; //可以形成连子则变true
    //先将两子交换，最后要换回去
    int temp = map[a][b];
    map[a][b] = map[m][n];
    map[m][n] = temp;
    //调用函数，检查交换后是否形成连子
    if (checkmap())
        flag = true;

    //将棋子换回去
    temp = map[a][b];
    map[a][b] = map[m][n];
    map[m][n] = temp;

    return flag;
}

//提示
int* GameLogic::hint()
{
    int* location;
    //没有找到可交换时，location[0] = 99
    location = new int[4]{ 99 };
    //现试同一行两个子互换
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

    //再试同一列两个子互换
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
