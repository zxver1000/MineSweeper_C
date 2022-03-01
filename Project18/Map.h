#pragma once

#include<vector>
#include<queue>
#include<fstream>
#include<iostream>
using namespace std;


class Map
{



private:
	int** map;
	int row;
	int col;
	int difficulty;
	int total_size;
	int** visit;
	int count = 0;
	int real_enter = 0;
	int total_min_num;
	vector<pair<int, int>>mines;

public:



	void setMap();
	void printmap();
	void init_visit();
	void key();


	void setCursorView(bool visible);
	void gotoxt(int x, int y);
	void mine_show();

	void main_screen();
	void setmine();
	void setmine_hint();


	void dfs(int y, int x);




};

