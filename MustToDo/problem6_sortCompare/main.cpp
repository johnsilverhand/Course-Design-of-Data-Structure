#include <iostream>
#include"sort.h"
#include <time.h>
#include<fstream>
using namespace std;
#define arrNumber 50000
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//随机创建样本 
void CreateRandomTxt()
{
	srand((int)time(0));
	int i = 1;
	ofstream out;
	out.open("input.txt");
	if (!out)
	{
		cout << "打开文件失败!";
		exit(1);
	}
	for (i; i < 50001; i++)
	{
		out << rand() % 50000 + 1<<' ';
		if (i%20==0)
		{
			out << endl;
		}
	}
	out.close();
}
//创建升序样本
void CreateOrderTxtp()
{
	int i = 1;
	ofstream out;
	out.open("input.txt");
	if (!out)
	{
		cout << "打开文件失败!";
		exit(1);
	}
	for (i; i < 50001; i++)
	{
		out << i<<' ';
		if (i % 20 == 0)
		{
			out << endl;
		}
	}
	cout<<"创建升序样本完成"<<endl;
	out.close();
	
}

//创建降序样本
void CreateOrderTxtn()
{
	int i = 50000;
	ofstream out;
	out.open("input.txt");
	if (!out)
	{
		cout << "打开文件失败!";
		exit(1);
	}
	for (i; i >0; i--)
	{
		out << i<<' ';
		if (i % 20 == 0)
		{
			out << endl;
		}
	}
	cout<<"创建降序样本完成"<<endl;
	out.close();
}
//将样本输入数组
void Inarr(int a[])
{
	int i = 1;
	ifstream in;
	in.open("input.txt");
	if (!in)
	{
		cout << "打开样本文件失败!";
		exit(0);
	}
	for (i; i <= 50000; i++)
	{
		in >> a[i];
	}
	in.close();
}
int main( ) {
	int sTime,eTime; 
	int a[arrNumber];
	cout <<"第一个样本（升序）排序如下"<<endl;
	sTime = clock();
	CreateOrderTxtp();
	Inarr(a);
	eTime = clock();
	cout<<"生成样本用时"<< eTime-sTime <<"ms"<<endl; 
	Sort temp(a,arrNumber);
	temp.ShowSort(1);
	cout <<"第二个样本（降序）排序如下"<<endl;
	sTime = clock();
	CreateOrderTxtn();
	Inarr(a);
	eTime = clock();
	cout<<"生成样本用时"<< eTime-sTime <<"ms"<<endl;
	Sort temp1(a,arrNumber);
	temp1.ShowSort(2);
	for (int i = 3;i <= 10;i++){
		sTime = clock();
		CreateRandomTxt();
		Inarr(a);
		eTime = clock();
		cout<<"生成样本用时"<< eTime-sTime <<"ms"<<endl; 
		Sort temp3(a,arrNumber);
		temp3.ShowSort(i);
	} 
	return 0;
}
