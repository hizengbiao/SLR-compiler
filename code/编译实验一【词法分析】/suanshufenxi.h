//最后编辑时间：2016-5-20 8:08
//
//主要更新说明：
//Ver 1.0:完成程序的基本结构，，完成对空字的处理，能识别表达式的正确与否
//Ver 2.0 :增加识别错误的表达式具体的错误类型，是什么错误
//Ver 3.0 :增加语义分析，识别出正确表达式的计算结果
//Ver 4.0 : 增加将结果输出到本地文本，更正部分小bug，对几个下标进行限定，防止可能产生的溢出
//Ver 5.0 : 增加显示计算过程，只有当次规约产生的计算过程对上一步过程有变化才显示
//Ver 6.0 : 优化计算过程的显示，删除多余的，增加必要的，如“=（3）”这类步骤省略，直接显示下一步“=3”，多个连续的加式或乘式分多步显示
//Ver 7.0 : 将程序用类封装实现，增加注释，方便以后阅读，修正几个可能引起程序崩溃的问题
//Ver 8.0 :	将LR(0)文法改造成SLR(1)文法，解决表达式文件最后一个表达式后缺分号所造成的部分下标越界问题

//因时间有限，其余的部分问题因影响不大，不再进行完善

//实验题目：词法分析&语法分析（平时上机）
//江苏大学计算机学院
//班级：计算机1302
//姓名：曾彪	
//学号：3130602050
//源代码仅供学习与参考，未经本人允许请勿作他用，转载请注明出处
//联系方式：982003834@qq.com，hizengbiao@vip.qq.com
//以上内容请勿删除或修改

#pragma once
#include "defineAndStruct.h"
#include <stdio.h>
#include <sstream>
class suanshufenxi
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
	int sp;//栈顶指针
	int ii;//当前要分析的符号在词法分析结果中的位置
	int lr;//分析动作，移进还是规约或是出错


	//keepwords kw[nOFkeepwords];
	//keepwords yunsuan[10];
	//keepwords border[7];

	aa buf[3000];//词法分析表，保存词法分析的结果


	stackType sstack[100];//语法分析栈
public:
	suanshufenxi();
	void stCifa();//开始进行词法分析
	void stYufa();//开始进行语法分析
	int findd(string m);//查找标识符m在标识符登记表中的位置
	void identifier();//识别字符串是标识符还是保留字
	void number();//识别数字
	void backch();//回退一个字符
	void readch();//读取一个字符
	void scanOneLine();//词法分析一行
	void show();//输出词法分析的结果
	string finsBuf(int q);//根据buf的下标返回对应的符号
	void reset();//重置语法分析栈
	void show2(int st, int en);//输出词法分析结果中从位置ista到iend的元素
	string finds(int tc);//根据种别编码返回符号
	void stsend();//语义分析时计算当前表达式的开始位置和结束位置
	void show3(int c);//输出计算到当前这一步的计算结果
	int conv(int c, aa tem);//根据输入符号返回在LR分析表中的横向序号
	void lrparse();//语法分析

	~suanshufenxi();
};






