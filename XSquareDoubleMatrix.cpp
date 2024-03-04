//=======================================================================
// 文件名(File name): XSquareDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.13
// ----------------------------------------------------------------------
// 描述：实现一个方形矩阵类，用于双精度实矩阵的操作。
// Description: define a class for square matrix of double.
// 注意事项：矩阵的行号和列号从1开始，而不是从0开始
// Notice: the row and column number count from 1 not 0
//=======================================================================

#include "XSquareDoubleMatrix.h"

using namespace ZjuMatrix;

XSquareDoubleMatrix::XSquareDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
}

XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize, double* pdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
	for (int i = 1; i <= nSize * nSize; i++)
		m_vdEntry(i) = pdEntry[i - 1];
}

XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize, XDoubleVector& vdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
	for (int i = 1; i <= nSize * nSize; i++)
		m_vdEntry(i) = vdEntry.Vi(i);
}

XSquareDoubleMatrix::XSquareDoubleMatrix(XSquareDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
}

XSquareDoubleMatrix& XSquareDoubleMatrix::operator=(const XSquareDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

XSquareDoubleMatrix& XSquareDoubleMatrix::operator=(const XDoubleMatrix& m)
{
	int nSize;
	int nRow = m.rowSize();
	int nCol = m.colSize();
	nSize = nRow < nCol ? nRow : nCol;
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

XSquareDoubleMatrix::~XSquareDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

void XSquareDoubleMatrix::resetSize(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	resetSize(nRow);
}

void XSquareDoubleMatrix::resetSize(int nSize)
{
	XDoubleMatrix::resetSize(nSize, nSize);
}

void XSquareDoubleMatrix::eye(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	eye(nRow);
}

void XSquareDoubleMatrix::eye(int nSize)
{
	XDoubleMatrix::eye(nSize, nSize);
}

void XSquareDoubleMatrix::random(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	random(nRow);
}

void XSquareDoubleMatrix::random(int nSize)
{
	XDoubleMatrix::random(nSize, nSize);
}

int XSquareDoubleMatrix::size() const
{
	return m_nRow;
}

int XSquareDoubleMatrix::colPivot(int kCol) const
{
	int nSize = size();
	if (kCol <= 0 || kCol > nSize)
	{
		throw("矩阵列号超出范围(the column number exceeds the matrix size)!");
		return kCol;
	}

	double dPivot = fabs(Aij(kCol, kCol));
	int iK = kCol;
	for (int i = kCol + 1; i <= nSize; i++)
	{
		if (fabs(Aij(i, kCol)) > dPivot)
		{
			dPivot = Aij(i, kCol);
			iK = i;
		}
	}
	return iK;
}

void XSquareDoubleMatrix::lu(XSquareDoubleMatrix& m)
{
	int nSize = size();

	// this implies U_1i = A_1i
	m = *this;

	// L_i1 = A_i1/U_11 ;
	if (m.Aij(1, 1) == 0.0)
	{
		throw("矩阵对角元素为零无法直接LU分解(The pivot is zero and cannot be LU decomposed directly)!");
		return;
	}
	for (int i = 2; i <= nSize; i++)
		m(i, 1) = Aij(i, 1) / m.Aij(1, 1);

	for (int r = 2; r <= nSize; r++)
	{
		for (int i = r; i <= nSize; i++)
		{
			double LrkUki = 0.0;
			for (int k = 1; k <= r - 1; k++)
				LrkUki += m.Aij(r, k) * m.Aij(k, i);
			m(r, i) = Aij(r, i) - LrkUki;
		}
		if (m.Aij(r, r) == 0.0)
		{
			throw("矩阵对角元素为零无法直接LU分解(The pivot is zero and cannot be LU decomposed directly)!");
			return;
		}
		for (int i = r + 1; i <= nSize; i++)
		{
			double LikUkr = 0.0;
			for (int k = 1; k <= r - 1; k++)
				LikUkr += m.Aij(i, k) * m.Aij(k, r);
			m(i, r) = (Aij(i, r) - LikUkr) / m.Aij(r, r);
		}
	}
}

void XSquareDoubleMatrix::lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU)
{
	int nSize = size();
	mL.eye(nSize);
	mU.resetSize(nSize);

	// U_1i = A_1i
	for (int i = 1; i <= nSize; i++)
		mU(1, i) = Aij(1, i);

	// L_i1 = A_i1/U_11 ;
	if (mU.Aij(1, 1) == 0.0)
	{
		throw("矩阵对角元素为零无法直接LU分解(The pivot is zero and cannot be LU decomposed directly)!");
		return;
	}
	for (int i = 2; i <= nSize; i++)
		mL(i, 1) = Aij(i, 1) / mU.Aij(1, 1);

	for (int r = 2; r <= nSize; r++)
	{
		for (int i = r; i <= nSize; i++)
		{
			double LrkUki = 0.0;
			for (int k = 1; k <= r - 1; k++)
				LrkUki += mL.Aij(r, k) * mU.Aij(k, i);
			mU(r, i) = Aij(r, i) - LrkUki;
		}
		if (mU.Aij(r, r) == 0.0)
		{
			throw("矩阵对角元素为零无法直接LU分解(The pivot is zero and cannot be LU decomposed directly)!");
			return;
		}
		for (int i = r + 1; i <= nSize; i++)
		{
			double LikUkr = 0.0;
			for (int k = 1; k <= r - 1; k++)
				LikUkr += mL.Aij(i, k) * mU.Aij(k, r);
			mL(i, r) = (Aij(i, r) - LikUkr) / mU.Aij(r, r);
		}
	}
}

void XSquareDoubleMatrix::lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XSquareDoubleMatrix& mP)
{
	int nSize = size();
	mL.eye(nSize);
	mU.resetSize(nSize);
	mP.eye(nSize);

	XSquareDoubleMatrix mA;
	mA = *this;

	for (int r = 1; r <= nSize; r++)
	{
		int rK = mA.colPivot(r);
		if (rK != r)
		{
			mA.rowExchange(r, rK);
			mP.rowExchange(r, rK);
		}

		if (mA.Aij(r, r) == 0.0)
		{
			throw("矩阵奇异无法进行LU分解(The matrix is singular and cannot be LU decomposed)!");
			return;
		}

		for (int i = r + 1; i <= nSize; i++)
			mA(i, r) = mA.Aij(i, r) / mA.Aij(r, r);

		for (int i = r + 1; i <= nSize; i++)
			for (int j = r + 1; j <= nSize; j++)
				mA(i, j) = mA.Aij(i, j) - mA.Aij(i, r) * mA.Aij(r, j);
	}

	for (int i = 2; i <= nSize; i++)
		for (int j = 1; j < i; j++)
			mL(i, j) = mA.Aij(i, j);

	for (int i = 1; i <= nSize; i++)
		for (int j = i; j <= nSize; j++)
			mU(i, j) = mA.Aij(i, j);
}

void XSquareDoubleMatrix::lu(XSquareDoubleMatrix& mLU, XIntVector& vP)
{
	int nSize = size();
	vP.resetSize(nSize);
	for (int i = 1; i <= nSize; i++)
		vP(i) = i;

	mLU = *this;

	for (int r = 1; r <= nSize; r++)
	{
		int rK = mLU.colPivot(r);
		if (rK != r)
		{
			mLU.rowExchange(r, rK);
			vP.exchange(r, rK);
		}

		if (mLU.Aij(r, r) == 0.0)
		{
			throw("矩阵奇异无法进行LU分解(The matrix is singular and cannot be LU decomposed)!");
			return;
		}

		for (int i = r + 1; i <= nSize; i++)
			mLU(i, r) = mLU.Aij(i, r) / mLU.Aij(r, r);

		for (int i = r + 1; i <= nSize; i++)
			for (int j = r + 1; j <= nSize; j++)
				mLU(i, j) = mLU.Aij(i, j) - mLU.Aij(i, r) * mLU.Aij(r, j);
	}
}

void XSquareDoubleMatrix::lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XIntVector& vP)
{
	int nSize = size();
	mL.eye(nSize);
	mU.resetSize(nSize);

	vP.resetSize(nSize);
	for (int i = 1; i <= nSize; i++)
		vP(i) = i;

	XSquareDoubleMatrix mA;
	mA = *this;

	for (int r = 1; r <= nSize; r++)
	{
		int rK = mA.colPivot(r);
		if (rK != r)
		{
			mA.rowExchange(r, rK);
			vP.exchange(r, rK);
		}

		if (mA.Aij(r, r) == 0.0)
		{
			throw("矩阵奇异无法进行LU分解(The matrix is singular and cannot be LU decomposed)!");
			return;
		}

		for (int i = r + 1; i <= nSize; i++)
			mA(i, r) = mA.Aij(i, r) / mA.Aij(r, r);

		for (int i = r + 1; i <= nSize; i++)
			for (int j = r + 1; j <= nSize; j++)
				mA(i, j) = mA.Aij(i, j) - mA.Aij(i, r) * mA.Aij(r, j);
	}

	for (int i = 2; i <= nSize; i++)
		for (int j = 1; j < i; j++)
			mL(i, j) = mA.Aij(i, j);

	for (int i = 1; i <= nSize; i++)
		for (int j = i; j <= nSize; j++)
			mU(i, j) = mA.Aij(i, j);
}

double XSquareDoubleMatrix::det()
{
	double dDet = 1.0;

	XSquareDoubleMatrix mA = *this;
	int nSize = mA.size();
	int iSign = 1;
	for (int r = 1; r <= nSize; r++)
	{
		int rK = mA.colPivot(r);
		if (rK != r)
		{
			mA.rowExchange(r, rK);
			iSign *= (-1);
		}

		if (mA(r, r) == 0.0)
			return 0.0;

		dDet *= mA(r, r);

		for (int i = r + 1; i <= nSize; i++)
			mA(i, r) = mA(i, r) / mA(r, r);

		for (int i = r + 1; i <= nSize; i++)
			for (int j = r + 1; j <= nSize; j++)
				mA(i, j) = mA(i, j) - mA(i, r) * mA(r, j);
	}

	dDet *= iSign;
	return dDet;
}

double XSquareDoubleMatrix::trace()
{
	double dTrace = 0.0;
	int nSize = size();
	for (int i = 1; i <= nSize; i++)
		dTrace += Aij(i, i);
	return dTrace;
}

XSquareDoubleMatrix XSquareDoubleMatrix::inverse()
{
	XSquareDoubleMatrix mI;
	mI.eye(size());
	solve(mI);
	return mI;
	//	XSquareDoubleMatrix mInv;
//	XSquareDoubleMatrix mI;
//	mI.eye(size());
//	mInv = solve(*this, mI);
//	return mInv;
}

void XSquareDoubleMatrix::solve(XDoubleMatrix& mC)
{
	int nSize = size();
	if (nSize != mC.rowSize())
	{
		throw("The size of matrices are not matched for the equation!");
	}

	// LU分解(LU decomposition)
	XSquareDoubleMatrix mLU;
	XIntVector vP, viCol;
	lu(mLU, vP);

	// 重新排列C矩阵(permutate the matric C)
	mC = mC.subMatrix(vP, viCol);

	// 求解(solve)
	//  LY = C
	int nCol = mC.colSize();
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= nCol; j++)
		{
			double LikYkj = 0.0;
			for (int k = 1; k <= i - 1; k++)
				LikYkj += mLU.Aij(i, k) * mC.Aij(k, j);
			mC(i, j) = mC.Aij(i, j) - LikYkj;
		}
	// UX = Y
	for (int i = nSize; i >= 1; i--)
		for (int j = 1; j <= nCol; j++)
		{
			double UikXkj = 0.0;
			for (int k = i + 1; k <= nSize; k++)
				UikXkj += mLU.Aij(i, k) * mC.Aij(k, j);
			mC(i, j) = (mC.Aij(i, j) - UikXkj) / mLU.Aij(i, i);
		}
}

XDoubleMatrix ZjuMatrix::solve(XSquareDoubleMatrix& mA, XDoubleMatrix& mC)
{
	XDoubleMatrix mB;
	mB = mC;
	mA.solve(mB);
	return mB;
	/*
	XDoubleMatrix mB;
	int nSize = mA.size();
	if (nSize != mC.rowSize())
	{
		throw("The size of matrices are not matched for the equation!");
		return mB;
	}

	// LU分解(LU decomposition)
	XSquareDoubleMatrix mLU;
	XIntVector vP, viCol;
	mA.lu(mLU, vP);

	// 重新排列C矩阵(permutate the matric C)
	XDoubleMatrix mCp;
	mCp = mC.subMatrix(vP, viCol);

	// 求解(solve)
	//  LY = C
	int nCol = mCp.colSize();
	mB.resetSize(nSize, nCol);
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= nCol; j++)
		{
			double LikYkj = 0.0;
			for (int k = 1; k <= i - 1; k++)
				LikYkj += mLU.Aij(i, k) * mB.Aij(k, j);
			mB(i, j) = mCp.Aij(i, j) - LikYkj;
		}
	// UX = Y
	for (int i = nSize; i >= 1; i--)
		for (int j = 1; j <= nCol; j++)
		{
			double UikXkj = 0.0;
			for (int k = i + 1; k <= nSize; k++)
				UikXkj += mLU.Aij(i, k) * mB.Aij(k, j);
			mB(i, j) = (mB.Aij(i, j) - UikXkj) / mLU.Aij(i, i);
		}
	return mB;
//*/
}
