//==================================================================================
// �ļ���(File name): XVector.cpp
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.24
// ---------------------------------------------------------------------------------
// ��������XVector�����Ϊ������һЩ������
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
