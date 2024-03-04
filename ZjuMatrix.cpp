//=======================================================================
// 文件名(File name): ZjuMatrix.cpp
// 作者(Author):      郑诗澄
// 修改(Reviser):     徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.03.13
// ----------------------------------------------------------------------
// 描述：实现ZjuMatrix.lib的与矩阵运算相关的函数
// Description: implement some operation for matrix in ZjuMatrix.lib
//=======================================================================

#include "ZjuMatrix.h"

//---------------------------------------------------------------------------
// 函数名(Function name): BtDB
// 描述: 实现形如K = tranpose(B) * D * B的矩阵乘法，这里矩阵D是对称矩阵。
// Description: implement the product like K = tranpose(B) * D * B, where D is
//              symmetric. 
// -------------------------------------------------------------------------
void ZjuMatrix::BtDB(XDoubleMatrix& mB, XSymDoubleMatrix& mD, XSymDoubleMatrix& mK)
{
	int nRowB = mB.rowSize();
	int nColB = mB.colSize();
	int nSizeD = mD.size();

	if (nRowB != nSizeD)
	{
		throw("矩阵维数不匹配，无法进行运算(size of matrices do not match for operation)!");
		return;
	}

	mK.resetSize(nColB);
	for(int i = 1; i <= nColB; i++)
		for(int j = 1; j <= i; j++)
			for(int r = 1; r <= nSizeD; r++)
				for (int s = 1; s <= nSizeD; s++)
					mK(i, j) = mK.Aij(i, j) + mB.Aij(r, i) * mD.Aij(r, s) * mB.Aij(s, j);
}

