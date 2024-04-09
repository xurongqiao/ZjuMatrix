//=======================================================================
// 文件名(File name): XSquareDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.13
// ----------------------------------------------------------------------
// 描述：定义一个方形矩阵类，用于双精度实矩阵的操作。
// Description: define a class for square matrix of double.
// 注意事项：矩阵的行号和列号从1开始，而不是从0开始
// Notice: the row and column number count from 1 not 0
//=======================================================================

#pragma once
#include "XVector.h"
#include "XDoubleMatrix.h"

namespace ZjuMatrix {
	/// Define a class for square matrix of double.
	class XSquareDoubleMatrix :
		public XDoubleMatrix
	{
	public:
		XSquareDoubleMatrix();                                          // 默认构造函数(default constructor)
		XSquareDoubleMatrix(int nSize);                                 // 构造函数1(constructor 1)
		XSquareDoubleMatrix(int nSize, double* pdEntry);                // 构造函数2(constructor 2)
		XSquareDoubleMatrix(int nSize, XDoubleVector& vdEntry);         // 构造函数3(constructor 3)
		XSquareDoubleMatrix(XSquareDoubleMatrix& m);                    // 复制构造函数(copy constructor)
		XSquareDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // 赋值运算符(assignment operator)
		XSquareDoubleMatrix& operator= (const XDoubleMatrix& m);        // 赋值运算符(assignment operator)
		~XSquareDoubleMatrix();                                         // 析构函数(destructor)

	public:
		void resetSize(int nRow, int nCol);         // 重新设置矩阵大小并初始化为零(resize the matrix and initialized to zero)
		virtual void resetSize(int nSize);          // 重新设置矩阵大小并初始化为零(resize the matrix and initialized to zero)
		void eye(int nRow, int nCol);               // 把矩阵设置为单位矩阵(reset matrix to identity)
		virtual void eye(int nSize);                // 把矩阵设置为单位矩阵(reset matrix to identity)
		void random(int nRow, int nCol);            // 把矩阵设置为随机矩阵(reset matrix to a random one)
		virtual void random(int nSize);             // 把矩阵设置为随机矩阵(reset matrix to a random one)
		int size() const;                           // 返回矩阵的大小(return the size)

	protected:
		int colPivot(int kCol)const;               // 返回列主元的行号(return the row number of a pivot in a column)

	public:
		// LU分解(Doolittle LU decomposition)
		//        [U_11  U_12  U_13 ... U_1n]       [ 1     0     0   ...  0 ]      [U_11  U_12  U_13 ... U_1n] 
		//        [L_21  U_22  U_23 ... U_2n]       [L_21   1     0   ...  0 ]      [ 0    U_22  U_23 ... U_2n]
		//  [mLU]=[L_31  L_32  U_33 ... U_3n]  [mL]=[L_31  L_32   1   ...  0 ] [mU]=[ 0      0   U_33 ... U_3n] 
		//        [ ...   ...   ... ...  ...]       [ ...   ...   ... ... ...]      [ ...   ...   ... ...  ...] 
		//        [L_n1  L_n2  L_n3 ... U_nn]       [L_n1  L_n2  L_n3 ...  1 ]      [ 0      0     0  ... U_nn]
		void lu(XSquareDoubleMatrix& mLU);                                                  // A = LU
		void lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU);                          // A = LU
		void lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XSquareDoubleMatrix& mP); // PA = LU
		void lu(XSquareDoubleMatrix& mLU, XIntVector& vP);                                  // A(p,:) = LU
		void lu(XSquareDoubleMatrix& mL, XSquareDoubleMatrix& mU, XIntVector& vP);          // A(p,:) = LU

	public:
		virtual double det();                  // 方阵的行列式值(determinant of square matrix)
		virtual double trace();                // 方阵的迹(trace of square matrix)
		virtual XSquareDoubleMatrix inverse(); // 逆矩阵(inverse of square matrix)
		virtual void solve(XDoubleMatrix& mC); // 利用LU分解解方程(solve the equation using LU decomposition)

	public:
		//---------------------------------------------------------------------------
		//  函数名(Function name): solve(XSquareDoubleMatrix& mA, XDoubleMatrix& mC)
		//  描述: 利用LU分解求解方程A*B=C
		/// Description: solve the equation A*B=C using LU decomposition
		// -------------------------------------------------------------------------
		friend XDoubleMatrix solve(XSquareDoubleMatrix& mA, XDoubleMatrix& mC);  // 求解方程A*B=C (Solve equation A*B=C)
	};
}