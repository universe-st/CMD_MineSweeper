#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<math.h>
#include<fstream>
using namespace std;
int length = 30, width = 30, lnum = 50;//全局变量，设置初始长度，宽度，雷数量
bool vol = true;//设置声音开启
const string cirnum[8] = { "１","２","３","４","５","６","７","８" };//定义string数组，用全角数字表示方块周围雷的数量
void swap(int &a, int &b)//定义交换函数
{
	int tem = a;
	a = b;
	b = tem;
}
int random(double start, double end)//定义随机数函数
{
	return int(start + (end - start)*rand() / (RAND_MAX + 1.0));
}
int main()
{
	ofstream ranko("phb.dat", ios::app);//建立一个排行榜文件，从尾部写入数据
	ranko << "";
	system("color 78");//设置背景颜色
	srand(unsigned(time(0)));//重置随机数种子
	while (1)
	{
		int select = 1;//定义初始选择项
		while (1)
		{
			system("Cls");
			cout << "_________________________________\n";//输出界面
			cout << "|                               |\n";
			cout << "|     扫雷 C++练习              |\n";
			cout << "|                               |\n";
			cout << "| BY  ECNU kuangthre            |\n";
			cout << "|                               |\n";
			switch (select)//按选择项输出界面
			{
			case 1:
			{
				cout << "|     ■开始游戏                |\n";
				cout << "|                               |\n";
				cout << "|     □修改设置                |\n";
				cout << "|                               |\n";
				cout << "|     □排行榜                  |\n";
				cout << "|                               |\n";
				cout << "|     □退出游戏                |\n";
				break;
			}
			case 2:
			{
				cout << "|     □开始游戏                |\n";
				cout << "|                               |\n";
				cout << "|     ■修改设置                |\n";
				cout << "|                               |\n";
				cout << "|     □排行榜                  |\n";
				cout << "|                               |\n";
				cout << "|     □退出游戏                |\n";
				break;
			}
			case 3:
			{
				cout << "|     □开始游戏                |\n";
				cout << "|                               |\n";
				cout << "|     □修改设置                |\n";
				cout << "|                               |\n";
				cout << "|     ■排行榜                  |\n";
				cout << "|                               |\n";
				cout << "|     □退出游戏                |\n";
				break;
			}
			case 4:
			{
				cout << "|     □开始游戏                |\n";
				cout << "|                               |\n";
				cout << "|     □修改设置                |\n";
				cout << "|                               |\n";
				cout << "|     □排行榜                  |\n";
				cout << "|                               |\n";
				cout << "|     ■退出游戏                |\n";
				break;
			}
			}
			cout << "|                               |\n";
			cout << "|_______________________________|\n";
			cout << "W:上 S:下 SPACE:确认\n请全屏进行游戏，并关闭输入法";
			bool oth = true, conf = false;//按选择项定义布尔值
			while (oth)
			{
				char an = _getch();//获取键盘按键
				if (an == 'w' || an == 'W')
				{
					select--;//选项上移
					oth = false;
				}
				else if (an == 's' || an == 'S')
				{
					select++;
					oth = false;//下移
				}
				else if (an == ' ')
				{
					conf = true;//确认选项
					oth = false;
				}
				if (select > 4)select -= 4;
				else if (select < 1)select += 4;//防止超出
			}
			if (conf)//如果按了空格键，按选项进行操作
			{
				if (select == 1)
				{
					break;//直接跳出循环开始游戏
				}
				else if (select == 2)
				{
					system("Cls");//清屏，输出设置界面
					while (1)
					{
						cout << "请设置雷区长度（默认30 取值范围15~30）：";
						cin >> length;
						if (length >= 15 && length <= 30)break;
					}
					while (1)
					{
						cout << "请设置雷区宽度（默认30 取值范围15~30）：";
						cin >> width;
						if (width >= 15 && width <= 30)break;
					}
					while (1)
					{
						cout << "请设置雷的数量（默认50 取值范围10~50）：";
						cin >> lnum;
						if (lnum >= 10 && lnum <= 50)break;
					}
					while (1)
					{
						cout << "请设置是否开启声音（默认开启）1.开启 0.关闭：";
						cin >> vol;
						if (vol == 1 || vol == 0)break;
					}
				}
				else if (select == 3)//读取排行榜数据
				{
					system("Cls");
					ifstream rank("phb.dat");
					int ranks[1000];
					int iph = 0;
					while (!rank.eof())
					{
						rank >> ranks[iph];
						iph++;
					}
					iph--;
					int f = 0;
					while (1)
					{
						for (int i = 0; i < iph; i++)
						{
							if (ranks[i]<ranks[i + 1])
							{
								swap(ranks[i], ranks[i + 1]);
							}
						}
						if (f == iph)break;
						f++;
					}
					for (int i = 0; i <= iph; i++)
					{
						cout << "第" << i + 1 << "名: " << ranks[i] << "分\n";
					}
					system("pause");
				}
				else if (select == 4)
				{
					return 1;//退出程序
				}
			}
		}
		while (1)//第二个循环，游戏开始
		{
			system("Cls");//清屏
			int lei[100][100];//记录雷的位置的二维数组
			for (int l = 0; l < width; l++)
			{
				for (int w = 0; w < length; w++)
				{
					lei[l][w] = 0;//初始化
				}
			}
			for (int leish = 0; leish < lnum; leish++)
			{
				lei[leish%length][leish / length] = 1;
			}//将第一行设置为雷区
			for (int leish = 0; leish < lnum; leish++)
			{
				int sj1 = random(0, length), sj2 = random(0, width);
				swap(lei[leish%length][leish / length], lei[sj1][sj2]);
			}//将第一行的格子与界面上随机格子进行交换
			for (int s = 0; s < (length*width); s++)
			{
				int sj1 = random(0, length);
				int sj2 = random(0, width);
				int sj3 = random(0, length);
				int sj4 = random(0, width);
				swap(lei[sj1][sj2], lei[sj3][sj4]);
			}//整体随机交换，进一步打乱，得到随机的lei数组
			int ln[100][100];//定义显示格子周围雷的数目的数组
			for (int l = 0; l < 100; l++)
			{
				for (int w = 0; w < 100; w++)
				{
					ln[l][w] = 0;//初始化
				}
			}
			for (int l = 0; l < width; l++)//判断每个格子周围的雷的数量并赋值到数组中
			{
				for (int w = 0; w < length; w++)
				{
					if (lei[w][l] != 1)
					{
						if (lei[w - 1][l] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w - 1][l - 1] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w][l - 1] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w + 1][l + 1] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w][l + 1] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w + 1][l] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w + 1][l - 1] == 1)
						{
							ln[w][l]++;
						}
						if (lei[w - 1][l + 1] == 1)
						{
							ln[w][l]++;
						}
					}
				}
			}
			int map[100][100], flag[100][100];//定义判断雷区是否开启和标记地雷的数组
			for (int i1 = 0; i1 < 100; i1++)
			{
				for (int i2 = 0; i2 < 100; i2++)
				{
					map[i1][i2] = 0;
					flag[i1][i2] = 0;//一起初始化
				}
			}
			int bx = 0, by = 0, outcome, success = 0, flagn = 0;//定义光标位置，游戏结果，成功标记数目，总标记数目
			long long ustime = time(NULL);
			while (1)
			{
				system("Cls");
				cout << "雷数：" << lnum - flagn << endl;
				for (int li = 0; li < length; li++)
				{
					cout << "--";
				}
				cout << endl;
				for (int i2 = 0; i2 < width; i2++)//按几个数组输出整个场景界面
				{
					for (int i1 = 0; i1 < length; i1++)
					{
						if (i1 == bx&&i2 == by)
						{
							cout << "◆";
						}
						else if (flag[i1][i2] == 1)
						{
							cout << "♀";
						}
						else if (map[i1][i2] == 0)
						{
							cout << "■";
						}
						else if (map[i1][i2] == 1)
						{
							if (ln[i1][i2]>0)
								cout << cirnum[ln[i1][i2] - 1];
							else
								cout << "  ";
						}
					}
					cout << "|" << endl;
				}
				for (int li = 0; li < length; li++)
				{
					cout << "--";
				}
				cout << endl;
				cout << "WSAD上下左右移动，按1开辟地图，按2标记地雷位置，按3取消标记\n";
				char an = _getch();
				int f5 = 0;
				if (an == 'w' || an == 'W')
				{
					if (by > 0)by--;
				}
				else if (an == 's' || an == 'S')
				{
					if (by < width - 1)by++;
				}
				else if (an == 'a' || an == 'A')
				{
					if (bx > 0)bx--;
				}
				else if (an == 'd' || an == 'D')
				{
					if (bx < length - 1)bx++;
				}
				else if (an == '1'&&map[bx][by] == 0)
				{
					if (lei[bx][by] == 1)
					{
						outcome = 1;
						break;
					}
					else
					{
						if (vol)
						{
							cout << "\a";
						}
						f5 = 1;
						map[bx][by] = 5;
					}
				}
				else if (an == '2'&&map[bx][by] == 0)
				{
					if (vol)
					{
						Beep(400, 200);
					}
					flag[bx][by] = 1;
					if (lei[bx][by] == 1)success++;
					flagn++;
				}
				else if (an == '3'&&flag[bx][by] == 1)
				{
					flag[bx][by] = 0;
					if (lei[bx][by] == 1)success--;
					flagn--;
				}
				if (f5)
				{
					while (1)
					{
						int none = 0;
						for (int i2 = 0; i2 < width; i2++)
						{
							for (int i1 = 0; i1 < length; i1++)
							{
								if (map[i1][i2] == 5)//开辟地图
								{
									none = 1;
									map[i1][i2] = 1;
									if (flag[i1][i2] == 1)flag[i1][i2] = 0;
									if (ln[i1][i2] == 0)
									{
										if (map[i1 - 1][i2] == 0)map[i1 - 1][i2] = 5;
										if (map[i1 + 1][i2] == 0)map[i1 + 1][i2] = 5;
										if (map[i1][i2 + 1] == 0)map[i1][i2 + 1] = 5;
										if (map[i1][i2 - 1] == 0)map[i1][i2 - 1] = 5;
									}
								}
							}
						}
						if (!none)break;
					}
				}
				if (success >= lnum)
				{
					outcome = 0;
					break;
				}
			}
			system("Cls");
			for (int li = 0; li < length; li++)
			{
				cout << "--";
			}
			cout << endl;
			for (int w = 0; w < width; w++)
			{
				for (int l = 0; l < length; l++)
				{
					if (lei[l][w] == 1)
					{
						cout << "★";
					}
					else if (ln[l][w] > 0)
					{
						cout << cirnum[ln[l][w] - 1];
					}
					else
					{
						cout << "  ";
					}

				}
				cout << "|" << endl;
			}
			for (int li = 0; li < length; li++)
			{
				cout << "--";
			}
			cout << endl;
			if (!outcome)
			{
				if (vol)
				{
					cout << "\a";
				}
				long long endtime = time(NULL);
				cout << "你获得了胜利！耗时" << endtime - ustime << "秒\n";
				cout << "评分【雷数平方X10000/（雷区面积+耗时X10）】:";
				double score;
				score = (lnum*lnum) * 10000 / (width*length + (endtime - ustime) * 10);
				cout << score << endl;
				ranko << score << endl;
			}
			else
			{
				if (vol)
				{
					Beep(500, 1500);
				}
				cout << "游戏失败！\n";
			}
			cout << "按任意键重新开始，按B返回，按E退出\n";
			char an = _getch();
			if (an == 'B' || an == 'b')
			{
				break;
			}
			else if (an == 'e' || an == 'E')
			{
				return 0;
			}
			system("pause");
		}
	}
	return 0;
}
