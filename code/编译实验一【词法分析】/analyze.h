#pragma once
#include "defineAndStruct.h"
#include <stdio.h>
#include <sstream>
class analyze
{

	string line;		 //当前扫瞄行
	int i;			 //当前扫瞄字符位置
	char ch;		//当前扫瞄字符
	int ccount;		//当前扫描到的词数
	int po_ch;		//当前登记了多少个标识符
	//int po_nu = 0;		//当前登记了多少个数字
	int nowline;//当前扫描的是代码中的第几行
	int count_err; //当前扫描出的错误数

	char errs[60];	//储存错误信息
	int errsLine[60];//每个错误在源代码中的行号
	string tab_ch[1000];//标识符登记表
	//int tab_nu[100];

	ifstream in;//待分析的文本
	ofstream out2;//生成待分析的文本
	ofstream out;//语义分析结果保存的文本
	int ista;//语法分析的表达式的起始位置
	int iend;//语法分析的表达式的结束位置
	int sp;//栈顶指针stack下标
	int ssp;//栈顶指针sstack下标
	int ii;//当前要分析的符号在词法分析结果(buf表)中的位置
	int lr;//分析动作，移进还是规约或是出错
	int nxq;//下一个四元式的地址
	ntab33 ntab3[200];//存储每个布尔表达式翻译成的两个四元式的地址
	int label;//ntab3表下标
	aa downline;//下划线
	aa Et;//产生式左部
	int sign; //sign=1表明是算术表达式语句，sign=2表明是循环语句，sign=3表明是控制语句
	int newt;//新产生的临时变量的整数码

	aa buf[3000];//词法分析表，保存词法分析的结果
	aa buf2[300];//保存算术或布尔表达式的输入字符串
	stackType stack[100];//程序语句语法分析栈
	stackType sstack[100];//算术或布尔表达式语法分析栈
	int jj;//当前要分析的符号在buf2表中的位置
	fourexp fexp[200];//四元式存储集
	ll labelmark[10];//保存if或while一开头的那个状态
	int labeltemp[10];//保存if和else中间那个跳过的状态
	int pointmark;//labelmark数组的当前下标
	int pointtemp;//labeltemp数组的当前下标
	int ret;//算术表达式、布尔表达式分析子程序退出标记
	int ret2;//程序语句退出标记
	int subline;//源代码的错误行号
public:
	analyze();//初始化各个变量
	void stCifa();//开始进行词法分析
	void stYufa();//开始进行语法分析
	int findd(string m);//查找标识符m在标识符登记表中的位置
	void identifier();//识别字符串是标识符还是保留字
	void number();//识别数字
	void backch();//回退一个字符
	void readch();//读取一个字符
	void scanOneLine();//词法分析一行
	void show();//输出词法分析的结果
	void showiden(); //输出标识符表
	void shownum();	//输出常数表
	void showZhuangtai();//输出状态栈
	void showFuhao();//输出符号栈
	void showYuyi();//输出语义栈
	void showYuyi(int yu);//输出语义栈
	void showZhan(int lrr);//显示各个栈及规约、移进动作
	string changeStackB(int sy,int zho);//根据种别编码回返相应的输入符号，第十个参数标识是否是非终结符
	string finsBuf(int q);//根据buf的下标返回对应的符号
	void reset();//重置语法分析栈
	void reset2();//重置语法分析栈
	void show2(int st, int en);//输出词法分析结果中从位置ista到iend的元素
	string finds(int tc);//根据种别编码返回符号
	void stsend();//语义分析时计算当前表达式的开始位置和结束位置
	void show3(/*int c*/);//输出计算到当前这一步的计算结果
	int conv(aa tem);//根据输入符号返回在程序语句LR分析表中的横向序号
	int conv2(aa tem);//根据输入符号返回在算术表达式LR分析表中的横向序号
	int conv3(aa tem);//根据输入符号返回在布尔表达式LR分析表中的横向序号
	int test(int value);//判断当前输入字符是程序语句的话返回0，否则返回1（布尔表达式或算术表达式）
	int newtemp();//产生一个新的临时变量
	int lrparse();//程序语句语法分析
	int lrparse2();//算术表达式的分析
	int lrparse3();//布尔表达式的分析
	int emit(string op1, aa arg1, aa arg2, int result1);//产生一个四元式
	int merge(int p1, int p2);//拉链函数
	void show4exp();//输出四元式
	void backpatch(int p, int t);//返填函数
	
	~analyze();
};






