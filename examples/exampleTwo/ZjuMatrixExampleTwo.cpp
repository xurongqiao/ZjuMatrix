// ZjuMatrixExampleTwo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include<string>
#include "../../ZjuMatrix/ZjuMatrix.h"

using namespace ZjuMatrix;
using namespace std;

int main()
{
    
    // Example2: 子空间迭代法求解广义特征值问题 START
    // 用txt读有限元数据
    int nIteration1, nMaxIteration, np, nn;
    
    XDoubleVector vEigenValue;
    XDoubleMatrix mEigenVector;
    double dTol;
    XSymDoubleMatrix mK_, mM_;
    XBandDoubleMatrix mM, mK;
    np = 6;
    nn = 299;
    mK_.resetSize(nn);
    mM_.resetSize(nn);
    mM.resetSize(nn);
    mK.resetSize(nn);
    vEigenValue.resetSize(np);
    mEigenVector.resetSize(nn, np);

    ifstream infileK;
    infileK.open("ExamTwo_gK.txt", ios::in);

    if (!infileK.is_open())
    {
        cout << "fail to read file ExamTwo_gK.txt" << endl;
        return 0;
    }
    string bufK;
    while (getline(infileK, bufK))
    {
        int nLeftBracket, nRightBracket, nDot;
        nLeftBracket = bufK.find("(");
        nRightBracket = bufK.find(")");
        nDot = bufK.find(",");
        int i = std::stoi(bufK.substr(nLeftBracket + 1, nDot - nLeftBracket - 1));
        int j = std::stoi(bufK.substr(nDot + 1, nRightBracket - nDot - 1));
        string sk = bufK.substr(nRightBracket + 1);
        if (!sk.empty())
        {
            sk.erase(0, sk.find_first_not_of(" "));
            sk.erase(sk.find_last_not_of(" ") + 1);
        }
        double dk = std::stod(sk);
        mK_(i, j) = dk;
        if (mK_(i, j) == 0)
            mK_(i, j) = 1e-12;
    }

    infileK.close();

    ifstream infileM;
    infileM.open("ExamTwo_gM.txt", ios::in);

    if (!infileM.is_open())
    {
        cout << "fail to read file ExamTwo_gM.txt" << endl;
        return 0;
    }
    string bufM;
    while (getline(infileM, bufM))
    {
        //cout << "bufM = " << bufM << endl;
        int nLeftBracket, nRightBracket, nDot;
        nLeftBracket = bufM.find("(");
        nRightBracket = bufM.find(")");
        nDot = bufM.find(",");
        int i = std::stoi(bufM.substr(nLeftBracket + 1, nDot - nLeftBracket - 1));
        int j = std::stoi(bufM.substr(nDot + 1, nRightBracket - nDot - 1));
        string sm = bufM.substr(nRightBracket + 1);
        if (!sm.empty())
        {
            sm.erase(0, sm.find_first_not_of(" "));
            sm.erase(sm.find_last_not_of(" ") + 1);
        }
        double dm = std::stod(sm);
        mM_(i, j) = dm;
        if (mM_(i, j) == 0)
            mM_(i, j) = 1e-12;
    }

    infileM.close();

    mK = mK_;
    mM = mM_;

    DWORD start_time = GetTickCount64();


    XDoubleMatrix mX0;
    int nm = 3;
    dTol = 0.000001;
    nMaxIteration = 100;
    int nIteration = subspaceIteration(mK, mM, vEigenValue, mEigenVector, dTol, nMaxIteration, nm, nn);
    cout << "vEigenValue =" << endl << vEigenValue << endl;
    cout << "特征向量 " << endl;
    cout << "eigenvectors " << endl;
    for (int i = 1; i <= nn; i++)
    {
        for (int j = 1; j <= nm; j++)
            printf("%.15f       ", mEigenVector.Aij(i, j));
        cout << endl;
    }

    DWORD end_time = GetTickCount64();
    cout << "这个程序运行时间为：" << (end_time - start_time) << "ms." << endl;
    cout << "The run time of the program is " << (end_time - start_time) << "ms." << endl;

    XDoubleVector vV3;
    vV3.resetSize(303);


    for (int i = 3; i <= 300; i++)
    {
        vV3(i) = mEigenVector.Aij(i - 2, 1);
    }
    vV3(303) = mEigenVector.Aij(nn, 1);

    cout << "The first mode： " << endl;
    cout << "第一阶： " << endl;
    cout << "dx: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 1)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }
    cout << "dy: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 2)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }

    cout << "The second mode： " << endl;
    cout << "第二阶： " << endl;
    for (int i = 3; i <= 300; i++)
    {
        vV3(i) = mEigenVector.Aij(i - 2, 2);
    }
    vV3(303) = mEigenVector.Aij(nn, 2);

    cout << "dx: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 1)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }
    cout << "dy: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 2)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }

    cout << "The third mode： " << endl;
    cout << "第三阶： " << endl;
    for (int i = 3; i <= 300; i++)
    {
        vV3(i) = mEigenVector.Aij(i - 2, 3);
    }
    vV3(303) = mEigenVector.Aij(nn, 3);

    cout << "dx: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 1)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }
    cout << "dy: " << endl;
    for (int i = 1; i <= 303; i++)
    {
        if (i % 3 == 2)
        {
            printf("%.15f\n", vV3.Vi(i));
        }
    }

    // Example2: 子空间迭代法求解广义特征值问题 END
    

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
