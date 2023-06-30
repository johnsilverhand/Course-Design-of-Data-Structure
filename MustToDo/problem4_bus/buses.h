#ifndef BUSES_H
#define BUSES_H
#include <bits/stdc++.h>
using namespace std;

const int MAX = 12000;
const int line_max = 2000; //���2000������·��

class ArcNode
{
public:
	int id; //�ߵ���һ��id
	ArcNode *next;

	ArcNode(int id) : id(id), next(nullptr) {}
};

class VertexHead
{
public:
	int id; //��ͷid
	ArcNode *first;
	VertexHead() : first(nullptr) {}
};

//·����
class Line
{
public:
	int no; //·�߱��
};

//վ����
class Station
{
public:
	int id;		   //վ��id
	string name;   //վ������
	set<int> buss; //����վ��Ĺ�������·��
	Station() {}

	Station(string name, int busNo) : name(name) { buss.insert(busNo); }
};

//·��+վ��
class LineBus
{
public:
	Line line;			  //·��
	vector<int> stations; //ÿһ��·�ߵ�����վ��
};

class Graph
{
public:
	VertexHead heads[MAX];	  //���еı�ͷ
	vector<LineBus> lines;	  //�ļ��е�����·��
	vector<Station> stations; //�洢���е�վ��
	vector<int> lines_no;	  //����·�߱��
	int line_num;			  //·����
	int station_num;		  //վ����

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
