#include <iostream>
#include <queue>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)											 //红色
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)						 //黄色
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)											 //绿色
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)     //白色
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE)						 //青色

void INFO(string info) {
	cout << "["; green; cout << "INFO"; white; cout << "]:" << info ;
}
void ERROROUT(string error) {
	cout  << "["; red; cout << "ERROR"; white; cout << "]:" << error << endl;
}
							//以邻接表为数据结构
							//非表头结点 
typedef struct ArcNode {      
	int adjvex;               
	struct ArcNode* nextarc;  
}ArcNode;
							//表头结点 
typedef struct VexNode {  
	//int data;             
	int maxdata;          	//所在路径上的最大值，判断是否为最大路径 
	ArcNode* firstarc;    
}VexNode;
typedef struct Graph {    	//邻接表结构类型
	VexNode* VNode;       	//定义邻接表
	int vexnum;           	//顶点个数
}Graph;

int  *visit; 			  	//标记点是否被访问过，动态申请
int  count = 0;			  	//特殊路径总数
int  num;					//顶点个数 
int	 lastSecondeRoad = 0;	//第二大的点的特殊路径数
int	 isConnectedlast = 0;	//第一大的点与第二大的点是否联通 
void CreatGraph(Graph &G){	//动态申请空间建图 
	while (1){
		INFO("请输入顶点个数\n");
		cin >> num;
							//顶点个数小于2错误 
		if (num <= 1)
			ERROROUT("顶点个数过少，不能构成路径,请重新输入顶点个数\n");
		else  
			break; 
	}
	if (num == 2){		 	//顶点个数为2直接得路径数不必建图
		int fake,fakes;
		INFO("请输入相关信息：\n");
		cin >> fake; cin >> fakes;
		return ;
	}
	else {
		G.vexnum = num;
		G.VNode = (VexNode*)malloc ((num+1)* sizeof(VexNode)); 
	} 
							//为访问数组动态分配空间 
	visit = (int*)malloc((num+1) * sizeof(int));
							//邻接表初始化，所有单向链表均为空表
	for (int i = 1; i <= G.vexnum; i++) {
		//G.VNode[i].data = i+1;
		G.VNode[i].firstarc = NULL;  
	}
	int a;
	ArcNode *p,*q;
	INFO("请输入相关信息：\n");
	for (int i = 1; i <= G.vexnum; i++){
		cin >> a;
							//判断第一大的点和第二点是否联通 
		if ((i == G.vexnum-1 && a == G.vexnum)||(a == G.vexnum-1 && i == G.vexnum))
			isConnectedlast = 1; 
		if (a > 0) {
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->nextarc = NULL;
			p->adjvex = i;
			q = G.VNode[a].firstarc;
			if (q == NULL) {
				G.VNode[a].firstarc = p;
			}
			else {
				while (q->nextarc != NULL) {
					q = q->nextarc;
				}
				q->nextarc = p;
			}
							//无向图创建对称边	
			p = (ArcNode*)malloc(sizeof(ArcNode));  
			p->nextarc = NULL;
			p->adjvex = a;
			q = G.VNode[i].firstarc;
			if (q == NULL) {
				G.VNode[i].firstarc = p;
			}
			else {
				while (q->nextarc != NULL) {
					q = q->nextarc;
				}
				q->nextarc = p;
			}
		}
	} 
	
}
void BFS(Graph G,int i){	//BFS获取路径
	queue<int> q;
	visit[i] = 1;
	q.push(i);
	int shouldNewline = 0;
	int maxInRoad; 
	while (!q.empty()){
		maxInRoad = q.front();
		q.pop();
		ArcNode *p = G.VNode[maxInRoad].firstarc;
		while (p){
			if (!visit[p->adjvex] && p->adjvex >= i) {
				if (p->adjvex >= G.VNode[maxInRoad].maxdata){
							//若当前结点大于当前路径的最大值，更新
					count++;
					cout << i << "->" << p->adjvex << " ";
					shouldNewline = 1; 
				}
				else{
					G.VNode[p->adjvex].maxdata = G.VNode[maxInRoad].maxdata;
				}
				visit[p->adjvex] = 1;
				q.push(p->adjvex);
			}
			p = p->nextarc;
		}
	}
	
	if (shouldNewline){
		cout << endl;
	}
	
}
int  CountRoad (Graph &G){	//计算特殊路径
	INFO("特殊路径为：\n") ; 
	if (num == 2){
		cout <<"1->2"<<endl;
		count = 2; 			//顶点个数为2直接得出结果
	}
	else{
		for (int i = 1; i < G.vexnum-1; i++){
			for (int i = 1; i <= G.vexnum; i++){
				visit[i] = 0;	//辅助数组Visit初始化
				G.VNode[i].maxdata = i;  //当前结点所在路径上的最大值初始化
			}
		BFS(G, i);
		}
		if (isConnectedlast){
			count++;
			cout <<G.vexnum-1<<"->"<<G.vexnum<<endl;
		} 
	}
	INFO("特殊路径数为：");cout<<count<<endl;
}
int main(){	
	Graph G;
	CreatGraph(G);
	CountRoad(G);
	return 0;	
} 
