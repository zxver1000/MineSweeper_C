#include "MinSweeper.h"
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<ctime>
#include<vector>
#include<Windows.h>
#include<conio.h>
#include<random>
#include<fstream>
using namespace std;

void MinSweeper::Loadgame()
{
	system("cls");
	cout << "********************" << endl;
	
	ifstream fin("save.txt");
	
	if (!fin.is_open()) 
		return;
	fin >> row >> col;
	fin >> difficulty;
	map = new int* [row];
	for (int i = 0; i < row; i++)
	{
		map[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			map[i][j] = 0;
		}
	}
	fin >>count;
	fin >> real_enter;
	total_size = row * col;
	init_visit();
	
	totoal_min_num = (total_size / 10) * difficulty;
	for (int i = 0; i < totoal_min_num; i++)
	{
		int a;
		int b;
		fin >> a>>b;
		mines.push_back(make_pair(a,b));
	}
	setmine();
	int x, y;
	for (int j = 0; j < real_enter; j++)
	{
		fin >> y >> x;
		replay.push(make_pair(y, x));
		load.push(make_pair(y, x));

	}
	
	setmine_hint();
	printfmap();
	 x = 0;
	 y = 2;
	gotoxt(x, y);
	count = 0;
	while (!load.empty())
	{
		y = load.front().first;
		x = load.front().second;
		gotoxt(x, y);
		load.pop();
		gotoxt(x * 2, y + 2);
		dfs(x, y);
		
	}


	y = row+2;
	gotoxt(x, y);
	key();

}

void MinSweeper::replay_game()
{
	system("cls");
	cout << "**********************" << endl;
	printfmap();
	Sleep(1000);
	int x = 0;
	int y = 2;
	gotoxt(x, y);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			visit[i][j] = 0;
		}
	}
	while (!replay.empty())
	{
		y = replay.front().first;
		x = replay.front().second;
		replay.pop();
		gotoxt(x * 2, y + 2);
		dfs(x, y);

		/*
		if (map[y][x] == 100)
			cout << "*";
		else
			cout << map[y][x];
			*/
		gotoxt(x * 2, y + 2);
		Sleep(1000);
	}
}

void MinSweeper::game()
{
	system("cls");
	//마인개수설정
	cout << "****************" << endl;

	cout << "원하는 지뢰찾기의 행과열을입력하세요" << endl;
	//maps.setMap();

	cin >> row >> col;
	cout << "원하는 지뢰찾기의 난이도를입력해주세요" << endl;
	cout << "1.Ease 2.Nomal 3.Hard" << endl;
	cin >> difficulty;
	map = new int* [row];
	for (int i = 0; i < row; i++)
	{
		map[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			map[i][j] = 0;
		}
	}
	init_visit();
	srand(time(0));

	std::random_device rd;
	std::mt19937 gen(rd());
	total_size = row * col;
	int total = row * col;
	totoal_min_num=(total_size/10) * difficulty;
	int witch;
	std::uniform_int_distribution<int> dis(0, row-1);
	std::uniform_int_distribution<int> diss(0, col-1);
	int mine_row;
	int mine_col;
	while (1)
	{
		if (mines.size() == totoal_min_num)
		{
			//마인개수끝설정완료
			break;
		}
		mine_row=dis(gen);
		mine_col = diss(gen);

		vector<pair<int,int>>::iterator alpa = find(mines.begin(), mines.end(),make_pair(mine_row,mine_col));
		witch = dis(gen);
		
		if (alpa != mines.end())
		{
			//중복
			continue;
		}
		else
		{
			mines.push_back(make_pair(mine_row,mine_col));
		}
	}
	sort(mines.begin(), mines.end());
	int rows;
	int cols;
	
	for (auto i = mines.begin(); i != mines.end(); i++)
	{
		rows = (*i).first;
		cols = (*i).second;
		map[rows][cols] = 100;//mine -> 100로설정하기

	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (map[i][j] == 100)
			{
				continue;
			}

			for (int k = i - 1; k < i + 2; k++)
			{
				for (int m = j - 1; m < j + 2; m++)
				{
					if (k<0 || m < 0 || k > row - 1 || m >col - 1)
						continue;
					if (map[k][m] == 100)
					{
						map[i][j]++;
					}
				}
			}
		}
	}


	/*
	for (auto it = mines.begin(); it != mines.end(); it++)
	{
		cout << *it << endl;

	}
	*/


	system("cls");
	cout << "****************" << endl;
	printfmap();
	key();






}

void MinSweeper::start()
{
	main_screen();
	int al;
	cin >> al;
	if (al == 1)
		game();
	else if (al == 2)
	{
		Loadgame();
	}
	else if (al == 3)
	{
		return;
	}
	



}

MinSweeper::~MinSweeper()
{
	if (map != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}
	map = nullptr;

	if (visit != nullptr)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] visit[i];
		}
		delete[] visit;
	}
	visit = nullptr;

}

void MinSweeper::key()
{

	int x = 0;
	int y = 2;
	cout << endl;
	cout << endl;

	//답지
	/*
	for (int i = 0; i < row; i++)
	{

		for (int j = 0; j < col; j++)
		{

			if (map[i][j] == 100)
					cout << "@";
			else
				cout << map[i][j] << "";


		}
		cout << endl;
	}
	*/

  this->gotoxt(x, y);
	this->setCursorView(true);
	while (true)
	{
		if (_kbhit())//키보드눌린거감지
		{
			int keycode = _getch();
			if (keycode == 224)
			{
				keycode = _getch();
				switch (keycode)
				{

				case 75:
					
					x -= 2;
					if (x < 0)
						x = 0;
					break;
				case 77:
					x += 2;
					if (x > col*2-2)
						x = col*2-2;
					break;

				case 72:
					y -= 1;
					if (y < 2)
						y = 2;
					break;
				case 80:

					y += 1;
					if (y > row+1)
						y = row + 1;
					break;

				}
				gotoxt(x, y);
			
			}
			else if (keycode == 120)
			{
				// -> 맵크기저장
				ofstream fout;
				fout.open("save.txt");
				fout << row<<" "<< col<<endl;
				fout << difficulty<<endl;
				fout << count << endl;
				fout << real_enter << endl;
				//지뢰위치
				for (auto i = mines.begin(); i != mines.end(); i++)
				{
					fout << (*i).first <<" "<< (*i).second<< endl;
				}
				//방문한 거
				while (!replay.empty())
				{
					fout << replay.front().first << " " << replay.front().second<<endl;
					replay.pop();
				}

				fout.close();
				return;
			}

			else if (keycode ==13)
			{
				replay.push(make_pair(y - 2, x / 2));
			//	replay.emplace(y - 2, x / 2);
				real_enter++;
				if (map[y-2][x/2] == 100)
				{
				//	system("cls");
		
					x = 0;
					y = 1;
					gotoxt(x, y);
					cout << "GAME OVER" << endl;
					mine_show();
					//게임종료시 지뢰위치출력!!
					Sleep(2000);
					replay_game();
					mine_show();
					y = row+2;
					gotoxt(x, y);
					
					return;
				}
				

				dfs(x / 2, y-2);
                //cout << map[y-2][x /2];	
				int a = count;
				if (count == total_size-mines.size())
				{
					//system("cls");
					x = 0;
					y = 1;
					gotoxt(x, y);
					cout << "Victory!!" << endl;
					mine_show();
					Sleep(2000);
					replay_game();
					mine_show();
					y = row + 2;
					gotoxt(x, y);
					return;
				}
				

			}
		
		}

		//gotoxy(x, y);

		//cout << _getch() << endl;//아스키코드에 입력되어있는것만 숫자로표시해줌
		//방향키는 코드두개주니 방향키로할려면 두개 getch로해야됨!!




	}





}

void MinSweeper::setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = { 1,visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void MinSweeper::gotoxt(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void MinSweeper::printfmap()
{
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		
		for (int j = 0; j < col; j++)
		{

			//if (map[i][j] == 100)
		    //		cout << "＊";
			
			//else
				//cout << map[i][j] << "";
                
			cout << "@ ";

		}
		cout << endl;
	}

}

void MinSweeper::main_screen()
{


	cout << "****************" << endl;
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"<<endl;
	cout << "1.게임시작하기" << endl;
	cout << "2.게임 이어서하기" << endl;
	cout << "3. 종료" << endl;




}

void MinSweeper::mine_show()
{

	int rows;
	int cols;
	int x=0;
	int y=2;
	
		
	for (auto i = mines.begin(); i != mines.end(); i++)
	{
		rows = (*i).first;
		cols = (*i).second;
		
		y = rows+2;
		x = cols*2;
		gotoxt(x, y);
		cout << "* " << endl;
		
	}





}

void MinSweeper::setmine()
{
	int rows, cols;
	for (auto i = mines.begin(); i != mines.end(); i++)
	{
		rows = (*i).first;
		cols = (*i).second;
		map[rows][cols] = 100;//mine -> 100로설정하기

	}


}

void MinSweeper::setmine_hint()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (map[i][j] == 100)
			{
				continue;
			}

			for (int k = i - 1; k < i + 2; k++)
			{
				for (int m = j - 1; m < j + 2; m++)
				{
					if (k<0 || m < 0 || k > row - 1 || j >col - 1)
						continue;
					if (map[k][m] == 100)
					{
						map[i][j]++;
					}
				}
			}
		}
	}
}

void MinSweeper::init_visit()
{
	visit = new int* [row];
	for (int i = 0; i < row; i++)
	{
		visit[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			visit[i][j] = 0;
		}
	}
}

void MinSweeper::dfs(int y, int x)
{
	if (visit[x][y] == 1)
	{
		return;
	}
	visit[x][y] = 1;
    count++;
	//좌표가반대로나타남
	gotoxt(y * 2, x + 2);
	if (map[x][y] == 100)
	{
		cout << "*";
		return;
	}
	cout << map[x][y];

	if (map[x][y] == 0)
	{
		for (int k = y - 1; k < y + 2; k++)
		{
			for (int m = x - 1; m < x + 2; m++)
			{
				if (k<0 || m < 0 || k >col - 1 || m >row - 1)
					continue;
				if (map[m][k] == 100)
				{
					continue;
				}
				if (map[m][k] == 0)
					dfs(k, m);
				if (map[m][k] != 0)
				{
					if (visit[m][k] == 1)
					{
						continue;
					}
					count++;
					visit[m][k] = 1;
					gotoxt(k * 2, m + 2);
					cout << map[m][k];
				}
			}
		}


	}

}
