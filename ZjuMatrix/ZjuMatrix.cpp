//=======================================================================
// 文件名(File name): ZjuMatrix.cpp
// 作者(Author):      郑诗澄
// 修改(Reviser):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.03.13
// ----------------------------------------------------------------------
// 描述：实现ZjuMatrix.lib的与矩阵运算相关的函数
// Description: implement some operation for matrix in ZjuMatrix.lib
//=======================================================================

#include "ZjuMatrix.h"
#include<math.h>

using namespace ZjuMatrix;

//---------------------------------------------------------------------------
//  函数名(Function name): BtDB
//  描述: 实现形如K = tranpose(B) * D * B的矩阵乘法，这里矩阵D是对称矩阵。
/// Description: Implement the product like K = tranpose(B) * D * B, where D is symmetric. 
// -------------------------------------------------------------------------
void ZjuMatrix::BtDB(XDoubleMatrix& mB, XSymDoubleMatrix& mD, XSymDoubleMatrix& mK)
{
	int nRowB = mB.rowSize();
	int nColB = mB.colSize();
	int nSizeD = mD.size();

	if (nRowB != nSizeD)
	{
		throw("矩阵维数不匹配，无法进行运算(size of matrices do not match for operation)!");
		return;
	}

	mK.resetSize(nColB);
	for(int i = 1; i <= nColB; i++)
		for(int j = 1; j <= i; j++)
			for(int r = 1; r <= nSizeD; r++)
				for (int s = 1; s <= nSizeD; s++)
					mK(i, j) = mK.Aij(i, j) + mB.Aij(r, i) * mD.Aij(r, s) * mB.Aij(s, j);
}

//---------------------------------------------------------------------------
//  函数名(Function name): GeneralizedJacobi
//  描述: 对两个实数对称矩阵mM与mK同时使用雅可比方法，从而求解广义特征值问题。
/// Description: Using Jacobian method simultaneously for matrices mM and mK to solve generalized eigenvalue problems. 
// -------------------------------------------------------------------------

int ZjuMatrix::GeneralizedJacobi(XSymDoubleMatrix& mM, XSymDoubleMatrix& mK, XDoubleVector& vEigenValue, XSquareDoubleMatrix& mEigenVector, double dTol, int nMaxIteration)
{
	int np = mK.rowSize();
	int nIteration;
	double dThreshold;
	double dCouplingFactor1, dCouplingFactor2;
	dCouplingFactor1 = 0; dCouplingFactor2 = 0;
	XSquareDoubleMatrix mVrjk, mLastEigenVector;
	XDoubleVector vLastEigenValue;
	vLastEigenValue.resetSize(np);
	vEigenValue.resetSize(np);
	mEigenVector.eye(np);
	nIteration = 0;
	for (int i = 1; i <= nMaxIteration; i++)
	{
		nIteration++;
		// 计算第i次迭代时的阈值 (calculate the threshold fot the i-th iteration)
		dThreshold = pow(10, -2 * i);

		// 对所有的(j,k)，当j<k时，计算coupling factor，当其中有一个coupling factor超过阈值时，进行一次变换
		// (For all (j,k), calculate the coupling factor when j<k, and perform a transformation when
		// one of the coupling factors excceds the threshold)
		mVrjk.eye(np);
		for (int j = 1; j <= np; j++)
		{
			// 分别计算mK和mM的coupling factor (calculate the coupling factor of mK and mM respectively)
			for (int k = j + 1; k <= np; k++)
			{
				dCouplingFactor1 = sqrt(mK.Aij(j, k) * mK.Aij(j, k) / mK.Aij(j, j) / mK.Aij(k, k));
				dCouplingFactor2 = sqrt(mM.Aij(j, k) * mM.Aij(j, k) / mM.Aij(j, j) / mM.Aij(k, k));

			    // 如果有一个coupling factor超过阈值，进行一次变换，并计算出变换矩阵
				// (if there is a coupling factor exceeding the threshold, perform a transformation
				// and calculate the transformation matrix)
			    if (dCouplingFactor1 > dThreshold || dCouplingFactor2 > dThreshold)
			    {
				    double dx, da, dx1, dx2,dKkk_, dKjj_, db, dr;
				    XSquareDoubleMatrix mV;
				    dKkk_ = mK.Aij(k, k) * mM.Aij(j, k) - mM.Aij(k, k) * mK.Aij(j, k);
				    dKjj_ = mK.Aij(j, j) * mM.Aij(j, k) - mM.Aij(j, j) * mK.Aij(j, k);
				    da = mK.Aij(j, j) * mM.Aij(k, k) - mK.Aij(k, k) * mM.Aij(j, j);
				    dx1 = da / 2 + sqrt((da * da + 4 * dKkk_ * dKjj_) / 4);
				    dx2 = da / 2 - sqrt((da * da + 4 * dKkk_ * dKjj_) / 4);
				    dx = abs(dx1) > abs(dx2) ? dx1 : dx2;
				    db = dKkk_ / dx;
				    dr = -dKjj_ / dx;

				    // 计算变换矩阵与变换后的mM与mK
					//  (calculate the transformation matrix and mM and mK after transformation)
				    mV.eye(np);
				    mV(j, k) = db;
				    mV(k, j) = dr;
				    mVrjk = mVrjk * mV;

					XBandDoubleMatrix mK_, mM_;
					mK_ = mK;
					mM_ = mM;
				    BtDB(mV, mK_, mK); 
				    BtDB(mV, mM_, mM);
				}
			}
		}

		// 计算第i次迭代的特征值与特征向量的估计值 
		// (Calculate the eigenvalues and eigenvector estimates of the i-th iteration)
		mEigenVector = mEigenVector * mVrjk;
		vEigenValue.resetSize(np);
		for (int m = 1; m <= np; m++)
			vEigenValue(m) = mK.Aij(m, m) / mM.Aij(m, m);

		//cout << i << " mVrijk = " << endl << mVrjk << endl;
		//cout << i << " mEigenVecor = " << endl << mEigenVector << endl;

		// 比较新的特征值和前一次的特征值 
		// (Compare the new eigenvalue with the previous one)
		int flag;
		if (i > 1)
		{
			if (norm2(vEigenValue) - norm2(vLastEigenValue) < dTol)
			{
				flag = 1;
				for (int j = 1; j <= np; j++)
				{
					for (int k = j + 1; k <= np; k++)
					{
						dCouplingFactor1 = sqrt(mK.Aij(j, k) * mK.Aij(j, k) / mK.Aij(j, j) / mK.Aij(k, k));
						dCouplingFactor2 = sqrt(mM.Aij(j, k) * mM.Aij(j, k) / mM.Aij(j, j) / mM.Aij(k, k));
						if (dCouplingFactor1 > dTol || dCouplingFactor2 > dTol)
						{
							flag = 0;
							break;
						}
					}
					if (flag == 0)
						break;
				}
				if (flag == 1)
				{
					vLastEigenValue = vEigenValue;
					break;
				}
			}
		}
		vLastEigenValue = vEigenValue;

	}
	for (int i = 1; i <= np; i++)
		for (int j = 1; j <= np; j++)
		{
			mEigenVector(i, j) = mEigenVector.Aij(i, j) / mM.Aij(j, j);
		}

	return nIteration;
}

//---------------------------------------------------------------------------
//  函数名(Function name): norm2
//  描述: 求实数矩阵vD的二范数。
/// Description: Get the 2-norm of double matrix vD.  
// -------------------------------------------------------------------------

double ZjuMatrix::norm2(XDoubleVector& vD)
{
	int nSizeD = vD.size();
	double dNorm;
	dNorm = 0.0;
	for (int i = 1; i <= nSizeD; i++)
		dNorm += vD.Vi(i) * vD.Vi(i);
	dNorm = sqrt(dNorm);
	return dNorm;
}

//---------------------------------------------------------------------------
//  函数名(Function name): initialVector
//  描述: 求子空间迭代法的初始向量。
/// Description: Get the initial vector of subspace iteration.  
// -------------------------------------------------------------------------

void ZjuMatrix::initialVector(XBandDoubleMatrix& mK, XBandDoubleMatrix& mM, XDoubleMatrix& mX0, int np, int nn)
{
	mX0.resetSize(nn, np);
	XDoubleVector vMK;
	vMK.resetSize(nn);
	
	for (int i = 1; i <= nn; i++)
	{
		vMK(i) = mM.Aij(i, i) / mK.Aij(i, i);	
	}

	XIntVector vI;
	vI.resetSize(nn);
	for (int k = 1; k <= nn; k++)
		vI(k) = k;
	quickDescendSortVector(1, nn, vMK, vI);

	for (int i = 1; i <= nn; i++)
		mX0(i, 1) = mM.Aij(i, i);
	
	for (int i = 2; i <= np; i++)
		mX0(vI.Vi(i - 1), i) = 1;

}

//---------------------------------------------------------------------------
//  函数名(Function name): quickDescendSortVector
//  描述: 采用快速排序，将实向量vMK降序排列，vI记录vMK排序后原编号。
/// Description: Sort vMK in descending order through quick sort, and record the original number of vMK sorted by vI. 
// -------------------------------------------------------------------------
void ZjuMatrix::quickDescendSortVector(int nLeft, int nRight, XDoubleVector& vMK, XIntVector& vI)
{
	int i, j, nTemp;
	double dTemp;
	int nn = vMK.size();

	if (nLeft > nRight)
		return;

	//dTemp中存基准数, vTempVector中存基准数对应的特征向量
	dTemp = vMK.Vi(nLeft);
	nTemp = vI.Vi(nLeft);

	i = nLeft;
	j = nRight;
	while (i != j)
	{
		while (vMK.Vi(j) <= dTemp && i < j)
			j--;
		while (vMK.Vi(i) >= dTemp && i < j)
			i++;
		if (i < j)
		{
			vMK.exchange(i, j);
			vI.exchange(i, j);
		}
	}

	vMK(nLeft) = vMK.Vi(i);
	vMK(i) = dTemp;
	vI(nLeft) = vI.Vi(i);
	vI(i) = nTemp;

	quickDescendSortVector(nLeft, i - 1, vMK, vI);
	quickDescendSortVector(i + 1, nRight, vMK, vI);

}

//---------------------------------------------------------------------------
// 函数名(Function name): quickSortEigenSolution
// 描述: 采用快速排序算法，对求得的特征值与对应的特征向量按特征值升序进行排序。
/// Description: sort the obtained eigenvalues and corresponding eigenvectors in ascending order of eigenvalues through quick sort.
// -------------------------------------------------------------------------
void ZjuMatrix::quickSortEigenSolution(int nLeft, int nRight, XDoubleVector& vEigenValue, XDoubleMatrix& mEigenVector)
{
	int i, j;
	double dTemp;
	XDoubleVector vTempVector;
	if (nLeft > nRight)
		return;

	//dTemp中存基准数, vTempVector中存基准数对应的特征向量
	dTemp = vEigenValue.Vi(nLeft);  
	int nn = mEigenVector.rowSize();
	vTempVector.resetSize(nn);
	for (int k = 1; k <= nn; k++)
		vTempVector(k) = mEigenVector.Aij(k, nLeft);

	i = nLeft;
	j = nRight;
	while (i != j)
	{
		while (vEigenValue.Vi(j) >= dTemp && i < j)
			j--;
		while (vEigenValue.Vi(i) <= dTemp && i < j)
			i++;
		if (i < j)
		{
			vEigenValue.exchange(i, j);
			mEigenVector.colExchange(i, j);
		}
	}

	vEigenValue(nLeft) = vEigenValue.Vi(i);
	vEigenValue(i) = dTemp;
	mEigenVector.colExchange(nLeft, i);
	for (int k = 1; k <= nn; k++)
		mEigenVector(k, i) = vTempVector.Vi(k);

	quickSortEigenSolution(nLeft, i - 1, vEigenValue, mEigenVector);
	quickSortEigenSolution(i + 1, nRight, vEigenValue, mEigenVector);
	
}


//---------------------------------------------------------------------------
//  函数名(Function name): subspaceIteration
//  描述: 用子空间迭代法求带状矩阵mK和mM的前nm阶特征值与特征向量，误差为dTol。
/// Description: Using subspace iteration method to obtain the first nm order eigenvalues and eigenvectors of the banded matrices mK and mM, with an error of dTol.  
// -------------------------------------------------------------------------

int ZjuMatrix::subspaceIteration(XBandDoubleMatrix& mK, XBandDoubleMatrix& mM, XDoubleVector& vEigenValue, XDoubleMatrix& mEigenVector, double dTol, int nMaxIteration, int nm, int nn)
{
	int nIteration = 0;
	int np = nm + 8 < 2 * nm ? nm + 8 : 2 * nm;
	
	mEigenVector.resetSize(nn, np);
	vEigenValue.resetSize(np);

	// 获得初始特征向量 (obtain the initial vector) 
	initialVector(mK, mM, mEigenVector, np, nn);

	//cout << "initialVector = " << endl << mEigenVector << endl;

	XDoubleVector vLastEigenValue;
	vLastEigenValue.resetSize(np);

	for (int k = 1; k <= nMaxIteration; k++)
	{
		cout << "nIteration = " << endl << k << endl;
		
		XDoubleMatrix mP;
		mP = mM * mEigenVector;
		mEigenVector = solve(mK, mP);  

		//cout << "LDL=" << endl << mEigenVector << endl;

		XSymDoubleMatrix mKr, mMr;
		mKr.resetSize(np);
		mMr.resetSize(np);
		XDoubleMatrix mEigenVectorT;
		mEigenVectorT = transpose(mEigenVector);

		//cout << "mEigenVectorT=" << endl << mEigenVectorT << endl;

		mKr = mEigenVectorT * mP;
		BtDB(mEigenVector, mM, mMr);

		//cout << "mKr=" << endl << mKr << endl;
		//cout << "mMr=" << endl << mMr << endl;

		XSquareDoubleMatrix mEigenVector_npdim;
		double dTol_npdim;
		int nMaxIteration_npdim, nIteration_npdim;
		dTol_npdim = 0.0001;
		nMaxIteration_npdim = 1000;

		// 计算降维后的广义特征值 (Calculate the generalized eigenvalue after dimension reduction)
		nIteration_npdim = GeneralizedJacobi(mMr, mKr, vEigenValue, mEigenVector_npdim, dTol_npdim, nMaxIteration_npdim);

		//cout << "mEigenVector_npdim=" << endl << mEigenVector_npdim << endl;

		// 判断收敛并退出循环 (Judge the convergence and exit loop)
		if (k > 1)
		{
			if (abs(abs(norm2(vLastEigenValue) - norm2(vEigenValue)) / norm2(vLastEigenValue)) < dTol)
			{
				nIteration = k;
				break;
			}
		}
		
		vLastEigenValue = vEigenValue;

		// 计算第k次迭代的特征向量 (calculate the eigenvector of the k-th iteration)

		mEigenVector = mEigenVector * mEigenVector_npdim;

		//cout << "mEigenVector = " << endl << mEigenVector << endl;

	}

	quickSortEigenSolution(1, np, vEigenValue, mEigenVector);
	return nIteration;
}


