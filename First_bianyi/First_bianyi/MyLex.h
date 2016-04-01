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
	void Analysis(char *input, char* output);//·ÖÎö½Ó¿Ú
private:
	int m_statu = 0;
	int m_line = 1;

	int ST(int st, char in);
	int ST_00(char in);//×´Ì¬º¯Êı 
	int ST_01(char in);//ID
	int ST_02(char in);//NUB 
	int ST_03(char in);//NUB 0//ÍË³ö×´Ì¬
	int ST_04(char in);//×¢ÊÍ1
	int ST_05(char in);//×¢ÊÍ2
	int ST_06(char in);//×¢ÊÍ3
	int ST_07(char in);//Ç°·ûºÅ×´Ì¬
	int ST_08(char in);
	vector<LexErro> m_ErroList;

	void init();//³õÊ¼»¯


	bool If_ABC(char in);
	bool If_NUB(char in);
	bool If_Sings(char in);
	bool If_FrontSings(char in);


	vector<char> m_shrase;//¶ÌÓï»º´æ
	void f_outshrase();//Êä³ö»º´æ
};

