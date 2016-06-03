//语法、语义分析及代码生成程序 
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#define maxvartablep 500 	//定乂符号表的容量
int TESTparse(); 
int program();
int statement();	
int expression_stat();
int expression();
int bool_expr();	
int additive_expr();
int term();	
int factor();	
int if_stat();	
int while_stat();
int for_stat();	
int write_stat();
int read_stat();	
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
int name_def(char *name);
char token[20], token1[40];          //token保存单词符号,token1保存单词值  
extern char Scanout[300],Codeout[300];//保存词法分析输出文件名
FILE *fp, *fout;                     //用于指向输入输出文件的指针 
 
struct{                               //定义符号表结构
	char name[8]; 
	int address;
	int initialize;
}vartable[maxvartablep];              //改符号表最多容纳maxvarltablep个记录           

int vartablep=0, labelp= 0, datap= 0;

//插入符号表动作@ name一 def n,t的程序如下： 
int name_def(char * name)
{
   int i,es=0;
   if(vartablep>=maxvartablep) return(21); 
   for(i=vartablep-1;i>=0;i--)              //查符号表
   {
	   if(strcmp(vartable[i].name,name)==0) 
	   {
		 es=22;                                    //22表示变量重复声明
		 break;
      }
    }
   if(es>0) return(es);
   strcpy(vartable[vartablep].name,name); 
   vartable[vartablep].address=datap;
   vartable[vartablep].initialize = 0;
   datap++;                                     //分配一个单元,数据区指针加1
   vartablep++; 
   return(es);
}

//查询符号表返回地址
int lookup(char * name, int * paddress) 
{
   int i,es=0;
   for(i=0;i<vartablep;i++)
   {
     if(strcmp(vartable[i].name,name)==0)
      {
        *paddress=vartable[i].address;
		if (vartable[i].initialize == 1) es = 0;
		else es = 24;//var dont initilize 
		vartable[i].initialize = 1;
        return(es);
       }
     }
   es=23;                                       //变量没有声明
   return(es);
}

//语法、语义分析及代码生成程序 
int TESTparse()
{
   int es=0;
   if((fp=fopen(Scanout,"r"))== NULL)
   { 
      printf("\n打开%s错误！\n",Scanout);
      es=10;
      return(es);
    }

   printf("请输入目标文件名(包括路径):");
   scanf("%s",Codeout); 
   if((fout=fopen(Codeout,"w"))==NULL)
   {     
     printf("\n 创建%s 错误！ \n",Codeout);
     es=10;
     return(es);
    }
   if(es==0) es=program();
   printf("==语法、语义分析及代码生成程序结果==\n"); 
   switch(es)
  {
    case 0: printf("语法、语义分析成功并抽象机汇编生成代码!\n");break;
    case 10:printf("打开文件 %s 失败\n",Scanout);break;
    case 1: printf("缺少 {! \n") ;break;
    case 2: printf("缺少 }! \n") ;break;
    case 3: printf("缺少标识符!");break;
    case 4: printf("少分号! \n") ;break;
    case 5: printf("缺少(！\n");break;
    case 6: printf("缺少 )！\n") ;break;
    case 7: printf("缺少操作数!\n");break;
    case 21:printf("符号表溢出！\n");break;
    case 22:printf("变量重复定义！\n");break;
    case 23:printf("变量未声明!\n");break;
	case 24:printf("变量未初始化!\n"); break;

   }

   fclose(fp);
   fclose(fout);
   return(es);
}

//program::= {<declaration_list><statement list> }.
int program()
{
  int es=0,i;
  fscanf(fp,"%s %s\n",token,token1);
  printf("%s %s\n",token,token1);
  if(strcmp(token,"{"))	                             //判断是否"{"
   {   
     es=1;
     return(es);
    }
   fscanf(fp,"%s %s\n",&token,&token1);
   printf("%s %s\n",token,token1); 
   es=declaration_list(); 
   if(es>0) return(es); 
 /*  printf("\t符号表\n");
   printf("\t名字\t地址\n");
   for(i=0;i<vartablep;i++)
	   printf("\t%s\t%d\n",vartable[i].name,vartable[i].address);*/
   es= statement_list();
   if(es>0) return(es);
   if(strcmp(token,"}")) //判断是否"}"
   {
       es=2;
      return(es);
    }
   fprintf(fout,"STOP\n");	            //产生停止指令
   return(es);
}

//<declaration_list> :: = < declaration_list>< decIaratibn_stat>y| < declaration_stat> //3CJ^<declaration_list> ::* {<declaration_stat> } 
int declaration_list()
 {
    int es=0;
    while(strcmp(token,"int")== 0)
    {
       es= declaration_stat();
       if(es>0) return(es);
     }
    return(es);
}

//<declaration_stat> \ vartabiep,datap,codep~^int IDf n @ name- def + n,t :
 int declaration_stat()
{
	 int es=0;
	 fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n",token,token1);
	 if(strcmp(token,"ID")) return(es=3);	     //不是标识符
	 es=name_def(token1);	                     //插入符号表
	 if(es>0) return(es);
	 fscanf(fp,"%s %s\n",&token,&token1);printf("%s %s\n", token,token1);
	 if(strcmp(token,";") ) return(es=4);
	 fscanf(fp,"%s %s\n", &token, &token1) ;printf("%s %s\n",token,token1);
	 return(es);
}

//< statement_list> :: = <statement_list><statement> | <statement>
//改成<statement_list> ::= {<statement> } 
int statement_list()
{
  int es=0;
  while(strcmp(token,"}"))
  {
        es=statement();
        if(es>0) return(es);
   }
  return(es);
}

//<statement> ::*<if_stat> |<while_stat> |<for_stat>
//  	        |<compound_stat> |<expression_stat> ^
int statement()
{
  int es=0;
  if(es==0 && strcmp(token,"if")== 0)       es=if_stat();//<if语句>
  else if(es==0 && strcmp(token,"while")==0) es=while_stat();//<while 语句> 
  else if (es == 0 && strcmp(token, "for") == 0)   es = for_stat();//<for语句>
  //可在此处添加过do语句调用
  else if (es == 0 && strcmp(token, "read") == 0)  es = read_stat();//<read 语句>
  else if (es == 0 && strcmp(token, "write") == 0) es = write_stat();//<write @^> 
  else if (es == 0 && strcmp(token, "{") == 0)es = compound_stat();//<复合语句> 
  else if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0))
	es=expression_stat();	        //<表达式语句>
  return(es);
}

//< if stat> :: = if(< expr> ) < statement>[else< statement> ]
/*
if(<expression> ) @ BRFfiaben < statement> @ BR+ iabei2 @ SETlabeljiaseii[else<statement>] @ SETlabel|iabei2
其中动作符号的含义如下
0BRFtiabeu,:输出 BRF label1.
 
BRf iabei2 ：输出 BR label2 0SETlabel|iabeii ：设置标号 label1 0SETlabel|iabei2 ：设置标号 label2
*/
int if_stat() 
{
  int es=0,label1,label2;                      //if
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token, token1);
  if(strcmp(token,"(")) return(es=5);        //少左括号
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es=expression();
  if(es> 0) return(es);
  if(strcmp(token,")")) return(es=6);      //少右括号 
  label1= labelp++;                            //用label1记住条件为假时要转向的标号
  fprintf(fout,"BRF LABEL%d\n",label1);//输出假转移指令
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n", token, token1);
  es=statement();
  if(es>0) return(es);
  label2= labelp++;                            //用label2记住要转向的挥号                  
  fprintf(fout,"BR LABEL%d\n",label2);      //输出无条件转移指令
  fprintf(fout,"LABEL%d: \n", label1);       //设置label1记住的标号  
  if(strcmp(token,"else")==0)               //else部分处理
   {
       fscanf(fp,"%s %s\n",&token, &token1);
       printf("%s %s\n",token,token1);
       es= statement(); 
       if(es>0) return(es);
   }

   
  fprintf(fout,"LABEL%d:\n",label2);                    //设置1沾612记住的标号
  return(es);

}

//<while_stat> :: = while(<expr> ) < statement>
//<while_stat> :: = while @ SETlabeltxaben(<expression>) @ BRFf 13&6]:2 //	<statement>0BRoabeu0SETlabel4iabei2
//动作解释如下： //0SETlabeltiabeii ：设置标号 label1 //0BRFt !abe!2 | 输出 BRF label2 //0BR* !aben :输出 BR label1 .
//@ SET1 abe 11 iabei2 ：设置标号 label2 
int while_stat()
{ 
  int es=0,label1,label2; label1=labelp++;
  fprintf(fout,"LABEL%d:\n",label1) ;	//设置1日匕611标号
  fscanf(fp,"%s %s\n",&token, &token1); printf("%s %s\n",token,token1);
  if(strcmp(token,"(")) return(es=5);	//少左括号
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es=expression();
  if(es>0) return(es) ;
  if(strcmp(token,")")) return(es= 6);	//少右括号
  label2= labelp++;
  fprintf(fout,"BRF LABEL%d\n",label2); //输出假转移指令
  fscanf(fp,"%s %s\n",&token,&token1);
  printf("%s %s\n",token,token1);
  es= statement();
  if(es>0) return(es);
  fprintf(fout,"BR LABEL%d\n",label1);	//输出无条件转移指令
  fprintf(fout,"LABEL%d:\n",label2);	    //设置1丑匕612标号.
  return(es);

} 

//< for_stat> ::~ior(<expr> ,<expr> ,<expr>) < statement>
/*
< for_stat> :: = for(<expression> @ POP;
@ SETlabel \ iabeii < expression> @ BRF|iabei2 @ BR+ iabei3 :
@ SETlabel 1 iabei4< expression> @ POP0 BR* iabeii)
@ SETlabel : ^13 <iS^I > 0 BR \ label46SETlabel|iabei2
动作解释： 1.	0SETlabeluabeii ：设置标号 label1
0BRFf iabei2 ：输出 BRF label2 3 . @ BR| iabei3 ：输出 BR label3
0SETlabeluabei4 ：设置标号 label4
0BRfiabeu :输出 BR label1
@36713&61丨131^13:设置标号13^13
@ BRf !abei4 ：输出 BR lsfcel4
0 SETlabel : iabei2 ：设置标号 lab.el2
*/
int for_stat()
{
	int es=0,label1,label2,label3,label4; 
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	if(strcmp(token,"(")) return(es=5);	//少左括号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token, token1);
	es=expression();
	if(es>0) return(es);
	fprintf(fout,"POP\n");                 //输出出栈指令
	if(strcmp(token,";")) return(es*=4);//少分号
	label1=labelp++ ;                      
	fprintf(fout,"LABEL%d:\n",label1);       //设置 label1标号
	fscanf(fp,"%s %s\n",&token,&token1);    
	printf("%s %s\n",token,token1);
	es=expression();
	if(es>0) return(es); 
	label2=labelp++;
	fprintf(fout,"BRF LABEL%d\n",label2); //输出假条件转移指令  
	label3=labelp++;
	fprintf(fout,"BR LABEL%d\n",label3);   //输出无条件转移指令
	if(strcmp(token,";"))  return(es=4);         //少分号
	label4=labelp++;
	fprintf(fout,"LABEL%d:\n", label4);         //设置label4标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=expression();
	if(es>0) return(es) ;
	fprintf(fout,"POP\n");                //输出出找指令        
	fprintf(fout,"BR LABEL%d\n", label1);     //输出无条件转移指令
	if(strcmp(token,")")) return(es= 6);        //少右括号
	fprintf(fout,"LABEL%d:\n",label3);          //设置label3标号
	fscanf(fp,"%s %s\n",&token,&token1);
	printf("%s %s\n",token,token1);
	es=statement();
	if(es>0) return(es);
	fprintf(fout,"BR LABEL%d\n",label4);     //输出无条件转移指令
	fprintf(fout,"LABEL%d:\n", label2);       //设置label2标号
	return(es);
	
}

//<write_stat> ::-write<expressipn> ;- //<write_stat> :: = write<expression>0OUT;
//动作解释：
//0OUT:输出 OUT
int write_stat() 
{
	int es=0;
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	es=expression(); 
	if(es>0) return(es);
	if(strcmp(token,";")) return(es=4);	//少分号
    fprintf(fout,"OUT\n") ;	            //输出0ut指令
	fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1) ; 
	return(es);
}

//< read_stat> ::==read ID;
//<read_stat> :: = read IDfnLOOK|nfd6lN0 STO|d0POP; //动作解释：
//@100化11^:查符号表?给出变量地址d;若没有,则变量未定义 //0IN:输出 IN
//@3|11"：输出指令代码31工d
int read_stat()
{
	int es= 0,address;
	fscanf(fp,"%s %s\n",&token, &token1); 
	printf("%s %s\n",token,token1); 
	if(strcmp(token,"ID")) return(es=3);    //少标识符
	es = lookup(token1, &address);
	if (es == 24) es = 0;
	if(es > 0) return(es);		
	fprintf(fout,"IN \n");               //输入指令
	fprintf(fout,"STO %d\n",address);    //输出STO指令
	fprintf(fout,"POP\n");
    fscanf(fp,"%s %s\n",&token,&token1); 
	printf("%s %s\n",token,token1);
	if(strcmp(token,";")) return(es=4);    //少分号
	fscanf(fp,"%s %s\n",&token, &token1); 
	printf("%s%s\n",token,token1); 
	return(es);
}

 
//<compound_stat> ::= {<statement_list> } 
int compound_stat()
{
	int es = 0;
	fscanf ( fp,"%s %s\n", &token, &token1); //复合语句函数
	printf("%s %s\n", token, token1);
	es = statement_list();
	if(es>0) return es;
	if (strcmp(token, "}") == 0){			//对 } 的匹配
		fscanf(fp, "%s %s\n", &token, &token1);
		printf("%s %s\n", token, token1);
	}
	else{
		es = 2;
		return(es);
	}
	return es;
}

//<expression_stat> i :==<expression> @ POP; |; 
int expression_stat()
{
	int es=0;
	if(strcmp(token,";")== 0)
	{
		fscanf(fp,"%s%s\n",&token,&token1); 
		printf("%s%s\n",token,token1); 
		return(es);
	}
	es=expression(); 
	if(es>0) return(es) ; 
	fprintf(fout,"POP\n");       //输出POP指令
	if(strcmp(token,";") == 0)    
	{
		fscanf(fp,"%s %s\n",&token, &token1);
		printf("%s %s\n",token,token1); 
		return(es);
	}else
	{
		es=4;
		return(es);                //少分号

		}

}

//<expression> :: = ID^n0 LOOKj nfd6 ASSIGN=<boo:l_expr>@ STO{d0 POP |<bool_expr> 
int expression()
{
	int es=0,fileadd;
	char token2[20],token3[40];
	if(strcmp(token,"ID")==0)
	{
		fileadd=ftell(fp);	//@ASSIGN己住当前文件位置
		fscanf(fp,"%s %s\n", &token2, &token3); 
		fseek(fp, fileadd, 0);
		if(strcmp(token2,"=") == 0)
		{
			int address;
			es=lookup(token1,&address);
			if (es == 24) es = 0; //var  initilize complete
			if (es>0)  return(es);
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s %s\n",token,token1); 
			fscanf(fp, "%s %s\n", &token, &token1);
			printf("%s %s\n", token, token1);
			es=bool_expr(); 
			if(es>0)  return(es);
			fprintf(fout,"STO %d\n",address);
			
		}else
		{
			es=bool_expr(); 
			if(es> 0) return(es);
		}
	}else es=bool_expr();

	return(es);
} 

//<bool_expr> :: = <additive_expr>
//   	|<additive__expr>(> |<1>尹 I<= l"=1 !=)<additivej_expr>
/*  <bool_expr> :: = < additive_expr>
| < additive_expr>> < additive_expr> 0 GT 
| < addi tive_exp r > < < additive_expr> @ LES 
| < Additive_expr>> = < additive_expr> @ GE 
| < additive_expr> < = < additive_expr> @ LE 
| < additive_expr> == <additive_expr> @ EQ 
| < additive_expr> ! = < additive_expr> 0 NOTEQ 
*/
int bool_expr()
{
	int es=0;
	es= additive_expr();
	if(es>0) return(es);
	if(strcmp(token,">")==0|| strcmp(token,">=")== 0 || strcmp(token,"<")== 0 || strcmp(token,"<=")==0 || strcmp(token,"==") == 0||strcmp(token,"!=")== 0)
	{
			char token2[20];
			strcpy(token2,token);	//保存运算符
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s%s\n",token,token1); 
			es = additive_expr();
			if (es > 0) return(es);
			if(strcmp(token2,">") ==0) fprintf(fout,"GT\n");
			if(strcmp(token2,">=")==0) fprintf(fout,"GE\n1");
			if(strcmp(token2,"<") ==0) fprintf(fout,"LES\n");
			if(strcmp(token2,"<=")==0) fprintf(fout,"LE\n");
			if(strcmp(token2,"==")==0) fprintf(fout,"EQ\n");
			if(strcmp(token2,"!=")==0) fprintf(fout,"NOTEQ\n");
		}
	
	return(es);
}

//< additive_expr> :: = <term> {(+ | - )<term> } 
//<additive_expr> ::*<term> {(+<term>0ADD|-<^>0SUB) }
int additive_expr()
{
	int es=0;
	es=term();
	if(es>0) return(es);
	while(strcmp(token,"+")== 0 || strcmp(token,"-") == 0)
	{
		char token2[20];
		strcpy(token2,token);
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token,token1);
		es=term();
		if(es>0) return(es);
		if(strcmp(token2,"+")== 0) fprintf(fout,"ADD\n");
		if(strcmp(token2,"-") == 0)fprintf(fout,"SUB\n");
	}
	
	return(es);
}

//< term> :: = < factor> {( * | /) < fagtor> }
//<term> :: = <factor> {( * <factor>6MULT 丨 /< factor>gDIV> } s
int term()
{
	int es=0;
	es=factor();
	if(es>0) return(es);
	while(strcmp(token,"*")== 0 ||strcmp(token,"/")== 0)
	{
		char token2[20];
		strcpy(token2, token);
		fscanf(fp,"%s %s\n",&token,&token1); 
		printf("%s %s\n",token,token1); 
		es= factor(); if(es>0) return(es);
		if(strcmp(token2,"*") == 0) fprintf(fout,"MULT\n");
		if(strcmp(token2,"/") == 0)fprintf(fout,"DIV\n");
	}
		
	return(es);
	
}

//< factor> ::=(<additive_expr> ) | ID,|NUM
//< factor> ::*=(<expression> ) j IDt n 0 LOOK| nf d*6 LOADfd INUMf i 0 LOADI\ ± 
int factor()
{
	int es=0;
	if(strcmp(token,"(") == 0)
	{
		fscanf(fp,"%s %s\n",&token,&token1);
		printf("%s %s\n",token, token1); 
		es=expression(); 
		if(es>0) return(es);
		if(strcmp(token,")")) return(es= 6);	//少右括号
		fscanf(fp,"%s %s\n",&token, & token1); printf("%s %s\n",token,token1);
	}else
	{ 
		if(strcmp(token,"ID")== 0)
		{
			int address;
			es=lookup(token1, &address) ;	//査符号表,获取变量地址
			if(es>0) return(es);	        //变量没声明
			fprintf(fout,"LOAD %d\n",address);
			fscanf(fp,"%s %s\n", &token, &token1);
			printf("%s %s\n",token,token1);
			return(es);
		}
		if(strcmp(token,"NUM")==0)
		{
			fprintf(fout,"LOADI %s\n",token1);
			fscanf(fp,"%s %s\n",&token,&token1); 
			printf("%s %s\n",token,token1);
			return(es);
		}else
		{
			es=7;	//缺少操作数
			return(es);
		}
	}
		
	return(es);
}