#pragma once
#include "suanshufenxi.h"
#define iWantDefault2

suanshufenxi::suanshufenxi()
{
	i = -1;			 //当前扫瞄字符位置
	ch = ' ';		//当前扫瞄字符
	ccount = 0;		//当前扫描到的词数
	po_ch = 0;		//当前登记了多少个标识符
	//int po_nu = 0;		//当前登记了多少个数字
	nowline = 0;//当前扫描的是代码中的第几行
	count_err = 0; //当前扫描出的错误数

	ista = 0;//起始位置
	iend = ista;//结束位置
	sp = 0;//栈顶指针
	ii = 0;//当前要分析的符号在词法分析结果中的位置

	system("md E:\\hizengbiao2");//创建一个文件夹 
	system("cls");
#ifdef iWantDefault2
	out2.open("E:\\hizengbiao2\\a.txt");
	if (!out2)
	{
		cerr << "保存的文件打开失败！";
	}
	{
		//out2 << "5 * 5 + (6 + 1) * 6 + 1; (1 + 2); (3 + 5) * 5;\n";
		out2 << "(1 + 2)*(3 + 4 + (5 + 6 * 7));\n";
		out2 << "((1 + 2) * 3 + 4;\n";
		out2 << "+8; *7 * 7;)7 + 3;\n";
		out2 << "(+8 * 7; 1 + 2 + (*3 + 4); 5 + 8; 7 + () + 3;\n";
		out2 << "7++3; 8 + *4; 2 + )6; 23 + ;\n";
		out2 << "34 * +2; 23 * *5 + 9; 23 * )3; 12 + 3 * ; 12 + 3;8 9; 3 * 7\n";
	}
	out2.close();
#endif
	in.open("E:\\hizengbiao2\\a.txt");
	if (!in)
	{
		cerr << "待分析文件打开失败！";
	}
	out.open("E:\\hizengbiao2\\b.txt");
	if (!out)
	{
		cerr << "保存的文件打开失败！";
	}
}

void suanshufenxi::stCifa(){//开始进行词法分析
	nowline = 0;
	while (getline(in, line))
	{
		nowline++;
		scanOneLine();//词法分析源代码的一行

	}

}

void suanshufenxi::stYufa(){//开始进行语法分析

	cout << "语法分析结果如下：\n\n";
	out << "语法分析结果如下：\n\n";
	ista = 0;//起始位置
	stsend();//语义分析时计算当前表达式的开始位置和结束位置
	show2(ista, iend);//输出词法分析结果中从位置ista到iend的元素
	out << endl;
	cout << endl;
	ii = 0;
	reset();//重置语法分析栈
	lrparse();//语法分析
}

int suanshufenxi::findd(string m){//查找标识符m在标识符登记表中的位置
	for (int q = 0; q < po_ch; q++){
		if (m == tab_ch[q])
			return q;
	}
	return -1;
}


void suanshufenxi::identifier(){//识别字符串是标识符还是保留字

	int ss = 0;//1表示保留字，0表示标识符
	int j;//j表示如果字符是标识符，在标识符登记表中的序号
	int iii = 0;//如果是保留字的话在保留字数组中的序号
	string spelling = "";//识别出来的串
	do{
		spelling.append(&ch, 1);
		readch();
	} while ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z') || (ch >= '0') && (ch <= '9'));
	backch();
	while ((ss == 0) && (iii < nOFkeepwords)){
		if (spelling == kw[iii].name)
			ss = 1;
		iii++;
	}
	if (ss == 1)
		buf[ccount].sy1 = kw[iii - 1].value;
	else
	{
		buf[ccount].sy1 = iden;
		j = findd(spelling);
		if (j == -1){
			buf[ccount].pos = po_ch;
			tab_ch[po_ch] = spelling;
			po_ch++;
		}
		else
			buf[ccount].pos = j;

	}
	ccount++;

}


void suanshufenxi::number(){//识别数字
	//
	string spelling = "";
	do{
		spelling.append(&ch, 1);
		readch();
	} while ((ch >= '0') && (ch <= '9'));
	backch();
	buf[ccount].sy1 = cons;
	buf[ccount].pos = atoi(spelling.c_str());//数字的值直接给pos，就不登记了
	ccount++;
}

void suanshufenxi::backch(){//回退一个字符
	ch = line[--i];
}

void suanshufenxi::readch(){//读取一个字符
	ch = line[++i];
}

void suanshufenxi::scanOneLine(){//词法分析一行
	//string token = "";
	i = 0;
	ch = line[i];
	while (i != line.length()){
		switch (ch){
		case ' ':case '\t':break;
		case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':
		case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':
		case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':
		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':
		case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
		case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':
			identifier(); break;

		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			number(); break;

		case '<':
			readch();
			if (ch == '='){
				buf[ccount].sy1 = xiaodeng;
			}
			else{
				buf[ccount].sy1 = smaller;
				backch();
			}
			ccount++; break;
		case '>':
			readch();
			if (ch == '='){
				buf[ccount].sy1 = dadeng;
			}
			else{
				buf[ccount].sy1 = bigger;
				backch();
			}
			ccount++; break;
		case '+':
			buf[ccount].sy1 = jia; ccount++; break;
		case '-':
			buf[ccount].sy1 = jian; ccount++; break;
		case '*':
			buf[ccount].sy1 = chen; ccount++; break;
		case '/':
			buf[ccount].sy1 = chu; ccount++; break;
		case '=':
			buf[ccount].sy1 = deng; ccount++; break;
		case '!':
			readch();
			if (ch == '='){
				buf[ccount].sy1 = budeng;
			}
			else{
				backch();
				buf[ccount].sy1 = err; buf[ccount].pos = count_err; errs[count_err] = ch; count_err++;

			}
			ccount++; break;

		case ',':
			buf[ccount].sy1 = douhao; ccount++; break;
		case ';':
			buf[ccount].sy1 = fenhao; ccount++; break;
		case '{':
			buf[ccount].sy1 = dal; ccount++; break;
		case '}':
			buf[ccount].sy1 = dar; ccount++; break;
		case '(':
			buf[ccount].sy1 = xiaol; ccount++; break;
		case ')':
			buf[ccount].sy1 = xiaor; ccount++; break;
		case '#':
			buf[ccount].sy1 = jinhao; ccount++; break;
		default: buf[ccount].sy1 = err; buf[ccount].pos = count_err; errs[count_err] = ch; errsLine[count_err] = nowline; count_err++; ccount++; break;
		}
		ch = line[++i];
	}

}

void suanshufenxi::show(){//输出词法分析的结果
	cout << "词法分析识别如下（种别编码，自身值）：";
	for (int q = 0; q < ccount; q++){
		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//保留字
			cout << "\n(" << buf[q].sy1 << ",\"" << kw[buf[q].sy1].name << "\")";
		}
		else if (buf[q].sy1 == 20){//标识符
			cout << "\n(" << buf[q].sy1 << ",\"" << tab_ch[buf[q].pos] << "\")";
		}
		else if (buf[q].sy1 == 21){//数字
			cout << "\n(" << buf[q].sy1 << ",\"" << buf[q].pos << "\")";
		}
		else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//运算符
			cout << "\n(" << buf[q].sy1 << ",\"" << yunsuan[buf[q].sy1 - 50].name << "\")";
		}
		else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//界符
			cout << "\n(" << buf[q].sy1 << ",\"" << border[buf[q].sy1 - 70].name << "\")";
		}
		else if (buf[q].sy1 == err){
			cout << "\n源代码第" << errsLine[buf[q].pos] << "行出现错误:\t" << errs[buf[q].pos];
		}
	}
}


string suanshufenxi::finsBuf(int q){//根据buf的下标返回对应的符号

	if (q >= ccount)
		return " ";

	if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//保留字
		return kw[buf[q].sy1].name;
	}
	else if (buf[q].sy1 == 20){//标识符
		return tab_ch[buf[q].pos];
	}
	else if (buf[q].sy1 == 21){//数字

		int hello = buf[q].pos;
		stringstream ss;
		ss << hello;
		string   s = ss.str();
		//调用string的方法  
		//cout << s.c_str() << endl


		/*char c[8];
		_itoa(i, buffer, 10);*/
		//int length = sprintf(c, "%05X", buf[q].pos);
		/*string ss(c);*/
		/*
		string ss;
		char cs[8] = { ' ' };
		cs[7] = '0';
		int cs1 = buf[q].pos;
		int tip = 0;
		while (cs1 != 0){

		}
		stringstream sss;
		string str;
		ss =buf[q].pos.tostring();*/
		return s;
	}
	else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//运算符
		return yunsuan[buf[q].sy1 - 50].name;
	}
	else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//界符
		return border[buf[q].sy1 - 70].name;
	}

	else
		return "undefine";
	/*else if (buf[q].sy1 == err){
	cout << "\n源代码第" << errsLine[buf[q].pos] << "行出现错误:\t" << errs[buf[q].pos];
	}*/

}

void suanshufenxi::reset(){//重置语法分析栈
	sp = 0;
	sstack[sp].a = 0;

	sstack[sp].b.sy1 = jinhao;
	sstack[sp].b.pos = 0;

	//sstack[sp].b = { jinhao, 0 };
	sstack[sp].c = -1;
}


void suanshufenxi::show2(int st, int en){//输出词法分析结果中从位置ista到iend的元素

	{
		for (int q = st; q <= en; q++){
			if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//保留字
				out << kw[buf[q].sy1].name << " ";
			}
			else if (buf[q].sy1 == 20){//标识符
				out << tab_ch[buf[q].pos] << " ";
			}
			else if (buf[q].sy1 == 21){//数字
				out << buf[q].pos << " ";
			}
			else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//运算符
				out << yunsuan[buf[q].sy1 - 50].name << " ";
			}
			else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//界符
				out << border[buf[q].sy1 - 70].name << " ";
			}
			else if (buf[q].sy1 == err){
				out << errs[buf[q].pos] << " ";
			}
		}
	}
	/*out.close();*/
	for (int q = st; q <= en; q++){
		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//保留字
			cout << kw[buf[q].sy1].name << " ";
		}
		else if (buf[q].sy1 == 20){//标识符
			cout << tab_ch[buf[q].pos] << " ";
		}
		else if (buf[q].sy1 == 21){//数字
			cout << buf[q].pos << " ";
		}
		else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//运算符
			cout << yunsuan[buf[q].sy1 - 50].name << " ";
		}
		else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//界符
			cout << border[buf[q].sy1 - 70].name << " ";
		}
		else if (buf[q].sy1 == err){
			cout << errs[buf[q].pos] << " ";
		}
	}
	//cout << endl;
}



string suanshufenxi::finds(int tc){//根据种别编码返回符号
	switch (tc){
	case jia:return "+";
	case chen:return "*";
	case xiaol:return "(";
	case xiaor:return ")";
	default:return "undefine";
	}
}

void suanshufenxi::stsend(){//语义分析时计算当前表达式的开始位置和结束位置


	iend = ista;
	while ((buf[iend].sy1 != douhao) && (buf[iend].sy1 != fenhao) && (buf[iend].sy1 != jinhao) && (iend<ccount - 1))
	{

		iend++;
	}
}

void suanshufenxi::show3(int c){//输出计算到当前这一步的计算结果

	int sl = sp + 1;
	bb *sss = new bb[sl];
	for (int p = 0; p <sl; p++){
		if (p == 0)
			sss[p].b = "=";
		else if (sstack[p].b.sy1 == -1){//非终结符
			sss[p].a = sstack[p].c;
			sss[p].b = "-";
		}
		else if (sstack[p].b.sy1 == kongzi){//空字
			sss[p].b = "kong";
		}
		else{//终结符
			sss[p].b = finds(sstack[p].b.sy1);
		}
	}
	/*int iend = ii;
	while ((buf[iend].sy1 != douhao) && (buf[iend].sy1 != fenhao) && (buf[iend].sy1 != jinhao))
	{

	iend++;
	}*/
	for (int p = 0; p < sl; p++){
		if (sss[p].b == "-"){
			cout << sss[p].a << " ";
			out << sss[p].a << " ";
		}
		else if (sss[p].b == "kong")
			;
		else{
			cout << sss[p].b << " ";
			out << sss[p].b << " ";


		}
	}
	if ((c == E_) || (c == T_)){
		cout << sstack[sp].c << " ";
		out << sstack[sp].c << " ";
	}


	show2(ii, iend);
	cout << endl;
	out << endl;


}
int suanshufenxi::conv(int c, aa tem){//根据输入符号返回在LR分析表中的横向序号
	if (c == 2 || c == 13){
		if (tem.sy1 == jia)
			return 1;
		/*else if (tem.sy1 == cons)
		return 0;*/
		else
			return 3;
	}
	if (c == 3 || c == 14){
		if (tem.sy1 == chen)
			return 2;
		/*else if (tem.sy1 == cons)
		return 0;*/
		else
			return 3;
	}

	switch (tem.sy1){
	case cons:return 0;
	case jia:return 1;
	case chen:return 2;
	case xiaol:return 4;
	case xiaor:return 5;
	case douhao:case fenhao:return 6;
	default:return 3;
	}
}


void suanshufenxi::lrparse(){//语法分析

	/*if (ii == (ccount - 1))
	return;*/
	lr = action22[sstack[sp].a][conv(sstack[sp].a, buf[ii])];
	if ((lr >= 0) && (lr < 18)){
		if (lr == 11){
			sstack[++sp].a = lr;

			sstack[sp].b.sy1 = kongzi;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { kongzi, 0 };//b等于空字
			sstack[sp].c = -1;
			lrparse();
		}
		else if (lr == 8){
			sstack[++sp].a = lr;


			sstack[sp].b.sy1 = kongzi;
			sstack[sp].b.pos = 0;


			//sstack[sp].b = { kongzi, 0 };//b等于空字
			sstack[sp].c = -1;
			lrparse();
		}
		else{
			sstack[++sp].a = lr;
			sstack[sp].b = buf[ii++];
			if (ii > iend){
				lr = -20;
				goto erro;
			}

			sstack[sp].c = -1;
			lrparse();
		}
	}
	else if ((lr >= 100) && (lr < 109)){
		int lrt;
		/*string sss;*/
		switch (lr){
		case 100://S'->E

			break;
		case 101://E->TE'
			sp = sp - 2;
			lrt = action22[sstack[sp].a][E2];
			++sp;
			sstack[sp].a = lrt;


			if (sstack[sp + 1].c == kongzi){
				//sstack[sp].c = sstack[sp + 2].c;

			}
			else{
				int ttt = sstack[sp].c + sstack[sp + 1].c;
				sstack[sp].c = ttt;
				if (buf[ii].sy1 != xiaor)//如果是小括号里只有一个数字这种情况就不输出
					show3(E2);
			}

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };

			break;
		case 102://E'->+TE'
			sp = sp - 3;
			lrt = action22[sstack[sp].a][E_];
			++sp;
			sstack[sp].a = lrt;

			if (sstack[sp + 2].c == kongzi){
				sstack[sp].c = sstack[sp + 1].c;
			}
			else{
				int ttt = sstack[sp + 1].c + sstack[sp + 2].c;
				sstack[sp].c = ttt;
				show3(E_);
			}

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			break;
		case 103://E'->null
			sp = sp - 1;
			lrt = action22[sstack[sp].a][E_];
			++sp;
			sstack[sp].a = lrt;

			sstack[sp].c = kongzi;

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			break;
		case 104://T->FT'
			sp = sp - 2;
			lrt = action22[sstack[sp].a][T];
			++sp;
			sstack[sp].a = lrt;

			if (sstack[sp + 1].c == kongzi){
				//sstack[sp].c = sstack[sp + 2].c;
			}
			else{
				int ttt = sstack[sp].c*sstack[sp + 1].c;
				sstack[sp].c = ttt;
				show3(T);
			}

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };

			break;
		case 105://T'->*FT'
			sp = sp - 3;
			lrt = action22[sstack[sp].a][T_];
			++sp;
			sstack[sp].a = lrt;

			if (sstack[sp + 2].c == kongzi){
				sstack[sp].c = sstack[sp + 1].c;
			}
			else{
				int ttt = sstack[sp + 1].c*sstack[sp + 2].c;
				sstack[sp].c = ttt;
				show3(T_);
			}

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			break;
		case 106://T'->null
			sp = sp - 1;
			lrt = action22[sstack[sp].a][T_];
			++sp;
			sstack[sp].a = lrt;

			sstack[sp].c = kongzi;

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			break;
		case 107://F->(E)
			sp = sp - 3;
			lrt = action22[sstack[sp].a][F];
			++sp;
			sstack[sp].a = lrt;

			sstack[sp].c = sstack[sp + 1].c;

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			show3(F);
			break;
		case 108://F->i
			sp = sp - 1;
			lrt = action22[sstack[sp].a][F];
			++sp;
			sstack[sp].a = lrt;

			sstack[sp].c = sstack[sp].b.pos;

			sstack[sp].b.sy1 = -1;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { -1, 0 };
			break;
		}
		if (lr == acc){
			//iend = ii;

			cout << "分析成功！结果为" << sstack[sp].c << endl << endl;

			out << "分析成功！结果为" << sstack[sp].c << endl << endl;

			//准备分析下一个表达式：
			ista = iend + 1;
			stsend();
			show2(ista, iend);
			cout << endl;
			out << endl;
			reset();
			if (ii >= (ccount - 1))
				return;
			ii = ista;

		}
		lrparse();
	}

	else{
		//lr<0,错误情况处理

		/*while ((buf[ii].sy1 != douhao) && (buf[ii].sy1 != fenhao) && (buf[ii].sy1 != jinhao))
		{

		if (ii >= (ccount-1))
		return;
		ii++;
		}*/
		//iend = ii;


	erro:
		string er;
		switch (lr){
		case -1:er = "表达式错误\n\n"; break;
		case -2:er = "表达式不能以+开头\n\n"; break;
		case -3:er = "表达式不能以*开头\n\n"; break;
		case -4:er = "表达式不能以）开头\n\n"; break;
		case -5:er = "表达式只有一个分号，没有其他内容\n\n"; break;
		case -6:er = "缺少与）匹配的（\n\n"; break;
		case -7:er = "左括号右边不能为+\n\n"; break;
		case -8:er = "左括号右边不能为*\n\n"; break;
		case -9:er = "小括号（）之间没有任何内容\n\n"; break;
		case -10:er = "（出现在最右边\n\n"; break;
		case -11:er = "出现两个连续的+\n\n"; break;
		case -12:er = "+后面出现*\n\n"; break;
		case -13:er = "+后面出现）\n\n"; break;
		case -14:er = "表达式以+结尾\n\n"; break;
		case -15:er = "*后面出现+\n\n"; break;
		case -16:er = "出现两个连续的*号\n\n"; break;
		case -17:er = "*后面出现）\n\n"; break;
		case -18:er = "表达式以*结尾\n\n"; break;
		case -19:er = "左右括号数量不匹配！\n\n"; break;
		case -20:er = "缺少分号或结束符！在表达式中字符" + finsBuf(ii - 1) + "的后面" + ((finsBuf(ii) != " ") ? ("，在" + finsBuf(ii) + "的前面") : "") + "\n\n"; break;
		default:er = "未知的错误\n\n"; break;
		}

		cout << "错误：" + er;
		//ofstream out;

		out << "错误：" << er;

		if (ii >= (ccount - 1))
			return;
		//准备分析下一个表达式：
		ista = iend + 1;

		stsend();
		show2(ista, iend);

		out << endl;

		cout << endl;
		reset();
		ii = ista;

		lrparse();

	}

}


suanshufenxi::~suanshufenxi()
{
	in.close();
	out.close();
}
