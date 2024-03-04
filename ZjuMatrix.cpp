//=======================================================================
// �ļ���(File name): ZjuMatrix.cpp
// ����(Author):      ֣ʫ��
// �޸�(Reviser):     ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.03.13
// ----------------------------------------------------------------------
// ������ʵ��ZjuMatrix.lib�������������صĺ���
// Description: implement some operation for matrix in ZjuMatrix.lib
//=======================================================================

#include "ZjuMatrix.h"

//---------------------------------------------------------------------------
// ������(Function name): BtDB
// ����: ʵ������K = tranpose(B) * D * B�ľ���˷����������D�ǶԳƾ���
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
		throw("����ά����ƥ�䣬�޷���������(size of matrices do not match for operation)!");
		return;
	}

	mK.resetSize(nColB);
	for(int i = 1; i <= nColB; i++)
		for(int j = 1; j <= i; j++)
			for(int r = 1; r <= nSizeD; r++)
				for (int s = 1; s <= nSizeD; s++)
					mK(i, j) = mK.Aij(i, j) + mB.Aij(r, i) * mD.Aij(r, s) * mB.Aij(s, j);
}

