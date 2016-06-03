//主程序
#include< stdio.h>
#include< ctype.h> 
extern int TESTmachine(); 
char Scanin[300], Scanout[300],Codeout[300];
FILE * fin, *fout;
extern int TESTscan();
extern int TESTparse();

void main ()
{

	int es = 0;
	es = TESTscan();
	if (es > 0){
		printf("词法分析有错，编译停止！");
	}
	if (es == 0){
		es = TESTparse();
		if (es == 0){
			es=TESTmachine();	//调用抽象机模拟器
		}
		else{
			printf("语法分析错误!\n");
		}
	}
	scanf("%d", es);
	scanf("%d", es);
	
}