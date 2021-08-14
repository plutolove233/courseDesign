#pragma once

#include "window.h"
#include <vector>
#include "pushButton.h"
class management
{
	enum Operator {
		AddPoint,
		AddEdge,
		ErasePoint,
		EraseEdge,
		DFS,
		BFS,
		Kruskal,
		Prim,
		Linked,
		minPath,
		Exit,
		Menu = 66
	};
public:
	management();
	void run();//启动管理类

	int menu();

	//操作
	void add_point();
	void add_edge();
	void erase_point();
	void erase_edge();
	void dfs();
	void bfs();
	void kruskal();
	void prim();
	void linked();
	void MinPath();
	void show_graph();

	void showBackground();
	void eventloop();
private:
	IMAGE m_bk;
	EASYXMSG m_msg;

	std::vector<pushButton*> menu_btns;
};

