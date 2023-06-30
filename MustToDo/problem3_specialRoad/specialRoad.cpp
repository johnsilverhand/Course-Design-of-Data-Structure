#include <iostream>
#include <queue>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)											 //��ɫ
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)						 //��ɫ
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)											 //��ɫ
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)     //��ɫ
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE)						 //��ɫ

void INFO(string info) {
	cout << "["; green; cout << "INFO"; white; cout << "]:" << info ;
}
void ERROROUT(string error) {
	cout  << "["; red; cout << "ERROR"; white; cout << "]:" << error << endl;
}
							//���ڽӱ�Ϊ���ݽṹ
							//�Ǳ�ͷ��� 
typedef struct ArcNode {      
	int adjvex;               
	struct ArcNode* nextarc;  
}ArcNode;
							//��ͷ��� 
typedef struct VexNode {  
	//int data;             
	int maxdata;          	//����·���ϵ����ֵ���ж��Ƿ�Ϊ���·�� 
	ArcNode* firstarc;    
}VexNode;
typedef struct Graph {    	//�ڽӱ�ṹ����
	VexNode* VNode;       	//�����ڽӱ�
	int vexnum;           	//�������
}Graph;

int  *visit; 			  	//��ǵ��Ƿ񱻷��ʹ�����̬����
int  count = 0;			  	//����·������
int  num;					//������� 
int	 lastSecondeRoad = 0;	//�ڶ���ĵ������·����
int	 isConnectedlast = 0;	//��һ��ĵ���ڶ���ĵ��Ƿ���ͨ 
void CreatGraph(Graph &G){	//��̬����ռ佨ͼ 
	while (1){
		INFO("�����붥�����\n");
		cin >> num;
							//�������С��2���� 
		if (num <= 1)
			ERROROUT("����������٣����ܹ���·��,���������붥�����\n");
		else  
			break; 
	}
	if (num == 2){		 	//�������Ϊ2ֱ�ӵ�·�������ؽ�ͼ
		int fake,fakes;
		INFO("�����������Ϣ��\n");
		cin >> fake; cin >> fakes;
		return ;
	}
	else {
		G.vexnum = num;
		G.VNode = (VexNode*)malloc ((num+1)* sizeof(VexNode)); 
	} 
							//Ϊ�������鶯̬����ռ� 
	visit = (int*)malloc((num+1) * sizeof(int));
							//�ڽӱ��ʼ�������е��������Ϊ�ձ�
	for (int i = 1; i <= G.vexnum; i++) {
		//G.VNode[i].data = i+1;
		G.VNode[i].firstarc = NULL;  
	}
	int a;
	ArcNode *p,*q;
	INFO("�����������Ϣ��\n");
	for (int i = 1; i <= G.vexnum; i++){
		cin >> a;
							//�жϵ�һ��ĵ�͵ڶ����Ƿ���ͨ 
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
							//����ͼ�����ԳƱ�	
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
void BFS(Graph G,int i){	//BFS��ȡ·��
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
							//����ǰ�����ڵ�ǰ·�������ֵ������
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
int  CountRoad (Graph &G){	//��������·��
	INFO("����·��Ϊ��\n") ; 
	if (num == 2){
		cout <<"1->2"<<endl;
		count = 2; 			//�������Ϊ2ֱ�ӵó����
	}
	else{
		for (int i = 1; i < G.vexnum-1; i++){
			for (int i = 1; i <= G.vexnum; i++){
				visit[i] = 0;	//��������Visit��ʼ��
				G.VNode[i].maxdata = i;  //��ǰ�������·���ϵ����ֵ��ʼ��
			}
		BFS(G, i);
		}
		if (isConnectedlast){
			count++;
			cout <<G.vexnum-1<<"->"<<G.vexnum<<endl;
		} 
	}
	INFO("����·����Ϊ��");cout<<count<<endl;
}
int main(){	
	Graph G;
	CreatGraph(G);
	CountRoad(G);
	return 0;	
} 
