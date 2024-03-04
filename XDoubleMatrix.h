//=======================================================================
// 文件名(File name): XDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.12
// ----------------------------------------------------------------------
// 描述：定义一个矩阵类，用于双精度实矩阵的操作。
// Description: define a class for matrix of double.
// 注意事项：矩阵的行号和列号从1开始，而不是从0开始
// Notice: the row and column number count from 1 not 0
//=======================================================================

#pragma once

namespace ZjuMatrix {
	class XDoubleMatrix
	{
	protected:
		int m_nRow;                  // 矩阵行数(row size of matrix)
		int m_nCol;                  // 矩阵列数(column size of matrix)
		XDoubleVector m_vdEntry;     // 矩阵元素(element of matrix)

	public:
		XDoubleMatrix();                                            // 默认构造函数(default constructor)
		XDoubleMatrix(int nRow, int nCol);                          // 构造函数1(constructor 1)
		XDoubleMatrix(int nRow, int nCol, double* pdEntry);         // 构造函数2(constructor 2)
		XDoubleMatrix(int nRow, int nCol, XDoubleVector& vdEntry);  // 构造函数3(constructor 3)
		XDoubleMatrix(XDoubleMatrix& m);                            // 复制构造函数(copy constructor)
		XDoubleMatrix& operator= (const XDoubleMatrix& m);          // 赋值运算符(assignment operator)
		~XDoubleMatrix();                                           // 析构函数(destructor)

	public:
		void resetSize(int nRow, int nCol);              // 重新设置矩阵大小并初始化为零(resize the matrix and initialized to zero)
		void eye(int nRow, int nCol);                    // 把矩阵设置为单位矩阵(reset matrix to identity)
		void random(int nRow, int nCol);                 // 把矩阵元素设置为随机数(reset matrix to a random one)
		virtual void rowExchange(int iRow, int jRow);    // 交换两行(exchange two rows)
		virtual void colExchange(int iCol, int jCol);    // 交换两列(exchange tow columns)
		int rowSize() const;                             // 返回矩阵的行数(return the row size)
		int colSize() const;                             // 返回矩阵的列数(return the column size)
		virtual double& operator()(int iRow, int jCol);  // 返回元素的引用(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;    // 返回元素的值(return the value of an element)
		XDoubleMatrix subMatrix(XIntVector viRow, XIntVector viCol);  // 子矩阵(return a sub-matrix)

	public:
		friend double max(const XDoubleMatrix& m); //最大的元素值(value of maximum element)
		friend double min(const XDoubleMatrix& m); //最小的元素值(value of minimum element)
		friend XDoubleMatrix transpose(XDoubleMatrix& m);                       //矩阵转置(matrix transpose)
		friend XDoubleMatrix operator + (XDoubleMatrix& m1, XDoubleMatrix& m2); //矩阵+矩阵(matrix addition)
		friend XDoubleMatrix operator - (XDoubleMatrix& m1, XDoubleMatrix& m2); //矩阵-矩阵(matrix - matrix)
		friend XDoubleMatrix operator * (XDoubleMatrix& m, double c);           //矩阵*标量(matrix * scalar)
		friend XDoubleMatrix operator * (double c, XDoubleMatrix& m);           //标量*矩阵(scalar * matrix)
		friend XDoubleMatrix operator * (XDoubleMatrix& m1, XDoubleMatrix& m2); //矩阵*矩阵(matrix * matrix)
		friend ostream& operator << (ostream& os, XDoubleMatrix& m);            //流输出(output to stream)
	};
}