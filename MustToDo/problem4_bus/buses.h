#ifndef BUSES_H
#define BUSES_H
#include <bits/stdc++.h>
using namespace std;

const int MAX = 12000;
const int line_max = 2000; //最多2000条公交路线

class ArcNode
{
public:
	int id; //边的下一个id
	ArcNode *next;

	ArcNode(int id) : id(id), next(nullptr) {}
};

class VertexHead
{
public:
	int id; //表头id
	ArcNode *first;
	VertexHead() : first(nullptr) {}
};

//路线类
class Line
{
public:
	int no; //路线编号
};

//站点类
class Station
{
public:
	int id;		   //站点id
	string name;   //站点名称
	set<int> buss; //经过站点的公交车的路线
	Station() {}

	Station(string name, int busNo) : name(name) { buss.insert(busNo); }
};

//路线+站点
class LineBus
{
public:
	Line line;			  //路线
	vector<int> stations; //每一条路线的所有站点
};

class Graph
{
public:
	VertexHead heads[MAX];	  //所有的表头
	vector<LineBus> lines;	  //文件中的所有路线
	vector<Station> stations; //存储所有的站点
	vector<int> lines_no;	  //所有路线编号
	int line_num;			  //路线数
	int station_num;		  //站点数

	Graph()
	{
		for (int i = 0; i < MAX; ++i)
		{
			heads[i].id = i;
		}
	}

	void insertArc(int &s1, int &s2)
	{
		ArcNode *p = heads[s1].first;
		while (p != nullptr)
		{
			if (p->id == s2)
			{
				return;
			}
			p = p->next;
		}
		ArcNode *arc = new ArcNode(s2);
		arc->next = heads[s1].first;
		heads[s1].first = arc;
		ArcNode *arc2 = new ArcNode(s1);
		arc2->next = heads[s2].first;
		heads[s2].first = arc2;
	}
};

#endif
