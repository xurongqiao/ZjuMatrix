//============================================================================
// 文件名(File name): XBandDoubleMatrix.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.15
// ---------------------------------------------------------------------------
// 描述：定义一个对称带状矩阵类，用于双精度实对称矩阵的操作。
// Description: define a class for symmetric band matrix of double.
// 注意事项：1. 矩阵的行号和列号从1开始，而不是从0开始
//           2. 矩阵只保存下三角带内非零部分，按行存储，从对角元素开始，保存顺序如下
//           3. 每行的带宽可变，用Skyline描述
//               1: [ | 1
//               2: [ | 3   2
//               3: [ | 6   5   4                 DiagonalPos(k)
//              ... [ ... ... ...               /
//               k: [   0   0   0 | *   *  ... *     
//                                +------------+ 
//                                  Skyline(k)
//              ... [   0   0   0   0 | *   *  ... *     
//              ... [  ... ... ... ... ... ... ... ... ...
// Notice: 1. the row and column number count from 1 not 0
//         2. only the low triangle part in band of the matrix is saved in rows,
//             starting with diagonal elements as shown 
//         3. the band width is not constant and described by a Skyline
//               1: [ | 1
//               2: [ | 3   2
//               3: [ | 6   5   4                 DiagonalPos(k)
//              ... [ ... ... ...               /
//               k: [   0   0   0 | *   *  ... *     
//                                +------------+ 
//                                  Skyline(k)
//              ... [   0   0   0   0 | *   *  ... *     
//              ... [  ... ... ... ... ... ... ... ... ...
//============================================================================

#pragma once
#include "XSymDoubleMatrix.h"

namespace ZjuMatrix {

	class XBandDoubleMatrix :
		public XSymDoubleMatrix
	{
	protected:
		XIntVector m_viSkyline;        // the skyline
		XIntVector m_viDiagonalPos;    // 对角线元素在一维数组中的位置(the position at 1D array for the diagonal element)

	public:
		XBandDoubleMatrix();                                          // 默认构造函数(default constructor)
		XBandDoubleMatrix(XIntVector& viSkyline);                     // 构造函数1(constructor 1)
		XBandDoubleMatrix(XBandDoubleMatrix& m);                      // 复制构造函数(copy constructor)
		XBandDoubleMatrix& operator= (const XBandDoubleMatrix& m);    // 赋值运算符(assignment operator)
		XBandDoubleMatrix& operator= (const XSymDoubleMatrix& m);     // 赋值运算符(assignment operator)
		XBandDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // 赋值运算符(assignment operator)
		XBandDoubleMatrix& operator= (const XDoubleMatrix& m);        // 赋值运算符(assignment operator)
		~XBandDoubleMatrix();                                         // 析构函数(destructor)

	public:
		void resetSkyline(XIntVector& viSkyline);           // 重新设置带宽(reset the skyline of band matrix)
		virtual void resetSize(int nSize);                  // 重新设置矩阵大小并初始化为零(resize the matrix and initialized to zero)
		void resetSize();
		virtual void eye(int nSize);                        // 把矩阵设置为单位矩阵(reset matrix to identity)
		void eye();
		virtual void random(int nSize);                     // 把矩阵设置为随机矩阵(reset matrix to a random one)
		void random();
		virtual double& operator()(int iRow, int jCol);     // 返回元素的引用(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;       // 返回元素的值(return the value of an element)

	public:
		virtual void ldl();                          // 对称带状矩阵的LDL分解，原矩阵被分解结果覆盖
													 // (LDL decomposition and this symmetical banded matrix is overwritten 
													 //  by the resulting matrix of LDL decomposition) 
		virtual void ldl(XBandDoubleMatrix& mLDL);   // 对称带状矩阵的LDL分解，原矩阵保留。
													 // (LDL decomposition and this symmetical banded matrix remains)
		virtual void solve(XDoubleMatrix& mC);       // 利用LDL分解求解方程A*B=C (Solve equation A*B=C) 

	public:
		friend XDoubleMatrix solve(XBandDoubleMatrix& mA, XDoubleMatrix& mC); //利用LDL分解求解方程A*B=C (Solve equation A*B=C)
	};
}