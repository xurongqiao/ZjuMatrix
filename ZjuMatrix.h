//=======================================================================
// 文件名(File name): ZjuMatrix.h
// 作者(Author):      郑诗澄
// 修改(Reviser):     徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.03.13
// ----------------------------------------------------------------------
// 描述：引用ZjuMatrix.lib的头文件
// Description: define a head file for ZjuMatrix.lib
//=======================================================================

#pragma once

#include "XVector.h"
#include "XPVector.h"
#include "XList.h"
#include "XDoubleMatrix.h"
#include "XSquareDoubleMatrix.h"
#include "XSymDoubleMatrix.h"
#include "XBandDoubleMatrix.h"

namespace ZjuMatrix {
	void BtDB(XDoubleMatrix& mB, XSymDoubleMatrix& mD, XSymDoubleMatrix& mK);
}