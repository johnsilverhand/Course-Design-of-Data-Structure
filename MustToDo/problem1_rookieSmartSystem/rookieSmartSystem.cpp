#include <bits/stdc++.h>
using namespace std;
#define MAX_PERSON 30
int Date = 0;
typedef struct pakege{
	string name;
	string packCode;
	string phone;
	string size;
	int date;
}pak; 
class Node {
 public:
  pak data;
  Node *prev;
  Node *next;
  Node(pak data) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
 public:
  Node *head;
  Node *tail;
  int MaxOfList;
  int NumOfList = 0; 
  DoublyLinkedList(int M) : MaxOfList(M), head(nullptr), tail(nullptr) {}

  void traverse() {
    Node *temp = head;
    while (temp) {
      cout << "������"<<temp->data.name << " �绰��"<<temp->data.phone<<" ���ڣ��ڼ��죩��"<<temp->data.date<<" ȡ����"<<temp->data.packCode<<" ���ܱ�ţ�"<<temp->data.size<<endl;
      temp = temp->next;
   }
 }

  void insertAtHead(pak data) {
  	if (NumOfList+1 <= MaxOfList){
  		Node *newNode = new Node(data);
  		NumOfList++;
    	if (!head) {
      	head = newNode;
      	tail = newNode;
      	return;
    	}
    	head->prev = newNode;
    	newNode->next = head;
    	head = newNode;
	}
	else{
		cout<<"��������"<<endl; 
	}
  }

  void insertAtTail(pak data) {
  	if (NumOfList+1 <= MaxOfList){
	    Node *newNode = new Node(data);
	    NumOfList++;
	    if (!tail) {
	      head = newNode;
	      tail = newNode;
	      return;
	    }
	    tail->next = newNode;
	    newNode->prev = tail;
	    tail = newNode;
	  }
	else {
		cout<<"��������"<<endl; 
	}
  }

  void deleteAtHead() {
    if (!head) {
      return;
    }
    if (head == tail) {
      NumOfList=0;
	  delete head;
      head = nullptr;
      tail = nullptr;
      return;
    }
    Node *temp = head;
    head = head->next;
    head->prev = nullptr;
    NumOfList--;
    delete temp;
  }

  void deleteAtTail() {
    if (!tail) {
      return;
    }
    if (head == tail) {
      NumOfList=0;
      delete tail;
      head = nullptr;
      tail = nullptr;
      return;
    }
    Node *temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    NumOfList--;
    delete temp;
  }
/*
  bool search(pak data) {
    Node *temp = head;
    while (temp) {
      if (temp->data == data) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }
  */
  bool searchPhone(string phoneNeedToSearch) {
    Node *temp = head;
    while (temp) {
      if (temp->data.phone == phoneNeedToSearch) {
        return true;
      }
      temp = temp->next;
    }
    return false;
	}
   bool searchCode(string codeNeedToSearch) {
    Node *temp = head;
    while (temp) {
      if (temp->data.packCode == codeNeedToSearch) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }
  string findPhoneByCode(string codeNeedToSearch){
  	Node *temp = head;
  	string result;
    while (temp) {
      if (temp->data.packCode == codeNeedToSearch) {
        result = temp->data.phone; 
		return result;
      }
      temp = temp->next;
    }
  } 
  void deleteNode(pak data) {
	  Node *temp = head;
	  while (temp) {
	    if (temp->data.phone == data.phone) {
	      if (temp == head) {
	        deleteAtHead();
	        return;
	      } else if (temp == tail) {
	        deleteAtTail();
	        return;
	      } else {
	        temp->prev->next = temp->next;
	        temp->next->prev = temp->prev;
	        delete temp;
	        NumOfList--;
	        return;
	      }
	    }
	    temp = temp->next;
	  }
	}
	void deleteNodeByPhone(string phoneDel) {
	  Node *temp = head;
	  while (temp) {
	    if (temp->data.phone == phoneDel) {
	      cout << "ȡ��ȡ����Ϊ"<<temp->data.packCode<<"�İ���\n"; 
	      if (temp == head) {
	        deleteAtHead();
	        return;
	      } else if (temp == tail) {
	        deleteAtTail();
	        return;
	      } else {
	        temp->prev->next = temp->next;
	        temp->next->prev = temp->prev;
	        delete temp;
	        NumOfList--;
	        return;
	      }
	    }
	    temp = temp->next;
	  }
	}
	void deleteOutdate(int date) {
	  Node *temp = head;
	  while (temp) {
	    if (temp->data.date + 2 <= date) {
	      if (temp == head) {
	        deleteAtHead();
	        return;
	      } else if (temp == tail) {
	        deleteAtTail();
	        return;
	      } else {
	        temp->prev->next = temp->next;
	        temp->next->prev = temp->prev;
	        delete temp;
	        NumOfList--;
	        return;
	      }
	    }
	    temp = temp->next;
	  }
	}
};
DoublyLinkedList Max(50);
DoublyLinkedList Mid(100);
DoublyLinkedList Min(500);
void packNotAuto(){
	pak packTemp;
	string codePart;
	cout<<"������Ҫ��ŵĻ��ܱ��: 1(��) 2(��) 3(С)\n";
	cin >> packTemp.size;
	if (packTemp.size=="1"){
		codePart = std::to_string(Max.NumOfList+1);
	}
	else if (packTemp.size=="2"){
		codePart = std::to_string(Mid.NumOfList+1);
	}
	else if (packTemp.size=="3"){
		codePart = std::to_string(Min.NumOfList+1);
	}
	cout<<"������������˵绰����\n";
	cin >> packTemp.phone;
	cout<<"�����������������\n";
	cin >> packTemp.name;
	packTemp.date = Date;
	packTemp.packCode = packTemp.size + codePart;
	if (packTemp.size=="1"){
		Max.insertAtTail(packTemp);
	}
	else if (packTemp.size=="2"){
		Mid.insertAtTail(packTemp);
	}
	else if (packTemp.size=="3"){
		Min.insertAtTail(packTemp);
	}
	cout<<"��Ű������\n";
}
void packAuto(){
	ifstream inputPack;
	inputPack.open("input.txt");
	while (!inputPack.eof()){
		pak packTemp;
		string codePart;
		inputPack >> packTemp.size;
		if (packTemp.size=="1"){
			codePart = std::to_string(Max.NumOfList+1);
		}
		else if (packTemp.size=="2"){
			codePart = std::to_string(Mid.NumOfList+1);
		}
		else if (packTemp.size=="3"){
			codePart = std::to_string(Min.NumOfList+1);
		}
		//cout<<"������������˵绰����\n";
		inputPack >> packTemp.phone;
		//cout<<"�����������������\n";
		inputPack >> packTemp.name;
		packTemp.date = Date;
		packTemp.packCode = packTemp.size + codePart;
		if (packTemp.size=="1"){
			Max.insertAtTail(packTemp);
		}
		else if (packTemp.size=="2"){
			Mid.insertAtTail(packTemp);
		}
		else if (packTemp.size=="3"){
			Min.insertAtTail(packTemp);
		}
	}
	cout<<"��Ű������\n";
	inputPack.close();
}
void analyse(){
	cout<<"����Ϊ��������Ϣ��������ݷ���\n";
	cout<<"���ڴ���ܰ�������Ϊ��"<<Max.NumOfList<<endl;
	cout<<"�����л��ܰ�������Ϊ��"<<Mid.NumOfList<<endl;
	cout<<"����С���ܰ�������Ϊ��"<<Min.NumOfList<<endl;
	cout<<"��y��ʾ��ϸ��Ϣ\n";
	string command;
	cin >> command;
	if (command == "y"||command == "Y") {
		cout<<"����ܰ���������Ϣ���£�\n";
		Max.traverse();
		cout<<"�л��ܰ���������Ϣ���£�\n";
		Mid.traverse();
		cout<<"С���ܰ���������Ϣ���£�\n";
		Min.traverse();
	} 
}
void admin(){
	while(1){
		char command;
		cout<<"����������ֽ�����ز���\n";
		cout<<"*******1.�ֶ������*****\n";
		cout<<"*******2.�Զ������*****\n";
		cout<<"*******3.��ȡ������Ϣ***\n";
		cout<<"*******4.�˳�����Աϵͳ*\n"; 
		cin>> command;
		if (command == '1') {
			packNotAuto();
			}
			else if (command =='2') {
				packAuto();
			}
			else if (command =='3') {
				analyse();
			}
			else if (command =='4') break;
			else cout<<"����ָ����Ч������������\n"; 
	}
}
void pickByPhone(){
	string phoneOfUser;
	cout<<"������绰����ȡ��\n";
	while (1){
		cin >> phoneOfUser;
		if (Max.searchPhone(phoneOfUser)||Mid.searchPhone(phoneOfUser)||Min.searchPhone(phoneOfUser)){
			while (Max.searchPhone(phoneOfUser)){
				Max.deleteNodeByPhone(phoneOfUser);	
			}
			while (Mid.searchPhone(phoneOfUser)){
				Mid.deleteNodeByPhone(phoneOfUser);	
			}
			while (Min.searchPhone(phoneOfUser)){
				Min.deleteNodeByPhone(phoneOfUser);	
			}
			cout<<"��ص����а����Ѿ�ȡ��\n";
			break; 
		}
		else{
			cout<<"�绰���벻���ڻ򲻴��ڸú�������Ӧ�İ���\n";
			break; 
		}
	}
}
void pickByCode(){
	string codeOfUser;
	string phoneOfUser;
	cout<<"��ȡ����ȡ��\n";
	while (1){
		cin >> codeOfUser;
		if (Max.searchCode(codeOfUser)||Mid.searchCode(codeOfUser)||Min.searchCode(codeOfUser)){
			if (Max.searchCode(codeOfUser)){
				phoneOfUser = Max.findPhoneByCode(codeOfUser);
				while (Max.searchPhone(phoneOfUser)){
					Max.deleteNodeByPhone(phoneOfUser);	
				}
			}
			if (Mid.searchCode(codeOfUser)){
				phoneOfUser = Mid.findPhoneByCode(codeOfUser);
				while (Mid.searchPhone(phoneOfUser)){
					Mid.deleteNodeByPhone(phoneOfUser);	
				}
			}
			if (Min.searchCode(codeOfUser)){
				phoneOfUser = Min.findPhoneByCode(codeOfUser);
				while (Min.searchPhone(phoneOfUser)){
					Min.deleteNodeByPhone(phoneOfUser);	
				}
			}
			cout<<"�绰��Ϊ"<<phoneOfUser<<"����ص����а����Ѿ�ȡ��\n";
			break; 
		}
		else{
			cout<<"ȡ���벻���ڻ򲻴��ڸ�ȡ��������Ӧ�İ���\n";
			break; 
		}
	}
}
void users(){
	while(1){
		char command;
		cout<<"����������ֽ�����ز���\n";
		cout<<"*******1.�绰��ȡ����***\n";
		cout<<"*******2.ȡ����ȡ����***\n";
		cout<<"*******3.�˳��û�ϵͳ***\n";
		cin>> command;
		if (command == '1') {
			pickByPhone();
			}
			else if (command =='2') {
				pickByCode();
			}
			else if (command =='3') break;
			else cout<<"����ָ����Ч������������\n"; 
	}
}
bool menu(){
	while(1){
		char command;
		cout<<"����������ֱ�ʾ�������\n";
		cout<<"*******1.����Ա*********\n";
		cout<<"*******2.�û�  *********\n";
		cout<<"*******3.��������*******\n";
		cout<<"*******4.�˳�ϵͳ*******\n";
		cin>> command;
		if (command == '1') {
			admin();
			}
			else if (command =='2') {
				users();
			}
			else if (command =='3') break;
			else if (command =='4') return false;
			else cout<<"����ָ����Ч������������\n"; 
	}
	return true;
}
void loadPack(){
	ifstream inputPack;
	inputPack.open("data.txt");
	while (!inputPack.eof()){
		pak packTemp;
		string codePart;
		inputPack >> packTemp.size;

		//cout<<"������������˵绰����\n";
		inputPack >> packTemp.phone;
		//cout<<"�����������������\n";
		inputPack >> packTemp.name;
		packTemp.date = Date;
		inputPack >> packTemp.packCode;
		if (packTemp.size=="1"){
			Max.insertAtTail(packTemp);
		}
		else if (packTemp.size=="2"){
			Mid.insertAtTail(packTemp);
		}
		else if (packTemp.size=="3"){
			Min.insertAtTail(packTemp);
		}
	}
	cout<<"�������\n";
	inputPack.close();
}
void updatePack(){
	Max.deleteOutdate(Date);
	Min.deleteOutdate(Date);
	Mid.deleteOutdate(Date);
}
void savePack(){
	ofstream savePack;
	savePack.open("data.txt");
	while (Max.head){
		savePack << Max.head->data.size <<" ";

		savePack << Max.head->data.phone<<" ";

		savePack << Max.head->data.name<<" ";

		savePack << Max.head->data.packCode<<endl;
		Max.deleteAtHead();
	}
	while (Mid.head){
		savePack << Mid.head->data.size <<" ";
		//cout<<"������������˵绰����\n";
		savePack << Mid.head->data.phone<<" ";
		//cout<<"�����������������\n";
		savePack << Mid.head->data.name<<" ";
		//packTemp.date = Date;
		savePack << Mid.head->data.packCode<<endl;
		Mid.deleteAtHead();
	}
	while (Min.head){
		savePack << Min.head->data.size <<" ";
		//cout<<"������������˵绰����\n";
		savePack << Min.head->data.phone<<" ";
		//cout<<"�����������������\n";
		savePack << Min.head->data.name<<" ";
		//packTemp.date = Date;
		savePack << Min.head->data.packCode<<endl;
		Min.deleteAtHead();
	}
	cout<<"�������\n";
	savePack.close();
}
int main() {
	bool needToExit;
	loadPack();
	while(1){
		cout<<"�����ǵ�"<<Date<<"��"<<endl; 
		cout<<"��������ڰ���\n"; 
		needToExit = menu();
		if (!needToExit) break;
		Date++;
		updatePack();
		cout<<"�������\n";

	}
  savePack();
  return 0;
}

