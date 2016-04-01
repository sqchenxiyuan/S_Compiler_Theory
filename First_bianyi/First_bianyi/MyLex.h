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
	int ST_02(char in);//NUB 
	int ST_03(char in);//NUB 0//退出状态
	int ST_04(char in);//注释1
	int ST_05(char in);//注释2
	int ST_06(char in);//注释3
	int ST_07(char in);//注释结束
	int ST_08(char in);//单符号结束
	int ST_09(char in);//双前
	int ST_10(char in);//双
	int ST_11(char in);//!

	vector<LexErro> m_ErroList;

	void init();//初始化


	bool If_ABC(char in);
	bool If_NUB(char in);
	bool If_Sings(char in);
	bool If_FrontSings(char in);


	vector<char> m_shrase;//短语缓存
	void f_outshrase();//输出缓存
	void f_outtype(int endstatu);//输出类型
};

