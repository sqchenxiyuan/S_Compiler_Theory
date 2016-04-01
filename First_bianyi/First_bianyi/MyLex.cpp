#include "stdafx.h"
#include "MyLex.h"

CMyLex::CMyLex()
{
	
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
		vector<char> duanyu;
		duanyu.clear();
		cout << "读取成功" << endl;
		while (!rf.eof())
		{
			char c=' ';
			rf.read(&c, 1);

			if (c == '\n')
			{
				//c = ' ';
				continue;
				m_line ++ ;
			}
			if (c == ' ')
			{
				c = '_';
			}
			int ms = m_statu;
			m_statu = ST(m_statu, c);
			//cout << c <<"--"<<ms<<"--"<<m_statu<< endl;
			if (m_statu != ms)
			{
				for (int i = 0; i < duanyu.size(); i++)
				{
					cout << duanyu.at(i);
				}
				duanyu.clear();
				cout << endl;
			}
			duanyu.push_back(c);
		}
		cout << "=============================";
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
	case 8:return ST_erro(in);
	}
}
int CMyLex::ST_00(char in)
{
	if (If_ABC(in)) return 1;//前往状态1   ID
	if (If_NUB(in) && in != '0') return 2;//前往状态2   NUB
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
	return 0;
}
int CMyLex::ST_05(char in)
{
	return 0;

}
int CMyLex::ST_06(char in)
{
	return 0;
}
int CMyLex::ST_07(char in)
{
	return 0;
}
int CMyLex::ST_erro(char in)
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
