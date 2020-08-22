//最后编辑时间：2016-6-23 9:45
//
//主要更新说明：
//Ver 1.0:在平时上机代码的基础上将算术表达式的文法改成课本上的文法并解决了由此产生的一系列新问题
//Ver 2.0:可以识别程序语句、布尔表达式、算术表达式，可以正确生成四元式
//Ver 3.0:还缺分析栈的输出
//Ver 4.0:暂时ok
//Ver 5.0:plus
//Ver 6.0:把程序改为只有当下一步是移进时才处理布尔表达式和算术表达式，
//解决了当一个分支/循环语句块后面是算术表达式时会先处理完算术表达式才回来处理分支/循环语句块的最后一个跳转相关的操作的问题

//实验题目：编译课程设计题目二（程序的小型编译器）
//江苏大学计算机学院
//班级：计算机1302
//姓名：曾彪	
//学号：3130602050
//源代码仅供学习与参考，未经本人允许请勿作他用，转载请注明出处
//联系方式：982003834@qq.com，hizengbiao@vip.qq.com
//以上内容请勿删除或修改


#pragma once
#include "analyze.h"
#include "suanshufenxi.h"

int main(){
	
	analyze an;

	an.stCifa();//开始进行词法分析
	an.show();//输出词法分析的结果
	cout << "\n\n\n";

	an.showiden();//输出标识符表
	cout << "\n\n\n";

	an.shownum();//输出常数表
	cout << "\n\n\n";

	cout << "分析栈如下：\n（状态栈      符号栈       动作）";

	an.stYufa();//开始进行语法分析

	an.show4exp();//输出中间代码


	//suanshufenxi bn;//分析算术表达式的，平时的上机实验2
	//bn.stCifa();//开始进行词法分析
	//bn.stYufa();//开始进行语法分析

	//system("explorer / select, E:\\hizengbiao2");
	//system("explorer / select, E:\\hizengbiao2\\a.txt");
	//system("explorer / select, E:\\hizengbiao2\\b.txt");
	//system("explorer / select, E:\\hizengbiao2\\c.txt");
	
	return 0;
}


//测试用例1，测试if,else控制语句
//if (x > y){
//	if (a){
//		m = m + 1;
//	}
//	else{
//		if (b){
//			m = m * 2;
//		}
//		else{
//			m = 3;
//		}
//		
//	}
//}
//else{
//	x = y;
//}


//测试用例2，测试while循环语句
//while (a < b){
//	while (x>y){
//		c = 9;
//	}
//	y = 4;
//	z = 45;
//}



//测试用例3，测试布尔语句
//if ((c<a) && b || (c != 8)){
//			m = m + 1;
//}
//else
//{
//	n = 45;
//}


//测试用例4，测试算术表达式语句

//if (a){
//	b = (c + 2)*(d + 4 + (e + 6 * f));
//}
//else{
//	g=((hd + e) * 3 + 42;
//}

//测试用例5，综合测试
//while (a || b){
//	if (x < y){
//		while (c&&d){
//			k = k + 1;
//		}
//	}
//	else{
//		if (m < n&&k < q){
//			m = k;
//		}
//		else{
//			while (m != k){
//				m = m + 1;
//			}
//		}
//	}
//}

//测试用例6，布尔表达式错误测试
//if (<=9){
//			m = m + 1;
//}
//else
//{
//	n = 45;
//}

//测试用例7，算术表达式错误测试1
//if (a<=9){
//			m=1 + 2 + (*3 + 4);
//}
//else
//{
//	n = 45;
//}

//测试用例8，算术表达式错误测试2
//if (a<=9){
//			m = m ++ 1;
//}
//else
//{
//	 n=7 + () + 3;
//}

//测试用例9，程序语句错误测试



//if (a<=9){
//			m = m +1;
//}
//else
//{
//	else
//	{
//		n = 45;
//	}
//}








//其他：
//if (a < b){
//	x = 3;
//}
//else{ y = 3; }

//4.5
//if (x > y){
//	if (a&&b){
//		m = m + 1;
//	}
//	else{
//		m = m - 1;
//	}
//}
//else{
//	x = y;
//}

//4.9
//


