// First_bianyi.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
//int _tmain(int argc, _TCHAR* argv[])
//{
//	int x;
//	CMyLex lex;
//	lex.Analysis("src/test.txt","");
//	cin >> x;
//	cin >> x;
//	return 0;
//}
#include "stdafx.h"


void UI_Head();

int _tmain(int argc, _TCHAR* argv[])
{
	char x;
	CMyLex lex;
	string in, out;

	while (1)
	{
		UI_Head();
		while (1)
		{
			cout << "请输入需要分析的文件名/路径：";
			cin >> in;
			ifstream rf;
			rf.open(in.c_str());
			if (rf){
				rf.close();
				break;
			}
			cout << "输入文件不存在,";
		}
		cout << "请输入存储结果的文件名/路径：";
		cin >> out;
		lex.Analysis(const_cast<char*>(in.c_str()), const_cast<char*>(out.c_str()));

		cout << "是否还需检测另一文件(Y/N)：";
		cin >> x;
		if (x != 'Y' || x != 'y') break;
		system("cls");
	}
	return 0;
}

void UI_Head()
{
	cout << "=================================================" <<endl;
	cout << "================编译原理第一次实验===============" << endl;
	cout << "=================TEST语言词法分析================" << endl;
	cout << "=====================第六组======================" << endl;
	cout << "================陈曦源  5120140975===============" << endl;
	cout << "================唐  荣  5120140988===============" << endl;
	cout << "================陶  琦  5120140548===============" << endl;
	cout << "================徐佳瑶  5120140970===============" << endl;
	cout << "=================================================" << endl;
}