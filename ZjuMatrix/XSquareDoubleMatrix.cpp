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

//---------------------------------------------------------------------------
//  函数名(Function name): XSquareDoubleMatrix()
//  描述: 默认构造函数
/// Description: default constructor
// -------------------------------------------------------------------------
XSquareDoubleMatrix::XSquareDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): XSquareDoubleMatrix(int nSize)
//  描述: 构造函数1
/// Description: constructor 1
// -------------------------------------------------------------------------
XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
}

//---------------------------------------------------------------------------
//  函数名(Function name): XSquareDoubleMatrix(int nSize, double* pdEntry)
//  描述: 构造函数2
/// Description: constructor 2
// -------------------------------------------------------------------------
XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize, double* pdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
	for (int i = 1; i <= nSize * nSize; i++)
		m_vdEntry(i) = pdEntry[i - 1];
}

//---------------------------------------------------------------------------
//  函数名(Function name): XSquareDoubleMatrix(int nSize, XDoubleVector& vdEntry)
//  描述: 构造函数3
/// Description: constructor 3
// -------------------------------------------------------------------------
XSquareDoubleMatrix::XSquareDoubleMatrix(int nSize, XDoubleVector& vdEntry)
{
	m_nRow = nSize;
	m_nCol = nSize;
	m_vdEntry.resetSize(nSize * nSize);
	for (int i = 1; i <= nSize * nSize; i++)
		m_vdEntry(i) = vdEntry.Vi(i);
}

//---------------------------------------------------------------------------
//  函数名(Function name): XSquareDoubleMatrix(XSquareDoubleMatrix& m)
//  描述: 复制构造函数
/// Description: copy constructor
// -------------------------------------------------------------------------
XSquareDoubleMatrix::XSquareDoubleMatrix(XSquareDoubleMatrix& m)
{
	m_nRow = m.size();
	m_nCol = m_nRow;
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): =(const XSquareDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//  重载名(Overloading name): =(const XDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): ~XSquareDoubleMatrix()
//  描述: 析构函数
/// Description: destructor
// -------------------------------------------------------------------------
XSquareDoubleMatrix::~XSquareDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSize(int nRow, int nCol)
//  描述: 重新设置矩阵大小并初始化为零
/// Description: Resize the matrix and initialized to zero.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::resetSize(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	resetSize(nRow);
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSize(int nSize)
//  描述: 重新设置矩阵大小并初始化为零
/// Description: Resize the matrix and initialized to zero.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::resetSize(int nSize)
{
	XDoubleMatrix::resetSize(nSize, nSize);
}

//---------------------------------------------------------------------------
//  函数名(Function name): eye(int nRow, int nCol)
//  描述: 把矩阵设置为单位矩阵
/// Description: Reset matrix to identity.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::eye(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	eye(nRow);
}

//---------------------------------------------------------------------------
//  函数名(Function name): eye(int nSize)
//  描述: 把矩阵设置为单位矩阵
/// Description: Reset matrix to identity.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::eye(int nSize)
{
	XDoubleMatrix::eye(nSize, nSize);
}

//---------------------------------------------------------------------------
//  函数名(Function name): random(int nRow, int nCol)
//  描述: 把矩阵设置为随机矩阵
/// Description: Reset matrix to a random one.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::random(int nRow, int nCol)
{
	if (nRow != nCol)
		throw("方阵的行数与列数必须相等(The row size must equal to column size of a square matrix)!");
	random(nRow);
}

//---------------------------------------------------------------------------
//  函数名(Function name): random(int nSize)
//  描述: 把矩阵设置为随机矩阵
/// Description: Reset matrix to a random one.
// -------------------------------------------------------------------------
void XSquareDoubleMatrix::random(int nSize)
{
	XDoubleMatrix::random(nSize, nSize);
}

//---------------------------------------------------------------------------
//  函数名(Function name): size() const
//  描述: 返回矩阵的大小
/// Description: Return the size.
// -------------------------------------------------------------------------
int XSquareDoubleMatrix::size() const
{
	return m_nRow;
}

//---------------------------------------------------------------------------
//  函数名(Function name): colPivot(int kCol) const
//  描述: 返回列主元的行号
/// Description: Return the row number of a pivot in a column
// -------------------------------------------------------------------------
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

// LU分解(Doolittle LU decomposition)
//        [U_11  U_12  U_13 ... U_1n]       [ 1     0     0   ...  0 ]      [U_11  U_12  U_13 ... U_1n] 
//        [L_21  U_22  U_23 ... U_2n]       [L_21   1     0   ...  0 ]      [ 0    U_22  U_23 ... U_2n]
//  [mLU]=[L_31  L_32  U_33 ... U_3n]  [mL]=[L_31  L_32   1   ...  0 ] [mU]=[ 0      0   U_33 ... U_3n] 
//        [ ...   ...   ... ...  ...]       [ ...   ...   ... ... ...]      [ ...   ...   ... ...  ...] 
//        [L_n1  L_n2  L_n3 ... U_nn]       [L_n1  L_n2  L_n3 ...  1 ]      [ 0      0     0  ... U_nn]

//---------------------------------------------------------------------------
//  函数名(Function name): lu(XSquareDoubleMatrix& m)
//  描述: LU分解，A=LU
/// Description: LU decomposition, A = LU
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU)
//  描述: LU分解，A=LU
/// Description: LU decomposition, A = LU
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XSquareDoubleMatrix& mP)
//  描述: LU分解，PA = LU
/// Description: LU decomposition, PA = LU
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): lu(XSquareDoubleMatrix& mLU, XIntVector& vP)
//  描述: LU分解，A(p,:) = LU
/// Description: LU decomposition, A(p,:) = LU
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XIntVector& vP)
//  描述: LU分解，A(p,:) = LU
/// Description: LU decomposition, A(p,:) = LU
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): det()
//  描述: 方阵的行列式值
/// Description: determinant of square matrix
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): trace()
//  描述: 方阵的迹
/// Description: trace of square matrix
// -------------------------------------------------------------------------
double XSquareDoubleMatrix::trace()
{
	double dTrace = 0.0;
	int nSize = size();
	for (int i = 1; i <= nSize; i++)
		dTrace += Aij(i, i);
	return dTrace;
}

//---------------------------------------------------------------------------
//  函数名(Function name): inverse()
//  描述: 逆矩阵
/// Description: inverse of square matrix
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): solve(XDoubleMatrix& mC)
//  描述: 利用LU分解解方程
/// Description: solve the equation using LU decomposition
// -------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
//  函数名(Function name): solve(XSquareDoubleMatrix& mA, XDoubleMatrix& mC)
//  描述: 利用LU分解求解方程A*B=C
/// Description: solve the equation A*B=C using LU decomposition
// -------------------------------------------------------------------------
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
