#include "management.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "Window.h"
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

#define heap pair<int,int>

int op = 66;

struct Point {
	int x;
	int y;
	bool isDeleted;
	COLORREF color;
};

double dist(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

struct Edge {
	int from;
	int to;
	int value;
	bool isDeleted;
	COLORREF color;
};

int edge_num = 0, point_num = 0;
Edge edge[20000];
Point point[1000];
int head[20000], nxt[20000];
short vis[1000];
int fa[1000],Rank[1000];
vector<int> dfn;

management::management()
{
	::loadimage(&m_bk, "./image/bk.png", 960, 640);

	//主界面按钮初始化
	menu_btns.push_back(new pushButton("新建结点"));
	menu_btns.push_back(new pushButton("新建边"));
	menu_btns.push_back(new pushButton("删除结点"));
	menu_btns.push_back(new pushButton("删除边"));
	menu_btns.push_back(new pushButton("深度遍历"));
	menu_btns.push_back(new pushButton("广度遍历"));
	menu_btns.push_back(new pushButton("Kruskal"));
	menu_btns.push_back(new pushButton("Prim"));
	menu_btns.push_back(new pushButton("是否连通"));
	menu_btns.push_back(new pushButton("两点最短路径"));
	menu_btns.push_back(new pushButton("退出系统"));
	for (int i = 0; i != menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(80, 25);
		int bx = 960 - menu_btns[i]->width();
		int by = i * menu_btns[i]->height();

		menu_btns[i]->move(bx, by);
	}
}

bool cmp(Edge a, Edge b) {
	return a.value < b.value;
}

void management::run(){
	memset(head, 0, sizeof(head));
	memset(nxt, 0, sizeof(nxt));

	Window::beginDraw();

	while (true) 
	{
		Window::clear();

		showBackground();

		for (int i = 1; i <= point_num; i++)
			point[i].color = BLACK;
		for (int i = 1; i <= edge_num; i++)
			edge[i].color = BLACK;

		show_graph();

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:		//按键按下
				//按下ESC退出操作，返回主界面
				if (m_msg.vkcode == VK_ESCAPE) {
					op = Menu;
				}
				break;
			default:

				break;
			}
		}

		//按住esc退出操作，返回主界面
		if (_kbhit()) {
			if (_getch() == 27) {
				op = Menu;
			}
		}
		switch (op)
		{
		case management::Menu:
			op = menu();
			break;
		case management::AddPoint:
			add_point();
			break;
		case management::AddEdge:
			add_edge();
			break;
		case management::ErasePoint:
			erase_point();
			break;
		case management::EraseEdge:
			erase_edge();
			break;
		case management::DFS:
			dfs();
			break;
		case management::BFS:
			bfs();
			break;
		case management::Kruskal:
			kruskal();
			break;
		case management::Prim:
			prim();
			break;
		case management::Linked:
			linked();
			break;
		case management::minPath:
			MinPath();
			break;
		case management::Exit:
			exit(0);
		default:
			break;
		}

		Window::flushDraw();
	}

	Window::endDraw();
}

int management::menu()
{
	//根据按钮的点击，返回操作
	setlinecolor(WHITE);
	for (int i = 0; i != menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->eventloop(m_msg);
		if (menu_btns[i]->isclicked())
		{
			return i;
		}
	}
	return Menu;
}

void management::add_point()
{
	cout << "ready" << endl;
	EASYXMSG mouse_msg = getmessage();
	if (mouse_msg.message == WM_LBUTTONDOWN)
	{
		point_num++;
		point[point_num].x = mouse_msg.x;
		point[point_num].y = mouse_msg.y;
		point[point_num].isDeleted = false;
		point[point_num].color = BLACK;
		cout << "add point" << endl;
	}
	show_graph();
}

void insert(int a, int b) {
	edge_num++;
	nxt[edge_num] = head[a];
	edge[edge_num].from = a;
	edge[edge_num].to = b;
	edge[edge_num].value = ((int)dist(point[a].x, point[a].y, point[b].x, point[b].y));
	head[a] = edge_num;
	edge[edge_num].isDeleted = false;
	edge[edge_num].color = BLACK;
}

void management::add_edge()
{
	Window::flushDraw();

	EASYXMSG mouse_msg;
	
	cout << "Ready" << endl;
	int from = 0, to = 0;
	while (true) {
		mouse_msg = getmessage();
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			for (int i = 1; i <= point_num; i++)
				if (dist(point[i].x, point[i].y, mouse_msg.x, mouse_msg.y) <= 10)
				{
					from = i;
					cout << "one point" << endl;
					break;
				}
			if (from != 0)	break;
		}
		if (mouse_msg.message == WM_KEYDOWN && mouse_msg.vkcode == VK_ESCAPE) {
			op = 66;
		}
		if (_kbhit()) {
			if (_getch() == 27) {
				op = 66;
			}
			return;
		}
		
	}
		
	while (true) {
		mouse_msg = getmessage();
		if (mouse_msg.message == WM_LBUTTONDOWN)
		{
			for (int i = 1; i <= point_num; i++)
				if (dist(point[i].x, point[i].y, mouse_msg.x, mouse_msg.y) <= 10)
				{
					to = i;
					cout << "anthor point" << endl;
					break;
				}
			if (to != 0)	break;
		}
		if (mouse_msg.message == WM_KEYDOWN && mouse_msg.vkcode == VK_ESCAPE) {
			op = 66;
		}
		if (_kbhit()) {
			if (_getch() == 27) {
				op = 66;
			}
			return;
		}
		
	}

	insert(from, to);
	insert(to, from);

	show_graph();
	
	cout << "add edge" << endl;
}

void management::erase_point()
{
	Window::flushDraw();

	cout << "请输入删除的结点编号(退出请输入0)";
	int a;
	cin >> a;
	if (a == 0) {
		op = 66;
		return;
	}
	point[a].isDeleted = true;
	for (int i = 1; i <= edge_num; i++)
	{
		if (edge[i].from == a || edge[i].to == a)
			edge[i].isDeleted = true;
	}
	cout << "erase point" << endl;
	show_graph();
}

void management::erase_edge()
{
	Window::flushDraw();

	cout << "请输入删除边的端点编号(退出请输入0 0)";
	int a,b;
	cin >> a >> b;
	if (a == 0 && b == 0)
	{
		op = 66;
		return;
	}
	for (int i = 1; i <= edge_num; i++)
	{
		if (edge[i].from == a && edge[i].to == b)
			edge[i].isDeleted = true;
		if (edge[i].from == b && edge[i].to == a)
			edge[i].isDeleted = true;
	}
	cout << "erase edge" << endl;
	show_graph();
}

void Dfs(int u) {
	dfn.push_back(u);
	vis[u] = 1;
	for (int i = head[u]; i != 0; i = nxt[i]) 
		if (!edge[i].isDeleted){
			int v = edge[i].to;
			if (!vis[v])	Dfs(v);
		}
}

void management::dfs()
{
	Window::flushDraw();
	memset(vis, 0, sizeof(vis));
	dfn.clear();
	for (int i = 1; i<=point_num; i++)
		if (!vis[i]) Dfs(1);
	
	cout << "dfs OK " << dfn.size() << endl;

	for (int i = 0; i < dfn.size(); i++) {
		point[dfn[i]].color = RGB(237,28,36);
		show_graph();
		Window::flushDraw();
		Sleep(2000);
	}
	op = 66;
}

void management::bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<int> Q;
	Q.push(1);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		point[u].color = RGB(237, 28, 36);
		show_graph();
		Window::flushDraw();
		Sleep(2000);
		vis[u] = 1;
		for (int i = head[u]; i; i = nxt[i]) 
			if (!edge[i].isDeleted)
			{
				int v = edge[i].to;
				if (!vis[v])	Q.push(v);
			}
	}
	op = 66;
}

int find(int x) {
	if (x == fa[x])	return fa[x];
	else return fa[x] = find(fa[x]);
}

void unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (Rank[x] < Rank[y]) {
		fa[x] = y;
	}
	else {
		fa[y] = x;
		if (Rank[x] == Rank[y]) Rank[x]++;
	}
}

void management::kruskal()
{
	//::outtextxy(0, 0, "kruskal");
	Edge e[1000];
	for (int i = 1; i <= edge_num; i++)
		e[i] = edge[i];
	for (int i = 1; i <= point_num; i++) {
		fa[i] = i;
		Rank[i] = 0;
	}
	sort(e + 1, e + edge_num + 1, cmp);
	int n = 0;
	for (int i = 1; i <= edge_num && n!=point_num-1; i++) {
		if (find(e[i].from) != find(e[i].to) && (!e[i].isDeleted)) {
			unite(e[i].from, e[i].to);
			n++;
			setlinecolor(RGB(237,28,36));
			line(point[e[i].from].x, point[e[i].from].y, point[e[i].to].x, point[e[i].to].y);
			Window::flushDraw();
			Sleep(2000);
		}
	}
	op = 66;
}

void management::prim()
{
	#define INF  0x3f3f3f3f
	priority_queue <heap, vector<heap>, greater<heap>> q;
	int tot = point_num,u,v,e;
	memset(vis, 0, sizeof(vis));
	heap x;
	q.push(make_pair(0, 0));
	edge[0].to = 1;
	while (!q.empty() && tot) 
	{
		x = q.top();
		q.pop();
		e = x.second;
		u = edge[e].to;
		if (vis[u]) continue;
		vis[u] = 1;
		tot--;
		if (e != 0) {
			setlinecolor(RGB(237, 28, 36));
			line(point[edge[e].from].x, point[edge[e].from].y, point[edge[e].to].x, point[edge[e].to].y);
			Window::flushDraw();
			Sleep(2000);
		}

		for (int i = head[u]; i; i = nxt[i])
			if (!edge[i].isDeleted)
			{
				v = edge[i].to;
				if (!vis[v])	q.push(make_pair(edge[i].value, i));
			}
	}
	op = 66;
}

void management::linked()
{

	//::outtextxy(0, 0, "linked");
	memset(vis, 0, sizeof(vis));
	Dfs(1);
	for (int i = 1; i<=point_num; i++)
	{
		if (!vis[i]) {
			::outtextxy(0, 550, "这不是一个连通图");
			return;
		}
	}
	::outtextxy(0, 550, "这是一个连通图");
}

void management::MinPath()
{
	int src, dst;
	cout << "请输入两个结点的编号：";
	cin >> src >> dst;

	int dist[1000],pre[1000];
	for (int i = 1; i <= point_num; i++)
		dist[i] = INF;
	dist[src] = 0;
	for (int i = 1; i <= point_num; i++)
		pre[i] = i;
	for (int i = head[src]; i; i = nxt[i])
	if (!edge[i].isDeleted)
		{
			dist[edge[i].to] = edge[i].value;
			if (edge[i].value < INF)
				pre[edge[i].to] = src;
		}
	memset(vis, 0, sizeof(vis));
	vis[src] = 1;

	for (int i = 1; i<point_num; i++)
	{
		int minn = INF; int k = -1;
		for (int j = 1; j <= point_num; j++)
		{
			if (vis[j] == 0 && dist[j] < minn) {
				minn = dist[j];
				k = j;
			}
		}
		if (k == -1)	break;

		vis[k] = 1;

		for (int j = head[k]; j; j = nxt[j])
			if (!edge[i].isDeleted)
			{
				if (!vis[edge[j].to]) {
					if (dist[edge[j].to] > dist[k] + edge[j].value)
					{
						dist[edge[j].to] = dist[k] + edge[j].value;
						pre[edge[j].to] = k;
					}
				}
			}
	}

	if (dist[dst] >= INF)
		::outtextxy(0, 0, "两点之间没有路径");
	else {
		char ans[100];
		sprintf_s(ans, "两点之间最短距离是%d", dist[dst]);
		settextcolor(BLACK);
		::outtextxy(0, 0, ans);
		Window::flushDraw();
		stack<int> S;
		int tmp = dst;
		S.push(tmp);
		while (tmp != src) {
			tmp = pre[tmp];
			S.push(tmp);
		}

		int last = S.top(),now;
		S.pop();
		while (!S.empty()) {
			now = S.top();

			setlinecolor(RGB(237, 28, 36));
			line(point[last].x, point[last].y, point[now].x, point[now].y);
			Window::flushDraw();
			Sleep(2000);

			last = now;
			S.pop();
		}
	}

	op = 66;
}

void management::show_graph()
{
	for (int i = 1; i <= point_num; i++)
		if (!point[i].isDeleted)
		{
			setfillcolor(point[i].color);
			fillcircle(point[i].x, point[i].y, 10);
			char Oct[120];
			sprintf_s(Oct, "%d", i);
			::outtextxy(point[i].x + 10, point[i].y-20, Oct);
		}
	for (int i = 1; i <= edge_num; i++)
		if (!edge[i].isDeleted)
		{
			setlinecolor(edge[i].color);
			line(point[edge[i].from].x, point[edge[i].from].y, point[edge[i].to].x, point[edge[i].to].y);
			char length[129];
			sprintf_s(length, "%d", edge[i].value);
			settextcolor(BLUE);
			::outtextxy((point[edge[i].from].x + point[edge[i].to].x) * 0.5 + 10, (point[edge[i].from].y + point[edge[i].to].y) * 0.5 - 20, length);
		}
}

void management::showBackground()
{
	::putimage(0, 0, &m_bk);
}

void management::eventloop()
{

}
