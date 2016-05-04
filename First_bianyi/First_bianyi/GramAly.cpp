#include "stdafx.h"
#include "GramAly.h"


CGramAly::CGramAly(vector<LexShrase> Shrases)
{
	reset();
	m_Shrase = Shrases;


	string F_1[10] = { "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", ";" };
	vector<string> FR_E(F_1,F_1+10);
	this->FR_E = FR_E;
	this->FR_D = FR_E;
	this->FR_D1 = FR_E;


	string F_2[4] = { "(", "ID", "NUM", ";" };
	vector<string> FR_L(F_2, F_2 + 4);
	this->FR_L = FR_L;



	string F_3[3] = { "(", "ID", "NUM" };
	vector<string> FR_M(F_3, F_3 + 3);
	this->FR_M = FR_M;
	this->FR_N = FR_M;
	this->FR_O = FR_M;
	this->FR_P = FR_M;
	this->FR_Q = FR_M;


	string F_4[11] = { "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", "}" };
	vector<string> FL_B(F_4, F_4 + 11);
	this->FL_B = FL_B;
	this->FL_B1 = FL_B;


	string F_5[1] = { "}" };
	vector<string> FL_D1(F_5, F_5 + 1);
	this->FL_D1 = FL_D1;


	string F_6[2] = { ";", ")" };
	vector<string> FL_N1(F_6, F_6 + 2);
	this->FL_N1 = FL_N1;



	string F_7[8] = { ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FL_O1(F_7, F_7 + 8);
	this->FL_O1 = FL_O1;


	string F_8[10] = { "+", "-", ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FL_P1(F_8, F_8 + 10);
	this->FL_P1 = FL_P1;
}


CGramAly::~CGramAly()
{
}


void CGramAly::Analysis()
{
	A_programe();
}


void CGramAly::reset()
{
	m_pos = 0;
}

void CGramAly::nextchar()
{
	cout << m_Shrase.at(m_pos).LexType << "==" << m_pos << endl;
	m_pos++;
	if (m_pos >= m_Shrase.size())
	{
		cout << "max!" << endl;
		m_pos = m_Shrase.size() - 1;
	}
	//Sleep(200);
}


void CGramAly::ST_to(string st)
{
	if (st == "A") A_programe();
	else if (st == "B") B_declaration_list();
	else if (st == "B1")B1_declaration_list();
	else if (st == "C") C_declaration_stat();
	else if (st == "D") D_statement_list();
	else if (st == "D1") D1_statement_list();
	else if (st == "E") E_statement();
	else if (st == "F") F_if_stat();
	else if (st == "G") G_while_stat();
	else if (st == "H") H_for_stat();
	else if (st == "I") I_write_stat();
	else if (st == "J") J_read_stat();
	else if (st == "K") K_commpound_stat();
	else if (st == "L") L_expression_stat();
	else if (st == "M") M_expression();
	else if (st == "N") N_bool_expr();
	else if (st == "N1") N1_bool_expr();
	else if (st == "O") O_additive_expr();
	else if (st == "O1") O1_additive_expr();
	else if (st == "P") P_term();
	else if (st == "P1") P1_term();
	else if (st == "Q") Q_factor();
}



void CGramAly::A_programe()
{
	if (m_Shrase.at(m_pos).LexType == "{")
	{
		nextchar();
		ST_to("B");
		ST_to("D");
		if (m_Shrase.at(m_pos).LexType == "}") nextchar();
		else error();
	}
	else error();
}
void CGramAly::B_declaration_list()
{
	if (m_Shrase.at(m_pos).LexType=="int")
	{
		ST_to("B1");
	}
	if (infrfl(m_Shrase.at(m_pos).LexType, FL_B)) return;
	else error();
}
void CGramAly::B1_declaration_list()
{
	if (m_Shrase.at(m_pos).LexType == "int")
	{
		ST_to("C");
		ST_to("B1");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FL_B1)) return;
	else error();
}
void CGramAly::C_declaration_stat()
{
	if (m_Shrase.at(m_pos).LexType == "int")
	{
		nextchar();
		if (m_Shrase.at(m_pos).LexType == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::D_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_D))
	{
		ST_to("D1");
	}
	else error();

}
void CGramAly::D1_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_D1))
	{
		ST_to("E");
		ST_to("D1");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FL_D1))
	{
		return;
	}
	else error();
}
void CGramAly::E_statement()
{
	if (m_Shrase.at(m_pos).LexType=="if")
	{
		ST_to("F");
	}
	else if (m_Shrase.at(m_pos).LexType == "while")
	{
		ST_to("G");
	}
	else if (m_Shrase.at(m_pos).LexType == "for")
	{
		ST_to("H");
	}
	else if (m_Shrase.at(m_pos).LexType == "write")
	{
		ST_to("I");
	}
	else if (m_Shrase.at(m_pos).LexType == "read")
	{
		ST_to("J");
	}
	else if (m_Shrase.at(m_pos).LexType == "{")
	{
		ST_to("K");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FR_L))
	{
		ST_to("L");
	}
	else error();
}
void CGramAly::F_if_stat()
{
	if (m_Shrase.at(m_pos).LexType == "if")
	{
		nextchar();
		if (m_Shrase.at(m_pos).LexType == "(") nextchar();
		else error();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ")") nextchar();
		else error();
		ST_to("E");
		if (m_Shrase.at(m_pos).LexType == "else") nextchar();
		else return;
		ST_to("E");
	}
	else error();
}
void CGramAly::G_while_stat()
{
	if (m_Shrase.at(m_pos).LexType == "while")
	{
		nextchar();
		if (m_Shrase.at(m_pos).LexType == "(") nextchar();
		else error();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ")") nextchar();
		else error();
		ST_to("E");
	}
	else error();
}
void CGramAly::H_for_stat()
{
	if (m_Shrase.at(m_pos).LexType == "for")
	{
		nextchar();
		if (m_Shrase.at(m_pos).LexType == "(") nextchar();
		else error();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ")") nextchar();
		else error();
		ST_to("E");
	}
	else error();
}
void CGramAly::I_write_stat()
{
	if (m_Shrase.at(m_pos).LexType == "write")
	{
		nextchar();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::J_read_stat()
{
	if (m_Shrase.at(m_pos).LexType == "read")
	{
		nextchar();
		if (m_Shrase.at(m_pos).LexType == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::K_commpound_stat()
{
	if (m_Shrase.at(m_pos).LexType == "{")
	{
		nextchar();
		ST_to("D");
		if (m_Shrase.at(m_pos).LexType == "}") nextchar();
		else error();
	}
	else error();
}
void CGramAly::L_expression_stat()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_M))
	{
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ";") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos).LexType == ";")
	{ 
		nextchar();
	}
	else error();
}
void CGramAly::M_expression()
{
	if (m_Shrase.at(m_pos + 1).LexType == "="&&m_Shrase.at(m_pos).LexType=="ID")
	{
		if (m_Shrase.at(m_pos).LexType == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos).LexType == "=") nextchar();
		else error();
		ST_to("N");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FR_N))
	{
		ST_to("N");
	}
	else error();
}
void CGramAly::N_bool_expr()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_O))
	{
		ST_to("O");
		ST_to("N1");
	}
	else error();
}
void CGramAly::N1_bool_expr()
{
	if (m_Shrase.at(m_pos).LexType == ">")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).LexType == "<")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).LexType == ">=")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).LexType == "<=")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).LexType == "==")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).LexType == "!=")
	{
		nextchar();
		ST_to("O");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FL_N1)) return;
	else error();
}
void CGramAly::O_additive_expr()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_P))
	{
		ST_to("P");
		ST_to("O1");
	}
	else error();
}
void CGramAly::O1_additive_expr()
{
	if (m_Shrase.at(m_pos).LexType == "+")
	{
		nextchar();
		ST_to("P");
		ST_to("O1");
	}
	else if (m_Shrase.at(m_pos).LexType == "-")
	{
		nextchar();
		ST_to("P");
		ST_to("O1");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FL_O1)) return;
	else error();
}
void CGramAly::P_term()
{
	if (infrfl(m_Shrase.at(m_pos).LexType, FR_P))
	{
		ST_to("Q");
		ST_to("P1");
	}
	else error();
}
void CGramAly::P1_term()
{
	if (m_Shrase.at(m_pos).LexType == "*")
	{
		nextchar();
		ST_to("Q");
		ST_to("P1");
	}
	else if (m_Shrase.at(m_pos).LexType == "/")
	{
		nextchar();
		ST_to("Q");
		ST_to("P1");
	}
	else if (infrfl(m_Shrase.at(m_pos).LexType, FL_P1))	return;
	else error();
}
void CGramAly::Q_factor()
{
	if (m_Shrase.at(m_pos).LexType == "(")
	{
		nextchar();
		ST_to("M");
		if (m_Shrase.at(m_pos).LexType == ")") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos).LexType == "ID")
	{
		nextchar();
	}
	else if (m_Shrase.at(m_pos).LexType == "NUM")
	{
		nextchar();
	}
	else error();
}


bool CGramAly::infrfl(string shr, vector<string> frfl)
{
	int l = frfl.size();
	for (int i = 0; i < l; i++)
	{
		if (frfl.at(i) == shr) return true;
	}
	return false;
}

void CGramAly::error()
{
	cout << "er!!  in     " << m_Shrase.at(m_pos).LexType << endl;
}