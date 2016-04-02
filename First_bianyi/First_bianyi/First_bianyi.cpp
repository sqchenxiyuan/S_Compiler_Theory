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
int _tmain(int argc, _TCHAR* argv[])
{
	int x;
	CMyLex lex;
	lex.Analysis("src/test.txt","src/out.txt");
	cin >> x;
	cin >> x;
	return 0;
}