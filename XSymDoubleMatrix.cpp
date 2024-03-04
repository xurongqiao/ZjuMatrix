//============================================================================
// 文件名(File name): XSymDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.14
// ---------------------------------------------------------------------------
// 描述：实现一个对称矩阵类，用于双精度实对称矩阵的操作。
// Description: Implement a class for symmetric matrix of double.
// 注意事项：1. 矩阵的行号和列号从1开始，而不是从0开始
//           2. 矩阵只保存下三角部分，按行存储，从对角元素开始，保存顺序如下
//               1: [1
//               2: [3   2
//               3: [6   5   4
//              ... [ ... ... ...
//               n: [ ... ... ... n(n-1)/2+1]
// Notice: 1. the row and column number count from 1 not 0
//         2. only the low triangle part of the matrix is saved in rows,
//             starting with diagonal elements as shown 
//               1: [1
//               2: [3   2
//               3: [6   5   4
//              ... [ ... ... ...
//               n: [ ... ... ... n(n-1)/2+1]
//============================================================================

#include "XSymDoubleMatrix.h"

using namespace ZjuMatrix;

XSymDoubleMatrix::XSymDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

XSymDoubleMatrix::XSymDoubleMatrix(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
}

XSymDoubleMatrix::XSymDoubleMatrix(int nSize, double* pdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize * (nSize + 1) / 2; i++)
		m_vdEntry(i) = pdEntry[i - 1];
}

XSymDoubleMatrix::XSymDoubleMatrix(int nSize, XDoubleVector& vdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize * (nSize + 1) / 2; i++)
		m_vdEntry(i) = vdEntry.Vi(i);
}

XSymDoubleMatrix::XSymDoubleMatrix(XSymDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry = m.m_vdEntry;
}

XSymDoubleMatrix& XSymDoubleMatrix::operator=(const XSymDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry.resetSize(m_nRow * (m_nRow + 1) / 2);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

XSymDoubleMatrix& XSymDoubleMatrix::operator=(const XSquareDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry.resetSize(m_nRow * (m_nRow + 1) / 2);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

XSymDoubleMatrix& XSymDoubleMatrix::operator=(const XDoubleMatrix& m)
{
	int nSize;
	int nRow = m.rowSize();
	int nCol = m.colSize();
	nSize = nRow < nCol ? nRow : nCol;
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

XSymDoubleMatrix::~XSymDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

void XSymDoubleMatrix::rowExchange(int iRow, int jRow)
{
	// 对称矩阵交换两行，必须同时交换对应的两列，以确保对称性。
	// For a symmetric matrix exchanges two rows, two corresponding 
	//  columns must be exchanged simultaneously to ensure the symmetry
	exchange(iRow, jRow);
}

void XSymDoubleMatrix::colExchange(int iCol, int jCol)
{
	// 对称矩阵交换两列，必须同时交换对应的两行，以确保对称性。
	// For a symmetric matrix exchanges two columns, two corresponding 
	//  rows must be exchanged simultaneously to ensure the symmetry
	exchange(iCol, jCol);
}

void XSymDoubleMatrix::exchange(int i, int j)
{
	// 交换规则：相同符号表示的元素相互交换，如下图所示
	// exchange rule: elements represented by the same symbol 
	// are swapped with each other, as shown in the following
	//    [                                               ]
	//    [                                               ]
	//  i [ A1  A2  ... (i,i)                             ]
	//    [               B1                              ]
	//    [               B2                              ]
	//    [               ...                             ]
	//  j [ A1  A2  ... (j,i) B1 B2 ... (j,j)             ]
	//    [               C1             C1               ]  
	//    [               C2             C2               ]
	//    [               ...            ...              ]
	//                     i              j       
	int nSize = size();
	int iRC = i < j ? i : j;
	int jRC = i > j ? i : j;
	for (int k = 1; k <= iRC - 1; k++)
	{
		double dTemp = Aij(iRC, k);
		(*this)(iRC, k) = Aij(jRC, k);
		(*this)(jRC, k) = dTemp;
	}
	for (int k = jRC + 1; k <= nSize; k++)
	{
		double dTemp = Aij(k, iRC);
		(*this)(k, iRC) = Aij(k, jRC);
		(*this)(k, jRC) = dTemp;
	}
	for (int k = iRC + 1; k <= jRC - 1; k++)
	{
		double dTemp = Aij(k,iRC);
		(*this)(k,iRC) = Aij(jRC, k);
		(*this)(jRC, k) = dTemp;
	}
	double dTemp = Aij(iRC, iRC);
	(*this)(iRC, iRC) = Aij(jRC, jRC);
	(*this)(jRC, jRC) = dTemp;
}

void XSymDoubleMatrix::resetSize(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
}

void XSymDoubleMatrix::eye(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize; i++)
		(*this)(i, i) = 1.0;
}

void XSymDoubleMatrix::random(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for(int i=1; i<=nSize*(nSize+1)/2; i++)
		m_vdEntry(i) = double(rand() % 100000) / 100000.0;
}

double& XSymDoubleMatrix::operator()(int iRow, int jCol)
{
	if (iRow <= 0 || jCol <= 0 || iRow > m_nRow || jCol > m_nCol)
	{
		throw("矩阵元素的行号或列号超出了范围(The index of entry exceed the size)!");
		return m_vdEntry(1);
	}
	else
	{
		int i = iRow > jCol ? iRow : jCol;
		int j = iRow < jCol ? iRow : jCol;
		int k = i * (i - 1) / 2 + 1 + (i - j);
		return m_vdEntry(k);
	}
}

double XSymDoubleMatrix::Aij(int iRow, int jCol) const
{
	if (iRow <= 0 || jCol <= 0 || iRow > m_nRow || jCol > m_nCol)
	{
		throw("矩阵元素的行号或列号超出了范围(The index of entry exceed the size)!");
		return 0.0;
	}
	else
	{
		int i = iRow > jCol ? iRow : jCol;
		int j = iRow < jCol ? iRow : jCol;
		int k = i * (i - 1) / 2 + 1 + (i - j);
		return m_vdEntry.Vi(k);
	}
}

double XSymDoubleMatrix::maxOffDiagonalPos(int& iRow, int& jCol)
{
	double dMax = 0.0;
	int nSize = size();
	for(int i = 1; i <= nSize; i++)
		for (int j = i + 1; j <= nSize; j++)
		{
			double absAij = fabs(Aij(i, j));
			if ( absAij > dMax)
			{
				iRow = i;
				jCol = j;
				dMax = absAij;
			}
		}
	return dMax;
}

void XSymDoubleMatrix::pap(int i, int j, double dCosine, double dSine)
{
	int m = i;
	int n = j;
	i = m < n ? m : n;
	j = m > n ? m : n;

	double c2 = dCosine * dCosine;
	double s2 = dSine * dSine;
	double cs = dCosine * dSine;
	double Cii = Aij(i, i) * c2 + Aij(j, j) * s2 + 2 * Aij(i, j) * cs;
	double Cjj = Aij(i, i) * s2 + Aij(j, j) * c2 - 2 * Aij(i, j) * cs;
	double Cij = (Aij(j, j) - Aij(i, i)) * cs + Aij(i, j) * (c2 - s2);

	XDoubleVector Cik, Cjk, Cki, Ckj;
	int nSize = size();
	Cik.resetSize(i - 1);
	Cki.resetSize(nSize - i);
	Cjk.resetSize(j - 1);
	Ckj.resetSize(nSize - j);
	for (int k = 1; k <= i - 1; k++)
	{
		if (k == j)
			continue;
		Cik(k) = Aij(i, k) * dCosine + Aij(j, k) * dSine;
	}
	for (int k = i + 1; k <= nSize; k++)
	{
		if (k == j)
			continue;
		Cki(k - i) = Aij(k, i) * dCosine + Aij(k, j) * dSine;
	}
	for (int k = 1; k <= j - 1; k++)
	{
		if (k == i)
			continue;
		Cjk(k) = Aij(j, k) * dCosine - Aij(i, k) * dSine;
	}
	for (int k = j + 1; k <= nSize; k++)
	{
		if (k == i)
			continue;
		Ckj(k - j) = Aij(k, j) * dCosine - Aij(k, i) * dSine;
	}

	for (int k = 1; k <= i - 1; k++)
		(*this)(i, k) = Cik(k);
	for (int k = i + 1; k <= nSize; k++)
		(*this)(k, i) = Cki(k - i);
	for (int k = 1; k <= j - 1; k++)
		(*this)(j, k) = Cjk(k);
	for (int k = j + 1; k <= nSize; k++)
		(*this)(k, j) = Ckj(k - j);

	(*this)(i, i) = Cii;
	(*this)(j, j) = Cjj;
	(*this)(i, j) = Cij;
}

double XSymDoubleMatrix::pap(int i, int j)
{
	int m = i;
	int n = j;
	i = m < n ? m : n;
	j = m > n ? m : n;

	double d = (Aij(i, i) - Aij(j, j)) / 2 / Aij(i, j);
	double t = 1 / (fabs(d) + sqrt(1 + d * d));
	if (d < 0)
		t = -t;
	double dCosine = 1 / sqrt(1 + t * t);
	double dSine = t * dCosine;

	double Cii = Aij(i, i) + Aij(i, j) * t;
	double Cjj = Aij(j, j) - Aij(i, j) * t;

	XDoubleVector Cik, Cjk, Cki, Ckj;
	int nSize = size();
	Cik.resetSize(i - 1);
	Cki.resetSize(nSize - i);
	Cjk.resetSize(j - 1);
	Ckj.resetSize(nSize - j);
	for (int k = 1; k <= i - 1; k++)
	{
		if (k == j)
			continue;
		Cik(k) = Aij(i, k) * dCosine + Aij(j, k) * dSine;
	}
	for (int k = i + 1; k <= nSize; k++)
	{
		if (k == j)
			continue;
		Cki(k - i) = Aij(k, i) * dCosine + Aij(k, j) * dSine;
	}
	for (int k = 1; k <= j - 1; k++)
	{
		if (k == i)
			continue;
		Cjk(k) = Aij(j, k) * dCosine - Aij(i, k) * dSine;
	}
	for (int k = j + 1; k <= nSize; k++)
	{
		if (k == i)
			continue;
		Ckj(k - j) = Aij(k, j) * dCosine - Aij(k, i) * dSine;
	}

	for (int k = 1; k <= i - 1; k++)
		(*this)(i, k) = Cik(k);
	for (int k = i + 1; k <= nSize; k++)
		(*this)(k, i) = Cki(k - i);
	for (int k = 1; k <= j - 1; k++)
		(*this)(j, k) = Cjk(k);
	for (int k = j + 1; k <= nSize; k++)
		(*this)(k, j) = Ckj(k - j);

	(*this)(i, i) = Cii;
	(*this)(j, j) = Cjj;
	(*this)(i, j) = 0.0;
	return t;
}

void XSymDoubleMatrix::ldl()
{
	int nSize = size();
	for (int i = 2; i <= nSize; i++)
	{
		for (int j = 1; j <= i - 1; j++)
		{
			double TikLjk = 0.0;
			for (int k = 1; k <= j - 1; k++)
				TikLjk += Aij(i, k) * Aij(j, k);
			(*this)(i, j) = Aij(i, j) - TikLjk;
		}
		for (int j = 1; j <= i - 1; j++)
			(*this)(i, j) = Aij(i, j) / Aij(j, j);
		double TikLik = 0;
		for (int k = 1; k <= i - 1; k++)
			TikLik += Aij(i, k) * Aij(i, k) * Aij(k, k);
		(*this)(i, i) = Aij(i, i) - TikLik;
	}
}

void XSymDoubleMatrix::ldl(XSymDoubleMatrix& mLDL)
{
	mLDL = *this;
	int nSize = size();
	for (int i = 2; i <= nSize; i++)
	{
		for (int j = 1; j <= i - 1; j++)
		{
			double TikLjk = 0.0;
			for (int k = 1; k <= j - 1; k++)
				TikLjk += mLDL.Aij(i, k) * mLDL.Aij(j, k);
			mLDL(i, j) = mLDL.Aij(i, j) - TikLjk;
		}
		for (int j = 1; j <= i - 1; j++)
			mLDL(i, j) = mLDL.Aij(i, j) / mLDL.Aij(j, j);
		double TikLik = 0;
		for (int k = 1; k <= i - 1; k++)
			TikLik += mLDL.Aij(i, k) * mLDL.Aij(i, k) * mLDL.Aij(k, k);
		mLDL(i, i) = mLDL.Aij(i, i) - TikLik;
	}
}

void XSymDoubleMatrix::solve(XDoubleMatrix& mC)
{
	int nSize = size();
	if (mC.rowSize() != nSize)
	{
		throw("系数矩阵大小与右端项不匹配(The sizes of matrices of the equation do not matched to solve)!");
		return;
	}
	XSymDoubleMatrix mLDL;
	ldl(mLDL);
	int nCol = mC.colSize();
	for (int jCol = 1; jCol <= nCol; jCol++)
	{
		for (int i = 1; i <= nSize; i++)
		{
			double LikYk = 0.0;
			for (int k = 1; k <= i - 1; k++)
				LikYk += mLDL.Aij(i, k) * mC.Aij(k, jCol);
			mC(i, jCol) = mC.Aij(i, jCol) - LikYk;
		}
		for (int i = nSize; i >= 1; i--)
		{
			double LkiXk = 0.0;
			for (int k = i + 1; k <= nSize; k++)
				LkiXk += mLDL.Aij(k, i) * mC.Aij(k, jCol);
			mC(i, jCol) = mC.Aij(i, jCol) / mLDL.Aij(i, i) - LkiXk;
		}
	}
}

void XSymDoubleMatrix::backSubstitute(XDoubleMatrix& mC)
{
	int nSize = size();
	if (mC.rowSize() != nSize)
	{
		throw("系数矩阵大小与右端项不匹配(The sizes of matrices of the equation do not matched to solve)!");
		return;
	}
	int nCol = mC.colSize();
	for (int jCol = 1; jCol <= nCol; jCol++)
	{
		for (int i = 1; i <= nSize; i++)
		{
			double LikYk = 0.0;
			for (int k = 1; k <= i - 1; k++)
				LikYk += Aij(i, k) * mC.Aij(k, jCol);
			mC(i, jCol) = mC.Aij(i, jCol) - LikYk;
		}
		for (int i = nSize; i >= 1; i--)
		{
			double LkiXk = 0.0;
			for (int k = i + 1; k <= nSize; k++)
				LkiXk += Aij(k, i) * mC.Aij(k, jCol);
			mC(i, jCol) = mC.Aij(i, jCol) / Aij(i, i) - LkiXk;
		}
	}
}

int XSymDoubleMatrix::Jacobi(XDoubleVector& vEigenValue, XSquareDoubleMatrix& mEigenVector, double dPrecision, int nMaxIteration)
{
	XSymDoubleMatrix mB;
	mB = *this;
	int nSize = mB.size();
	vEigenValue.resetSize(nSize);
	mEigenVector.eye(nSize);

	int i, j;
	int nIteration = 0;
	double dMax = mB.maxOffDiagonalPos(i, j);
	do {
		nIteration++;
		if (nIteration > nMaxIteration)
			return -1;

		double t = mB.pap(i, j);
		double c = 1 / sqrt(1 + t * t);
		double s = t * c;
		for (int k = 1; k <= nSize; k++)
		{
			double dRki, dRkj;
			dRki = mEigenVector.Aij(k, i) * c + mEigenVector.Aij(k, j) * s;
			dRkj = -mEigenVector.Aij(k, i) * s + mEigenVector.Aij(k, j) * c;
			mEigenVector(k, i) = dRki;
			mEigenVector(k, j) = dRkj;
		}

		dMax = mB.maxOffDiagonalPos(i, j);
	} while (dMax > dPrecision);

	for (int k = 1; k <= nSize; k++)
		vEigenValue(k) = mB.Aij(k, k);

	return nIteration;
}

int XSymDoubleMatrix::powerIteration(double& dEigenValue, XDoubleVector& vEigenVector, double dTol, int nMaxIteration)
{
	int nIteration = 0;
	int nSize = size();
	if (vEigenVector.size() == 0 || vEigenVector.size() != nSize)
		vEigenVector.ones(size());

	XDoubleVector vk;
	vk.resetSize(nSize);
	double dPrecision;
	double lamda1 = 0.0;
	do {
		nIteration++;
		if (nIteration > nMaxIteration)
			break;

		for (int i = 1; i <= nSize; i++)
		{
			vk(i) = 0.0;
			for (int j = 1; j <= nSize; j++)
				vk(i) += Aij(i, j) * vEigenVector.Vi(j);
		}
		double vmax = max(vk);
		double vmin = min(vk);
		double lamda2 = fabs(vmax) > fabs(vmin) ? vmax : vmin;

		for (int i = 1; i <= nSize; i++)
			vEigenVector(i) = vk.Vi(i) / lamda2;
	
		dPrecision = fabs((lamda2 - lamda1) / lamda2);
		lamda1 = lamda2;
	} while (dPrecision > dTol);
	dEigenValue = lamda1;
	double dSum2 = sum2(vEigenVector);
	for (int i = 1; i <= nSize; i++)
		vEigenVector(i) = vEigenVector.Vi(i) / sqrt(dSum2);
	return nIteration;
}

int XSymDoubleMatrix::invPowerIteration(double& dEigenValue, XDoubleVector& vEigenVector, double dShift, double dTol, int nMaxIteration)
{
	int nIteration = 0;
	int nSize = size();
	if (vEigenVector.size() == 0 || vEigenVector.size() != nSize)
		vEigenVector.ones(size());

	XDoubleMatrix vk;
	vk.resetSize(nSize, 1);

	for (int i = 1; i <= nSize; i++)
		vk(i,1) = vEigenVector.Vi(i);

	XSymDoubleMatrix mA;
	mA = *this;
	for (int i = 1; i <= nSize; i++)
		mA(i, i) = mA.Aij(i, i) - dShift;
	XSymDoubleMatrix mLDL;
	mA.ldl(mLDL);

	double dPrecision;
	double lamda1 = 0.0;
	do {
		nIteration++;
		if (nIteration > nMaxIteration)
			break;

		mLDL.backSubstitute(vk);

		double vmax = max(vk);
		double vmin = min(vk);
		double lamda2 = fabs(vmax) > fabs(vmin) ? vmax : vmin;

		for (int i = 1; i <= nSize; i++)
			vk(i,1) = vk.Aij(i,1) / lamda2;

		dPrecision = fabs((lamda2 - lamda1) / lamda2);
		lamda1 = lamda2;
	} while (dPrecision > dTol);
	dEigenValue = 1/lamda1 + dShift;
	for (int i = 1; i <= nSize; i++)
		vEigenVector(i) = vk.Aij(i, 1);
	double dSum2 = sum2(vEigenVector);
	for (int i = 1; i <= nSize; i++)
		vEigenVector(i) = vEigenVector.Vi(i) / sqrt(dSum2);
	return nIteration;
}

XDoubleMatrix ZjuMatrix::solve(XSymDoubleMatrix& mA, XDoubleMatrix& mC)
{
	XDoubleMatrix mB;
	mB = mC;
	mA.solve(mB);
	return mB;
/*
	XDoubleMatrix mB;
	int nSize = mA.size();
	if (mC.rowSize() != nSize)
	{
		throw("系数矩阵大小与右端项不匹配(The sizes of matrices of the equation do not matched to solve)!");
		return mB;
	}

	mB = mC;
	XSymDoubleMatrix mLDL;
	mA.ldl( mLDL );
	int nCol = mB.colSize();
	for (int jCol = 1; jCol <= nCol; jCol++)
	{
		for (int i = 1; i <= nSize; i++)
		{
			double LikYk = 0.0;
			for (int k = 1; k <= i - 1; k++)
				LikYk += mLDL.Aij(i, k) * mB.Aij(k, jCol);
			mB(i, jCol) = mB.Aij(i, jCol) - LikYk;
		}
		for (int i = nSize; i >= 1; i--)
		{
			double LkiXk = 0.0;
			for (int k = i + 1; k <= nSize; k++)
				LkiXk += mLDL.Aij(k, i) * mB.Aij(k, jCol);
			mB(i, jCol) = mB.Aij(i, jCol) / mLDL.Aij(i, i) - LkiXk;
		}
	}

	return mB;
//*/
}

int ZjuMatrix::eig(XSymDoubleMatrix& mA, XDoubleVector& vEigenValue,
	               XSquareDoubleMatrix& mEigenVector,
	               double dPrecision, int nMaxIteration)
{
	return mA.Jacobi(vEigenValue, mEigenVector, dPrecision, nMaxIteration);
/*
	XSymDoubleMatrix mB;
	mB = mA;
	int nSize = mB.size();
	vEigenValue.resetSize(nSize);
	mEigenVector.eye(nSize);

	int i, j;
	int nIteration = 0;
	double dMax = mB.maxOffDiagonalPos(i, j);
	do {
		nIteration++;
		if (nIteration > nMaxIteration)
			return -1;

		double t = mB.pap(i, j);
		double c = 1 / sqrt(1 + t * t);
		double s = t * c;
		for (int k = 1; k <= nSize; k++)
		{
			double dRki, dRkj;
			dRki = mEigenVector.Aij(k, i) * c + mEigenVector.Aij(k, j) * s;
			dRkj = -mEigenVector.Aij(k, i) * s + mEigenVector.Aij(k, j) * c;
			mEigenVector(k, i) = dRki;
			mEigenVector(k, j) = dRkj;
		}

		dMax = mB.maxOffDiagonalPos(i, j);
	} while (dMax > dPrecision);

	for (int k = 1; k <= nSize; k++)
		vEigenValue(k) = mB.Aij(k, k);

	return nIteration;
//*/
}
