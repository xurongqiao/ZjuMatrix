//=======================================================================
// 文件名(File name): XDoubleMatrix.cpp
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.13
// ----------------------------------------------------------------------
// 描述：实现一个矩阵类，用于双精度实矩阵的操作。
// Description: implementation of a class for matrix of double.
// 注意事项：矩阵的行号和列号从1开始，而不是从0开始
// Notice: the row and column number count from 1 not 0
//=======================================================================

#include "XVector.h"
#include "XDoubleMatrix.h"
#include <ostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;
using namespace ZjuMatrix;

//---------------------------------------------------------------------------
//  函数名(Function name): XDoubleMatrix()
//  描述: 默认构造函数
/// Description: default constructor
// -------------------------------------------------------------------------
XDoubleMatrix::XDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): XDoubleMatrix(int nRow, int nCol)
//  描述: 构造函数1
/// Description: constructor 1
// -------------------------------------------------------------------------
XDoubleMatrix::XDoubleMatrix(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_vdEntry.resetSize(nRow * nCol);
}

//---------------------------------------------------------------------------
//  函数名(Function name): XDoubleMatrix(int nRow, int nCol, double* pdEntry)
//  描述: 构造函数2
/// Description: constructor 2
// -------------------------------------------------------------------------
XDoubleMatrix::XDoubleMatrix(int nRow, int nCol, double* pdEntry)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_vdEntry.resetSize(nRow * nCol);
	for (int i = 1; i <= nRow*nCol; i++)
			m_vdEntry(i) = pdEntry[i - 1];
}

//---------------------------------------------------------------------------
//  函数名(Function name): XDoubleMatrix(int nRow, int nCol, XDoubleVector& vdEntry)
//  描述: 构造函数3
/// Description: constructor 3
// -------------------------------------------------------------------------
XDoubleMatrix::XDoubleMatrix(int nRow, int nCol, XDoubleVector& vdEntry)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_vdEntry.resetSize(nRow * nCol);
	for (int i = 1; i <= nRow * nCol; i++)
		m_vdEntry(i) = vdEntry.Vi(i);
}

//---------------------------------------------------------------------------
//  函数名(Function name): XDoubleMatrix(XDoubleMatrix& m)
//  描述: 复制构造函数
/// Description: copy constructor
// -------------------------------------------------------------------------
XDoubleMatrix::XDoubleMatrix(XDoubleMatrix& m)
{
	m_nRow = m.rowSize();
	m_nCol = m.colSize();
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): =(const XDoubleMatrix& m)
//  描述: 赋值运算符
/// Description: assignment operator
// -------------------------------------------------------------------------
XDoubleMatrix& XDoubleMatrix::operator=(const XDoubleMatrix& m)
{
	m_nRow = m.rowSize();
	m_nCol = m.colSize();
	m_vdEntry.resetSize(m_nRow * m_nCol);
	for (int i = 1; i <= m_nRow; i++)
		for (int j = 1; j <= m_nCol; j++)
			(*this)(i, j) = m.Aij(i, j);
	return *this;
}

//---------------------------------------------------------------------------
//  函数名(Function name): ~XDoubleMatrix()
//  描述: 析构函数
/// Description: destructor
// -------------------------------------------------------------------------
XDoubleMatrix::~XDoubleMatrix()
{
	m_nRow = 0;
	m_nCol = 0;
}

//---------------------------------------------------------------------------
//  函数名(Function name): resetSize(int nRow, int nCol)
//  描述: 重新设置矩阵大小并初始化为零
/// Description: Resize the matrix and initialized to zero.
// -------------------------------------------------------------------------
void XDoubleMatrix::resetSize(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_vdEntry.resetSize(nRow * nCol);
}

//---------------------------------------------------------------------------
//  函数名(Function name): eye(int nRow, int nCol)
//  描述: 把矩阵设置为单位矩阵
/// Description: Reset matrix to identity.
// -------------------------------------------------------------------------
void XDoubleMatrix::eye(int nRow, int nCol)
{
	resetSize(nRow, nCol);
	for (int i = 1; i <= nRow; i++)
		for (int j = 1; j <= nCol; j++)
		{
			if (i == j)
				(*this)(i, j) = 1.0;
			else
				(*this)(i, j) = 0.0;
		}
}

//---------------------------------------------------------------------------
//  函数名(Function name): random(int nRow, int nCol)
//  描述: 把矩阵元素设置为随机数
/// Description: Reset matrix to a random one.
// -------------------------------------------------------------------------
void XDoubleMatrix::random(int nRow, int nCol)
{
	resetSize(nRow, nCol);
	for (int i = 1; i <= nRow; i++)
		for (int j = 1; j <= nCol; j++)
			(*this)(i, j) = double(rand()%100000)/100000.0 ;
}

//---------------------------------------------------------------------------
//  函数名(Function name): rowExchange(int iRow, int jRow)
//  描述: 交换两行
/// Description: Exchange two rows.
// -------------------------------------------------------------------------
void XDoubleMatrix::rowExchange(int iRow, int jRow)
{
	if (iRow <= 0 || iRow > m_nRow || jRow <= 0 || jRow > m_nRow)
	{
		throw("矩阵行号超出了范围(The row number exceed the size of matrix)!");
		return;
	}
	for(int j=1; j<=m_nCol; j++)
	{
		double dTemp = (*this)(iRow, j);
		(*this)(iRow, j) = Aij(jRow, j);
		(*this)(jRow, j) = dTemp;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): colExchange(int iCol, int jCol)
//  描述: 交换两列
/// Description: Exchange tow columns.
// -------------------------------------------------------------------------
void XDoubleMatrix::colExchange(int iCol, int jCol)
{
	if (iCol <= 0 || iCol > m_nCol || jCol <= 0 || jCol > m_nCol)
	{
		throw("矩阵列号超出了范围(The column number exceed the size of matrix)!");
		return;
	}
	for (int i = 1; i <= m_nRow; i++)
	{
		double dTemp = (*this)(i, iCol);
		(*this)(i, iCol) = Aij(i, jCol);
		(*this)(i, jCol) = dTemp;
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): rowSize() const
//  描述: 返回矩阵的行数
/// Description: Return the row size.
// -------------------------------------------------------------------------
int XDoubleMatrix::rowSize() const
{
	return m_nRow;
}

//---------------------------------------------------------------------------
//  函数名(Function name): colSize() const
//  描述: 返回矩阵的列数
/// Description: Return the column size.
// -------------------------------------------------------------------------
int XDoubleMatrix::colSize() const
{
	return m_nCol;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): ()(int iRow, int jCol)
//  描述: 返回元素的引用
/// Description: Return the reference of an element.
// -------------------------------------------------------------------------
double& XDoubleMatrix::operator()(int iRow, int jCol)
{
	if (iRow <= 0 || jCol <= 0 || iRow > m_nRow || jCol > m_nCol)
	{
		throw("矩阵元素的行号或列号超出了范围(The index of entry exceed the size)!");
		return m_vdEntry(1);
	}
	else
	{
		int k = (iRow - 1) * m_nCol + jCol ;
		return m_vdEntry(k);
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): Aij(int iRow, int jCol) const
//  描述: 返回元素的值
/// Description: Return the value of an element.
// -------------------------------------------------------------------------
double XDoubleMatrix::Aij(int iRow, int jCol) const
{
	if (iRow <= 0 || jCol <= 0 || iRow > m_nRow || jCol > m_nCol)
	{
		throw("矩阵元素的行号或列号超出了范围(The index of entry exceed the size)!");
		return 0.0;
	}
	else
	{
		int k = (iRow - 1) * m_nCol + jCol;
		return m_vdEntry.Vi(k);
	}
}

//---------------------------------------------------------------------------
//  函数名(Function name): vdEntry()
//  描述: 返回矩阵所有元素
/// Description: Return all the value of a matrix.
// -------------------------------------------------------------------------
XDoubleVector XDoubleMatrix::vdEntry()
{
	return this->m_vdEntry;
}

//---------------------------------------------------------------------------
//  函数名(Function name): subMatrix(XIntVector viRow, XIntVector viCol)
//  描述: 返回子矩阵
/// Description: Return a sub-matrix.
// -------------------------------------------------------------------------
XDoubleMatrix XDoubleMatrix::subMatrix(XIntVector viRow, XIntVector viCol)
{
	int nRow = viRow.size();
	int nCol = viCol.size();
	XDoubleMatrix subMat;
	if (nRow != 0 && nCol != 0)
	{
		subMat.resetSize(nRow, nCol);
		for(int i=1; i<=nRow; i++)
			for (int j = 1; j <= nCol; j++)
				subMat(i, j) = Aij(viRow(i), viCol(j));
	}
	else if (nRow != 0)  // nCol == 0  所有列
	{
		int kCol = colSize();
		subMat.resetSize(nRow, kCol);
		for (int i = 1; i <= nRow; i++)
			for (int j = 1; j <= kCol; j++)
				subMat(i, j) = Aij(viRow(i), j);
	}
	else  if (nCol !=0)  // nRow == 0  所有行
	{
		int kRow = rowSize();
		subMat.resetSize(kRow, nCol);
		for (int i = 1; i <= kRow; i++)
			for (int j = 1; j <= nCol; j++)
				subMat(i, j) = Aij(i, viCol(j));
	}
	return subMat;
}

//---------------------------------------------------------------------------
//  函数名(Function name): max(const XDoubleMatrix& m)
//  描述: 最大的元素值
/// Description: value of maximum element
// -------------------------------------------------------------------------
double ZjuMatrix::max(const XDoubleMatrix& m)
{
	double dMax = 0.0;
	for (int i = 1; i <= m.m_nRow; i++)
	{
		for (int j = 1; j <= m.m_nCol; j++)
		{
			if (i == 1 && j == 1)
				dMax = m.Aij(i, j);
			else
			{
				if (dMax < m.Aij(i, j))
					dMax = m.Aij(i, j);
			}
		}
	}
	return dMax;
}

//---------------------------------------------------------------------------
//  函数名(Function name): min(const XDoubleMatrix& m)
//  描述: 最小的元素值
/// Description: value of minimum element
// -------------------------------------------------------------------------
double ZjuMatrix::min(const XDoubleMatrix& m)
{
	double dMin = 0.0;
	for (int i = 1; i <= m.m_nRow; i++)
	{
		for (int j = 1; j <= m.m_nCol; j++)
		{
			if (i == 1 && j == 1)
				dMin = m.Aij(i, j);
			else
			{
				if (dMin > m.Aij(i, j))
					dMin = m.Aij(i, j);
			}
		}
	}
	return dMin;
}

//---------------------------------------------------------------------------
//  函数名(Function name): transpose(XDoubleMatrix& m)
//  描述: 矩阵转置
/// Description: matrix transpose
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::transpose(XDoubleMatrix& m)
{
	int nRow = m.rowSize();
	int nCol = m.colSize();
	XDoubleMatrix mTranspose(nCol, nRow);
	for(int i=1; i<=nRow; i++)
		for (int j = 1; j <= nCol; j++)
			mTranspose(j, i) = m.Aij(i, j);
	return mTranspose ;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): +(XDoubleMatrix& m1, XDoubleMatrix& m2)
//  描述: 矩阵+矩阵
/// Description: matrix addition
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::operator+(XDoubleMatrix& m1, XDoubleMatrix& m2)
{
	XDoubleMatrix m3;
	int nRow = m1.rowSize();
	int nCol = m1.colSize();
	if (nRow != m2.rowSize() || nCol != m2.colSize())
	{
		throw("两个相加的矩阵维数不匹配(Sizes of matrices do not match for addition)!");
	}
	else
	{
		m3.resetSize(nRow, nCol);
		for (int i = 1; i <= nRow; i++)
			for (int j = 1; j <= nCol; j++)
				m3(i, j) = m1.Aij(i, j) + m2.Aij(i, j);
	}
	return m3;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): -(XDoubleMatrix& m1, XDoubleMatrix& m2)
//  描述: 矩阵-矩阵
/// Description: matrix - matrix
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::operator-(XDoubleMatrix& m1, XDoubleMatrix& m2)
{
	XDoubleMatrix m3;
	int nRow = m1.rowSize();
	int nCol = m1.colSize();
	if (nRow != m2.rowSize() || nCol != m2.colSize())
	{
		throw("两个相减的矩阵维数不匹配(Sizes of matrices do not match for subtraction)!");
	}
	else
	{
		m3.resetSize(nRow, nCol);
		for (int i = 1; i <= nRow; i++)
			for (int j = 1; j <= nCol; j++)
				m3(i, j) = m1.Aij(i, j) - m2.Aij(i, j);
	}
	return m3;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): *(XDoubleMatrix& m1, double c)
//  描述: 矩阵*标量
/// Description: matrix * scalar
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::operator*(XDoubleMatrix& m1, double c)
{
	int nRow = m1.rowSize();
	int nCol = m1.colSize();
	XDoubleMatrix m2(nRow, nCol);
	for (int i = 1; i <= nRow; i++)
		for (int j = 1; j <= nCol; j++)
			m2(i, j) = m1.Aij(i, j) * c;
	return m2;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): *(double c, XDoubleMatrix& m1)
//  描述: 标量*矩阵
/// Description: scalar * matrix
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::operator*(double c, XDoubleMatrix& m1)
{
	int nRow = m1.rowSize();
	int nCol = m1.colSize();
	XDoubleMatrix m2(nRow, nCol);
	for (int i = 1; i <= nRow; i++)
		for (int j = 1; j <= nCol; j++)
			m2(i, j) = m1.Aij(i, j) * c;
	return m2;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): *(XDoubleMatrix& m1, XDoubleMatrix& m2)
//  描述: 矩阵*矩阵
/// Description: matrix * matrix
// -------------------------------------------------------------------------
XDoubleMatrix ZjuMatrix::operator*(XDoubleMatrix& m1, XDoubleMatrix& m2)
{
	XDoubleMatrix m;
	int nR = m1.colSize();
	if (nR != m2.rowSize())
	{
		throw("相乘的两个矩阵的维数不匹配(Size of matrices do not match for product)!");
	}
	else
	{
		int nRow = m1.rowSize();
		int nCol = m2.colSize();
		m.resetSize(nRow, nCol);
		for (int i = 1; i <= nRow; i++)
			for (int j = 1; j <= nCol; j++)
			{
				m(i, j) = 0.0;
				for (int r = 1; r <= nR; r++)
					m(i, j) += m1.Aij(i, r) * m2.Aij(r, j);
			}
	}
	return m;
}

//---------------------------------------------------------------------------
//  重载名(Overloading name): *=(XDoubleMatrix& m, double c)
//  描述: 矩阵m=矩阵m*标量
/// Description: matrix m = matrix m * scalar
// -------------------------------------------------------------------------
void ZjuMatrix::operator*=(XDoubleMatrix& m, double c)
{
	int nRow = m.rowSize();
	int nCol = m.colSize();
	for (int i = 1; i <= nRow; i++)
	{
		for (int j = 1; j <= nCol; j++)
		{
			m(i, j) = m.Aij(i, j) * c;
		}
	}

}

//---------------------------------------------------------------------------
//  重载名(Overloading name): <<(ostream& os, XDoubleMatrix& m)
//  描述: 流输出
/// Description: output to stream
// -------------------------------------------------------------------------
ostream& ZjuMatrix::operator<<(ostream& os, XDoubleMatrix& m)
{
	int nWidth = 7;
	int nPrecision = 5;
	os << endl;
	for (int i = 1; i <= m.rowSize(); i++)
	{
		for (int j = 1; j <= m.colSize(); j++)
			os << setw(nWidth) << setprecision(nPrecision) << setiosflags(ios::fixed) << m.Aij(i, j) << "  ";
		os << endl;
	}
	return os;
}

