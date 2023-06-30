#include<iostream>
#include<fstream>
#include<iomanip>
#include<stack> 
#include<Windows.h>
using namespace std;
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)											 //��ɫ
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)																	 //��ɫ
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)						 //��ɫ
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)											//��ɫ
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)    //��ɫ
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE)						//��ɫ 
#define MAZEMAXSIZE 200
//1Ϊǽ�ڣ�0Ϊͨ· 
//���� 
struct point{
	int x;
	int y;
};
//�Թ�
typedef struct maze{
	char mazeMap[MAZEMAXSIZE][MAZEMAXSIZE];
}maze,*mazepoint;

bool check_board(int x,int mx){
	if (x < 0) {
		cout << "�������곬���߽�"<<endl;
		return false;
	}
	else if (x >= mx) {
		cout << "�������곬���߽�"<<endl; 
		return false;
	}
	else return true;
}
//�����Թ�
void CreateMaze(mazepoint p,point &start,point &end ,int &x,int &y)
{
	//�洢�Թ����Ϳ�
	//int x, y;
	ifstream in;
	in.open("maze.txt");
	if (!in)
	{
		cout << "�� maze.txt ʧ��" << endl;
		exit(1);
	}
	//�����Թ�
	in >> x >> y;
	for (int i = 0; i < x; i++)
	{	
		
		for (int j = 0; j < y; j++)
		{
			in >>p->mazeMap[i][j];
		}
	}
	in.close();
	//����Թ�
	cout << "ԭ�Թ�Ϊ:\n(��1��ʾǽ��)\n(��0��ʾͨ·)" << endl;
	cout<<"   ";
	for (int j = 0; j < y; j++)
		cout<< setw(3)<<setiosflags(ios::left)<<j;
	cout << endl;
	for (int i = 0; i < x; i++)
	{
		cout << setw(3)<<setiosflags(ios::left) << i;
		for (int j = 0; j < y; j++)
		{
			if ( p->mazeMap[i][j] == '1'){	
				//ǽ�� 
				red; 
				cout << p->mazeMap[i][j]<<"  ";
				white;
			} 
			else if (p->mazeMap[i][j] == '0'){
				//ͨ·
				yellow;
				cout << p->mazeMap[i][j]<<"  ";
				white; 
			}	
			if (j == y - 1)
				cout << endl;
		}
	}
	cout << "�������ĺ����귶ΧΪ 0��"<<x-1<<endl;
	cout << "�������������귶ΧΪ 0��"<<y-1<<endl;
	while (1){
		cout << "�������Թ����������:";
	 
		cin >> start.x >> start.y;
		if (check_board(start.x,x) && check_board(start.y,y)) {
			if (p->mazeMap[start.x][start.y] =='1'){
				cout << "������������Ϊǽ�ڣ�����������\n"<<endl;
				continue; 
			}
			else break;
		} 
		else {
			cout <<"�������������������������\n"<<endl;
			continue; 
		}
	}
	while (1){
		cout << "�������Թ��ĳ�������:";
		cin >> end.x >> end.y;
		if (check_board (end.x,x)&& check_board(end.y,y)){
			if (p->mazeMap[start.x][start.y] =='1'){
				cout << "����ĳ�������Ϊǽ�ڣ�����������\n"<<endl;
				continue; 
			}
			else break; 
		}
		else {
			cout <<"�������������������������\n"<<endl;
			continue;
		}
		
	}
}
//���Թ� 
void Mazes(mazepoint p,point &start,point &end,int &boardX,int &boardY ){
	stack<point> Stack;
	Stack.push(start);
	//cur��ʾ��ǰλ��
	point cur = start,q;
	int cur_x = start.x;
	int cur_y = start.y;
	//�Ƿ��߹���־ 
	bool flag = false;
	//�����������ұ�ʾ�ĸ�������ƶ���i��ʾ�������򱻳��Թ��� 
	int moveing[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
	int i = 0;
	while (!Stack.empty() && ((cur.x != end.x)||(cur.y != end.y)) ){
		cur = Stack.top();
		flag = 0;
		i = 0;
		//�ӵ�ǰ�㿪ʼ�����ĸ�����
		while (flag == 0 && i < 4) {
			cur_x = cur.x + moveing[i][0];
			cur_y = cur.y + moveing[i][1];
			if  (p->mazeMap[cur_x][cur_y] == '0'){
				cur.x = cur_x;
				cur.y = cur_y;
				Stack.push(cur);
				// *��ʾͨ· 
				p->mazeMap[cur_x][cur_y] = '*';
				flag = 1;	//�õ��Ѿ��߹� 
			}
			i++; //������ 
		}
		if (i == 4 && flag == 0)
		{
			p->mazeMap[cur.x][cur.y] = '#';  //��ô����ǰ����Ϊǽ��,���ڴ���
			Stack.pop();     //���õ��ջ�ص���һ����
		}	
	}
	p -> mazeMap[start.x][start.y] ='*';
	p -> mazeMap[end.x][end.y] ='*';
	if (Stack.empty()){
		cout << "û��·��"<<endl; 
	} 
	else{
		//����Թ�·��ͼ 
		cout << "����Թ�·������\n(��1��ʾǽ��)\n(��0��ʾͨ·)\n(��*��ʾ·��)\n(��#��ʾ���㷨����ʱ̽������·���������Ǵ�·��)"<<endl;
		cout<<"   ";
		for (int j = 0; j < boardY; j++)
			cout<< setw(3)<<setiosflags(ios::left)<<j;
		cout << endl;
		for (int i = 0; i < boardX; i++)
		{
			cout << setw(3)<<setiosflags(ios::left) << i;
			for (int j = 0; j < boardY; j++)
			{	
				if ( p->mazeMap[i][j] == '1'){	
					//ǽ�� 
					red; 
					cout << p->mazeMap[i][j]<<"  ";
					white;
				} 
				else if (p->mazeMap[i][j] == '0'){
					//ͨ·
					yellow;
					cout << p->mazeMap[i][j]<<"  ";
					white; 
				}	
				else if (p->mazeMap[i][j] == '*'){
					green;
					cout << p->mazeMap[i][j]<<"  ";
					white;
				}
				else if (p->mazeMap[i][j] == '#'){
					ching;
					cout << p->mazeMap[i][j]<<"  ";
					white;
				}	
				if (j == boardY - 1)
					cout << endl;
			}
		}
		cout << endl; 
		//����Թ�·����
		//ջ��ת 
		stack<point> temp;
		while (!Stack.empty()){
			q = Stack.top();
			Stack.pop();
			temp.push(q);
		}  
		cout << "��������ʾ���Թ�·�����£�"<<endl;
		int huanhang = 0;
		while (!temp.empty()){
			q = temp.top();
			temp.pop();
			huanhang++;
			
			cout << "("<< q.x <<","<<q.y<<")";
			if (!temp.empty()) cout << "->";
			if (huanhang % 8 == 0) cout<<endl;
		} 
		//StackTraverse(S);
	}
}

int main(){
	maze map;
	mazepoint p = &map;
	point start,end;
	int x,y;
	CreateMaze(p,start,end,x,y);

	Mazes(p,start,end,x,y);
	return 0;
}
