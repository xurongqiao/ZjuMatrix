//=======================================================================
// �ļ���(File name): XDoubleMatrix.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.12
// ----------------------------------------------------------------------
// ����������һ�������࣬����˫����ʵ����Ĳ�����
// Description: define a class for matrix of double.
// ע�����������кź��кŴ�1��ʼ�������Ǵ�0��ʼ
// Notice: the row and column number count from 1 not 0
//=======================================================================

#pragma once

namespace ZjuMatrix {
	class XDoubleMatrix
	{
	protected:
		int m_nRow;                  // ��������(row size of matrix)
		int m_nCol;                  // ��������(column size of matrix)
		XDoubleVector m_vdEntry;     // ����Ԫ��(element of matrix)

	public:
		XDoubleMatrix();                                            // Ĭ�Ϲ��캯��(default constructor)
		XDoubleMatrix(int nRow, int nCol);                          // ���캯��1(constructor 1)
		XDoubleMatrix(int nRow, int nCol, double* pdEntry);         // ���캯��2(constructor 2)
		XDoubleMatrix(int nRow, int nCol, XDoubleVector& vdEntry);  // ���캯��3(constructor 3)
		XDoubleMatrix(XDoubleMatrix& m);                            // ���ƹ��캯��(copy constructor)
		XDoubleMatrix& operator= (const XDoubleMatrix& m);          // ��ֵ�����(assignment operator)
		~XDoubleMatrix();                                           // ��������(destructor)

	public:
		void resetSize(int nRow, int nCol);              // �������þ����С����ʼ��Ϊ��(resize the matrix and initialized to zero)
		void eye(int nRow, int nCol);                    // �Ѿ�������Ϊ��λ����(reset matrix to identity)
		void random(int nRow, int nCol);                 // �Ѿ���Ԫ������Ϊ�����(reset matrix to a random one)
		virtual void rowExchange(int iRow, int jRow);    // ��������(exchange two rows)
		virtual void colExchange(int iCol, int jCol);    // ��������(exchange tow columns)
		int rowSize() const;                             // ���ؾ��������(return the row size)
		int colSize() const;                             // ���ؾ��������(return the column size)
		virtual double& operator()(int iRow, int jCol);  // ����Ԫ�ص�����(return the reference of an element)
		virtual double Aij(int iRow, int jCol) const;    // ����Ԫ�ص�ֵ(return the value of an element)
		XDoubleMatrix subMatrix(XIntVector viRow, XIntVector viCol);  // �Ӿ���(return a sub-matrix)

	public:
		friend double max(const XDoubleMatrix& m); //����Ԫ��ֵ(value of maximum element)
		friend double min(const XDoubleMatrix& m); //��С��Ԫ��ֵ(value of minimum element)
		friend XDoubleMatrix transpose(XDoubleMatrix& m);                       //����ת��(matrix transpose)
		friend XDoubleMatrix operator + (XDoubleMatrix& m1, XDoubleMatrix& m2); //����+����(matrix addition)
		friend XDoubleMatrix operator - (XDoubleMatrix& m1, XDoubleMatrix& m2); //����-����(matrix - matrix)
		friend XDoubleMatrix operator * (XDoubleMatrix& m, double c);           //����*����(matrix * scalar)
		friend XDoubleMatrix operator * (double c, XDoubleMatrix& m);           //����*����(scalar * matrix)
		friend XDoubleMatrix operator * (XDoubleMatrix& m1, XDoubleMatrix& m2); //����*����(matrix * matrix)
		friend ostream& operator << (ostream& os, XDoubleMatrix& m);            //�����(output to stream)
	};
}