#pragma once

struct LexErro
{
	int line=0;
	string errowords;
	string message;
};


class CMyLex
{
public:
	CMyLex();
	~CMyLex();
	void Analysis(char *input, char* output);//分析接口
private:
	int m_statu = 0;
	int m_line = 1;

	int ST(int st, char in);
	int ST_00(char in);//状态函数 
	int ST_01(char in);//ID
	int ST_02(char in);
	int ST_03(char in);
	int ST_04(char in);
	int ST_05(char in);
	int ST_06(char in);
	int ST_07(char in);
	int ST_erro(char in);
	vector<LexErro> m_ErroList;

	void init();//初始化

	bool If_ABC(char in);
	bool If_NUB(char in);
};

