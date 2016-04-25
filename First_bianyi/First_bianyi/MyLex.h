#pragma once
struct LexErro
{
	int line = 0;
	int endstatu = 0;
	string message;
	string word;
};
struct LexShrase
{
	int line = 0;
	int endstatu = 0;
	string type;
	string LexType;
	string word;
};


class CMyLex
{
public:
	CMyLex();
	~CMyLex();
	void Analysis(char *input, char* output, bool cover);//分析接口
private:

	void init();//初始化

	int m_statu = 0;
	int m_line = 1;
	vector<string> m_keywords;//用于缓存关键词

	int ST(int st, char in);//状态分配函数
	int ST_00(char in);//状态函数 
	int ST_01(char in);//ID
	int ST_02(char in);//NUB 
	int ST_03(char in);//NUB 0
	int ST_04(char in);//注释1
	int ST_05(char in);//注释2
	int ST_06(char in);//注释3
	int ST_07(char in);//注释结束
	int ST_08(char in);//单符号结束
	int ST_09(char in);//双前
	int ST_10(char in);//双
	int ST_11(char in);//!

	vector<char> m_shrase;//短语缓存
	vector<LexShrase> m_ShraseList;//正确短语缓存
	vector<LexErro> m_ErroList;//错误信息缓存

	//判断
	bool If_ABC(char in);
	bool If_NUB(char in);
	bool If_Sings(char in);
	bool If_FrontSings(char in);


	void f_settype(LexShrase* Shrase);//通过短语信息，设置短语类型
	void f_erromessage(LexErro* Erro);//通过ERROR信息，给予ERROR错误提示
	bool f_ShraseComType(string type, vector<char>v);//string与vector<char>对比
	void f_saveError(int laststatu);//保存错误信息




	//控制台输出
	void OutShrase();//输出所有短语缓存
	void OutError();//输出所有错误缓存
	void OutCode(ifstream* rf);//输出源文件
	//文件
	void SaveFile(char* output);//输出文件
	void OutShrase(char* output);//向文件输出正确的词
	void OutError(char* output);//向文件输出错误
};

