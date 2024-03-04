//==================================================================================
// 文件名(File name): XVector.cpp
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.24
// ---------------------------------------------------------------------------------
// 描述：以XVector类对象为参数的一些函数。
// Description: Implement some functions with parameters of objects of XVector.
//==================================================================================
#include "XVector.h"

using namespace ZjuMatrix;

double ZjuMatrix::sum2(XDoubleVector v)
{
	double dSum2 = 0.0;
	int nSize = v.size();
	for(int i=1; i<=nSize; i++)
	{
		double dVi = v.Vi(i);
		dSum2 += dVi * dVi;
	}
	return dSum2;
}
