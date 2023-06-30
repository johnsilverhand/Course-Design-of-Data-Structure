#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define chNum 255
#define INF 10000
//设置为asiica码表字符个数 
typedef struct Node
{
	char alpha='\0';
	int num=0;	//所在文章的该字符的个数 
	bool flag=true;//是否被访问过 
	string code="";
	int Father=0,LChild=0,RChild=0;
}Node;
Node nodes[2*chNum];
 
typedef struct BiTNode
{
	Node data;
	BiTNode *LChild,*RChild;
}BiTNode,*BiTree;
 
bool ReadFromFile(Node a[])
{
	char ch;
	int loc;
	FILE *fp;
	if((fp=fopen("source.txt","r"))==NULL){
		cout<<"文件打开失败！\n";
		return false;
	}
	else
	{
		while(!feof(fp))
		{
			ch=fgetc(fp);
			loc=int(ch);
			a[loc].num++;
		}
	}
	fclose(fp);
	return true;
}
 
int SearchMin(Node a[],int n)
{
	int min=INF,k;
	for(int i=0;i<n;i++){
    	if(a[i].flag && (a[i].num<min)){
    		min=a[i].num;
    		k=i;
		}
	}
	return k;
}
char h[20];
void Encode(Node a[])
{
    string s;
	for(int i=0;i<chNum+1;i++)
	{
		s="";
		int k=0,f=-1,c=i;
		while(f!=0)
		{
			f=a[c].Father;
			if(a[f].LChild==c)
			{
				s+='0';
			}
			if(a[f].RChild==c)
			{
				s+='1';
			}
			c=f;
		}
		reverse(s.begin(),s.end());
		a[i].code=s;
	}
}
 
void EncodeOutput(Node a[])
{
	char ch;
	int x;
	ifstream infile;
	infile.open("source.txt");
	ofstream outfile;
	outfile.open("code.txt");
	if(outfile&&infile)
	{
		while(!infile.eof()){
			infile>>std::noskipws;
			//使之可以读取到空格 
			infile>>ch;
	 		x=int(ch);
	    	outfile<<a[x].code;

		}
	}
	else
	{
		cout<<"打开失败！\n";
	}
	outfile.close();
	infile.close();
}
 
void RecodeOutput(Node a[])
{
	char ch;
	int x;
	ifstream infile;
	infile.open("code.txt");
	ofstream outfile;
	outfile.open("recode.txt");
	if(outfile&&infile)
	{
		infile>>noskipws;
		while(!infile.eof())
		{
			infile>>ch;
	    	if((ch!='0')&&(ch!='1'))
	    	{
	    		outfile<<ch;
			}
			else if(ch==' ')
			{
				cout<<" ";
			}
			else
			{
				int k=2*chNum;
				while(k>chNum)
				{
					if(ch=='0')
					{
						k=a[k].LChild;
					}
					if(ch=='1')
					{
						k=a[k].RChild;
					}
					if(k>chNum)
					{
						infile>>ch;
					}
				}
				outfile<<a[k].alpha;
			}
		}
	}
	else
	{
		cout<<"打开失败！\n";
	}
	outfile.close();
	infile.close();
}
 
int main() 
{
	//初始化 
	for(int i=0;i<chNum+1;i++)
	{
		nodes[i].alpha= i;
	}
	if( !ReadFromFile(nodes) )return 0;
	int n=chNum+1;
	for(int i=0;i<chNum;i++)
	{
		int a1,a2;
		a1=SearchMin(nodes,n);
		nodes[a1].flag=false;
		a2=SearchMin(nodes,n);
		nodes[a2].flag=false;
		nodes[n].num=nodes[a1].num+nodes[a2].num;
		nodes[n].flag=true;
		nodes[n].LChild=a1;
		nodes[n].RChild=a2;
		nodes[a1].Father=n;
		nodes[a2].Father=n;
		n++;
	}
	Encode(nodes);
	EncodeOutput(nodes);
	cout<<"文件编码成功！\n";
	RecodeOutput(nodes);
	cout<<"文件译码成功！\n";
	return 0;
}
