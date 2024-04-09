#include "XBandDoubleMatrix.h"

using namespace ZjuMatrix;

//---------------------------------------------------------------------------
//  函数名(Function name): XBandDoubleMatrix()
//  描述: 默认构造函数
/// Description: default constructor
// -------------------------------------------------------------------------
XBandDoubleMatrix::XBandDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): XBandDoubleMatrix(XIntVector& viSkyline)
//  描述: 构造函数1
/// Description: constructor 1
// -------------------------------------------------------------------------
XBandDoubleMatrix::XBandDoubleMatrix(XIntVector& viSkyline)
{
	int nSize = viSkyline.size();
	m_nRow = nSize;
	m_nCol = nSize;
	m_viDiagonalPos.resetSize(nSize);
	m_viSkyline = viSkyline;
	m_viDiagonalPos(1) = viSkyline(1);
	for (int i = 2; i <= nSize; i++)
		m_viDiagonalPos(i) = m_viDiagonalPos(i - 1) + viSkyline(i - 1);
	m_vdEntry.resetSize(m_viDiagonalPos(nSize) + viSkyline(nSize) - 1);
}

//---------------------------------------------------------------------------
//  函数名(Function name): XBandDoubleMatrix(XBandDoubleMatrix& m)
//  描述: 复制构造函数
/// Description: copy constructor
// -------------------------------------------------------------------------
XBandDoubleMatrix::XBandDoubleMatrix(XBandDoubleMatrix& m)
{
	m_nRow = m.m_nRow;
	m_nCol = m.m_nCol;
	m_vdEntry = m.m_vdEntry;
	m_viSkyline = m.m_viSkyline;
	m_viDiagonalPos = m.m_viDiagonalPos;
}

//---------------------------------------------------------------------------
//  函数名(Function name): =(const XBandDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
XBandDoubleMatrix& XBandDoubleMatrix::operator=(const XBandDoubleMatrix& m)
{
	m_nRow = m.m_nRow;
	m_nCol = m.m_nCol;
	m_vdEntry = m.m_vdEntry;
	m_viSkyline = m.m_viSkyline;
	m_viDiagonalPos = m.m_viDiagonalPos;
	return (*this);
}

//---------------------------------------------------------------------------
//  函数名(Function name): =(const XSymDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
XBandDoubleMatrix& XBandDoubleMatrix::operator=(const XSymDoubleMatrix& m)
{
	int nSize = m.size();
	m_nRow = nSize;
	m_nCol = nSize;
	m_viSkyline.resetSize(nSize);
	m_viDiagonalPos.resetSize(nSize);
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize; i++)
	{
		m_viSkyline(i) = i;
		m_viDiagonalPos(i) = i * (i - 1) / 2 + 1;
	}
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);

	return (*this);
}

//---------------------------------------------------------------------------
//  函数名(Function name): =(const XSquareDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
XBandDoubleMatrix& XBandDoubleMatrix::operator=(const XSquareDoubleMatrix& m)
{
	int nSize = m.size();
	m_nRow = nSize;
	m_nCol = nSize;
	m_viSkyline.resetSize(nSize);
	m_viDiagonalPos.resetSize(nSize);
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize; i++)
	{
		m_viSkyline(i) = i;
		m_viDiagonalPos(i) = i * (i - 1) / 2 + 1;
	}
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);

	return (*this);
}

//---------------------------------------------------------------------------
//  函数名(Function name): =(const XDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
XBandDoubleMatrix& XBandDoubleMatrix::operator=(const XDoubleMatrix& m)
{
	int nSize;
	int nRow = m.rowSize();
	int nCol = m.colSize();
	nSize = nRow < nCol ? nRow : nCol;

	m_nRow = nSize;
	m_nCol = nSize;
	m_viSkyline.resetSize(nSize);
	m_viDiagonalPos.resetSize(nSize);
	m_vdEntry.resetSize(nSize * (nSize + 1) / 2);
	for (int i = 1; i <= nSize; i++)
	{
		m_viSkyline(i) = i;
		m_viDiagonalPos(i) = i * (i - 1) / 2 + 1;
	}
	for (int i = 1; i <= nSize; i++)
		for (int j = 1; j <= i; j++)
			(*this)(i, j) = m.Aij(i, j);

	return (*this);
}

//---------------------------------------------------------------------------
//  函数名(Function name): ~XBandDoubleMatrix()
//  描述: 析构函数
/// Description: destructor
// -------------------------------------------------------------------------
XBandDoubleMatrix::~XBandDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSkyline(XIntVector& viSkyline)
//  描述: 重新设置带宽
/// Description: reset the skyline of band matrix
// -------------------------------------------------------------------------
void XBandDoubleMatrix::resetSkyline(XIntVector& viSkyline)
{
	int nSize = viSkyline.size();
	m_nRow = nSize;
	m_nCol = nSize;
	m_viDiagonalPos.resetSize(nSize);
	m_viSkyline = viSkyline;
	m_viDiagonalPos(1) = viSkyline(1);
	for (int i = 2; i <= nSize; i++)
		m_viDiagonalPos(i) = m_viDiagonalPos(i - 1) + viSkyline(i - 1);
	m_vdEntry.resetSize(m_viDiagonalPos(nSize) + viSkyline(nSize) - 1);
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSize(int nSize)
//  描述: 重新设置矩阵大小并初始化为零
/// Description: resize the matrix and initialized to zero
// -------------------------------------------------------------------------
void XBandDoubleMatrix::resetSize(int nSize)
{
	// 带状矩阵不重新设置矩阵大小，只是把元素全部初始化为零
	// The banded matrix does not resize the matrix,
	// but simply initializes all the elements to zero
	resetSize();
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSize()
//  描述: 重新设置矩阵大小并初始化为零
/// Description: resize the matrix and initialized to zero
// -------------------------------------------------------------------------
void XBandDoubleMatrix::resetSize()
{
	for (int i = 1; i <= m_nRow; i++)
	{
		int iM = i - m_viSkyline(i) + 1;
		for (int j = iM; j <= i; j++)
			(*this)(i, j) = 0.0;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): eye(int nSize)
//  描述: 把矩阵设置为单位矩阵
/// Description: reset matrix to identity
// -------------------------------------------------------------------------
void XBandDoubleMatrix::eye(int nSize)
{
	// 带状矩阵不重新设置矩阵大小，只是把矩阵变为单位矩阵
	// The banded matrix does not resize the matrix,
	// but simply changes the matrix to an identity
	eye();
}

//---------------------------------------------------------------------------
//  函数名(Function name): eye()
//  描述: 把矩阵设置为单位矩阵
/// Description: reset matrix to identity
// -------------------------------------------------------------------------
void XBandDoubleMatrix::eye()
{
	for (int i = 1; i <= m_nRow; i++)
	{
		int iM = i - m_viSkyline(i) + 1;
		for (int j = iM; j <= i; j++)
		{
			if (i == j)
				(*this)(i, j) = 1.0;
			else
				(*this)(i, j) = 0.0;
		}
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): random(int nSize)
//  描述: 把矩阵设置为随机矩阵
/// Description: reset matrix to a random one
// -------------------------------------------------------------------------
void XBandDoubleMatrix::random(int nSize)
{
	// 带宽和元素都设为随机数。
	// Both the skyline and elements are set to random
	m_nRow = nSize;
	m_nCol = nSize;
	m_viSkyline.resetSize(nSize);
	m_viDiagonalPos.resetSize(nSize);
	
	for (int i = 1; i <= nSize; i++)
	{
		int nMaxHalfOfWidth = (nSize / 2) < 25 ? nSize / 2 : 25;
		int nRand = (rand() % nMaxHalfOfWidth + 1);
		m_viSkyline(i) = nRand < i ? nRand : i;
	}
	m_viDiagonalPos(1) = m_viSkyline(1);
	for (int i = 2; i <= nSize; i++)
		m_viDiagonalPos(i) = m_viDiagonalPos(i - 1) + m_viSkyline(i - 1);
	m_vdEntry.resetSize(m_viDiagonalPos(nSize) + m_viSkyline(nSize) - 1);
	random();
}

//---------------------------------------------------------------------------
//  函数名(Function name): random()
//  描述: 把矩阵设置为随机矩阵
/// Description: reset matrix to a random one
// -------------------------------------------------------------------------
void XBandDoubleMatrix::random()
{
	// 不改变带宽属性，只是把元素设置为随机数
	// The skyline remains and the elements are set to random 
	for (int i = 1; i <= m_nRow; i++)
	{
		int iM = i - m_viSkyline(i) + 1;
		for (int j = iM; j <= i; j++)
			(*this)(i, j) = double(rand() % 100000) / 100000.0;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): viSkyline()
//  描述: 返回带状矩阵每行的skyline
/// Description: Return the matrix's skyline
// -------------------------------------------------------------------------
XIntVector XBandDoubleMatrix::viSkyline()
{
	return this->m_viSkyline;
}

//---------------------------------------------------------------------------
//  函数名(Function name): viDiagonalPos()
//  描述: 返回带状矩阵每行对角线元素在一维数组中的位置
/// Description: return the position at 1D array for the diagnal element of each row
// -------------------------------------------------------------------------
XIntVector XBandDoubleMatrix::viDiagonalPos()
{
	return this->m_viDiagonalPos;
}

//---------------------------------------------------------------------------
//  函数名(Function name): ()(int iRow, int jCol)
//  描述: 返回元素的引用
/// Description: Return the reference of an element
// -------------------------------------------------------------------------
double& XBandDoubleMatrix::operator()(int iRow, int jCol)
{
	if (iRow <= 0 || iRow > m_nRow || jCol <= 0 || jCol > m_nCol)
	{
		throw("元素行号或列号超出了矩阵大小(The index of matrix exceed the size)!");
		return m_vdEntry(1);
	}

	int i = iRow < jCol ? iRow : jCol;
	int j = iRow > jCol ? iRow : jCol;

	int k = j - i;
	if (k >= m_viSkyline(j))
	{
		throw("所引用元素超出了skyline(The element referred beyound the skyline)!");
		return m_vdEntry(1);
	}
	else
		return m_vdEntry(m_viDiagonalPos(j) + k);
}

//---------------------------------------------------------------------------
//  函数名(Function name): Aij(int iRow, int jCol) const
//  描述: 返回元素的值
/// Description: Return the value of an element
// -------------------------------------------------------------------------
double XBandDoubleMatrix::Aij(int iRow, int jCol) const
{
	if (iRow <= 0 || iRow > m_nRow || jCol <= 0 || jCol > m_nCol)
	{
		throw("元素行号或列号超出了矩阵大小(The index of matrix exceed the size)!");
		return 0.0;
	}

	int i = iRow < jCol ? iRow : jCol;
	int j = iRow > jCol ? iRow : jCol;

	int k = j - i;
	if (k >= m_viSkyline.Vi(j))
	{
		return 0.0;
	}
	else
		return m_vdEntry.Vi(m_viDiagonalPos.Vi(j) + k);
}

//---------------------------------------------------------------------------
//  函数名(Function name): ldl()
//  描述: 对称带状矩阵的LDL分解，原矩阵被分解结果覆盖
/// Description: LDL factorization and this symmetical banded matrix is overwritten by the resulting matrix of LDL factorization
// -------------------------------------------------------------------------
void XBandDoubleMatrix::ldl()
{
	for (int i = 2; i <= m_nRow; i++)
	{
		int iM = i - m_viSkyline(i) + 1;
		for (int j = iM; j <= i - 1; j++)
		{
			double TikLjk = 0.0;
			int jM = j - m_viSkyline(j) + 1;
			for (int k = (iM > jM ? iM : jM); k <= j - 1; k++)
			{
				TikLjk += Aij(i, k) * Aij(j, k);
			}
			(*this)(i, j) = Aij(i, j) - TikLjk;
		}
		for (int j = iM; j <= i - 1; j++)
		{
			(*this)(i, j) = Aij(i, j) / Aij(j, j);
		}
		double TikLik = 0;
		for (int k = iM; k <= i - 1; k++)
		{
			TikLik += Aij(i, k) *Aij(i, k) * Aij(k, k);
		}
		(*this)(i, i) = Aij(i, i) - TikLik;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): ldl(XBandDoubleMatrix& mLDL)
//  描述: 对称带状矩阵的LDL分解，原矩阵保留。
/// Description: LDL decomposition and this symmetical banded matrix remains
// -------------------------------------------------------------------------
void XBandDoubleMatrix::ldl(XBandDoubleMatrix& mLDL)
{
	mLDL = *this;
	for (int i = 2; i <= m_nRow; i++)
	{
		int iM = i - m_viSkyline(i) + 1;
		for (int j = iM; j <= i - 1; j++)
		{
			double TikLjk = 0.0;
			int jM = j - m_viSkyline(j) + 1;
			for (int k = (iM > jM ? iM : jM); k <= j - 1; k++)
			{
				TikLjk += mLDL.Aij(i, k) * mLDL.Aij(j, k);
			}
			mLDL(i, j) = mLDL.Aij(i, j) - TikLjk;
		}
		for (int j = iM; j <= i - 1; j++)
		{
			mLDL(i, j) = mLDL.Aij(i, j) / mLDL.Aij(j, j);
		}
		double TikLik = 0;
		for (int k = iM; k <= i - 1; k++)
		{
			TikLik += mLDL.Aij(i, k) * mLDL.Aij(i, k) * mLDL.Aij(k, k);
		}
		mLDL(i, i) = mLDL.Aij(i, i) - TikLik;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): solve(XDoubleMatrix& mC)
//  描述: 利用LDL分解求解方程A*B=C
/// Description: Solve equation A*B=C using LDL factorization.
// -------------------------------------------------------------------------
void XBandDoubleMatrix::solve(XDoubleMatrix& mC)
{
	int nSize = size();
	if (mC.rowSize() != nSize)
	{
		throw("系数矩阵大小与右端项不匹配(The sizes of matrices of the equation do not matched to solve)!");
	}

	XBandDoubleMatrix mLDL;
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


//---------------------------------------------------------------------------
//  函数名(Function name): solve(XBandDoubleMatrix& mA, XDoubleMatrix& mC)
//  描述: 利用LDL分解求解方程A*B=C
/// Description: Solve equation A*B=C using LDL factorization.
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::solve(XBandDoubleMatrix& mA, XDoubleMatrix& mC)
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
	XBandDoubleMatrix mLDL;
	mA.ldl(mLDL);
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

