#include<iostream>
using namespace std;
#define MAX -99
#define MIN 99
//采用深度优先算法
// 0:null 
// 1:Alice: X(first)
// 2:Bob: O
int board[3][3];	//数组形式记录棋盘 
bool Judge (int side){
	//判断谁胜利
	for (int i = 0;i<3;i++){
		//行连成一条线 
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == side )
			return true;
		//列连成一条线 
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] == side )
			return true;
	} 
		//判断对角线 
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == side)
		return true;
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] == side)
		return true;
	return false;
} 
int DFS(int side){
	int nullNum = 0;
	int maxFinal = MAX;
	int minFinal = MIN;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == 0) 
				nullNum ++;
		}
	}
	//返回得分情况 
	if (side == 1 && Judge(2)) 
		return -nullNum-1;
	else if (side == 2 &&Judge(1))
		return nullNum+1;
	else if (nullNum == 0)
		return 0;
	//进行下棋 
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == 0){
				board[i][j] = side;
				if (side == 1)	//当前为Alice下棋，计算 下一步Bob下棋Bob最优策略得分 
					maxFinal = max(maxFinal,DFS(2));
				if (side == 2)	//当前为Bob下棋，计算 下一步Alice下棋Alice最优策略得分 
					minFinal = min(minFinal,DFS(1));
				board[i][j] = 0;//回溯时重新初始化 
		}
		}
	}
	if (side == 1) return maxFinal;
	if (side == 2) return minFinal;	
}
int main() {
	int group;
	cin >> group;
	while (group--){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				cin >> board[i][j];
			}	
		}
		cout << DFS(1) << endl;
	}
	return 0;		
}
//代码总行数：73行 
