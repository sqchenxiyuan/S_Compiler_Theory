#include "stdafx.h"
#include "GramAly.h"


CGramAly::CGramAly(vector<LexShrase> Shrases)
{
	reset();
	for (int i = 0; i < Shrases.size(); i++)
	{
		GramShrase sh;
		if (sh.type == "NOTES") continue;
		sh.word = Shrases.at(i).word;
		sh.type = Shrases.at(i).LexType;
		sh.line = Shrases.at(i).line;
		m_Shrase.push_back(sh);
	}
	GramShrase sh;
	sh.word = "END";
	sh.type = "#";
	m_Shrase.push_back(sh);
	m_Shrase.insert(m_Shrase.begin(), sh);

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
	cout << "===================语法分析=====================" << endl;
	ST_to("S");
}


void CGramAly::reset()
{
	m_pos = 0;
}

void CGramAly::end(bool ok){
		cout << "===================分析结果=====================" << endl;
	if (ok){
		cout << "===================NOERROR!=====================" << endl;
	}
	else{
		cout << "================Have Some Wrong=================" << endl;
	}
	cout << "================================================" << endl;
}

void CGramAly::ST_to(string st)
{

	if (st == "S") S_start();
	else if (st == "A") A_programe();
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

void CGramAly::S_start()
{
	if (m_Shrase.at(m_pos).type == "#")
	{
		cmpshrase("#");
		ST_to("A");
		if (m_Shrase.at(m_pos).type == "#") end(true);
		else 
		{
			error(0, "#");
			end(false);
		}
	}
	else{
		error(1, "S");
		end(false);
	}
}

void CGramAly::A_programe()
{
	if (m_Shrase.at(m_pos).type == "{")
	{
		cmpshrase("{");
		ST_to("B");
		ST_to("D");
		cmpshrase("}");
	}
	else error(1,"A");
}
void CGramAly::B_declaration_list()
{
	if (m_Shrase.at(m_pos).type=="int")
	{
		ST_to("B1");
	}
	if (infrfl(m_Shrase.at(m_pos).type, FL_B)) return;
	else error(1,"B");
}
void CGramAly::B1_declaration_list()
{
	if (m_Shrase.at(m_pos).type == "int")
	{
		ST_to("C");
		ST_to("B1");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FL_B1)) return;
	else error(1,"B1");
}
void CGramAly::C_declaration_stat()
{
	if (m_Shrase.at(m_pos).type == "int")
	{
		cmpshrase("int");
		cmpshrase("ID");
		cmpshrase(";");
	}
	else error(1,"C");
}
void CGramAly::D_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_D))
	{
		ST_to("D1");
	}
	else error(1,"D");

}
void CGramAly::D1_statement_list()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_D1))
	{
		ST_to("E");
		ST_to("D1");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FL_D1))
	{
		return;
	}
	else error(1,"D1");
}
void CGramAly::E_statement()
{
	if (m_Shrase.at(m_pos).type=="if")
	{
		ST_to("F");
	}
	else if (m_Shrase.at(m_pos).type == "while")
	{
		ST_to("G");
	}
	else if (m_Shrase.at(m_pos).type == "for")
	{
		ST_to("H");
	}
	else if (m_Shrase.at(m_pos).type == "write")
	{
		ST_to("I");
	}
	else if (m_Shrase.at(m_pos).type == "read")
	{
		ST_to("J");
	}
	else if (m_Shrase.at(m_pos).type == "{")
	{
		ST_to("K");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FR_L))
	{
		ST_to("L");
	}
	else error(1,"E");
}
void CGramAly::F_if_stat()
{
	if (m_Shrase.at(m_pos).type == "if")
	{
		cmpshrase("if");
		cmpshrase("(");
		ST_to("M");
		cmpshrase(")");
		ST_to("E");
		if (m_Shrase.at(m_pos).type == "else") nextchar();
		else return;
		ST_to("E");
	}
	else error(1,"F");
}
void CGramAly::G_while_stat()
{
	if (m_Shrase.at(m_pos).type == "while")
	{
		cmpshrase("while");
		cmpshrase("(");
		ST_to("M");
		cmpshrase(")");
		ST_to("E");
	}
	else error(1,"G");
}
void CGramAly::H_for_stat()
{
	if (m_Shrase.at(m_pos).type == "for")
	{
		cmpshrase("for");
		cmpshrase("(");
		ST_to("M");
		cmpshrase(";");
		ST_to("M");
		cmpshrase(";");
		ST_to("M");
		cmpshrase(")");
		ST_to("E");
	}
	else error(1,"H");
}
void CGramAly::I_write_stat()
{
	if (m_Shrase.at(m_pos).type == "write")
	{
		cmpshrase("write");
		ST_to("M");
		cmpshrase(";");
	}
	else error(1,"I");
}
void CGramAly::J_read_stat()
{
	if (m_Shrase.at(m_pos).type == "read")
	{
		cmpshrase("read");
		cmpshrase("ID");
		cmpshrase(";");
	}
	else error(1,"J");
}
void CGramAly::K_commpound_stat()
{
	if (m_Shrase.at(m_pos).type == "{")
	{
		cmpshrase("{");
		ST_to("D");
		cmpshrase("}");
	}
	else error(1,"K");
}
void CGramAly::L_expression_stat()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_M))
	{
		ST_to("M");
		cmpshrase(";");
	}
	else if (m_Shrase.at(m_pos).type == ";")
	{ 
		cmpshrase(";");
	}
	else error(1,"L");
}
void CGramAly::M_expression()
{
	if (m_Shrase.at(m_pos + 1).type == "="&&m_Shrase.at(m_pos).type=="ID")
	{
		cmpshrase("ID");
		cmpshrase("=");
		ST_to("N");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FR_N))
	{
		ST_to("N");
	}
	else error(1,"m");
}
void CGramAly::N_bool_expr()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_O))
	{
		ST_to("O");
		ST_to("N1");
	}
	else error(1,"N");
}
void CGramAly::N1_bool_expr()
{
	if (m_Shrase.at(m_pos).type == ">")
	{
		cmpshrase(">");
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).type == "<")
	{
		cmpshrase("<");
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).type == ">=")
	{
		cmpshrase(">=");
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).type == "<=")
	{
		cmpshrase("<=");
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).type == "==")
	{
		nextchar();
		ST_to("O");
	}
	else if (m_Shrase.at(m_pos).type == "!=")
	{
		cmpshrase("!=");
		ST_to("O");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FL_N1)) return;
	else error(1,"N1");
}
void CGramAly::O_additive_expr()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_P))
	{
		ST_to("P");
		ST_to("O1");
	}
	else error(1,"O");
}
void CGramAly::O1_additive_expr()
{
	if (m_Shrase.at(m_pos).type == "+")
	{
		cmpshrase("+");
		ST_to("P");
		ST_to("O1");
	}
	else if (m_Shrase.at(m_pos).type == "-")
	{
		cmpshrase("-");
		ST_to("P");
		ST_to("O1");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FL_O1)) return;
	else error(1,"O1");
}
void CGramAly::P_term()
{
	if (infrfl(m_Shrase.at(m_pos).type, FR_P))
	{
		ST_to("Q");
		ST_to("P1");
	}
	else error(1,"P");
}
void CGramAly::P1_term()
{
	if (m_Shrase.at(m_pos).type == "*")
	{
		cmpshrase("*");
		ST_to("Q");
		ST_to("P1");
	}
	else if (m_Shrase.at(m_pos).type == "/")
	{
		cmpshrase("/");
		ST_to("Q");
		ST_to("P1");
	}
	else if (infrfl(m_Shrase.at(m_pos).type, FL_P1))	return;
	else error(1,"P1");
}
void CGramAly::Q_factor()
{
	if (m_Shrase.at(m_pos).type == "(")
	{
		cmpshrase("(");
		ST_to("M");
		cmpshrase(")");
	}
	else if (m_Shrase.at(m_pos).type == "ID")
	{
		cmpshrase("ID");
	}
	else if (m_Shrase.at(m_pos).type == "NUM")
	{
		cmpshrase("NUM");
	}
	else error(1,"Q");
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

void CGramAly::error(int type, string need)
{
	if (type == 1)return;

	cout << "error(" << type << "): [ ";
	if (m_pos > 0)cout << m_Shrase.at(m_pos - 1).type + " , ";
	cout << m_Shrase.at(m_pos).type;
	if (m_pos < m_Shrase.size() - 1) cout << " , " + m_Shrase.at(m_pos + 1).type;
	cout << " ] ==> you input [ " << m_Shrase.at(m_pos).type << " ] ";
	switch (type){
	case 0: cout<<",but we need:[ " << need << " ]"; break;//缺少字符
	case 1:cout << "error statu: [ " << need << " ]"; break;//进入错误状态
	}
	cout << " at(" << m_Shrase.at(m_pos).line << ")."<<endl;
}

void CGramAly::nextchar()
{
	//cout << m_Shrase.at(m_pos).type << "==" << m_pos << endl;
	m_pos++;
	if (m_pos >= m_Shrase.size())
	{
		cout << "max!" << endl;
		m_pos = m_Shrase.size() - 1;
	}
	//Sleep(200);
}


void CGramAly::cmpshrase(string cmp)
{
	if (m_Shrase.at(m_pos).type == cmp) nextchar();
	else error(0, cmp );
}