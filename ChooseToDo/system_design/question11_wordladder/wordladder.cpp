#include <bits/stdc++.h>
using namespace std;

map<string, string> dict,startSet,endSet;	//���ʱ������������ı߼��� �յ���������ı߼��� 
vector<string> midPath;		//�洢�м���Ա��ҵ�·�� 
int len;					//�ַ��� ���� 
typedef pair<string,string> line;	 
ifstream in;
void CreatDict (){
	in.open("words.txt");
	if (!in){
		cout << "���ļ� words.txt ʧ��";
		exit(1);
	}
	string temp;
	while ( getline(in,temp) ){
		dict.insert(make_pair(temp,temp));	 
	}
	in.close();
	cout <<"�Ѷ�ȡ�������ʱ�"<<endl;
}
bool Check(string isExit){
	if (dict.count(isExit)) return true;
	else return false;
}
//flag : 0Ϊ����㿪ʼ������1Ϊ���յ㿪ʼ���� 
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
					//�����ʴ�����û�ڵ�ǰ���򱻷��ʹ� 
					q.push(temp);
					//������Ա���Ѱ·�� 
					if(flag == 0) startSet[temp] = st;
					else{
						endSet[temp] = st;
					}
					visit[temp] = temp;
					//�����ʱ���һ���������������ҵ�·��������ֵΪ-1 
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
//˫��BFS 
void WorldLadder(string start,string end){
	//��ʼ�� 
	queue <string> fromStart,fromEnd;
	map<string, string> visitS,visitE;
	//�������յ㿪ʼ���������з������� 
	visitS[start] = start;
	visitE[end]	  = end;
	//�������յ㿪ʼ����������
	fromStart.push(start);
	fromEnd.push(end);
	
	int countS = 1,countE = 1;//��ǰ�������Ԫ�ظ��� 
	int isExitRoad = 0;
	//˫��BFS��Ҫ���� 
	while (!fromStart.empty() && !fromEnd.empty()){
		if (fromStart.size() <= fromEnd.size()){
			countS = update(fromStart,visitS,visitE,countS,0);
		}
		else{
			countE = update(fromEnd,visitE,visitS,countE,1);
		}
		//����ֵΪ-1��˵�������ҵ�����ֹ���� 
		if (countS == -1 || countE == -1) {
			cout << "��������Ѱ��\n";
			isExitRoad = 1;
			break;
		}
	}
	if (!isExitRoad) cout <<"���ݲ�����"<<endl; 
	//���·�� 
	cout <<"��ʼ�������\n"<<endl; 
	for (auto it = midPath.begin(); it != midPath.end(); it++)
	{
		vector<string> path;
		string tmp = *it;
		string tmp1 = *it;
		path.push_back(tmp);
		//�����м���ҵ��ôʵ�����·����ת�� 
		while (tmp != start){
			tmp = startSet[tmp];
			path.push_back(tmp);
		};
		reverse(path.begin(),path.end());
		//�����м���ҵ��ôʵ��յ��·�� 
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
	//���� 
	while (1){
		cout <<"����������\n";
		cin  >>start;
		if (Check(start)) break;
		else {
			cout <<"�ôʲ����ڣ�����������\n";
			continue; 
		}
	}
	while (1){
		cout <<"�������յ��\n";
		cin  >>end;
		if (start.length() != end.length()){
			cout <<"���ʳ��Ȳ��ȣ������������յ��\n";
			continue; 
		}
		if (Check(end)) break;
		else {
			cout <<"�ôʲ����ڣ�����������\n";
			continue; 
		}
	}
	//������� 
	if (start == end){
		cout << "������ͬ������ת�������ݳ���Ϊ0\n";
	}
	else {
		len = start.length(); 
		WorldLadder(start,end);
	}
	system("pause");
	return 0;
}
