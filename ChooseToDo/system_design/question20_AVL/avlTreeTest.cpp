#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <queue>
using namespace std;

// ����AVL���ڵ�
struct Node {
  int key;
  int value;
  int height;
  Node *left;
  Node *right;

  // ���캯��
  Node(int k, int v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

// ��ȡ�ڵ�ĸ߶�
int getHeight(Node *node) {
  if (node == nullptr) return 0;
  return node->height;
}

// ��ȡ�ڵ��ƽ������
int getBalanceFactor(Node *node) {
  if (node == nullptr) return 0;
  return getHeight(node->left) - getHeight(node->right);
}

// ���½ڵ�ĸ߶�
void updateHeight(Node *node) {
  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// ����
Node* leftRotate(Node *node) {
  Node *temp = node->right;
  node->right = temp->left;
  temp->left = node;

  updateHeight(node);
  updateHeight(temp);

  return temp;
}

// ����
Node* rightRotate(Node *node) {
  Node *temp = node->left;
  node->left = temp->right;
  temp->right = node;

  updateHeight(node);
  updateHeight(temp);

  return temp;
}
//Ѱ����������С���
Node* findMin(Node *node) {
  if (node == nullptr || node->left == nullptr) return node;
  return findMin(node->left);
}

// ��AVL���в����½ڵ�
Node* insert(Node *node, int key, int value) {
  if (node == nullptr) return new Node(key, value);

  if (key < node->key) {
    node->left = insert(node->left, key, value);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value);
  } else {
    // ���key�Ѿ����ڣ�����½ڵ��ֵ
    node->value = value;
    return node;
  }

  // ���½ڵ�ĸ߶�
  updateHeight(node);

  // ����ڵ��ƽ������
  int balanceFactor = getBalanceFactor(node);

  // ����ڵ��ƽ�����Ӵ���1������Ҫ������ת����
    if (balanceFactor > 1) {
    // ����²���Ľڵ��ڽڵ������������࣬���������
    if (key < node->left->key) {
      return rightRotate(node);
    }
    // ����²���Ľڵ��ڽڵ�����������Ҳ࣬���Ƚ��������ٽ�������
    if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  // ����ڵ��ƽ������С��-1������Ҫ������ת����
  if (balanceFactor < -1) {
    // ����²���Ľڵ��ڽڵ�����������Ҳ࣬���������
    if (key > node->right->key) {
      return leftRotate(node);
    }
    // ����²���Ľڵ��ڽڵ������������࣬���Ƚ��������ٽ�������
    if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }

  return node;
}

// ��AVL���в��ҽڵ�
Node* find(Node *node, int key) {
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    return find(node->left, key);
  } else if (key > node->key) {
    return find(node->right, key);
  } else {
    return node;
  }
}
// ��AVL����ɾ���ڵ�
Node* remove(Node *node, int key) {
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    } else if (node->left == nullptr) {
      Node *temp = node->right;
      delete node;
      return temp;
    }

  else if (node->right == nullptr) {
    Node *temp = node->left;
    delete node;
    return temp;
  } else {
    // ����ڵ�������������������������ҵ��������е���С�ڵ����滻��ǰ�ڵ�
    Node *successor = findMin(node->right);
    node->key = successor->key;
    node->value = successor->value;
    node->right = remove(node->right, successor->key);
  }
}
  // ���½ڵ�ĸ߶�
  updateHeight(node);
  // ����ڵ��ƽ������
  int balanceFactor = getBalanceFactor(node);
  // ����ڵ��ƽ�����Ӵ���1������Ҫ������ת����
  if (balanceFactor > 1) {
    // ����ڵ����������ƽ�����Ӵ���0�����������
    if (getBalanceFactor(node->left) > 0) {
      return rightRotate(node);
    }
    // ����ڵ����������ƽ������С��0�����Ƚ��������ٽ�������
    if (getBalanceFactor(node->left) < 0) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  // ����ڵ��ƽ������С��-1������Ҫ������ת����
  if (balanceFactor < -1) {
    // ����ڵ����������ƽ������С��0�����������
    if (getBalanceFactor(node->right) < 0) {
      return leftRotate(node);
    }
    // ����ڵ����������ƽ�����Ӵ���0�����Ƚ��������ٽ�������
    if (getBalanceFactor(node->right) > 0) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}
//��ӡ������ 
void printTree(Node *node) {
	if (node == nullptr) return;
	queue<Node *> q;
	q.push(node);
	Node *temp;
	cout<<"key lchild rchild"<<endl;
	while (!q.empty()){
		temp = q.front();
		q.pop();

		cout <<  std::left << setw(4)<<temp->key;
		if (temp->left) {
			q.push(temp->left);
			cout<< std::left << setw(7)<<temp->left->key;
		}else {
			cout<< std::left << setw(7)<<" ";
		}
		if (temp->right) {
			q.push(temp->right);
			cout<< std::left << setw(7)<<temp->right->key<<endl;;
		}else {
			cout<<endl;
		}
	}
	cout << endl;
}
//���ļ� 
void printTreeFile(Node* root,ofstream &fout) {
    if (root == nullptr) {
        return;
    }
    fout << root->key<<" "<<root->value << endl;
    printTreeFile(root->left,fout);
    printTreeFile(root->right,fout);
}
int main() {
  // ���ļ��ж�ȡ����
  ifstream fin("data.txt");
  if (!fin) {
    cerr << "���ļ�data.txtʧ��." << endl;
    return 1;
  }

  // ����AVL��
  Node *root = nullptr;
  int key, value;
  while (fin >> key >> value) {
    root = insert(root, key, value);
  }
  while (1){
  	  // �˵�
  	  int command;
	  cout<<"****************"<<endl;
	  cout<<"** 1.���ҽڵ� **"<<endl;
	  cout<<"** 2.����ڵ� **"<<endl;
	  cout<<"** 3.ɾ���ڵ� **"<<endl;
	  cout<<"** 4.���AVL��**"<<endl;
	  cout<<"** 5.  �˳�   **"<<endl;
	  cout<<"****************"<<endl;
	  cin >> command;
	  if (command == 1){
	  	// ���ҽڵ�
		  int searchKey;
		  cout << "������һ�������ؼ���Key���в��ҽڵ�: ";
		  cin >> searchKey;
		  Node *node = find(root, searchKey);
		  if (node != nullptr) {
		    cout << "Key: " << node->key << ", Value: " << node->value << endl;
		  } else {
		    cout << "�ؼ���δ�ҵ�." << endl;
		  }
		  system("pause");
	  } else if (command == 2){
	  	// ����ڵ�
		  int insertKey, insertValue;
		  cout << "������һ�������ؼ���Key��һ������Value���в���ڵ�: ";
		  cin >> insertKey >> insertValue;
		  root = insert(root, insertKey, insertValue);
		  cout << "����ɹ�."<<endl;
		  system("pause");
	  } else if (command == 3){
	    // ɾ���ڵ�
		  int removeKey;
		  cout << "������һ�������ؼ���Key����ɾ���ڵ�: ";
		  cin >> removeKey;
		  root = remove(root, removeKey);
		  cout << "ɾ���ɹ���������������������۲���"<<endl;
		  // �Կ���֤�ķ�ʽ������
		  cout << "AVL Tree: " << endl;
		  printTree(root);
		  system("pause");
	  } else if (command == 4){
	  	// �Կ���֤�ķ�ʽ������
		  cout << "AVL Tree: " << endl;
		  printTree(root);
		  system("pause");
	  } else if (command == 5){
	  	// �޸ĺ��������data.txt���Ը��ǵ���ʽ 
	  	    ofstream fout("data.txt");
  			if (!fout) {
    			cerr << "���ļ�data.txtʧ��." << endl;
    			return 1;
  			}
  		  printTreeFile(root,fout);	
	  	  break;		
	  } else {
	  	  cout << "����ָ����Ч������������"<<endl;
		  system("pause");
		}
	//���� 
	system("cls");
	}
  system("pause");
  return 0;
}
