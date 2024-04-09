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

	/// Define a class for matrix of double.
	class XDoubleMatrix
	{
	protected:
	    /// Description: row size of matrix
		int m_nRow;                  // 矩阵行数(row size of matrix)
		/// Description: column size of matrix
		int m_nCol;                  // 矩阵列数(column size of matrix)
		/// Description: element of matrix
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
		XDoubleVector vdEntry();                         // 返回矩阵所有元素(return all the value of a matrix)
		XDoubleMatrix subMatrix(XIntVector viRow, XIntVector viCol);  // 返回子矩阵(return a sub-matrix)

	public:
	    //---------------------------------------------------------------------------
		//  函数名(Function name): max(const XDoubleMatrix& m)
		//  描述: 最大的元素值
		/// Description: value of maximum element
		// -------------------------------------------------------------------------
		friend double max(const XDoubleMatrix& m);  

		//---------------------------------------------------------------------------
		//  函数名(Function name): min(const XDoubleMatrix& m)
		//  描述: 最小的元素值
		/// Description: value of minimum element
		// -------------------------------------------------------------------------
		friend double min(const XDoubleMatrix& m);  

		//---------------------------------------------------------------------------
		//  函数名(Function name): transpose(XDoubleMatrix& m)
		//  描述: 矩阵转置
		/// Description: matrix transpose
		// -------------------------------------------------------------------------
		friend XDoubleMatrix transpose(XDoubleMatrix& m);

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): +(XDoubleMatrix& m1, XDoubleMatrix& m2)
		//  描述: 矩阵+矩阵
		/// Description: matrix addition
		// -------------------------------------------------------------------------
		friend XDoubleMatrix operator + (XDoubleMatrix& m1, XDoubleMatrix& m2); 

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): -(XDoubleMatrix& m1, XDoubleMatrix& m2)
		//  描述: 矩阵-矩阵
		/// Description: matrix - matrix
		// -------------------------------------------------------------------------
		friend XDoubleMatrix operator - (XDoubleMatrix& m1, XDoubleMatrix& m2); 

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): *(XDoubleMatrix& m1, double c)
		//  描述: 矩阵*标量
		/// Description: matrix * scalar
		// -------------------------------------------------------------------------
		friend XDoubleMatrix operator * (XDoubleMatrix& m, double c);  

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): *(double c, XDoubleMatrix& m1)
		//  描述: 标量*矩阵
		/// Description: scalar * matrix
		// -------------------------------------------------------------------------
		friend XDoubleMatrix operator * (double c, XDoubleMatrix& m); 

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): *(XDoubleMatrix& m1, XDoubleMatrix& m2)
		//  描述: 矩阵*矩阵
		/// Description: matrix * matrix
		// -------------------------------------------------------------------------
		friend XDoubleMatrix operator * (XDoubleMatrix& m1, XDoubleMatrix& m2); 

		//---------------------------------------------------------------------------
		//  重载名(Overloading name): *=(XDoubleMatrix& m, double c)
		//  描述: 矩阵m=矩阵m*标量
		/// Description: matrix m = matrix m * scalar
		// -------------------------------------------------------------------------
		friend void operator *= (XDoubleMatrix& m, double c); 

        //---------------------------------------------------------------------------
        //  重载名(Overloading name): <<(ostream& os, XDoubleMatrix& m)
        //  描述: 流输出
        /// Description: output to stream
        // -------------------------------------------------------------------------
		friend ostream& operator << (ostream& os, XDoubleMatrix& m); 
	};
}