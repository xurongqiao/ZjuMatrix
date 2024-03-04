//============================================================================
// �ļ���(File name): XBandDoubleMatrix.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.15
// ---------------------------------------------------------------------------
// ����������һ���Գƴ�״�����࣬����˫����ʵ�Գƾ���Ĳ�����
// Description: define a class for symmetric band matrix of double.
// ע�����1. ������кź��кŴ�1��ʼ�������Ǵ�0��ʼ
//           2. ����ֻ���������Ǵ��ڷ��㲿�֣����д洢���ӶԽ�Ԫ�ؿ�ʼ������˳������
//           3. ÿ�еĴ���ɱ䣬��Skyline����
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
		XIntVector m_viDiagonalPos;    // �Խ���Ԫ����һά�����е�λ��(the position at 1D array for the diagonal element)

	public:
		XBandDoubleMatrix();                                          // Ĭ�Ϲ��캯��(default constructor)
		XBandDoubleMatrix(XIntVector& viSkyline);                     // ���캯��1(constructor 1)
		XBandDoubleMatrix(XBandDoubleMatrix& m);                      // ���ƹ��캯��(copy constructor)
		XBandDoubleMatrix& operator= (const XBandDoubleMatrix& m);    // ��ֵ�����(assignment operator)
		XBandDoubleMatrix& operator= (const XSymDoubleMatrix& m);     // ��ֵ�����(assignment operator)
		XBandDoubleMatrix& operator= (const XSquareDoubleMatrix& m);  // ��ֵ�����(assignment operator)
		XBandDoubleMatrix& operator= (const XDoubleMatrix& m);        // ��ֵ�����(assignment operator)
		~XBandDoubleMatrix();                                         // ��������(destructor)

	public:
		void resetSkyline(XIntVector& viSkyline);           // �������ô���(reset the skyline of band matrix)
		virtual void resetSize(int nSize);                  // �������þ����С����ʼ��Ϊ��(resize the matrix and initialized to zero)
		void resetSize();
		virtual void eye(int nSize);                        // �Ѿ�������Ϊ��λ����(reset matrix to identity)
		void eye();
		virtual void random(int nSize);                     // �Ѿ�������Ϊ�������(reset matrix to a random one)
		void random();
		virtual double& operator()(int iRow, int jCol);     // ����Ԫ�ص�����(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;       // ����Ԫ�ص�ֵ(return the value of an element)

	public:
		virtual void ldl();                          // �Գƴ�״�����LDL�ֽ⣬ԭ���󱻷ֽ�������
													 // (LDL decomposition and this symmetical banded matrix is overwritten 
													 //  by the resulting matrix of LDL decomposition) 
		virtual void ldl(XBandDoubleMatrix& mLDL);   // �Գƴ�״�����LDL�ֽ⣬ԭ��������
													 // (LDL decomposition and this symmetical banded matrix remains)
		virtual void solve(XDoubleMatrix& mC);       // ����LDL�ֽ���ⷽ��A*B=C (Solve equation A*B=C) 

	public:
		friend XDoubleMatrix solve(XBandDoubleMatrix& mA, XDoubleMatrix& mC); //����LDL�ֽ���ⷽ��A*B=C (Solve equation A*B=C)
	};
}