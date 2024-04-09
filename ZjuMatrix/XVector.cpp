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

//---------------------------------------------------------------------------
//  函数名(Function name): max(XDoubleVector v)
//  描述: 最大值
/// Description: maximum element
// -------------------------------------------------------------------------
double ZjuMatrix::max(XDoubleVector v)
{
	int nSize = v.size();
	if (nSize <= 1)
		return 0.0;
	double dMax = v.Vi(1);
	for (int i = 2; i <= nSize; i++)
	{
		if (dMax < v.Vi(i))
			dMax = v.Vi(i);
	}
	return dMax;
}

//---------------------------------------------------------------------------
//  函数名(Function name): min(XDoubleVector v)
//  描述: 最小值
/// Description: minimum element
// -------------------------------------------------------------------------
double ZjuMatrix::min(XDoubleVector v)
{
	int nSize = v.size();
	if (nSize <= 1)
		return 0.0;
	double dMin = v.Vi(1);
	for (int i = 2; i <= nSize; i++)
	{
		if (dMin > v.Vi(i))
			dMin = v.Vi(i);
	}
	return dMin;
}

//---------------------------------------------------------------------------
//  函数名(Function name): sum2(XDoubleVector v)
//  描述: 平方和
/// Description: summation of squares
// -------------------------------------------------------------------------
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
