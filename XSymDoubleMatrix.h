//============================================================================
// 文件名(File name): XSymDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.14
// ---------------------------------------------------------------------------
// 描述：定义一个对称矩阵类，用于双精度实对称矩阵的操作。
// Description: define a class for symmetric matrix of double.
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

#pragma once
#include "XSquareDoubleMatrix.h"

namespace ZjuMatrix
{
	class XSymDoubleMatrix :
		public XSquareDoubleMatrix
	{
	public:
		XSymDoubleMatrix();                                          // 默认构造函数(default constructor)
		XSymDoubleMatrix(int nSize);                                 // 构造函数1(constructor 1)
		XSymDoubleMatrix(int nSize, double* pdEntry);                // 构造函数2(constructor 2)
		XSymDoubleMatrix(int nSize, XDoubleVector& vdEntry);         // 构造函数3(constructor 3)
		XSymDoubleMatrix(XSymDoubleMatrix& m);                       // 复制构造函数(copy constructor)
		XSymDoubleMatrix& operator= (const XSymDoubleMatrix& m);     // 赋值运算符(assignment operator)
		XSymDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // 赋值运算符(assignment operator)
		XSymDoubleMatrix& operator= (const XDoubleMatrix& m);        // 赋值运算符(assignment operator)
		~XSymDoubleMatrix();                                         // 析构函数(destructor)

	public:
		virtual void rowExchange(int iRow, int jRow);  // 对称矩阵交换两行(列)，必须同时交换对应的两列(行)，以确保对称性。
		virtual void colExchange(int iCol, int jCol);  // For a symmetric matrix exchanges two rows (columns), two corresponding 
		virtual void exchange(int i, int j);           //  columns (rows) must be exchanged simultaneously to ensure the symmetry

		virtual void resetSize(int nSize);                  // 重新设置矩阵大小并初始化为零(resize the matrix and initialized to zero)
		virtual void eye(int nSize);                        // 把矩阵设置为单位矩阵(reset matrix to identity)
		virtual void random(int nSize);                     // 把矩阵设置为随机矩阵(reset matrix to a random one)
		virtual double& operator()(int iRow, int jCol);     // 返回元素的引用(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;       // 返回元素的值(return the value of an element)

	private:
		double maxOffDiagonalPos(int& iRow, int& jCol);       // 查找绝对值最大的非对角元的位置，并返回其值
															  //  (Find the position of the max off-diagonal entries and return the value)
		void pap(int i, int j, double dCosine, double dSine); // 对称矩阵的初等正交相似变换(PAP^t),结果覆盖原矩阵
															  //    dCosine = cos(theta), dSine = sin(theta)
															  // (Elementary orthogonal similar transformation of a symmetric matrix,
															  //   the result covers the original matrix)
		double pap(int i, int j);  // 对称矩阵的初等正交相似变换使第i行第j列元素为零
								   // The elementary orthogonal similar transformation of a symmetric matrix 
								   //  causes the element in the i-th row and j-th column to be zero

	public:
		virtual void ldl();    // 对称矩阵的LDL分解，结果覆盖原矩阵(LDL decomposition and this symmetric matrix is overwritren)
		virtual void ldl(XSymDoubleMatrix& mLDL);   // 对称矩阵的LDL分解(LDL decomposition and this symmetric matrix remains)
		virtual void solve(XDoubleMatrix& mC);      // 利用LDL分解求解方程
		virtual void backSubstitute(XDoubleMatrix& mC); // LDL分解完成后的回代
		virtual int Jacobi(XDoubleVector& vEigenValue,                  //利用Jacobi法求特征值和特征向量
			XSquareDoubleMatrix& mEigenVector,           //(eigen-values and eigen-vectors by Jacobi method)
			double dTol, int nMaxIteration);
		virtual int powerIteration(double& dEigenValue,            // 幂迭代法求特征值
			XDoubleVector& vEigenVector,           // (eigen-value and eigen-vector by power iteration method)
			double dTol, int nMaxIteration);
		virtual int invPowerIteration(double& dEigenValue,         // 反幂迭代法求特征值
			XDoubleVector& vEigenVector, double dShift,            // (eigen-value and eigen-vector by inverse power iteration method)
			double dTol, int nMaxIteration);

	public:
		friend XDoubleMatrix solve(XSymDoubleMatrix& mA, XDoubleMatrix& mC); //利用LDL分解求解方程A*B=C (Solve equation A*B=C)
		friend int eig(XSymDoubleMatrix& mA, XDoubleVector& vEigenValue,     //利用Jacobi法求特征值和特征向量
			XSquareDoubleMatrix& mEigenVector,                   //(eigen-values and eigen-vectors by Jacobi method)
			double dTol, int nMaxIteration);
	};
}