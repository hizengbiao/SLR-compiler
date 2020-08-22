#pragma once
#include "suanshufenxi.h"
#define iWantDefault2

suanshufenxi::suanshufenxi()
{
	i = -1;			 //��ǰɨ���ַ�λ��
	ch = ' ';		//��ǰɨ���ַ�
	ccount = 0;		//��ǰɨ�赽�Ĵ���
	po_ch = 0;		//��ǰ�Ǽ��˶��ٸ���ʶ��
	//int po_nu = 0;		//��ǰ�Ǽ��˶��ٸ�����
	nowline = 0;//��ǰɨ����Ǵ����еĵڼ���
	count_err = 0; //��ǰɨ����Ĵ�����

	ista = 0;//��ʼλ��
	iend = ista;//����λ��
	sp = 0;//ջ��ָ��
	ii = 0;//��ǰҪ�����ķ����ڴʷ���������е�λ��

	system("md E:\\hizengbiao2");//����һ���ļ��� 
	system("cls");
#ifdef iWantDefault2
	out2.open("E:\\hizengbiao2\\a.txt");
	if (!out2)
	{
		cerr << "������ļ���ʧ�ܣ�";
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
		cerr << "�������ļ���ʧ�ܣ�";
	}
	out.open("E:\\hizengbiao2\\b.txt");
	if (!out)
	{
		cerr << "������ļ���ʧ�ܣ�";
	}
}

void suanshufenxi::stCifa(){//��ʼ���дʷ�����
	nowline = 0;
	while (getline(in, line))
	{
		nowline++;
		scanOneLine();//�ʷ�����Դ�����һ��

	}

}

void suanshufenxi::stYufa(){//��ʼ�����﷨����

	cout << "�﷨����������£�\n\n";
	out << "�﷨����������£�\n\n";
	ista = 0;//��ʼλ��
	stsend();//�������ʱ���㵱ǰ���ʽ�Ŀ�ʼλ�úͽ���λ��
	show2(ista, iend);//����ʷ���������д�λ��ista��iend��Ԫ��
	out << endl;
	cout << endl;
	ii = 0;
	reset();//�����﷨����ջ
	lrparse();//�﷨����
}

int suanshufenxi::findd(string m){//���ұ�ʶ��m�ڱ�ʶ���ǼǱ��е�λ��
	for (int q = 0; q < po_ch; q++){
		if (m == tab_ch[q])
			return q;
	}
	return -1;
}


void suanshufenxi::identifier(){//ʶ���ַ����Ǳ�ʶ�����Ǳ�����

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
			tab_ch[po_ch] = spelling;
			po_ch++;
		}
		else
			buf[ccount].pos = j;

	}
	ccount++;

}


void suanshufenxi::number(){//ʶ������
	//
	string spelling = "";
	do{
		spelling.append(&ch, 1);
		readch();
	} while ((ch >= '0') && (ch <= '9'));
	backch();
	buf[ccount].sy1 = cons;
	buf[ccount].pos = atoi(spelling.c_str());//���ֵ�ֱֵ�Ӹ�pos���Ͳ��Ǽ���
	ccount++;
}

void suanshufenxi::backch(){//����һ���ַ�
	ch = line[--i];
}

void suanshufenxi::readch(){//��ȡһ���ַ�
	ch = line[++i];
}

void suanshufenxi::scanOneLine(){//�ʷ�����һ��
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

void suanshufenxi::show(){//����ʷ������Ľ��
	cout << "�ʷ�����ʶ�����£��ֱ���룬����ֵ����";
	for (int q = 0; q < ccount; q++){
		if (buf[q].sy1 >= 0 && buf[q].sy1 < nOFkeepwords){//������
			cout << "\n(" << buf[q].sy1 << ",\"" << kw[buf[q].sy1].name << "\")";
		}
		else if (buf[q].sy1 == 20){//��ʶ��
			cout << "\n(" << buf[q].sy1 << ",\"" << tab_ch[buf[q].pos] << "\")";
		}
		else if (buf[q].sy1 == 21){//����
			cout << "\n(" << buf[q].sy1 << ",\"" << buf[q].pos << "\")";
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


string suanshufenxi::finsBuf(int q){//����buf���±귵�ض�Ӧ�ķ���

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

void suanshufenxi::reset(){//�����﷨����ջ
	sp = 0;
	sstack[sp].a = 0;

	sstack[sp].b.sy1 = jinhao;
	sstack[sp].b.pos = 0;

	//sstack[sp].b = { jinhao, 0 };
	sstack[sp].c = -1;
}


void suanshufenxi::show2(int st, int en){//����ʷ���������д�λ��ista��iend��Ԫ��

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



string suanshufenxi::finds(int tc){//�����ֱ���뷵�ط���
	switch (tc){
	case jia:return "+";
	case chen:return "*";
	case xiaol:return "(";
	case xiaor:return ")";
	default:return "undefine";
	}
}

void suanshufenxi::stsend(){//�������ʱ���㵱ǰ���ʽ�Ŀ�ʼλ�úͽ���λ��


	iend = ista;
	while ((buf[iend].sy1 != douhao) && (buf[iend].sy1 != fenhao) && (buf[iend].sy1 != jinhao) && (iend<ccount - 1))
	{

		iend++;
	}
}

void suanshufenxi::show3(int c){//������㵽��ǰ��һ���ļ�����

	int sl = sp + 1;
	bb *sss = new bb[sl];
	for (int p = 0; p <sl; p++){
		if (p == 0)
			sss[p].b = "=";
		else if (sstack[p].b.sy1 == -1){//���ս��
			sss[p].a = sstack[p].c;
			sss[p].b = "-";
		}
		else if (sstack[p].b.sy1 == kongzi){//����
			sss[p].b = "kong";
		}
		else{//�ս��
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
int suanshufenxi::conv(int c, aa tem){//����������ŷ�����LR�������еĺ������
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


void suanshufenxi::lrparse(){//�﷨����

	/*if (ii == (ccount - 1))
	return;*/
	lr = action22[sstack[sp].a][conv(sstack[sp].a, buf[ii])];
	if ((lr >= 0) && (lr < 18)){
		if (lr == 11){
			sstack[++sp].a = lr;

			sstack[sp].b.sy1 = kongzi;
			sstack[sp].b.pos = 0;

			//sstack[sp].b = { kongzi, 0 };//b���ڿ���
			sstack[sp].c = -1;
			lrparse();
		}
		else if (lr == 8){
			sstack[++sp].a = lr;


			sstack[sp].b.sy1 = kongzi;
			sstack[sp].b.pos = 0;


			//sstack[sp].b = { kongzi, 0 };//b���ڿ���
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
				if (buf[ii].sy1 != xiaor)//�����С������ֻ��һ��������������Ͳ����
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

			cout << "�����ɹ������Ϊ" << sstack[sp].c << endl << endl;

			out << "�����ɹ������Ϊ" << sstack[sp].c << endl << endl;

			//׼��������һ�����ʽ��
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
		case -1:er = "���ʽ����\n\n"; break;
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
		case -20:er = "ȱ�ٷֺŻ���������ڱ��ʽ���ַ�" + finsBuf(ii - 1) + "�ĺ���" + ((finsBuf(ii) != " ") ? ("����" + finsBuf(ii) + "��ǰ��") : "") + "\n\n"; break;
		default:er = "δ֪�Ĵ���\n\n"; break;
		}

		cout << "����" + er;
		//ofstream out;

		out << "����" << er;

		if (ii >= (ccount - 1))
			return;
		//׼��������һ�����ʽ��
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
