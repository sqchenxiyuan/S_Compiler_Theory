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
	cout << m_Shrase.at(m_pos) << "==" << m_pos << endl;
	m_pos++;
	if (m_pos >= m_Shrase.size())
	{
		cout << "max!" << endl;
		m_pos = m_Shrase.size() - 1;
	}
	//Sleep(200);
}
void CGramAly::A_programe()
{
	if (m_Shrase.at(m_pos) == "{")
	{
		nextchar();
		B_declaration_list();
		D_statement_list();
		if (m_Shrase.at(m_pos) == "}") nextchar();
		else error();
	}
	else error();
}
void CGramAly::B_declaration_list()
{
	if (m_Shrase.at(m_pos)=="int")
	{
		B1_declaration_list();
	}
	if (infrfl(m_Shrase.at(m_pos), FL_B)) return;
	else error();
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
	if (m_Shrase.at(m_pos) == "int")
	{
		nextchar();
		if (m_Shrase.at(m_pos) == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos) == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::D_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos), FR_D))
	{
		D1_statement_list();
	}
	else error();

}
void CGramAly::D1_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos), FR_D1))
	{
		E_statement();
		D1_statement_list();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_D1))
	{
		return;
	}
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
	if (m_Shrase.at(m_pos) == "if")
	{
		nextchar();
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
	else error();
}
void CGramAly::G_while_stat()
{
	if (m_Shrase.at(m_pos) == "while")
	{
		nextchar();
		if (m_Shrase.at(m_pos) == "(") nextchar();
		else error();
		M_expression();
		if (m_Shrase.at(m_pos) == ")") nextchar();
		else error();
		E_statement();
	}
	else error();
}
void CGramAly::H_for_stat()
{
	if (m_Shrase.at(m_pos) == "for")
	{
		nextchar();
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
	else error();
}
void CGramAly::I_write_stat()
{
	if (m_Shrase.at(m_pos) == "write")
	{
		nextchar();
		M_expression();
		if (m_Shrase.at(m_pos) == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::J_read_stat()
{
	if (m_Shrase.at(m_pos) == "read")
	{
		nextchar();
		if (m_Shrase.at(m_pos) == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos) == ";") nextchar();
		else error();
	}
	else error();
}
void CGramAly::K_commpound_stat()
{
	if (m_Shrase.at(m_pos) == "{")
	{
		nextchar();
		D_statement_list();
		if (m_Shrase.at(m_pos) == "}") nextchar();
		else error();
	}
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
		nextchar();
	}
	else error();
}
void CGramAly::M_expression()
{
	if (m_Shrase.at(m_pos + 1) == "="&&m_Shrase.at(m_pos)=="ID")
	{
		if (m_Shrase.at(m_pos) == "ID") nextchar();
		else error();
		if (m_Shrase.at(m_pos) == "=") nextchar();
		else error();
		N_bool_expr(); 
	}
	else if (infrfl(m_Shrase.at(m_pos), FR_N))
	{
		N_bool_expr();
	}
	else error();
}
void CGramAly::N_bool_expr()
{
	if (infrfl(m_Shrase.at(m_pos), FR_O))
	{
		O_additive_expr();
		N1_bool_expr();
	}
	else error();
}
void CGramAly::N1_bool_expr()
{
	if (m_Shrase.at(m_pos) == ">")
	{
		nextchar();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "<")
	{
		nextchar();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == ">=")
	{
		nextchar();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "<=")
	{
		nextchar();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "==")
	{
		nextchar();
		O_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "!=")
	{
		nextchar();
		O_additive_expr();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_N1)) return;
	else error();
}
void CGramAly::O_additive_expr()
{
	if (infrfl(m_Shrase.at(m_pos), FR_P))
	{
		P_term();
		O1_additive_expr();
	}
	else error();
}
void CGramAly::O1_additive_expr()
{
	if (m_Shrase.at(m_pos) == "+")
	{
		nextchar();
		P_term();
		O1_additive_expr();
	}
	else if (m_Shrase.at(m_pos) == "-")
	{
		nextchar();
		P_term();
		O1_additive_expr();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_O1)) return;
	else error();
}
void CGramAly::P_term()
{
	if (infrfl(m_Shrase.at(m_pos), FR_P))
	{
		Q_factor();
		P1_term();
	}
	else error();
}
void CGramAly::P1_term()
{
	if (m_Shrase.at(m_pos) == "*")
	{
		nextchar();
		Q_factor();
		P1_term();
	}
	else if (m_Shrase.at(m_pos) == "/")
	{
		nextchar();
		Q_factor();
		P1_term();
	}
	else if (infrfl(m_Shrase.at(m_pos), FL_P1))	return;
	else error();
}
void CGramAly::Q_factor()
{
	if (m_Shrase.at(m_pos) == "(")
	{
		nextchar();
		M_expression();
		if (m_Shrase.at(m_pos) == ")") nextchar();
		else error();
	}
	else if (m_Shrase.at(m_pos) == "ID")
	{
		nextchar();
	}
	else if (m_Shrase.at(m_pos) == "NUM")
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
	cout << "er!!  in     " << m_Shrase.at(m_pos) << endl;
}