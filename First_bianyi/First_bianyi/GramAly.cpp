#include "stdafx.h"
#include "GramAly.h"


CGramAly::CGramAly(vector<LexShrase> Shrases)
{
	reset();
	int l = Shrases.size();
	for (int i = 0; i < l; i++)
	{
		m_Shrase.push_back(Shrases.at(i).LexType);
	}
	m_Shrase.push_back("#");


	string FR_1[9] = { "if", "while", "for", "wirte", "read", "{", "(", "ID", "NUM" };
	vector<string> FR_E(FR_1,FR_1+9);
	this->FR_E = FR_E;

	string FR_2[3] = { "(", "ID", "NUM" };
	vector<string> FR_L(FR_2, FR_2 + 3);
	this->FR_L = FR_L;

	string FR_3[3] = { "(", "ID", "NUM" };
	vector<string> FR_M(FR_3, FR_3 + 3);
	this->FR_M = FR_M;

	string FR_4[11] = { "if", "while", "for", "write", "read", "{", "(", "ID", "NUM", "}", "#" };
	vector<string> FL_B1(FR_4, FR_4 + 11);
	this->FL_B1 = FL_B1;

	string FR_5[2] = { "}", "#" };
	vector<string> FL_D1(FR_5, FR_5 + 2);
	this->FL_D1 = FL_D1;

	string FR_6[2] = { ";", ")" };
	vector<string> FR_N1(FR_6, FR_6 + 2);
	this->FL_N1 = FL_N1;

	string FR_7[8] = { ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FR_O1(FR_7, FR_7 + 8);
	this->FL_O1 = FL_O1;

	string FR_8[10] = { "+", "-", ")", ";", ">", "<", ">=", "<=", "==", "!=" };
	vector<string> FR_P1(FR_8, FR_8 + 10);
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
	cout << m_Shrase.at(m_pos) << endl;
	m_pos++;
	if (m_pos > m_Shrase.size())
	{
		cout << "max!" << endl;
		m_pos = m_Shrase.size() - 1;
	}
	Sleep(200);
}
void CGramAly::A_programe()
{
	if (m_Shrase.at(m_pos) == "{") nextchar();
	else error();
	B_declaration_list();
	D_statement_list();
	if (m_Shrase.at(m_pos) == "}") nextchar();
	else error();
}
void CGramAly::B_declaration_list()
{
	B1_declaration_list();
}
void CGramAly::B1_declaration_list()
{
	if (m_Shrase.at(m_pos) == "int")
	{
		C_declaration_stat();
		B1_declaration_list();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_B1)) return;
	else error();
}
void CGramAly::C_declaration_stat()
{
	if (m_Shrase.at(m_pos) == "int") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == "ID") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
}
void CGramAly::D_statement_list()
{
	D1_statement_list();
}
void CGramAly::D1_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos), FR_E))
	{
		E_statement();
		D1_statement_list();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_D1)) return;
	else error();
}
void CGramAly::E_statement()
{
	if (m_Shrase.at(m_pos)=="if")
	{
		F_if_stat();
	}
	else if (m_Shrase.at(m_pos) == "while")
	{
		G_while_stat();
	}
	else if (m_Shrase.at(m_pos) == "for")
	{
		H_for_stat();
	}
	else if (m_Shrase.at(m_pos) == "write")
	{
		I_write_stat();
	}
	else if (m_Shrase.at(m_pos) == "read")
	{
		J_read_stat();
	}
	else if (m_Shrase.at(m_pos) == "{")
	{
		K_commpound_stat();
	}
	else if (infrfl(m_Shrase.at(m_pos), FR_L))
	{
		L_expression_stat();
	}
	else error();
}
void CGramAly::F_if_stat()
{
	if (m_Shrase.at(m_pos) == "if") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == "(") nextchar();
	else error();
	M_expression();
	if (m_Shrase.at(m_pos) == ")") nextchar();
	else error();
	E_statement();
	if (m_Shrase.at(m_pos) == "else") nextchar();
	else return;
	E_statement();
}
void CGramAly::G_while_stat()
{
	if (m_Shrase.at(m_pos) == "while") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == "(") nextchar();
	else error();
	M_expression();
	if (m_Shrase.at(m_pos) == ")") nextchar();
	else error();
	E_statement();
}
void CGramAly::H_for_stat()
{
	if (m_Shrase.at(m_pos) == "for") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == "(") nextchar();
	else error();
	M_expression();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
	M_expression();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
	M_expression();
	if (m_Shrase.at(m_pos) == ")") nextchar();
	else error();
	E_statement();
}
void CGramAly::I_write_stat()
{
	if (m_Shrase.at(m_pos) == "write") nextchar();
	else error();
	E_statement();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
}
void CGramAly::J_read_stat()
{
	if (m_Shrase.at(m_pos) == "read") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == "ID") nextchar();
	else error();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
}
void CGramAly::K_commpound_stat()
{
	if (m_Shrase.at(m_pos) == "write") nextchar();
	else error();
	D_statement_list();
	if (m_Shrase.at(m_pos) == ";") nextchar();
	else error();
}
void CGramAly::L_expression_stat()
{
	if (infrfl(m_Shrase.at(m_pos), FR_M))
	{
		M_expression();
		if (m_Shrase.at(m_pos) == ";") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos) == ";")
	{
		if (m_Shrase.at(m_pos) == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::M_expression()
{
	if (m_Shrase.at(m_pos + 1) == "=")
	{
		if (m_Shrase.at(m_pos) == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos) == "=") nextchar();
		else error();
		N_bool_expr(); 
	}
	else
	{
		N_bool_expr();
	}
}
void CGramAly::N_bool_expr()
{
	O_additive_expr();
	N1_bool_expr();
}
void CGramAly::N1_bool_expr()
{
	if (m_Shrase.at(m_pos) == ">")
	{
		if (m_Shrase.at(m_pos) == ">") nextchar();
		else error();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "<")
	{
		if (m_Shrase.at(m_pos) == "<") nextchar();
		else error();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == ">=")
	{
		if (m_Shrase.at(m_pos) == ">=") nextchar();
		else error();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "<=")
	{
		if (m_Shrase.at(m_pos) == "<=") nextchar();
		else error();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "==")
	{
		if (m_Shrase.at(m_pos) == "==") nextchar();
		else error();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "!=")
	{
		if (m_Shrase.at(m_pos) == "!=") nextchar();
		else error();
		O_additive_expr();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_N1)) return;
	else error();
}
void CGramAly::O_additive_expr()
{
	P_term();
	O1_additive_expr();
}
void CGramAly::O1_additive_expr()
{
	if (m_Shrase.at(m_pos) == "+")
	{
		if (m_Shrase.at(m_pos) == "+") nextchar();
		else error();
		P_term();
		O1_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "-")
	{
		if (m_Shrase.at(m_pos) == "-") nextchar();
		else error();
		P_term();
		O1_additive_expr();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_O1)) return;
	else error();
}
void CGramAly::P_term()
{
	Q_factor();
	P1_term();
}
void CGramAly::P1_term()
{
	if (m_Shrase.at(m_pos) == "*")
	{
		if (m_Shrase.at(m_pos) == "*") nextchar();
		else error();
		Q_factor();
		P1_term();
	}
	else if (m_Shrase.at(m_pos) == "/")
	{
		if (m_Shrase.at(m_pos) == "/") nextchar();
		else error();
		Q_factor();
		P1_term();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_P1)) return;
	else error();
}
void CGramAly::Q_factor()
{
	if (m_Shrase.at(m_pos) == "(")
	{
		if (m_Shrase.at(m_pos) == "(") nextchar();
		else error();
		M_expression();
		if (m_Shrase.at(m_pos) == ")") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos) == "ID")
	{
		if (m_Shrase.at(m_pos) == "ID") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos) == "NUM")
	{
		if (m_Shrase.at(m_pos) == "NUM") nextchar();
		else error();
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
	cout << "er!!  in     "<< m_pos<< endl;
}