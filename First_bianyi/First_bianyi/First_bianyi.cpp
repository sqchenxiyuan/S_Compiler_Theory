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
	bool cover= TRUE;
	char x;
	string in, out;

	while (1)
	{
		UI_Head();
		CMyLex lex;
		////对输入文件路径验证
		//while (1)
		//{
		//	cout << "请输入需要分析的文件名/路径：";
		//	cin >> in;
		//	ifstream rf;
		//	rf.open(in.c_str());
		//	if (rf){
		//		rf.close();
		//		break;
		//	}
		//	cout << "输入文件不存在,";
		//}

		////对输出文件路径验证
		//cout << "请输入存储结果的文件名/路径：";
		//cin >> out;
		//ifstream rf;
		//rf.open(out.c_str());
		//if (rf)
		//{
		//	cout << "输出文件已存在是否继续覆盖？(Y/N)：";
		//	char x;
		//	cin >> x;
		//	if (x == 'N'||x == 'n') cover = FALSE;
		//}
		//rf.close();

		in = "src/test.txt";
		out = "src/out.txt";

		//解析
		lex.Analysis(const_cast<char*>(in.c_str()), const_cast<char*>(out.c_str()),cover);

		CGramAly galy(lex.getShraseList());
		galy.Analysis();




		cout << "是否还需检测另一文件(Y/N)：";
		cin >> x;
		if (x != 'Y' && x != 'y') break;
		system("cls");
	}
	return 0;
}

void UI_Head()
{
	cout << "=================================================" << endl;
	cout << "===================编译原理实验==================" << endl;
	cout << "===================TEST语言分析==================" << endl;
	cout << "=====================第六组======================" << endl;
	cout << "================陈曦源  5120140975===============" << endl;
	cout << "=================================================" << endl;
}