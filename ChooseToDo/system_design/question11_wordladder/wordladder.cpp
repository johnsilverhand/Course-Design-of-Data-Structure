#include <bits/stdc++.h>
using namespace std;

map<string, string> dict,startSet,endSet;	//单词表，起点出发搜索的边集合 终点出发搜索的边集合 
vector<string> midPath;		//存储中间点以便找到路径 
int len;					//字符串 长度 
typedef pair<string,string> line;	 
ifstream in;
void CreatDict (){
	in.open("words.txt");
	if (!in){
		cout << "打开文件 words.txt 失败";
		exit(1);
	}
	string temp;
	while ( getline(in,temp) ){
		dict.insert(make_pair(temp,temp));	 
	}
	in.close();
	cout <<"已读取建立单词表"<<endl;
}
bool Check(string isExit){
	if (dict.count(isExit)) return true;
	else return false;
}
//flag : 0为从起点开始搜索，1为从终点开始搜索 
int update(queue <string> &q,map<string, string> &visit,map<string, string> &other,int count,int flag){
	int isFind = 0; 
	for(int i = 0;i < count;i++){
		string st =  q.front();
		q.pop();
		for (int j = 0;j < len;j++){
			string temp = st;
			for (char ch = 'a';ch <='z';ch++){
				temp[j] = ch;
				if (dict.count(temp) && (!visit.count(temp))){
					//若单词存在且没在当前方向被访问过 
					q.push(temp);
					//存出边以便找寻路径 
					if(flag == 0) startSet[temp] = st;
					else{
						endSet[temp] = st;
					}
					visit[temp] = temp;
					//若单词被另一方向搜索过，则找到路径，返回值为-1 
					if (other.count(temp)) {
						midPath.push_back(temp);
						isFind = -1;
					}	
				}
			}
		}
	}
	if (isFind == -1) return isFind;
	else return q.size();
} 
//双向BFS 
void WorldLadder(string start,string end){
	//初始化 
	queue <string> fromStart,fromEnd;
	map<string, string> visitS,visitE;
	//从起点或终点开始的搜索队列访问数组 
	visitS[start] = start;
	visitE[end]	  = end;
	//从起点或终点开始的搜索队列
	fromStart.push(start);
	fromEnd.push(end);
	
	int countS = 1,countE = 1;//当前搜索层的元素个数 
	int isExitRoad = 0;
	//双向BFS主要过程 
	while (!fromStart.empty() && !fromEnd.empty()){
		if (fromStart.size() <= fromEnd.size()){
			countS = update(fromStart,visitS,visitE,countS,0);
		}
		else{
			countE = update(fromEnd,visitE,visitS,countE,1);
		}
		//返回值为-1则说明词梯找到，终止搜索 
		if (countS == -1 || countE == -1) {
			cout << "词梯已找寻到\n";
			isExitRoad = 1;
			break;
		}
	}
	if (!isExitRoad) cout <<"词梯不存在"<<endl; 
	//输出路径 
	cout <<"开始输出词梯\n"<<endl; 
	for (auto it = midPath.begin(); it != midPath.end(); it++)
	{
		vector<string> path;
		string tmp = *it;
		string tmp1 = *it;
		path.push_back(tmp);
		//根据中间词找到该词到起点的路径并转换 
		while (tmp != start){
			tmp = startSet[tmp];
			path.push_back(tmp);
		};
		reverse(path.begin(),path.end());
		//根据中间词找到该词到终点的路径 
		while (tmp1 != end){
			tmp1 = endSet[tmp1];
			path.push_back(tmp1);
		}
		
		for (auto it = path.begin(); it != path.end(); it++)
		{
			cout <<(*it);
			if (it != path.end()-1){
				cout<<"->";
			}
		}
		cout <<endl; 
	} 		
}
int main(){
	CreatDict();
	string start,end;
	//输入 
	while (1){
		cout <<"请输入起点词\n";
		cin  >>start;
		if (Check(start)) break;
		else {
			cout <<"该词不存在，请重新输入\n";
			continue; 
		}
	}
	while (1){
		cout <<"请输入终点词\n";
		cin  >>end;
		if (start.length() != end.length()){
			cout <<"两词长度不等，请重新输入终点词\n";
			continue; 
		}
		if (Check(end)) break;
		else {
			cout <<"该词不存在，请重新输入\n";
			continue; 
		}
	}
	//处理输出 
	if (start == end){
		cout << "两词相同，无需转换，词梯长度为0\n";
	}
	else {
		len = start.length(); 
		WorldLadder(start,end);
	}
	system("pause");
	return 0;
}
