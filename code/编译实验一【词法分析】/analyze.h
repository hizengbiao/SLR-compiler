#pragma once
#include "defineAndStruct.h"
#include <stdio.h>
#include <sstream>
class analyze
{

	string line;		 //��ǰɨ����
	int i;			 //��ǰɨ���ַ�λ��
	char ch;		//��ǰɨ���ַ�
	int ccount;		//��ǰɨ�赽�Ĵ���
	int po_ch;		//��ǰ�Ǽ��˶��ٸ���ʶ��
	//int po_nu = 0;		//��ǰ�Ǽ��˶��ٸ�����
	int nowline;//��ǰɨ����Ǵ����еĵڼ���
	int count_err; //��ǰɨ����Ĵ�����

	char errs[60];	//���������Ϣ
	int errsLine[60];//ÿ��������Դ�����е��к�
	string tab_ch[1000];//��ʶ���ǼǱ�
	//int tab_nu[100];

	ifstream in;//���������ı�
	ofstream out2;//���ɴ��������ı�
	ofstream out;//����������������ı�
	int ista;//�﷨�����ı��ʽ����ʼλ��
	int iend;//�﷨�����ı��ʽ�Ľ���λ��
	int sp;//ջ��ָ��stack�±�
	int ssp;//ջ��ָ��sstack�±�
	int ii;//��ǰҪ�����ķ����ڴʷ��������(buf��)�е�λ��
	int lr;//�����������ƽ����ǹ�Լ���ǳ���
	int nxq;//��һ����Ԫʽ�ĵ�ַ
	ntab33 ntab3[200];//�洢ÿ���������ʽ����ɵ�������Ԫʽ�ĵ�ַ
	int label;//ntab3���±�
	aa downline;//�»���
	aa Et;//����ʽ��
	int sign; //sign=1�������������ʽ��䣬sign=2������ѭ����䣬sign=3�����ǿ������
	int newt;//�²�������ʱ������������

	aa buf[3000];//�ʷ�����������ʷ������Ľ��
	aa buf2[300];//���������򲼶����ʽ�������ַ���
	stackType stack[100];//��������﷨����ջ
	stackType sstack[100];//�����򲼶����ʽ�﷨����ջ
	int jj;//��ǰҪ�����ķ�����buf2���е�λ��
	fourexp fexp[200];//��Ԫʽ�洢��
	ll labelmark[10];//����if��whileһ��ͷ���Ǹ�״̬
	int labeltemp[10];//����if��else�м��Ǹ�������״̬
	int pointmark;//labelmark����ĵ�ǰ�±�
	int pointtemp;//labeltemp����ĵ�ǰ�±�
	int ret;//�������ʽ���������ʽ�����ӳ����˳����
	int ret2;//��������˳����
	int subline;//Դ����Ĵ����к�
public:
	analyze();//��ʼ����������
	void stCifa();//��ʼ���дʷ�����
	void stYufa();//��ʼ�����﷨����
	int findd(string m);//���ұ�ʶ��m�ڱ�ʶ���ǼǱ��е�λ��
	void identifier();//ʶ���ַ����Ǳ�ʶ�����Ǳ�����
	void number();//ʶ������
	void backch();//����һ���ַ�
	void readch();//��ȡһ���ַ�
	void scanOneLine();//�ʷ�����һ��
	void show();//����ʷ������Ľ��
	void showiden(); //�����ʶ����
	void shownum();	//���������
	void showZhuangtai();//���״̬ջ
	void showFuhao();//�������ջ
	void showYuyi();//�������ջ
	void showYuyi(int yu);//�������ջ
	void showZhan(int lrr);//��ʾ����ջ����Լ���ƽ�����
	string changeStackB(int sy,int zho);//�����ֱ����ط���Ӧ��������ţ���ʮ��������ʶ�Ƿ��Ƿ��ս��
	string finsBuf(int q);//����buf���±귵�ض�Ӧ�ķ���
	void reset();//�����﷨����ջ
	void reset2();//�����﷨����ջ
	void show2(int st, int en);//����ʷ���������д�λ��ista��iend��Ԫ��
	string finds(int tc);//�����ֱ���뷵�ط���
	void stsend();//�������ʱ���㵱ǰ���ʽ�Ŀ�ʼλ�úͽ���λ��
	void show3(/*int c*/);//������㵽��ǰ��һ���ļ�����
	int conv(aa tem);//����������ŷ����ڳ������LR�������еĺ������
	int conv2(aa tem);//����������ŷ������������ʽLR�������еĺ������
	int conv3(aa tem);//����������ŷ����ڲ������ʽLR�������еĺ������
	int test(int value);//�жϵ�ǰ�����ַ��ǳ������Ļ�����0�����򷵻�1���������ʽ���������ʽ��
	int newtemp();//����һ���µ���ʱ����
	int lrparse();//��������﷨����
	int lrparse2();//�������ʽ�ķ���
	int lrparse3();//�������ʽ�ķ���
	int emit(string op1, aa arg1, aa arg2, int result1);//����һ����Ԫʽ
	int merge(int p1, int p2);//��������
	void show4exp();//�����Ԫʽ
	void backpatch(int p, int t);//�����
	
	~analyze();
};






