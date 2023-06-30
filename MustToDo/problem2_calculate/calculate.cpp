#include <iostream>
#include <Windows.h>
#include <stack>
#include <queue> 
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
#define red  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)											 //��ɫ
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)						 //��ɫ
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)											//��ɫ
#define white 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)    //��ɫ
#define ching SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE)						//��ɫ

void INFO(string info) {
	cout << "["; green; cout << "INFO"; white; cout << "]:" << info ;

}
void ERROROUT(string error) {
	cout  << "["; red; cout << "ERROR"; white; cout << "]:" << error << endl;
}

// ����ʹ����������ȷ�����Ҫ��ȡ���ȼ�
int getPriority(char ch) {
    int level = 0; // ���ȼ�
    
    switch(ch) {
        case '(':
            level = 1;
            break;
        case '+':
        case '-':
            level = 2;
            break;
        case '*':
        case '/':
            level = 3;
            break;
        default:
            break;
    }
    return level;
}
// ������Ӧ�ļ���
double Calculate(char ch, int a, int b) {
    double result = 0;
    
    switch(ch) {
        case '+':
            result = b + a;
            break;
        case '-':
            result = b - a;
            break;
        case '*':
            result = b * a;
            break;
        case '/':
            if(a == 0) {
                ERROROUT( "��������Ϊ0��\n");
				exit(1);//��������  
            }
            else
                result = b / a;
            break;
        default:
            break;
    } 
    return result; // ���ؼ���õ��Ľ��
}
void calculator(const string &s){
	
    std::stack<double> m_integer;  // ��ջ
    std::stack<char> op; 		   // ������ջ
    char  c; 					   // c�洢������ջ����Ԫ��
    int num, a, b; 				   // result�洢����Ľ��,a,b�洢����ջ��ȡ����������
	double result;
	for (int i = 0; i<s.size(); i++){
		ching;cout<<"��ǰ������ַ�Ϊ��";white;cout<<s[i]<<endl; 
		if (s[i] == '#') continue;
		if(isdigit(s[i])) { 	   // ���������
                num = 0;
                do {
                    num = num * 10 + (s[i] - '0'); // ch - '0'����ASCAII�룬�ַ�������֮���ת����ϵ
                    i++;
                    ching;cout<<"��ǰ������ַ�Ϊ��";white;cout<<s[i]<<endl; 
                }while(isdigit(s[i]));
                m_integer.push(num); // �浽��ջ��
                INFO("��ǰ���Ѵ�����ջ��,����Ϊ��");cout<<num<<endl;             
		}
		if(s[i] == '(') { 	   // (:������
                op.push(s[i]);
                INFO("��ǰ�������Ѵ���������ջ��\n"); 
        }
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') { // ������
                if(op.empty()) {   // ���ջ�գ�ֱ��ѹ��ջ
                    op.push(s[i]);
                    INFO("��ǰ�������Ѵ�����ջ��,�ò�����Ϊ��");cout<<s[i]<<endl; 
                }
                else {
                    // �Ƚ�ջop���Ĳ������뵱ǰ�����������ȼ�
                    // �����ǰ���ȼ��ߣ���ջ�����򣬵���ջ�еĲ�����������1.����������С�ڵ�ǰ���ȼ� 2.�����( 3.��ջ��
                    while(!op.empty()) {
                        c = op.top();
                        if(getPriority(s[i]) <= getPriority(c)) {
                            // ���ȼ��ͻ����
                            // ȡ��ջ�в���������ջ���������������㣬�ٽ�����Ż���ջ
                            result = 0;
                            a = m_integer.top(); // �ڶ���������,��Ϊջ�Ǻ���ȳ�
                            m_integer.pop();
                            INFO("��������ջ������Ϊ��");cout<< a <<endl;
                            b = m_integer.top(); // ��һ��������
                            INFO("��������ջ������Ϊ��");cout<< b <<endl;
                            m_integer.pop();
                            result = Calculate(c, a, b); // ����
                            //������Ϊ��λС�� 
                			INFO("��������ջ������Ϊ��");cout<<setiosflags(ios::fixed)<<setprecision(2)<<result<<endl;            
                            m_integer.push(result); // �Ѽ�����ѹ��ջ��
                            op.pop(); // ��������ջ
                            INFO("�в�������������ջ���ò�����Ϊ");cout<< c <<endl; 
                        } else // ��ǰ���������ȼ�����ջ�в�����
                            break;
                    } // while����
                    op.push(s[i]); // ��ֹ���ϵ��Ƴ�������������ջ��;���ߵ�ǰ���������ȼ�����
                    INFO("��ǰ�������Ѵ�����ջ��,�ò�����Ϊ��");cout<<s[i]<<endl;
                } // else
        }
        if(s[i] == ')') { // ����������ţ�һֱ�Ƴ�ջ�в�������ֱ������������(
                while(op.top() != '(') {
                    c = op.top(); // ȡ��ջ��������
                    // ȡ��ջ�в���������ջ���������������㣬�ٽ�����Ż���ջ
                    result = 0;
                    a = m_integer.top(); // �ڶ���������,��Ϊջ�Ǻ���ȳ�
                    m_integer.pop();
                    INFO("��������ջ������Ϊ��");cout<< a <<endl;
                    b = m_integer.top(); // ��һ��������
                    INFO("��������ջ������Ϊ��");cout<< b <<endl;
                    m_integer.pop();
        
                    result = Calculate(c, a, b); // ����
                    //������Ϊ��λС�� 
        			INFO("��������ջ������Ϊ��");cout<<setiosflags(ios::fixed)<<setprecision(2)<<result<<endl;            
                    m_integer.push(result); // �Ѽ�����ѹ��ջ��
                    INFO("�в�������������ջ���ò�����Ϊ");cout<< c <<endl;
					op.pop(); // �Ѳ������Ƴ�ջ
                }
                op.pop(); // ��������(�Ƴ�ջ
                INFO("��ǰ�������ѵ���������ջ\n");
        }   
	}
	 while(!op.empty()) { // ��ջ���գ�����ȡ�����������м���
           c = op.top(); // ȡ��ջ��������
	        // ȡ��ջ�в���������ջ���������������㣬�ٽ�����Ż���ջ
	        result = 0;
	        a = m_integer.top(); // �ڶ���������,��Ϊջ�Ǻ���ȳ�
	        m_integer.pop();
	        INFO("��������ջ������Ϊ��");cout<< a <<endl;
	        b = m_integer.top(); // ��һ��������
	        INFO("��������ջ������Ϊ��");cout<< b <<endl;
	        m_integer.pop();
	        result = Calculate(c, a, b); // ����
	        //������Ϊ��λС�� 
			INFO("��������ջ������Ϊ��");cout<<setiosflags(ios::fixed)<<setprecision(2)<<result<<endl;            
	        m_integer.push(result); // �Ѽ�����ѹ��ջ��
	        INFO("�в�������������ջ���ò�����Ϊ");cout<< c <<endl;
			op.pop(); // �Ѳ������Ƴ�ջ
        }
        INFO("��������ջ������Ϊ��");cout<<setiosflags(ios::fixed)<<setprecision(2)<<m_integer.top()<<endl;
        INFO("���Ϊ"); 
        cout<<setiosflags(ios::fixed)<<setprecision(2)<<m_integer.top()<<endl;
        m_integer.pop();

}
bool iscorrect(const string &s)
{
	int zuokuohao = 0;
	char ch;
	int onlyOPND = 0;
	int isColiedOPND = 0;
	stack<char> brackets;
	for (int i = 0; i<s.size(); i++)
	{
		if (i!=0 && i != s.size()-1 && s[i] == '#'){
			ERROROUT( "���ʽ�м京��#������������" );cout << endl;
			return false;
		}
		if (s[i] == '(') {
			//if (s[i])
			brackets.push(s[i]);
			isColiedOPND == 0; 
		}
		if (isdigit(s[i])) isColiedOPND = 1;
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
			if (isColiedOPND == 0) {
				ERROROUT("�����λ�ô���ʹ��ΪһĿ���������û���κ���������ƥ��Ĳ�����");cout<< endl;
				return false;
			}
			else isColiedOPND = 0; 
		}
		if (!(isdigit(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '#' || s[i] == '(' || s[i] == ')')){
			ERROROUT( "���зǷ��ַ�������������" );cout << endl;
			return false;
		}
		else if (s[i] == ')'){
			if (brackets.empty())
			{
				ERROROUT("����û�гɶԣ�����������");cout<< endl;
				return false;
			}
			if (isColiedOPND == 0){
				ERROROUT( "���������������" );cout << endl;
				return false;
			} 	 
			else brackets.pop();
		}
	}
	if (s == "" || s == " " || s == "\n"||s == "#"||s=="##"){
		ERROROUT("�����룬����������" );cout << endl;
		return false; 
	}
	if (s[0] != '#'){
		ERROROUT( "û����#��ͷ������������"); cout<< endl;
		return false;
	}
	if (s[s.size() - 1] != '#'){
		ERROROUT( "û����#��β������������"); cout<< endl;
		return false;
	}

	if (brackets.empty()) return true;
	else {
		ERROROUT("����û�гɶԣ�����������");cout<< endl;
		return false;
	}
}

int main()
{
	int flag = 1;
	INFO("��������ʽ���ʽ,��#��ͷ������#��β��\n");
	string s;
	while (flag)
	{
		cin >> s;
		if (iscorrect(s)) flag = 0;
	}
	INFO("����������£�");
	cout << s <<endl; 
	calculator(s);
	system("pause");
	return 0;
}
