#include<iostream>
#include<fstream>
#include<iomanip>
#include<stack> 
#include<Windows.h>
using namespace std;
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)											 //红色
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)																	 //蓝色
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)						 //黄色
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)											//绿色
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)    //白色
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE)						//青色 
#define MAZEMAXSIZE 200
//1为墙壁，0为通路 
//坐标 
struct point{
	int x;
	int y;
};
//迷宫
typedef struct maze{
	char mazeMap[MAZEMAXSIZE][MAZEMAXSIZE];
}maze,*mazepoint;

bool check_board(int x,int mx){
	if (x < 0) {
		cout << "您的坐标超出边界"<<endl;
		return false;
	}
	else if (x >= mx) {
		cout << "您的坐标超出边界"<<endl; 
		return false;
	}
	else return true;
}
//创建迷宫
void CreateMaze(mazepoint p,point &start,point &end ,int &x,int &y)
{
	//存储迷宫长和宽
	//int x, y;
	ifstream in;
	in.open("maze.txt");
	if (!in)
	{
		cout << "打开 maze.txt 失败" << endl;
		exit(1);
	}
	//输入迷宫
	in >> x >> y;
	for (int i = 0; i < x; i++)
	{	
		
		for (int j = 0; j < y; j++)
		{
			in >>p->mazeMap[i][j];
		}
	}
	in.close();
	//输出迷宫
	cout << "原迷宫为:\n(用1表示墙壁)\n(用0表示通路)" << endl;
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
				//墙壁 
				red; 
				cout << p->mazeMap[i][j]<<"  ";
				white;
			} 
			else if (p->mazeMap[i][j] == '0'){
				//通路
				yellow;
				cout << p->mazeMap[i][j]<<"  ";
				white; 
			}	
			if (j == y - 1)
				cout << endl;
		}
	}
	cout << "你可输入的横坐标范围为 0至"<<x-1<<endl;
	cout << "你可输入的纵坐标范围为 0至"<<y-1<<endl;
	while (1){
		cout << "请输入迷宫的入口坐标:";
	 
		cin >> start.x >> start.y;
		if (check_board(start.x,x) && check_board(start.y,y)) {
			if (p->mazeMap[start.x][start.y] =='1'){
				cout << "输入的入口坐标为墙壁，请重新输入\n"<<endl;
				continue; 
			}
			else break;
		} 
		else {
			cout <<"输入入口坐标有误，请重新输入\n"<<endl;
			continue; 
		}
	}
	while (1){
		cout << "请输入迷宫的出口坐标:";
		cin >> end.x >> end.y;
		if (check_board (end.x,x)&& check_board(end.y,y)){
			if (p->mazeMap[start.x][start.y] =='1'){
				cout << "输入的出口坐标为墙壁，请重新输入\n"<<endl;
				continue; 
			}
			else break; 
		}
		else {
			cout <<"输入出口坐标有误，请重新输入\n"<<endl;
			continue;
		}
		
	}
}
//走迷宫 
void Mazes(mazepoint p,point &start,point &end,int &boardX,int &boardY ){
	stack<point> Stack;
	Stack.push(start);
	//cur表示当前位置
	point cur = start,q;
	int cur_x = start.x;
	int cur_y = start.y;
	//是否走过标志 
	bool flag = false;
	//依次下左上右表示四个方向的移动，i表示几个方向被尝试过； 
	int moveing[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
	int i = 0;
	while (!Stack.empty() && ((cur.x != end.x)||(cur.y != end.y)) ){
		cur = Stack.top();
		flag = 0;
		i = 0;
		//从当前点开始尝试四个方向
		while (flag == 0 && i < 4) {
			cur_x = cur.x + moveing[i][0];
			cur_y = cur.y + moveing[i][1];
			if  (p->mazeMap[cur_x][cur_y] == '0'){
				cur.x = cur_x;
				cur.y = cur_y;
				Stack.push(cur);
				// *表示通路 
				p->mazeMap[cur_x][cur_y] = '*';
				flag = 1;	//该点已经走过 
			}
			i++; //换方向 
		}
		if (i == 4 && flag == 0)
		{
			p->mazeMap[cur.x][cur.y] = '#';  //那么将当前点置为墙壁,便于处理
			Stack.pop();     //将该点出栈回到上一个点
		}	
	}
	p -> mazeMap[start.x][start.y] ='*';
	p -> mazeMap[end.x][end.y] ='*';
	if (Stack.empty()){
		cout << "没有路径"<<endl; 
	} 
	else{
		//输出迷宫路径图 
		cout << "解后迷宫路径如下\n(用1表示墙壁)\n(用0表示通路)\n(用*表示路径)\n(用#表示用算法回溯时探索过的路径，但不是答案路径)"<<endl;
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
					//墙壁 
					red; 
					cout << p->mazeMap[i][j]<<"  ";
					white;
				} 
				else if (p->mazeMap[i][j] == '0'){
					//通路
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
		//输出迷宫路径表
		//栈反转 
		stack<point> temp;
		while (!Stack.empty()){
			q = Stack.top();
			Stack.pop();
			temp.push(q);
		}  
		cout << "以坐标显示的迷宫路径如下："<<endl;
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
