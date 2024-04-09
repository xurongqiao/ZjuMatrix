// ZjuMatrixExampleOne.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include<string>
#include "..\ZjuMatrix\ZjuMatrix.h"
#include<windows.h>

using namespace ZjuMatrix;
using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    XDoubleMatrix m1; //(3, 3, adEntry1);
    XDoubleMatrix m2; // (3, 3, adEntry2);
    m1.random(4, 4);
    m2.random(4, 4);
    cout << "m1=" << endl << m1 << endl;
    cout << "m2=" << endl << m2 << endl;
    XDoubleMatrix m3;
    m3 = m1 + m2;
    cout << "m3=m1+m2=" << endl << m3 << endl;
    m3 = m1 * m2;
    cout << "m3=m1*m2=" << endl << m3 << endl;
    m3 = m2 * m1;
    cout << "m3=m2*m1=" << endl << m3 << endl;
    XDoubleMatrix m4;
    m4 = transpose(m3);
    cout << "m4=transpose(m3)" << endl << m4 << endl;
    m4.rowExchange(1, 3);
    cout << "m4([3<=>1],:)=" << endl << m4 << endl;
    m4.colExchange(3, 1);
    cout << "m4(:,[3<=>1])=" << endl << m4 << endl;
    m4 = m4 * 2.0;
    cout << "m4=m4*2=" << endl << m4 << endl;
    m4 = 1.5 * m4;
    cout << "m4=1.5*m4=" << endl << m4 << endl;
    int aiRow[] = { 1,3 };
    int aiCol[] = { 3,2 };
    XIntVector viRow(2, aiRow);
    XIntVector viCol(2, aiCol);
    XDoubleMatrix m5;
    m5 = m4.subMatrix(viRow, viCol);
    cout << "m5=m4([1,3],[3,2])=" << endl << m5 << endl;
    XSquareDoubleMatrix m6;
    m6 = m5;
    cout << "m6=m5=" << endl << m6;
    XSquareDoubleMatrix m7;
    m7 = m6 * m5;
    cout << "m7=m6*m5=" << endl << m7;
    XDoubleMatrix m8;
    m8.random(4, 6);
    cout << "m8=" << endl << m8 << endl;
    m8 = transpose(m8);
    cout << "m8=transpose(m8)=" << endl << m8 << endl;
    m7.random(5);
    cout << "m7=" << endl << m7 << endl;

    XSquareDoubleMatrix mLU, mL, mU, mP;
    XIntVector vP;
    m7.lu(mL, mU, mP);
    cout << "[L,U,P] = LU(m7) " << endl;
    cout << "L=" << endl << mL << endl;
    cout << "U=" << endl << mU << endl;
    cout << "P=" << endl << mP << endl;
    m7.lu(mL, mU, vP);
    cout << "[L,U,p] = LU(m7) " << endl;
    cout << "L=" << endl << mL << endl;
    cout << "U=" << endl << mU << endl;
    cout << "p=" << endl << vP << endl;
    m7.lu(mL, mU);
    cout << "L*U = m7" << endl;
    cout << "L=" << endl << mL << endl;
    cout << "U=" << endl << mU << endl;
    m7.lu(mLU);
    cout << "LU =" << endl << mLU << endl;
    cout << "det(m7)=" << m7.det() << endl;
    cout << "trance(m7)=" << m7.trace() << endl;
    m8.random(5, 3);
    m1 = solve(m7, m8);
    cout << "m7=" << endl << m7 << endl;
    cout << "m8=" << endl << m8 << endl;
    cout << "m1=m7\\m8=" << endl << m1 << endl;
    XSquareDoubleMatrix m9;
    m9 = m7.inverse();
    cout << "m9=inv(m7)=" << endl;
    cout << m9 << endl;
    XSquareDoubleMatrix m10;
    XDoubleMatrix m11;
    m11.random(5, 8);
    m10 = m11;
    cout << "m11=" << endl << m11 << endl;
    cout << "m10=square(m11)=" << endl << m10 << endl;

    XSymDoubleMatrix m12, m13;
    m12.random(5);
    cout << "m12=" << endl << m12 << endl;
    m10 = m12.inverse();
    cout << "m10=inverse(m12)=" << endl << m10 << endl;
    cout << "det(m12) = " << m12.det() << endl;
    cout << "det(m10) = " << m10.det() << endl;
    m12.ldl(m13);
    cout << "m13=LDL(m12)=" << endl << m13;
    XDoubleMatrix m14, m15;
    m14.random(5, 3);
    m15 = solve(m12, m14);
    cout << "m12 = " << endl << m12;
    cout << "m14 = " << endl << m14;
    cout << "m15 = m12\\m14 = " << endl << m15;
    m12.solve(m14);
    cout << "m14 = m12\\m14 = " << endl << m14;
    m12.random(8);
    cout << "m12 = " << endl << m12;
    m12.exchange(3, 6);
    cout << "m12(3<->6) = " << endl << m12;

    XBandDoubleMatrix m20;
    m20.random(10);
    cout << "m20=" << endl << m20 << endl;
    m20.ldl();
    cout << "m20=" << endl << m20 << endl;
    m20.random(20);
    cout << "m20=" << endl << m20 << endl;
    XDoubleMatrix m21, m22;
    m21.random(20, 3);
    cout << "m21=" << endl << m21 << endl;
    m22 = solve(m20, m21);
    m20.solve(m21);
    cout << "m20\\m21=" << endl << m21 << endl;
    cout << "m20\\m21=" << endl << m22 << endl;

    XSymDoubleMatrix m30;
    m30.random(8);
    cout << "m30=" << endl << m30 << endl;
    XDoubleVector vEigValue;
    XSquareDoubleMatrix mEigVector;
    int nIteration = eig(m30, vEigValue, mEigVector, 1e-10, 500);
    cout << "m30" << endl << m30 << endl;
    cout << "nIteration=" << nIteration << endl;
    cout << "EigenValue=" << endl << vEigValue << endl;
    cout << "EigenVector=" << endl << mEigVector << endl;
    double d1, d2;
    XDoubleVector v1, v2;
    nIteration = m30.powerIteration(d1, v1, 1e-10, 500);
    cout << "nIteration=" << nIteration << endl;
    cout << "EigenValue= " << d1 << endl;
    cout << "EigenVector=" << endl << v1 << endl;

    nIteration = m30.invPowerIteration(d2, v2, -0.08, 1e-10, 500);
    cout << "nIteration=" << nIteration << endl;
    cout << "EigenValue= " << d2 << endl;
    cout << "EigenVector=" << endl << v2 << endl;

    XIntList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    XIntVector vL;
    list.toVector(vL);
    cout << "vector" << vL;
    list.append(10);
    list.append(9);
    list.append(8);
    list.append(7);
    list.append(6);
    list.append(5);
    list.toVector(vL);
    cout << "vector" << vL;



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
