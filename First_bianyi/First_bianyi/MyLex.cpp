#include "stdafx.h"
#include "MyLex.h"

CMyLex::CMyLex()
{
	init();
}


CMyLex::~CMyLex()
{
}

void CMyLex::Analysis(char *input, char* output, bool cover)
{
	ifstream rf;//读取文件
	ofstream wf;//输出文件
	rf.open(input);
	if (cover)
	{
		wf.open(output);
	}
	else
	{
		wf.open(output, ios_base::app);
	}
	wf.close();

	Sleep(500);
	if (!rf)  //读取txt文件
	{
		printf("读取文件失败 \n ");
	}
	else
	{
		cout << "读取成功" << endl;
		char c = ' ';
		rf.read(&c, 1);
		while (!rf.eof())
		{
			int last_statu = m_statu;//存储上一个状态，用于判断单词类型，错误来源
			m_statu = ST(m_statu, c);

			////正确
			if (m_statu != last_statu&&m_statu == 0)//初始状态为0 或者  变为0  输出单词  
			{
					LexShrase sh;
					sh.line = m_line;
					string word;
					word.insert(word.begin(), m_shrase.begin(), m_shrase.end());
					sh.word = word;
					sh.endstatu = last_statu;
					f_settype(&sh);

					m_ShraseList.push_back(sh);

					m_statu = 0;
					m_shrase.clear();
					continue;
			}

			////错误
			if (m_statu < 0)
			{
				if (last_statu == 0)
				{
					m_shrase.push_back(c);
					rf.read(&c, 1);
				}
				f_saveError(m_statu);
				continue;
			}



			if (c == '\n')
			{
				m_line++;
			}

			if (c != ' '&&c!='\n')
			{
				m_shrase.push_back(c);
				rf.read(&c, 1);
			}
			else
			{
				rf.read(&c, 1);
			}


		}



		if (m_shrase.size() != 0)
		{
			f_saveError(-2);
		}

		for (int i = 0; i <m_ShraseList.size(); i++)
		{
			f_settype(&m_ShraseList.at(i));
		}
		for (int i = 0; i <m_ErroList.size(); i++)
		{
			f_erromessage(&m_ErroList.at(i));
		}

		OutShrase();
		OutError();
		OutCode(&rf);
		SaveFile(output);
	}
	rf.close();
	wf.close();
}

int CMyLex::ST(int st, char in)
{
	switch (st)
	{
	case 0:return ST_00(in);
	case 1:return ST_01(in);
	case 2:return ST_02(in);
	case 3:return ST_03(in);
	case 4:return ST_04(in);
	case 5:return ST_05(in);
	case 6:return ST_06(in);
	case 7:return ST_07(in);
	case 8:return ST_08(in);
	case 9:return ST_09(in);
	case 10:return ST_10(in);
	case 11:return ST_11(in);
	}
	return -1;
}
int CMyLex::ST_00(char in)
{
	if (If_ABC(in)) return 1;//前往状态1   ID
	if (If_NUB(in) && in != '0') return 2;//前往状态2   NUB
	if (in == '0' ) return 3;//前往状态3   NUB
	if (in == '/') return 4;//前往状态4   /
	if (If_Sings(in)) return 8;//单符号结束
	if (If_FrontSings(in)) return 9;//前往状态7   前符号
	if (in == '!') return 11;//前往状态7   前符号
	if (in == ' ' || in == '\n') return 0;
	return -1;
}
int CMyLex::ST_01(char in)
{
	if (If_NUB(in) || If_ABC(in)) return 1;
	return 0;
}
int CMyLex::ST_02(char in)
{
	if (If_NUB(in)) return 2;
	return 0;
}
int CMyLex::ST_03(char in)
{
	return 0;
}
int CMyLex::ST_04(char in)
{
	if (in == '*') return 5;//前往状态5   /*
	return 0;
}
int CMyLex::ST_05(char in)
{
	if (in == '*') return 6;//前往状态6  /**
	return 5;

}
int CMyLex::ST_06(char in)
{
	if (in == '/') return 7;//前往状态7  /**/
	return 5;
}
int CMyLex::ST_07(char in)
{
	return 0;
}
int CMyLex::ST_08(char in)
{
	return 0;
}
int CMyLex::ST_09(char in)
{
	if (in == '=')return 10;
	return 0;
}
int CMyLex::ST_10(char in)
{
	return 0;
}
int CMyLex::ST_11(char in)
{
	if (in == '=')return 10;
	return -2;
}



void CMyLex::init()
{
	m_statu = 0;
	m_line = 1;

	//加载保留字列表
	m_keywords.push_back("if");
	m_keywords.push_back("else");
	m_keywords.push_back("for");
	m_keywords.push_back("while");
	m_keywords.push_back("do");
	m_keywords.push_back("int");
	m_keywords.push_back("write");
	m_keywords.push_back("read");



}


bool CMyLex::If_ABC(char in)
{
	if ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))
	{
		return true;
	}
	return false;
}
bool CMyLex::If_NUB(char in)
{
	if (in >= '0' && in <= '9' )
	{
		return true;
	}
	return false;
}
bool CMyLex::If_Sings(char in)
{
	char m_sgins[] = { '(', ')', '{', '}', ';', '+', '-', '*' };
	for (int i = 0; i < 8; i++)
	{
		if (in == m_sgins[i]) {
			return true;
		}
	}
	return false;
}
bool CMyLex::If_FrontSings(char in)
{
	char m_sgins[] = { '=', '<', '>' };
	for (int i = 0; i < 3; i++)
	{
		if (in == m_sgins[i]) {
			return true;
		}
	}
	return false;
}




void CMyLex::f_settype(LexShrase* Shrase)
{
	string a="";
	string b = "";
	switch (Shrase->endstatu)
	{
	case 1:a = "标志符"; Shrase->LexType ="ID"; break;
	case 2:a = "无符号整数"; Shrase->LexType="NUM"; break;
	case 3:a = "无符号整数"; Shrase->LexType = "NUM"; break;
	case 7:a = "注释"; Shrase->LexType = "NOTES"; break;
	case 8:a = "分界符"; Shrase->LexType = Shrase->word; break;
	case 9:a = "运算符"; Shrase->LexType = Shrase->word; break;
	case 10:a = "运算符"; Shrase->LexType = Shrase->word; break;
	}

	if (Shrase->endstatu == 1)
	{
		int l = m_keywords.size();
		for (int i = 0; i < l; i++)
		{
			if (m_keywords.at(i)==Shrase->word)
			{
				a = "保留字";
				Shrase->LexType = Shrase->word;
				break;
			}
		}
	}
	Shrase->type = a;

}

bool CMyLex::f_ShraseComType(string type, vector<char>v)
{
	bool iftrue = true;
	if (type.size() == v.size())
	{
		int l = v.size();
		for (int i = 0; i < l; i++)
		{
			if (type.at(i) != v.at(i))
			{
				iftrue = false;
				break;
			}
		}
	}
	else
	{
		iftrue = false;
	}
	return iftrue;
}

void CMyLex::f_saveError(int laststatu)
{
	LexErro er;
	er.line = m_line;
	string word;
	word.insert(word.begin(), m_shrase.begin(), m_shrase.end());
	er.word = word;
	er.endstatu = laststatu;
	m_ErroList.push_back(er);
	m_statu = 0;
	m_shrase.clear();
}

void CMyLex::f_erromessage(LexErro* Erro)
{
	string a = "";

	switch (Erro->endstatu)
	{
	case -2:a = "结构不全"; break;
	default:a = "非法字符"; break;
	}

	Erro->message = a;
}


void CMyLex::OutShrase()
{
	cout << "=====================SHRASE=====================" << endl;
	cout << "|类型|    <==> |词法分析| <==>  |符号|" << endl;
	for (int i = 0; i <m_ShraseList.size(); i++)
	{
		cout << m_ShraseList.at(i).type;

		int l = 10 - m_ShraseList.at(i).type.size();
		for (int j = 0; j < l; j++) cout << " ";

		cout << "  <==>  " << m_ShraseList.at(i).LexType;

		 l = 10 - m_ShraseList.at(i).LexType.size();
		for (int j = 0; j < l; j++) cout << " ";



		cout << "  <==>  " << m_ShraseList.at(i).word<<endl;
	}
}

void CMyLex::OutError()
{
	cout << "=====================ERROR======================" << endl;
	cout << "|类型|      <==>  |行数|  <==> |符号|" << endl;
	for (int i = 0; i <m_ErroList.size(); i++)
	{
		cout << m_ErroList.at(i).message;
		int l = 10 - m_ErroList.at(i).message.size();
		for (int j = 0; j < l; j++) cout << " ";


		cout << "  <==>  " << m_ErroList.at(i).line;
		int m = m_ErroList.at(i).line;
		int x;
		for (x = 1; m > 10; x++) m = m / 10;
		l = 8 - x;
		for (int j = 0; j < l; j++) cout << " ";
		cout << "<==>  " << m_ErroList.at(i).word << endl;
	}
}
void CMyLex::OutCode(ifstream* rf)
{
	cout << "=====================原文=======================" << endl;
	rf->clear();
	rf->seekg(0);
	while (!rf->eof())
	{
		char c = ' ';
		rf->read(&c, 1);
		cout << c;
	}

	cout << endl;
	cout << "=====================原文=======================" << endl;
}
void CMyLex::SaveFile(char* output)
{
	OutShrase(output);
	OutError(output);
}
void CMyLex::OutShrase(char* output)
{
	ofstream wf;
	wf.open(output, ios_base::app);
	wf << "=====================SHRASE=====================" << endl;
	wf << "|类型|    <==> |词法分析| <==>  |符号|" << endl;
	for (int i = 0; i <m_ShraseList.size(); i++)
	{
		wf << m_ShraseList.at(i).type;

		int l = 10 - m_ShraseList.at(i).type.size();
		for (int j = 0; j < l; j++) wf << " ";

		wf << "  <==>  " << m_ShraseList.at(i).LexType;

		 l = 10 - m_ShraseList.at(i).LexType.size();
		for (int j = 0; j < l; j++) wf << " ";

		wf << "  <==>  " << m_ShraseList.at(i).word << endl;
	}
	wf.close();
}
void CMyLex::OutError(char* output)
{
	ofstream wf;
	wf.open(output, ios_base::app);
	wf << "=====================ERROR======================" << endl;
	wf << "|类型|      <==>  |行数|  <==> |符号|" << endl;
	for (int i = 0; i <m_ErroList.size(); i++)
	{
		wf << m_ErroList.at(i).message;
		int l = 10 - m_ErroList.at(i).message.size();
		for (int j = 0; j < l; j++) wf << " ";


		wf << "  <==>  " << m_ErroList.at(i).line;

		int m = m_ErroList.at(i).line;
		int x;
		for (x = 1; m > 10; x++) m = m / 10;

		l = 8 - x;
		for (int j = 0; j < l; j++) wf << " ";

		wf << "<==>  " << m_ErroList.at(i).word << endl;
	}
	wf.close();
}

vector<LexShrase> CMyLex::getShraseList()
{
	return m_ShraseList;
}