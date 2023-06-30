#include<cstdio>
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<string.h>
#include<sstream>
using namespace std;
//����
class Rule{
public:
    string name;
    vector<string> content;
    Rule(string in_name,vector<string> in_content) :name(in_name),content(in_content){}
};
//�洢��������ı���
vector<Rule> rules;
bool isMatch;

//string��int�໥ת���ĺ���
//stringstream��������ת�����ַ����ָ�
int StringToInt(string s){
    int answer;
    stringstream ss(s);
    ss >> answer;
    return answer; 
}
string IntToString(int answer){
    stringstream ss;
    ss << answer;
    return ss.str();
}
bool JudgeIsNum(string s){
    for (int  i = 0; i < s.length(); i++){
        if (s[i] > '9' || s[i] < '0') return false;
    } 
	return true; 
}
void HandleURLRule (string s,string name){
    int spiltLoc;
    string str;
    vector<string> content;
    bool isSpilt = true;
    //URL���һ���ַ�Ϊ / �ǲ������ָ�����,֮��ҲҪ������ַ�������
    if (s[s.length()-1] != '/'){
        isSpilt = false;
        s = s + "/"; //����������ͬ�������ַ�ƴ��
    }
    spiltLoc = s.find("/");
    while (spiltLoc != -1){
        str = s.substr(0,spiltLoc); //��ȡ�ָ�������һ���ַ���
        s = s.substr(spiltLoc + 1,s.length());
        content.push_back(str);
        spiltLoc = s.find("/");
    }
    if (isSpilt){
        content.push_back("/");
    }
    rules.push_back(Rule(name,content));
}
//�жϷ��Ϲ���������һ��һ�����if-else��ȥ�ж�
vector<string> Match (int k, string url){
    int spiltLoc;
    int i;
    string str;
    bool isSpilt = true;
    vector<string> result;
    vector<string> urlCur;
    if (url[url.length() - 1] != '/')
    {
        isSpilt = false;
        url = url + "/";
    }
    int urlIndex = 0;
    spiltLoc = url.find("/");
    while (spiltLoc != -1)
    {
        str = url.substr(0,spiltLoc);
        url = url.substr(spiltLoc + 1,url.length());
        urlCur.push_back(str);
        spiltLoc = url.find("/");
    }
    if (isSpilt)
        urlCur.push_back("/");
    for (i = 0; i < rules[k].content.size() && urlIndex < urlCur.size(); i++){
        if (rules[k].content[i] == "<path>" && urlCur[urlIndex].length() != 0){
			str = urlCur[urlIndex];
            for (int j = urlIndex + 1;j < urlCur.size();j++){
                if (urlCur[j] == "/"){
                    str = str + "/";
                }
                else
                    str = str + "/" + urlCur[j];
            }
            result.push_back(str);
            urlIndex = urlCur.size();
            i = rules[k].content.size();
        }
        else if (rules[k].content[i] == "<int>" && urlCur[urlIndex].length() != 0){
            if (JudgeIsNum(urlCur[urlIndex])){
                result.push_back(IntToString(StringToInt(urlCur[urlIndex])));
                urlIndex++;
            }
            else {
                isMatch = false;
                break;
            }    
        }
        else if (rules[k].content[i] == "<str>" && urlCur[urlIndex].length() != 0){
            result.push_back(urlCur[urlIndex]);
            urlIndex++;
        }
        else {
        	if (rules[k].content[i] == urlCur[urlIndex])
        		urlIndex++;
        	else{
        		isMatch = false;
				break;	
			}
        }
    }
    //δƥ������ 
    if (urlIndex != urlCur.size() || i < rules[k].content.size()){
    	isMatch = false;
	}
    return result;
}

int main(){
    string format,name,url;
    int ruleNum,addressNum;
    int error;
    int j;
    cin >> ruleNum >> addressNum;
    for (int i = 0; i < ruleNum; i++){
        cin >> format >> name;
        format = format.substr(1, format.length());
        HandleURLRule(format,name);
    }
    for (int i = 0; i < addressNum; i++){
        cin >> url;
        url = url.substr(1,url.length());
        //��ʼ�Ե�ǰ��ַ���й���ƥ�� 
        for ( j = 0; j < ruleNum; j++){
            isMatch = true;
            vector<string> vec = Match(j,url);
            if (isMatch){
                cout << rules[j].name;
                for (int h = 0; h < vec.size(); h++)                {
                    cout << " "<< vec[h]; 
                }
                cout << endl;
                break;
                
            }  
        }
        if (j == ruleNum) cout<<"404"<<endl;
    }
    
   return 0; 
}
