//============================================================================
// �ļ���(File name): XSymDoubleMatrix.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.14
// ---------------------------------------------------------------------------
// ����������һ���Գƾ����࣬����˫����ʵ�Գƾ���Ĳ�����
// Description: define a class for symmetric matrix of double.
// ע�����1. ������кź��кŴ�1��ʼ�������Ǵ�0��ʼ
//           2. ����ֻ���������ǲ��֣����д洢���ӶԽ�Ԫ�ؿ�ʼ������˳������
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
		XSymDoubleMatrix();                                          // Ĭ�Ϲ��캯��(default constructor)
		XSymDoubleMatrix(int nSize);                                 // ���캯��1(constructor 1)
		XSymDoubleMatrix(int nSize, double* pdEntry);                // ���캯��2(constructor 2)
		XSymDoubleMatrix(int nSize, XDoubleVector& vdEntry);         // ���캯��3(constructor 3)
		XSymDoubleMatrix(XSymDoubleMatrix& m);                       // ���ƹ��캯��(copy constructor)
		XSymDoubleMatrix& operator= (const XSymDoubleMatrix& m);     // ��ֵ�����(assignment operator)
		XSymDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // ��ֵ�����(assignment operator)
		XSymDoubleMatrix& operator= (const XDoubleMatrix& m);        // ��ֵ�����(assignment operator)
		~XSymDoubleMatrix();                                         // ��������(destructor)

	public:
		virtual void rowExchange(int iRow, int jRow);  // �Գƾ��󽻻�����(��)������ͬʱ������Ӧ������(��)����ȷ���Գ��ԡ�
		virtual void colExchange(int iCol, int jCol);  // For a symmetric matrix exchanges two rows (columns), two corresponding 
		virtual void exchange(int i, int j);           //  columns (rows) must be exchanged simultaneously to ensure the symmetry

		virtual void resetSize(int nSize);                  // �������þ����С����ʼ��Ϊ��(resize the matrix and initialized to zero)
		virtual void eye(int nSize);                        // �Ѿ�������Ϊ��λ����(reset matrix to identity)
		virtual void random(int nSize);                     // �Ѿ�������Ϊ�������(reset matrix to a random one)
		virtual double& operator()(int iRow, int jCol);     // ����Ԫ�ص�����(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;       // ����Ԫ�ص�ֵ(return the value of an element)

	private:
		double maxOffDiagonalPos(int& iRow, int& jCol);       // ���Ҿ���ֵ���ķǶԽ�Ԫ��λ�ã���������ֵ
															  //  (Find the position of the max off-diagonal entries and return the value)
		void pap(int i, int j, double dCosine, double dSine); // �Գƾ���ĳ����������Ʊ任(PAP^t),�������ԭ����
															  //    dCosine = cos(theta), dSine = sin(theta)
															  // (Elementary orthogonal similar transformation of a symmetric matrix,
															  //   the result covers the original matrix)
		double pap(int i, int j);  // �Գƾ���ĳ����������Ʊ任ʹ��i�е�j��Ԫ��Ϊ��
								   // The elementary orthogonal similar transformation of a symmetric matrix 
								   //  causes the element in the i-th row and j-th column to be zero

	public:
		virtual void ldl();    // �Գƾ����LDL�ֽ⣬�������ԭ����(LDL decomposition and this symmetric matrix is overwritren)
		virtual void ldl(XSymDoubleMatrix& mLDL);   // �Գƾ����LDL�ֽ�(LDL decomposition and this symmetric matrix remains)
		virtual void solve(XDoubleMatrix& mC);      // ����LDL�ֽ���ⷽ��
		virtual void backSubstitute(XDoubleMatrix& mC); // LDL�ֽ���ɺ�Ļش�
		virtual int Jacobi(XDoubleVector& vEigenValue,                  //����Jacobi��������ֵ����������
			XSquareDoubleMatrix& mEigenVector,           //(eigen-values and eigen-vectors by Jacobi method)
			double dTol, int nMaxIteration);
		virtual int powerIteration(double& dEigenValue,            // �ݵ�����������ֵ
			XDoubleVector& vEigenVector,           // (eigen-value and eigen-vector by power iteration method)
			double dTol, int nMaxIteration);
		virtual int invPowerIteration(double& dEigenValue,         // ���ݵ�����������ֵ
			XDoubleVector& vEigenVector, double dShift,            // (eigen-value and eigen-vector by inverse power iteration method)
			double dTol, int nMaxIteration);

	public:
		friend XDoubleMatrix solve(XSymDoubleMatrix& mA, XDoubleMatrix& mC); //����LDL�ֽ���ⷽ��A*B=C (Solve equation A*B=C)
		friend int eig(XSymDoubleMatrix& mA, XDoubleVector& vEigenValue,     //����Jacobi��������ֵ����������
			XSquareDoubleMatrix& mEigenVector,                   //(eigen-values and eigen-vectors by Jacobi method)
			double dTol, int nMaxIteration);
	};
}