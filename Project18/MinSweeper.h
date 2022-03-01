#pragma once
#include<vector>
#include<iostream>
#include<queue>
#include<fstream>

using namespace std;

class MinSweeper
{
private:
	

	int** map;
	int row;
	int col;
	int difficulty;
	int total_size;
	int totoal_min_num;
	queue<pair<int,int>>replay;
	queue<pair<int, int>>load;
	int count=0;
	int** visit;
	vector<pair<int, int>>mines;
	int real_enter=0;

	


public:
	void alpa()
	{
	
	};
	void Loadgame();
	void replay_game();
	void game();
	void start();
	~MinSweeper();
	void key();
	void setCursorView(bool visible);
	void gotoxt(int x, int y);
	void printfmap();
	void main_screen();
	void mine_show();
	void setmine();
	void setmine_hint();
	void init_visit();
	
	void dfs(int y, int x);
	


};

