//=======================================================================
// �ļ���(File name): XSquareDoubleMatrix.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.13
// ----------------------------------------------------------------------
// ����������һ�����ξ����࣬����˫����ʵ����Ĳ�����
// Description: define a class for square matrix of double.
// ע�����������кź��кŴ�1��ʼ�������Ǵ�0��ʼ
// Notice: the row and column number count from 1 not 0
//=======================================================================

#pragma once
#include "XVector.h"
#include "XDoubleMatrix.h"

namespace ZjuMatrix {
	class XSquareDoubleMatrix :
		public XDoubleMatrix
	{
	public:
		XSquareDoubleMatrix();                                          // Ĭ�Ϲ��캯��(default constructor)
		XSquareDoubleMatrix(int nSize);                                 // ���캯��1(constructor 1)
		XSquareDoubleMatrix(int nSize, double* pdEntry);                // ���캯��2(constructor 2)
		XSquareDoubleMatrix(int nSize, XDoubleVector& vdEntry);         // ���캯��3(constructor 3)
		XSquareDoubleMatrix(XSquareDoubleMatrix& m);                    // ���ƹ��캯��(copy constructor)
		XSquareDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // ��ֵ�����(assignment operator)
		XSquareDoubleMatrix& operator= (const XDoubleMatrix& m);        // ��ֵ�����(assignment operator)
		~XSquareDoubleMatrix();                                         // ��������(destructor)

	public:
		void resetSize(int nRow, int nCol);         // �������þ����С����ʼ��Ϊ��(resize the matrix and initialized to zero)
		virtual void resetSize(int nSize);          // �������þ����С����ʼ��Ϊ��(resize the matrix and initialized to zero)
		void eye(int nRow, int nCol);               // �Ѿ�������Ϊ��λ����(reset matrix to identity)
		virtual void eye(int nSize);                // �Ѿ�������Ϊ��λ����(reset matrix to identity)
		void random(int nRow, int nCol);            // �Ѿ�������Ϊ�������(reset matrix to a random one)
		virtual void random(int nSize);             // �Ѿ�������Ϊ�������(reset matrix to a random one)
		int size() const;                           // ���ؾ���Ĵ�С(return the size)

	protected:
		int colPivot(int kCol)const;               // ��������Ԫ���к�(return the row number of a pivot in a column)

	public:
		// LU�ֽ�(Doolittle LU decomposition)
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
		virtual double det();                  // ���������ʽֵ(determinant of square matrix)
		virtual double trace();                // ����ļ�(trace of square matrix)
		virtual XSquareDoubleMatrix inverse(); // �����(inverse of square matrix)
		virtual void solve(XDoubleMatrix& mC); // ����LU�ֽ�ⷽ��(solve the equation using LU decomposition)

	public:
		friend XDoubleMatrix solve(XSquareDoubleMatrix& mA, XDoubleMatrix& mC);  // ��ⷽ��A*B=C (Solve equation A*B=C)
	};
}