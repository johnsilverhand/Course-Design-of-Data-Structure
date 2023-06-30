#include<iostream>
using namespace std;
#define MAX -99
#define MIN 99
//������������㷨
// 0:null 
// 1:Alice: X(first)
// 2:Bob: O
int board[3][3];	//������ʽ��¼���� 
bool Judge (int side){
	//�ж�˭ʤ��
	for (int i = 0;i<3;i++){
		//������һ���� 
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == side )
			return true;
		//������һ���� 
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] == side )
			return true;
	} 
		//�ж϶Խ��� 
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
	//���ص÷���� 
	if (side == 1 && Judge(2)) 
		return -nullNum-1;
	else if (side == 2 &&Judge(1))
		return nullNum+1;
	else if (nullNum == 0)
		return 0;
	//�������� 
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == 0){
				board[i][j] = side;
				if (side == 1)	//��ǰΪAlice���壬���� ��һ��Bob����Bob���Ų��Ե÷� 
					maxFinal = max(maxFinal,DFS(2));
				if (side == 2)	//��ǰΪBob���壬���� ��һ��Alice����Alice���Ų��Ե÷� 
					minFinal = min(minFinal,DFS(1));
				board[i][j] = 0;//����ʱ���³�ʼ�� 
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
//������������73�� 
