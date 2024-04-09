//=======================================================================

// 文件名(File name):  ZjuMatrix.h
// 作者(Author):       郑诗澄
// 修改(Reviser):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):         2023.03.13
// 版本(Version):      v1.0
// ----------------------------------------------------------------------
// 描述：引用ZjuMatrix.lib的头文件
//       Description: define a head file for ZjuMatrix.lib
//=======================================================================

#pragma once

#include "XVector.h"
#include "XPVector.h"
#include "XList.h"
#include "XDoubleMatrix.h"
#include "XSquareDoubleMatrix.h"
#include "XSymDoubleMatrix.h"
#include "XBandDoubleMatrix.h"

/// Define a head file for ZjuMatrix.lib.
namespace ZjuMatrix {
	void BtDB(XDoubleMatrix& mB, XSymDoubleMatrix& mD, XSymDoubleMatrix& mK); 
	                                                                 // 实现形如K=BTDB的矩阵乘法，其中D是对称矩阵
	                                                                 // implement the product like K = tranpose(B) * D * B, where D is symmetric
	int GeneralizedJacobi(XSymDoubleMatrix& mM, XSymDoubleMatrix& mK, 
		                  XDoubleVector& vEigenValue,                //利用广义Jacobi法求特征值和特征向量
		                  XSquareDoubleMatrix& mEigenVector,         //(eigen-values and eigen-vectors by Generalized Jacobi method)
		                  double dTol, int nMaxIteration);
	double norm2(XDoubleVector& vD);                                 // 求实数向量的二范数 (return the 2-norm of a real vector)
	void initialVector(XBandDoubleMatrix& mK, XBandDoubleMatrix& mM, 
		               XDoubleMatrix& mX0, int np, int nn);          // 求子空间迭代法的初始迭代向量 (obtain the initial vector of subspace iteration method )
	void quickDescendSortVector(int nLeft, int nRight, XDoubleVector& vMK, XIntVector& vI); 
	                                                                 // 采用快速排序，对一维实向量进行降序排序 
	                                                                 // (sort one-dimensional real vectors in descending order through quick sort)
	void quickSortEigenSolution(int nLeft, int nRight, XDoubleVector& vEigenValue, XDoubleMatrix& mEigenVector);
	                                                                 // 采用快速排序算法，对求得的特征值与对应的特征向量按特征值升序进行排序
	                                                                 // (sort the obtained eigenvalues and corresponding eigenvectors in ascending order of eigenvalues through quick sort)
	int subspaceIteration(XBandDoubleMatrix& mK, XBandDoubleMatrix& mM,
		                  XDoubleVector& vEigenValue, XDoubleMatrix& mEigenVector,
		                  double dTol, int nMaxIteration,            // 利用子空间迭代法求前m阶的特征值和相应的特征向量
		                  int nm, int nn);                           // (calculate the first m mode of eigenvalues and corresponding eigenvectors through subspace iteration method)
}