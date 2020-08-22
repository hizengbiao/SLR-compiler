#pragma once
#include "analyze.h"
#define iWantDefault

analyze::analyze()
{
	ret = 0;
	pointmark=-1;
	pointtemp=-1;
	newt = 0;
	i = -1;			 //��ǰɨ���ַ�λ��
	ch = ' ';		//��ǰɨ���ַ�
	ccount = 0;		//��ǰɨ�赽�Ĵ���
	po_ch = 0;		//��ǰ�Ǽ��˶��ٸ���ʶ��
	//int po_nu = 0;		//��ǰ�Ǽ��˶��ٸ�����
	nowline = 0;//��ǰɨ����Ǵ����еĵڼ���
	count_err = 0; //��ǰɨ����Ĵ�����
	nxq = 100;
	label = 0;
	downline.sy1 = underline;

	ista = 0;//��ʼλ��
	iend = ista;//����λ��
	sp = 0;//ջ��ָ��
	ii = 0;//��ǰҪ�����ķ����ڴʷ���������е�λ��

	system("md E:\\hizengbiao2");//����һ���ļ��� 
	system("cls");
#ifdef iWantDefault
	out2.open("E:\\hizengbiao2\\c.txt");
	if (!out2)
	{
		cerr << "�ļ���ʧ�ܣ�";
	}
	{

		out2 << "while (a || b){ if (x < y){ while (c&&d){ k = k + 1; } } else{ if (m < n&&k < q){ m = k; } else{ while (m != k){ m = m + 1; } } }	}\n"; 
	}
	out2.close();
#endif
	in.open("E:\\hizengbiao2\\c.txt");
	if (!in)
	{
		cerr << "�������ļ���ʧ�ܣ�";
	}
	/*out.open("E:\\hizengbiao2\\b.txt");
	if (!out)
	{
		cerr << "������ļ���ʧ�ܣ�";
	}*/
}

void analyze::stCifa(){//��ʼ���дʷ�����
	nowline = 0;
	while (getline(in, line))
	{
		nowline++;
		scanOneLine();//�ʷ�����Դ�����һ��
	}
	buf[ccount].sy1 = jinhao; ccount++;
}

void analyze::stYufa(){//��ʼ�����﷨����

	/*cout << "�﷨����������£�\n\n";
	out << "�﷨����������£�\n\n";*/
	//ista = 0;//��ʼλ��
	//stsend();//�������ʱ���㵱ǰ���ʽ�Ŀ�ʼλ�úͽ���λ��
	//show2(ista, iend);//����ʷ���������д�λ��ista��iend��Ԫ��
	//out << endl;
	//cout << endl;
	ii = 0;
	ret2 = 0;
	reset();//�����﷨����ջ
	lrparse();//�﷨����
}

int analyze::findd(string m){//���ұ�ʶ��m�ڱ�ʶ���ǼǱ��е�λ��
	for (int q = 0; q < po_ch; q++){
		if (m == tab_ch[q])
			return q;
	}
	return -1;
}


void analyze::identifier(){//ʶ���ַ����Ǳ�ʶ�����Ǳ�����
	
	int ss = 0;//1��ʾ�����֣�0��ʾ��ʶ��
	int j;//j��ʾ����ַ��Ǳ�ʶ�����ڱ�ʶ���ǼǱ��е����
	int iii = 0;//����Ǳ����ֵĻ��ڱ����������е����
	string spelling = "";//ʶ������Ĵ�
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
			buf[ccount].linecount = nowline;
			tab_ch[po_ch] = spelling;
			po_ch++;
		}
		else
			buf[ccount].pos = j;

	}
	ccount++;

}


void analyze::number(){//ʶ������
	//
	string spelling = "";
	do{
		spelling.append(&ch, 1);
		readch();
	} while ((ch >= '0') && (ch <= '9'));
	backch();
	buf[ccount].sy1 = cons;
	buf[ccount].pos = atoi(spelling.c_str());//���ֵ�ֱֵ�Ӹ�pos���Ͳ��Ǽ���
	buf[ccount].linecount = nowline;
	ccount++;
}

void analyze::backch(){//����һ���ַ�
	ch = line[--i];
}

void analyze::readch(){//��ȡһ���ַ�
	ch = line[++i];
}

void analyze::scanOneLine(){//�ʷ�����һ��
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
			buf[ccount].linecount = nowline;
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
			buf[ccount].linecount = nowline;
			ccount++; break;
		case '+':
			buf[ccount].sy1 = jia;
			buf[ccount].linecount = nowline; ccount++; break;
		case '-':
			buf[ccount].sy1 = jian;
			buf[ccount].linecount = nowline; ccount++; break;
		case '*':
			buf[ccount].sy1 = chen;
			buf[ccount].linecount = nowline; ccount++; break;
		case '/':
			buf[ccount].sy1 = chu;
			buf[ccount].linecount = nowline; ccount++; break;
		case '=':
			buf[ccount].sy1 = deng;
			buf[ccount].linecount = nowline; ccount++; break;
		case '!':
			readch();
			if (ch == '='){
				buf[ccount].sy1 = budeng;
			}
			else{
				backch();
				buf[ccount].sy1 = not; 
			}
			buf[ccount].linecount = nowline;
			ccount++; break;
		case '&':
			readch();
			if (ch == '&'){
				buf[ccount].sy1 = and;
			}
			else{
				backch();
				buf[ccount].sy1 = err; buf[ccount].pos = count_err; errs[count_err] = ch; count_err++;

			}
			buf[ccount].linecount = nowline;
			ccount++; break;
		case '|':
			readch();
			if (ch == '|'){
				buf[ccount].sy1 = or;
			}
			else{
				backch();
				buf[ccount].sy1 = err; buf[ccount].pos = count_err; errs[count_err] = ch; count_err++;

			}
			buf[ccount].linecount = nowline;
			ccount++; break;

		case ',':
			buf[ccount].sy1 = douhao;
			buf[ccount].linecount = nowline; ccount++; break;
		case ';':
			buf[ccount].sy1 = fenhao;
			buf[ccount].linecount = nowline; ccount++; break;
		case '{':
			buf[ccount].sy1 = dal;
			buf[ccount].linecount = nowline; ccount++; break;
		case '}':
			buf[ccount].sy1 = dar;
			buf[ccount].linecount = nowline; ccount++; break;
		case '(':
			buf[ccount].sy1 = xiaol;
			buf[ccount].linecount = nowline; 
			ccount++; break;
		case ')':
			buf[ccount].sy1 = xiaor;
			buf[ccount].linecount = nowline; ccount++; break;
		case '#':
			buf[ccount].sy1 = jinhao;
			buf[ccount].linecount = nowline; ccount++; break;
		default: buf[ccount].sy1 = err;
			buf[ccount].linecount = nowline; buf[ccount].pos = count_err; errs[count_err] = ch; errsLine[count_err] = nowline; count_err++; ccount++; break;
		}
		ch = line[++i];
	}

}
void analyze::shownum(){
	cout << "���������£�";
	int kd=0;
	for (int q = 0; q < ccount - 1; q++){
		if (buf[q].sy1 == 21){//����
			cout << "\n(  " << kd++ << " , " << buf[q].pos << "  )";
		}

	}
}
void analyze::showiden(){
	cout << "��ʶ�������£�";
	for (int q = 0; q < po_ch; q++){
			cout << "\n(  " << q<< " , " << tab_ch[q] << "  )";
			
	}
}

void analyze::show(){//����ʷ������Ľ��
	cout << "�ʷ�����ʶ�����£��ֱ���룬����ֵ����";
	for (int q = 0; q < ccount-1; q++){
		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//������
			cout << "\n(" << buf[q].sy1 << ",\"" << kw[buf[q].sy1].name << "\")";
		}
		else if (buf[q].sy1 == 20){//��ʶ��
			cout << "\n(" << buf[q].sy1 << ",\"" << tab_ch[buf[q].pos] << "\")";
		}
		else if (buf[q].sy1 == 21){//����
			cout << "\n(" << buf[q].sy1 << ",\"" << buf[q].pos << "\")";
		}
		else if (buf[q].sy1 >= 22 && buf[q].sy1 < 28){//����
			cout << "\n(" << buf[q].sy1 << ",\"" << others[buf[q].sy1 - 22].name << "\")";
		}
		else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//�����
			cout << "\n(" << buf[q].sy1 << ",\"" << yunsuan[buf[q].sy1 - 50].name << "\")";
		}
		else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//���
			cout << "\n(" << buf[q].sy1 << ",\"" << border[buf[q].sy1 - 70].name << "\")";
		}
		else if (buf[q].sy1 == err){
			cout << "\nԴ�����" << errsLine[buf[q].pos] << "�г��ִ���:\t" << errs[buf[q].pos];
		}
	}
}


string analyze::finsBuf(int q){//����buf���±귵�ض�Ӧ�ķ���
	
	if (q >= ccount)
		return " ";

		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//������
			return kw[buf[q].sy1].name;
		}
		else if (buf[q].sy1 == 20){//��ʶ��
			return tab_ch[buf[q].pos];
		}
		else if (buf[q].sy1 == 21){//����

			int hello = buf[q].pos;
			stringstream ss;
			ss << hello;
			string   s = ss.str();
			//����string�ķ���  
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
		else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//�����
			return yunsuan[buf[q].sy1 - 50].name;
		}
		else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//���
			return border[buf[q].sy1 - 70].name;
		}
		
		else
			return "undefine";
		/*else if (buf[q].sy1 == err){
			cout << "\nԴ�����" << errsLine[buf[q].pos] << "�г��ִ���:\t" << errs[buf[q].pos];
		}*/

}
string analyze::changeStackB(int sy,int zhong){
	if (zhong == -2){
		if (sy == S)
			return "S";
		else
			return "L";
	}
	else{
		switch (sy){
		case s_if:
			return "if";
		case s_else:
			return "else";
		case s_while:
			return "while";
		case suanshu:
			return "a";
		case fenhao:
			return ";";
		case buer:
			return "e";
		case dal:
			return "��";
		case dar:
			return "��";
		case jinhao:
			return "#";
		}
	}
	
}
void analyze::showZhuangtai(){
	for (int i = 0; i <= sp; i++)
		cout << stack[i].a << " ";
}

void analyze::showFuhao(){
	for (int i = 0; i <= sp; i++)
		cout << changeStackB(stack[i].b.sy1, stack[i].b.zhongjie) << " ";
}
void analyze::showZhan(int lrr){
	cout << "\n";
	showZhuangtai();
	cout << "\t";
	showFuhao();
	cout << "\t";
	showYuyi();
	cout << "\t";
	if (lrr < 100)
		cout << "s" << lrr;
	else if (lrr == acc)
		cout << "acc\n";
	else
		cout << "r" << lrr-100;
}

void analyze::showYuyi(int yu){
	if (yu == -1)
		cout << "_ ";
	else
		cout << yu << " ";
}

void analyze::showYuyi(){
	/*for (int i = 0; i < sp; i++)
		showYuyi(stack[i].c);*/
}
void analyze::reset(){//�����﷨����ջ
	sp = 0;
	stack[sp].a = 0;

	stack[sp].b.sy1=jinhao;
	stack[sp].b.pos=0;

	//sstack[sp].b = { jinhao, 0 };
	stack[sp].c = -1;
	
}

void analyze::reset2(){//�����﷨����ջ
	ssp = 0;
	sstack[ssp].a = 0;

	sstack[ssp].b.sy1 = jinhao;
	sstack[ssp].b.pos = 0;

	//sstack[sp].b = { jinhao, 0 };
	sstack[ssp].c = -1;
}


void analyze::show2(int st, int en){//����ʷ���������д�λ��ista��iend��Ԫ��
	
	{
		for (int q = st; q <= en; q++){
			if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//������
				out << kw[buf[q].sy1].name << " ";
			}
			else if (buf[q].sy1 == 20){//��ʶ��
				out << tab_ch[buf[q].pos] << " ";
			}
			else if (buf[q].sy1 == 21){//����
				out << buf[q].pos << " ";
			}
			else if (buf[q].sy1 >= 22 && buf[q].sy1 < 28){//����
				out << others[buf[q].sy1 - 22].name << " ";
			}
			else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//�����
				out << yunsuan[buf[q].sy1 - 50].name << " ";
			}
			else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//���
				out << border[buf[q].sy1 - 70].name << " ";
			}
			else if (buf[q].sy1 == err){
				out << errs[buf[q].pos] << " ";
			}
		}
	}
	/*out.close();*/
	for (int q = st; q <= en; q++){
		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//������
			cout << kw[buf[q].sy1].name << " ";
		}
		else if (buf[q].sy1 == 20){//��ʶ��
			cout << tab_ch[buf[q].pos] << " ";
		}
		else if (buf[q].sy1 == 21){//����
			cout << buf[q].pos << " ";
		}
		else if (buf[q].sy1 >= 22 && buf[q].sy1 < 28){//����
			cout << others[buf[q].sy1 - 22].name << " ";
		}
		else if (buf[q].sy1 >= 50 && buf[q].sy1 < 70){//�����
			cout << yunsuan[buf[q].sy1 - 50].name << " ";
		}
		else if (buf[q].sy1 >= 70 && buf[q].sy1 <= 80){//���
			cout << border[buf[q].sy1 - 70].name << " ";
		}
		else if (buf[q].sy1 == err){
			cout << errs[buf[q].pos] << " ";
		}
	}
	//cout << endl;
}



string analyze::finds(int tc){//�����ֱ���뷵�ط���
	switch (tc){
	case jia:return "+";
	case chen:return "*";
	case xiaol:return "(";
	case xiaor:return ")";
	case bigger:return ">";
	case smaller:return "<";
	case dadeng:return ">=";
	case xiaodeng:return "<=";
	case budeng:return "!=";
	case equal:return "==";
	default:return "undefine";
	}
}

void analyze::stsend(){//�������ʱ���㵱ǰ���ʽ�Ŀ�ʼλ�úͽ���λ��


	iend = ista;
	while ((buf[iend].sy1 != douhao) && (buf[iend].sy1 != fenhao) && (buf[iend].sy1 != jinhao)&&(iend<ccount-1))
	{

		iend++;
	}
}

void analyze::show3(){//������㵽��ǰ��һ���ļ�����

	int sl = sp + 1;
	bb *sss = new bb[sl];
	for (int p = 0; p <sl; p++){
		if (p == 0)
			sss[p].b = "=";
		else if (sstack[p].b.sy1 == -1){//���ս��
			sss[p].a = sstack[p].c;
			sss[p].b = "-";
		}
		else{//�ս��
			sss[p].b = finds(sstack[p].b.sy1);
		}
	}
	
	for (int p = 0; p < sl; p++){
		if (sss[p].b == "-"){
			cout << sss[p].a << " ";
			out << sss[p].a << " ";
		}
		else{
			cout << sss[p].b << " ";
			out << sss[p].b << " ";
		}
	}

	show2(ii, iend);
	cout << endl;
	out << endl;


}

int analyze::conv2(aa tem){//����������ŷ�����LR�������еĺ������
	switch (tem.sy1){
	case cons:case iden:return 0;
	case jia:return 1;
	case chen:return 2;
	case xiaol:return 3;
	case xiaor:return 4;
	case douhao:case fenhao:return 5;
	default:return -1;
	}
}

int analyze::conv3(aa tem){//����������ŷ����ڲ������ʽLR�������еĺ������
	switch (tem.sy1){
	case cons:case iden:return 0;
	case xiaodeng:case smaller:case dadeng:
	case bigger:case budeng:case equal:return 1;
	case xiaol:return 2;
	case xiaor:return 3;
	case not:return 4;
	case and:return 5;
	case or:return 6;
	case douhao:case fenhao:return 7;
	default:return -1;
	}
}

int analyze::conv(aa tem){//����������ŷ����ڳ������LR�������еĺ������
	switch (tem.sy1){
	case s_if:return 0;
	case s_else:return 1;
	case s_while:return 2;
	case suanshu:return 3;
	case fenhao:return 4;
	case buer:return 5;
	case dal:return 6;
	case dar:return 7;
	case jinhao:return 8;
	default:if (tem.sy1 == xiaol ) return 5;else  return 3;
	}
}

int analyze::newtemp(){
	newt++;
	return newt;
}

int analyze::lrparse2(){//�������ʽ�ķ���
	

	lr = action2[sstack[ssp].a][conv2(buf2[jj])];
	if ((lr >= 0) && (lr < 10)){
			sstack[++ssp].a = lr;
			sstack[ssp].b = buf2[jj++];
			/*if (jj > iend){
				lr = -20;
				goto erro;
			}*/
			sstack[ssp].c = -1;
			lrparse2();
	}
/*	else */if ((lr > 100) && (lr < 109)){
		int lrt;
		/*string sss;*/
		switch (lr){
		//case 100://S'->E
		//	
		//	break;
		case 101://E->E+E
			Et.pos = newtemp();
			emit("+", sstack[ssp-2].b, sstack[ssp].b, Et.pos+100);
			
			ssp = ssp - 3;
			lrt = action2[sstack[ssp].a][E];
			++ssp;
			sstack[ssp].a = lrt;


			//if (sstack[ssp + 1].c == kongzi){
			//	//sstack[ssp].c = sstack[ssp + 2].c;

			//}
			//else{
			
					//sstack[ssp].c = sstack[ssp].c + sstack[ssp + 2].c;
					//if (sstack[ssp - 1].b.sy1!=xiaol||buf2[jj].sy1 != xiaor)//�����С������ֻ��һ��������������Ͳ����
					//show3();
			//}
			
			sstack[ssp].b.zhongjie=-2;
			/*sstack[ssp].b.pos=0;*/

			//sstack[ssp].b = { -1, 0 };

			break;
		case 102://E->E*E
			Et.pos = newtemp();
			emit("*", sstack[ssp - 2].b, sstack[ssp].b, Et.pos + 100);
			ssp = ssp - 3;
			lrt = action2[sstack[ssp].a][E];
			++ssp;
			sstack[ssp].a = lrt;

			/*if (sstack[ssp + 2].c == kongzi){
				sstack[ssp].c = sstack[ssp + 1].c;
			}
			else{*/
				
				//	sstack[ssp].c = sstack[ssp].c * sstack[ssp + 2].c;
				//	if (sstack[ssp - 1].b.sy1 != xiaol||buf2[jj].sy1 != xiaor)//�����С������ֻ��һ��������������Ͳ����
				//show3();
			//}
						
			sstack[ssp].b.zhongjie = -2;

			//sstack[ssp].b = { -1, 0 };
			break;
		
		case 103://E->(E)
			Et.pos = sstack[ssp - 1].b.pos;
			

			
			ssp = ssp - 3;
			lrt = action2[sstack[ssp].a][E];
			++ssp;
			sstack[ssp].a = lrt;

			//
			sstack[ssp].b = sstack[ssp+1].b;

			//

			
				sstack[ssp].c = sstack[ssp + 1].c;

				//sstack[ssp].b.zhongjie = -2;

			//sstack[ssp].b = { -1, 0 };
			/*show3();*/
			break;
		case 104://E->i
			Et.pos = sstack[ssp].b.pos;
			ssp = ssp - 1;
			lrt = action2[sstack[ssp].a][E];
			++ssp;
			sstack[ssp].a = lrt;

			sstack[ssp].c = sstack[ssp].b.pos;
						
			//sstack[ssp].b.zhongjie = -2;

			//sstack[ssp].b = { -1, 0 };
			break;
		}
		sstack[ssp].b.pos = Et.pos;
		lrparse2();
	}
if (lr == acc&&ret == 0){
	//iend = jj;
	emit("=", sstack[ssp].b, downline, buf2[0].pos);

	//cout << "�������ʽ�����ɹ���"  << endl;
	ret = 1;
	/*cout << "�����ɹ������Ϊ" << sstack[ssp].c << endl << endl;

	out << "�����ɹ������Ϊ" << sstack[ssp].c << endl << endl;*/

	//׼��������һ�����ʽ��
	/*ista = iend + 1;
	stsend();
	show2(ista, iend);
	cout << endl;
	out << endl;
	reset();
	if (jj >= (ccount - 1))
	return 0;
	jj = ista;*/

}

	if(lr<0&&ret==0){
		//lr<0,�����������

		/*while ((buf2[jj].sy1 != douhao) && (buf2[jj].sy1 != fenhao) && (buf2[jj].sy1 != jinhao))
		{

		if (jj >= (ccount-1))
		return;
		jj++;
		}*/
		//iend = jj;


erro:
		string er;
		switch (lr){
		case -1:er = "���ʽ����\n\n"; break;
		case -2:er = "���ʽ������+��ͷ\n\n"; break;
		case -3:er = "���ʽ������*��ͷ\n\n"; break;
		case -4:er = "���ʽ�����ԣ���ͷ\n\n"; break;
		case -5:er = "���ʽֻ��һ���ֺţ�û����������\n\n"; break;
		case -6:er = "ȱ���룩ƥ��ģ�\n\n"; break;
		case -7:er = "�������ұ߲���Ϊ+\n\n"; break;
		case -8:er = "�������ұ߲���Ϊ*\n"; break;
		case -9:er = "С���ţ���֮��û���κ�����\n"; break;
		case -10:er = "�����������ұ�\n\n"; break;
		case -11:er = "��������������+\n\n"; break;
		case -12:er = "+�������*\n\n"; break;
		case -13:er = "+������֣�\n\n"; break;
		case -14:er = "���ʽ��+��β\n\n"; break;
		case -15:er = "*�������+\n\n"; break;
		case -16:er = "��������������*��\n\n"; break;
		case -17:er = "*������֣�\n\n"; break;
		case -18:er = "���ʽ��*��β\n\n"; break;
		case -19:er = "��������������ƥ�䣡\n\n"; break;
		//case -20:er = "ȱ�ٷֺŻ���������ڱ��ʽ���ַ�" + finsBuf(jj - 1) + "�ĺ���" + ((finsBuf(jj) != " ") ? ("����"+finsBuf(jj)+"��ǰ��") : "") + "\n\n"; break;
		default:er = ""; break;
		}

		cout << "\n\nԴ�����е�"<<subline<<"���������ʽ����" + er+"";
		ret = 1;
		//ofstream out;

		out << "����" << er;

		//if (jj >= (ccount - 1))
		//	return 0;
		////׼��������һ�����ʽ��
		//ista = iend + 1;

		//stsend();
		//show2(ista, iend);

		//out << endl;

		//cout << endl;
		//reset();
		//jj = ista;

		//lrparse();

	}
	return 1;
}


int analyze::emit(string op1, aa arg11, aa arg22, int result1){//����һ����Ԫʽ
	fexp[nxq].op = op1;
	fexp[nxq].arg1.sy1 = arg11.sy1;
	fexp[nxq].arg1.pos = arg11.pos;
	fexp[nxq].arg1.zhongjie = arg11.zhongjie;
	fexp[nxq].arg2.sy1 = arg22.sy1;
	fexp[nxq].arg2.pos = arg22.pos;
	fexp[nxq].arg2.zhongjie = arg22.zhongjie;
	fexp[nxq].result = result1;
	nxq++;
	return nxq - 1;
}

int analyze::merge(int p1, int p2){//��������
	int p;
	if (p2 == 0)
		return p1;
	else{
		p = p2;
		while (fexp[p].result != 0)
			p = fexp[p].result;
		fexp[p].result = p1;
		return p2;
	}
}

void analyze::backpatch(int p, int t){//�����
	int q = p;
	int tem;
	while (q != 0){
		tem = fexp[q].result;
		fexp[q].result = t;
		q = tem;
	}
}


int analyze::lrparse3(){//�������ʽ�ķ���
	if (ret == 1)
		return 1;
	lr = action3[sstack[ssp].a][conv3(buf2[jj])];
	if ((lr >= 0) && (lr < 16)){
		sstack[++ssp].a = lr;
		sstack[ssp].b = buf2[jj++];
		/*if (jj > iend){
			lr = -20;
			goto erro;
		}*/
		sstack[ssp].c = -1;
		lrparse3();
	}
	/*else*/ if ((lr > 100) && (lr < 109)){
		int lrt;
		/*string sss;*/
		switch (lr){
			int temm;
		//case 100://S'->B

		//	break;
		case 101://B->i
			ntab3[label].tc = nxq;
			ntab3[label].fc = nxq+1;
			emit("jnz", sstack[ssp].b, downline, 0);
			emit("j", downline, downline, 0);

			ssp = ssp - 1;
			label++;

			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;


			//if (sstack[ssp + 1].c == kongzi){
			//	//sstack[ssp].c = sstack[ssp + 2].c;

			//}
			//else{

			//sstack[ssp].c = sstack[ssp].c + sstack[ssp + 2].c;
			//if (sstack[ssp - 1].b.sy1 != xiaol || buf2[jj].sy1 != xiaor)//�����С������ֻ��һ��������������Ͳ����
			//	show3();
			//}

			sstack[ssp].b.sy1 = -1;//���ս��
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };

			break;
		case 102://B->i rop i
			ntab3[label].tc = nxq;
			ntab3[label].fc = nxq + 1;
			switch (sstack[ssp-1].b.sy1){
			case xiaodeng:
				emit("j<=", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			case smaller:
				emit("j<", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			case dadeng:
				emit("j>=", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			case bigger:
				emit("j>", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			case budeng:
				emit("j!=", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			case equal:
				emit("j==", sstack[ssp - 2].b, sstack[ssp].b, 0);
				break;
			}
			emit("j", downline, downline, 0);
			label++;
			ssp = ssp - 3;
			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;
			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			break;

		case 103://B->(B)

			ssp = ssp - 3;
			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;


			//sstack[ssp].c = sstack[ssp + 1].c;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			break;
		case 104://B->not B
			label--;
			temm = ntab3[label].tc;
			ntab3[label].tc = ntab3[label].fc;
			ntab3[label].fc = temm;
			label++;
			ssp = ssp - 2;
			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;

			//sstack[ssp].c = sstack[ssp].b.pos;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };
			break;
		case 105://A->B and
			label--;
			backpatch(ntab3[label].tc, nxq);
			label++;
			ssp = ssp - 2;
			lrt = action3[sstack[ssp].a][A];
			++ssp;
			sstack[ssp].a = lrt;

			//sstack[ssp].c = sstack[ssp].b.pos;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };
			break;
		case 106://B->AB
			label -= 2;
			ntab3[label].tc = ntab3[label + 1].tc;
			ntab3[label].fc = merge(ntab3[label].fc, ntab3[label + 1].fc);
			label++;
			ssp = ssp - 2;
			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;

			//sstack[ssp].c = sstack[ssp].b.pos;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };
			break;
		case 107://O->B or
			label--;

			backpatch(ntab3[label].fc, nxq);
			label++;



			ssp = ssp - 2;
			lrt = action3[sstack[ssp].a][O];
			++ssp;
			sstack[ssp].a = lrt;

			//sstack[ssp].c = sstack[ssp].b.pos;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };
			break;
		case 108://B->OB
			label -= 2;
			ntab3[label].fc = ntab3[label + 1].fc;
			ntab3[label].tc = merge(ntab3[label].tc, ntab3[label + 1].tc);
			label++;

			ssp = ssp - 2;
			lrt = action3[sstack[ssp].a][B];
			++ssp;
			sstack[ssp].a = lrt;

			//sstack[ssp].c = sstack[ssp].b.pos;

			sstack[ssp].b.sy1 = -1;
			sstack[ssp].b.pos = 0;

			//sstack[ssp].b = { -1, 0 };
			break;
		}		
		lrparse3();
	}

	if (lr<0 && ret == 0){
		//lr<0,�����������

		/*while ((buf2[jj].sy1 != douhao) && (buf2[jj].sy1 != fenhao) && (buf2[jj].sy1 != jinhao))
		{

		if (jj >= (ccount-1))
		return;
		jj++;
		}*/
		//iend = jj;


	erro:
		string er;
		//et = ;
		switch (lr){
		case -1:er = " \n\n"; break;
		case -4:er = "���ʽ�����ԣ���ͷ\n"; break;
		/*case -2:er = "���ʽ������+��ͷ\n\n"; break;
		case -3:er = "���ʽ������*��ͷ\n\n"; break;
		
		case -5:er = "���ʽֻ��һ���ֺţ�û����������\n\n"; break;
		case -6:er = "ȱ���룩ƥ��ģ�\n\n"; break;
		case -7:er = "�������ұ߲���Ϊ+\n\n"; break;
		case -8:er = "�������ұ߲���Ϊ*\n\n"; break;
		case -9:er = "С���ţ���֮��û���κ�����\n\n"; break;
		case -10:er = "�����������ұ�\n\n"; break;
		case -11:er = "��������������+\n\n"; break;
		case -12:er = "+�������*\n\n"; break;
		case -13:er = "+������֣�\n\n"; break;
		case -14:er = "���ʽ��+��β\n\n"; break;
		case -15:er = "*�������+\n\n"; break;
		case -16:er = "��������������*��\n\n"; break;
		case -17:er = "*������֣�\n\n"; break;
		case -18:er = "���ʽ��*��β\n\n"; break;
		case -19:er = "��������������ƥ�䣡\n\n"; break;
		case -20:er = "ȱ�ٷֺŻ���������ڱ��ʽ���ַ�" + finsBuf(jj - 1) + "�ĺ���" + ((finsBuf(jj) != " ") ? ("����" + finsBuf(jj) + "��ǰ��") : "") + "\n\n"; break;*/
		case -22:er = "�ȽϷ���rop����������ߣ�\n\n"; break;
		case -23:er = "and�����������\n\n"; break;
		case -24:er = "or�����������\n\n"; break;
		case -25:er = "�ȽϷ���" + finds(buf2[jj].sy1)+"û���������\n"; break;
		default:er = " \n\n"; break;
		}
		cout << "\n\nԴ�����е�" << subline << "�в������ʽ�д���   " + er + "";
		ret = 1;
		//ofstream out;

		out << "����" << er;

		/*if (jj >= (ccount - 1))
			return 0;*/
		//׼��������һ�����ʽ��
		/*ista = iend + 1;

		stsend();
		show2(ista, iend);

		out << endl;

		cout << endl;
		reset();
		jj = ista;

		lrparse3();*/

	}
	if (lr == acc&&ret == 0){
		//cout << "�������ʽ�����ɹ���\n" ;
		ret = 1;
		return 1;
		//iend = jj;

		//cout << "�����ɹ������Ϊ" << sstack[ssp].c << endl << endl;

		//out << "�����ɹ������Ϊ" << sstack[ssp].c << endl << endl;

		////׼��������һ�����ʽ��
		//ista = iend + 1;
		//stsend();
		//show2(ista, iend);
		//cout << endl;
		//out << endl;
		//reset();
		//if (jj >= (ccount - 1))
		//	return;
		//jj = ista;

	}
}


int analyze::test(int value){//�жϵ�ǰ�����ַ��ǳ������Ļ�����0�����򷵻�1���������ʽ���������ʽ��
	switch (value){
	case iden:case cons:case jia:case chen:
	case xiaol:case xiaor:
	case xiaodeng:case smaller:case dadeng:
	case bigger:case budeng:case equal:
	case not:case and:case or:
	case deng:return 1;
	default:return 0;
	}
}


int analyze::lrparse(){//�������ķ���
	
	/*if (stack[sp].a == 4){
		cout << "hh";
	}*/

	lr = action[stack[sp].a][conv(buf[ii])];
	
	if ((lr >= 0) && (lr < 18)){
		showZhan(lr);
		

		{
			
			jj = 0;
			/*if (ii == 13)
			cout << "h";*/
			//if (!((stack[sp].b.sy1 == dar) && (test(buf[ii].sy1)))){}
			if (test(buf[ii].sy1)){
				
				if (stack[sp].b.sy1 == s_while)
					sign = 2;
				else
				{
					if (stack[sp].b.sy1 == s_if)
						sign = 3;
					else
						sign = 1;
				}
				do{
					buf2[jj].pos = buf[ii].pos;
					buf2[jj].sy1 = buf[ii].sy1;
					buf2[jj].linecount = buf[ii].linecount;
					ii++;
					jj++;

				} while (test(buf[ii].sy1));
				buf2[jj].sy1 = fenhao;
				//jj = 0;
				if (sign == 1){//�������ʽ
					jj = 2;
					subline = buf[ii].linecount;
					reset2();
					ret = 0;
					lrparse2();
					ii--;
					buf[ii].sy1 = suanshu;
				}
				if ((sign == 2) || (sign == 3)){//�������ʽ����
					pointmark++;
					labelmark[pointmark].nxq1 = nxq;//����if��while����Ԫʽ���
					jj = 0;
					subline = buf2[0].linecount;
					reset2();
					ret = 0;
					lrparse3();
					labelmark[pointmark].tc1 = ntab3[label - 1].tc; //����if��while��ȷ������ָ����
					labelmark[pointmark].fc1 = ntab3[label - 1].fc;
					backpatch(labelmark[pointmark].tc1, nxq);
					ii--;
					buf[ii].sy1 = buer;
				}
				lr = action[stack[sp].a][conv(buf[ii])];
			}

		}
		stack[++sp].a = lr;
		stack[sp].b = buf[ii++];//
		/*if (ii > iend){
			lr = -20;
			goto erro;
		}*/
		stack[sp].c = -1;
		//showZhan();
		lrparse();
	}
	/*else*/ if ((lr > 100) && (lr < 107)){
		int lrt;
		/*string sss;*/
		switch (lr){
			int temm;
			//case 100://S'->B

			//	break;
		case 101://S->if e S else S
			
			showZhan(lr);
			sp = sp - 5;
			cout << "\n��S->if e S else S��Լ";
			//showZhan();
			fexp[labeltemp[pointtemp]].result = nxq;
			pointtemp--;
			pointmark--;//
			if (stack[sp - 1].b.sy1 == s_if){
				emit("j", downline, downline, 0);
				backpatch(labelmark[pointmark].fc1, nxq);
				pointtemp++;
				labeltemp[pointtemp] = nxq - 1;
			}
			
			if (stack[sp - 1].b.sy1 == s_while){
				emit("j", downline, downline, labelmark[pointmark].nxq1);
				backpatch(labelmark[pointmark].fc1, nxq);
			}

			lrt = action[stack[sp].a][S];
			++sp;
			stack[sp].a = lrt;

			stack[sp].b.sy1 =S;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;
			//showZhan(lrt);
			//stack[sp].b = { -1, 0 };

			break;
		case 102://S->while e S

			showZhan(lr);
			sp = sp - 3;
			cout << "\n��S->while e S��Լ";
			//showZhan();
			
			pointmark--;
			if (stack[sp - 1].b.sy1 == s_if){
				emit("j", downline, downline, 0);
				fexp[labelmark[pointmark].fc1].result = nxq;
				pointtemp++;
				labeltemp[pointtemp] = nxq - 1;
			}
			
			if (stack[sp - 1].b.sy1 == s_while){
				emit("j", downline, downline, labelmark[pointmark].nxq1);
				backpatch(labelmark[pointmark].fc1, nxq);
			}
			
			lrt = action[stack[sp].a][S];
			++sp;
			stack[sp].a = lrt;
			stack[sp].b.sy1 = S;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;
			//showZhan(lrt);
			//stack[sp].b = { -1, 0 };

			break;
		case 103://S->{L}

			showZhan(lr);
			sp = sp - 3;
			cout << "\n��S->{L}��Լ";
			//showZhan();
			
			if (stack[sp - 1].b.sy1 == s_if){
				emit("j", downline, downline, 0);
				backpatch(labelmark[pointmark].fc1, nxq);
				pointtemp++;
				labeltemp[pointtemp] = nxq - 1;
			}
			if (stack[sp - 1].b.sy1 == s_while){
				emit("j", downline, downline, labelmark[pointmark].nxq1);
				backpatch(labelmark[pointmark].fc1, nxq);
			}

			lrt = action[stack[sp].a][S];
			++sp;
			stack[sp].a = lrt;
			stack[sp].b.sy1 = S;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;
			//showZhan(lrt);
			//stack[sp].b = { -1, 0 };

			break;
		case 104://S->a;

			showZhan(lr);
			sp = sp - 2;
			cout << "\n��S->a;��Լ";
			//showZhan();

			if (stack[sp - 1].b.sy1 == s_if){
				emit("j", downline, downline, 0);
				backpatch(labelmark[pointmark].fc1, nxq);
				pointtemp++;
				labeltemp[pointtemp] = nxq - 1;
			}
			if (stack[sp - 1].b.sy1 == s_while){
				emit("j", downline, downline, labelmark[pointmark].nxq1);
				backpatch(labelmark[pointmark].fc1, nxq);
			}

			lrt = action[stack[sp].a][S];
			++sp;
			stack[sp].a = lrt;
			stack[sp].b.sy1 = S;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;
			//showZhan(lrt);
			//stack[sp].b = { -1, 0 };

			break;
		case 105://L->SL

			showZhan(lr);
			sp = sp - 2;
			cout << "\n��L->SL��Լ";
			//showZhan();

			lrt = action[stack[sp].a][L];
			++sp;
			stack[sp].a = lrt;
			stack[sp].b.sy1 = L;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;

			//stack[sp].b = { -1, 0 };
			//showZhan(lrt);
			break;
		case 106://L->S

			showZhan(lr);
			sp = sp - 1;
			cout << "\n��L->S��Լ";
			//showZhan();

			lrt = action[stack[sp].a][L];
			//showZhan(lrt);
			++sp;
			stack[sp].a = lrt;
			stack[sp].b.sy1 = L;//���ս��
			stack[sp].b.zhongjie = -2;
			stack[sp].b.pos = 0;
			
			//stack[sp].b = { -1, 0 };

			break;
		}
		lrparse();
	}

	if (lr<0 && ret2 == 0){
		//lr<0,�����������

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
		case -30:er = "û����elseƥ���if���\n"; break;
		case -31:er = "�����ԣ���ͷ\n\n"; break;
		case -32:er = "û����ifƥ���else���\n\n"; break;
		/*case -1:er = "���ʽ����\n\n"; break;
		case -2:er = "���ʽ������+��ͷ\n\n"; break;
		case -3:er = "���ʽ������*��ͷ\n\n"; break;
		case -4:er = "���ʽ�����ԣ���ͷ\n\n"; break;
		case -5:er = "���ʽֻ��һ���ֺţ�û����������\n\n"; break;
		case -6:er = "ȱ���룩ƥ��ģ�\n\n"; break;
		case -7:er = "�������ұ߲���Ϊ+\n\n"; break;
		case -8:er = "�������ұ߲���Ϊ*\n\n"; break;
		case -9:er = "С���ţ���֮��û���κ�����\n\n"; break;
		case -10:er = "�����������ұ�\n\n"; break;
		case -11:er = "��������������+\n\n"; break;
		case -12:er = "+�������*\n\n"; break;
		case -13:er = "+������֣�\n\n"; break;
		case -14:er = "���ʽ��+��β\n\n"; break;
		case -15:er = "*�������+\n\n"; break;
		case -16:er = "��������������*��\n\n"; break;
		case -17:er = "*������֣�\n\n"; break;
		case -18:er = "���ʽ��*��β\n\n"; break;
		case -19:er = "��������������ƥ�䣡\n\n"; break;
		case -20:er = "ȱ�ٷֺŻ���������ڱ��ʽ���ַ�" + finsBuf(ii - 1) + "�ĺ���" + ((finsBuf(ii) != " ") ? ("����" + finsBuf(ii) + "��ǰ��") : "") + "\n\n"; break;*/
		/*default:er = "δ֪�Ĵ���\n\n"; break;*/
		}
		cout << "\n\nԴ�����е�" << buf[ii-1].linecount+1<< "�г���������\t" + er + "";
		ret2 = 1;
		//ofstream out;

		out << "����" << er;

		/*if (ii >= (ccount - 1))
			return 0;*/
		//׼��������һ�����ʽ��
		/*ista = iend + 1;

		stsend();
		show2(ista, iend);

		out << endl;

		cout << endl;
		reset();
		ii = ista;

		lrparse();*/

	}
	if (lr == acc&&ret2 == 0){
		//cout << "�����������ɹ���\n";
		showZhan(lr);
		ret2 = 1;
		return 1;
		//iend = ii;

		//cout << "�����ɹ������Ϊ" << stack[sp].c << endl << endl;

		//out << "�����ɹ������Ϊ" << stack[sp].c << endl << endl;

		////׼��������һ�����ʽ��
		//ista = iend + 1;
		//stsend();
		//show2(ista, iend);
		//cout << endl;
		//out << endl;
		//reset();
		//if (ii >= (ccount - 1))
		//	return;
		//ii = ista;

	}
}


void analyze::show4exp(){//�����Ԫʽ
	//int k = 100;
	//for (k; k < nxq-1; k++){
	//	cout << "\n" << k << "\t��" << fexp[k].op << "	,	";
	//	if (fexp[k].arg1.sy1 == iden)
	//		cout << tab_ch[fexp[k].arg1.pos] << "	,	";
	//	else{
	//		if (fexp[k].arg1.zhongjie == -2)//���ս��
	//			cout << "T" << fexp[k].arg1.pos << "	,	";
	//		else{
	//			if (fexp[k].arg1.sy1 == cons)
	//				cout << fexp[k].arg1.pos << "	,	";
	//			else
	//				cout << "_	,	";
	//		}
	//	}

	//	if (fexp[k].arg2.sy1 == iden)
	//		cout << tab_ch[fexp[k].arg2.pos] << "	,	";
	//	else{
	//		if (fexp[k].arg2.zhongjie == -2)
	//			cout << "T" << fexp[k].arg2.pos << "	,	";
	//		else{
	//			if (fexp[k].arg2.sy1 == cons)
	//				cout << fexp[k].arg2.pos << "	,	";
	//			else
	//				cout << "_	,	";
	//		}
	//	}

	//	if (fexp[k].op[0] != 'j'){
	//		if (fexp[k].result>=100)
	//			cout << "T" << fexp[k].result - 100 << "	)";
	//		else
	//			cout << tab_ch[fexp[k].result] <<"	)";
	//	}
	//	else
	//		cout << fexp[k].result << "	)";
	//}
	//cout << "\n" << k << "\n" ;
	cout << "\n���Դ������м���루��Ԫʽ�����£�";
	int k = 100;
	for (k; k < nxq - 1; k++){
		cout << "\n" << k << "\t��" << fexp[k].op << "	,	";
		if (fexp[k].arg1.zhongjie == -2)//���ս��
			cout << "T" << fexp[k].arg1.pos << "	,	";
		else{
			if (fexp[k].arg1.sy1 == iden)
				cout << tab_ch[fexp[k].arg1.pos] << "	,	";			
			else{
				if (fexp[k].arg1.sy1 == cons)
					cout << fexp[k].arg1.pos << "	,	";
				else
					cout << "_	,	";
			}
		}


		if (fexp[k].arg2.zhongjie == -2)
			cout << "T" << fexp[k].arg2.pos << "	,	";
		else{
			if (fexp[k].arg2.sy1 == iden)
				cout << tab_ch[fexp[k].arg2.pos] << "	,	";
			
			else{
				if (fexp[k].arg2.sy1 == cons)
					cout << fexp[k].arg2.pos << "	,	";
				else
					cout << "_	,	";
			}
		}

		if (fexp[k].op[0] != 'j'){
			if (fexp[k].result >= 100)
				cout << "T" << fexp[k].result - 100 << "	)";
			else
				cout << tab_ch[fexp[k].result] << "	)";
		}
		else
			cout << fexp[k].result << "	)";
	}
	cout << "\n" << k << "\n";
}

analyze::~analyze()
{
	in.close();
	out.close();
}
