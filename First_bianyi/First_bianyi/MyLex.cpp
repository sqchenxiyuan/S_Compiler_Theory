#include "stdafx.h"
#include "MyLex.h"

CMyLex::CMyLex()
{
	init();
}


CMyLex::~CMyLex()
{
}

void CMyLex::Analysis(char *input, char* output)
{
	ifstream rf;
	rf.open("src/test.txt");


	if (!rf)  //读取txt文件
	{
		printf("读取文件失败 \n ");
	}
	else
	{
		m_shrase;
		m_shrase.clear();
		cout << "读取成功" << endl;
		while (!rf.eof())
		{
			char c=' ';
			rf.read(&c, 1);

			if (c == '\n')
			{
				//c = ' ';
				m_line ++ ;
			}
			int ms = m_statu;
			m_statu = ST(m_statu, c);
			//cout << c <<"--"<<ms<<"--"<<m_statu<< endl;
			if (m_statu != ms&&m_statu==0||ms==0)//初始状态为0 或者  变为0  输出单词  
			{
				f_outshrase();
				m_shrase.clear();
			}
			if (c != ' '&&c!='\n')
			{
				if (m_statu == 0){
					m_statu = ST(m_statu, c);
					if (m_statu == 0)
					{
						cout << c << "             erro--------------" <<m_line<< endl;
						continue;
					}
				}
				m_shrase.push_back(c);
			}
		}
		if (m_shrase.size() != 0)
		{
			f_outshrase();
			cout  << "             erro--------------" << m_line << endl;
		}
		cout << "============================="<<endl;
		rf.clear();
		rf.seekg(0);
		while (!rf.eof())
		{
			char c = ' ';
			rf.read(&c, 1);
			cout << c;
		}
	}
	cout << m_line;
	rf.close();
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
	}
}
int CMyLex::ST_00(char in)
{
	if (If_ABC(in)) return 1;//前往状态1   ID
	if (If_NUB(in) && in != '0') return 2;//前往状态2   NUB
	if (in == '0' || If_Sings(in)) return 3;//前往状态3   NUB
	if (in == '/') return 4;//前往状态4   /
	if (If_FrontSings(in)) return 7;//前往状态7   前符号
	return 0;
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
	if (in == '*') return 6;//前往状态56  /**
	return 5;

}
int CMyLex::ST_06(char in)
{
	if (in == '/') return 3;//退出状态  /**/
	return 5;
}
int CMyLex::ST_07(char in)
{
	if (in == '=') return 3;//退出状态  /**/
	return 0;
}
int CMyLex::ST_08(char in)
{
	return 0;
}




void CMyLex::init()
{
	m_statu = 0;
	m_line = 1;
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
		//cout << m_sgins[i] << "--------" << in << endl;
		if (in == m_sgins[i]) {
			//cout << "aaaaaaa";
			return true;
		}
	}
	return false;
}
bool CMyLex::If_FrontSings(char in)
{
	char m_sgins[] = { '=', '<', '>', '!' };
	for (int i = 0; i < 4; i++)
	{
		//cout << m_sgins[i] << "--------" << in << endl;
		if (in == m_sgins[i]) {
			//cout << "aaaaaaa";
			return true;
		}
	}
	return false;
}



void CMyLex::f_outshrase()
{
	for (int i = 0; i < m_shrase.size();)
	{
		cout << m_shrase.at(i);
		i++;
		if (i == m_shrase.size())
		{
			cout << endl;
		}
	}
	m_shrase.clear();
}