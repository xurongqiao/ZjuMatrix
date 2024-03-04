//=======================================================================
// �ļ���(File name): ZjuMatrix.h
// ����(Author):      ֣ʫ��
// �޸�(Reviser):     ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.03.13
// ----------------------------------------------------------------------
// ����������ZjuMatrix.lib��ͷ�ļ�
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