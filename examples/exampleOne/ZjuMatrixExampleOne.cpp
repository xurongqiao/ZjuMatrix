// ZjuMatrixExampleOne.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include<string>
#include "..\..\ZjuMatrix\ZjuMatrix.h"
//#include<windows.h>

using namespace ZjuMatrix;
using namespace std;

int main()
{


    // Example1: 静力问题——线性代数方程组求解 START
    // 用txt读有限元数据
    XDoubleMatrix vDelta, vF;
    XSymDoubleMatrix mK_;
    XBandDoubleMatrix mK;
    int nn;
    nn = 21;
    mK_.resetSize(nn);
    vDelta.resetSize(nn, 1);
    vF.resetSize(nn, 1);

    ifstream infileK;
    infileK.open("examOne_gK.txt", ios::in);

    if (!infileK.is_open())
    {
        cout << "fail to read file examOne_gK.txt" << endl;
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
    }

    infileK.close();

    ifstream infileF;
    infileF.open("examOne_f.txt", ios::in);

    if (!infileF.is_open())
    {
        cout << "fail to read file examOne_f.txt" << endl;
        return 0;
    }
    string bufF;
    while (getline(infileF, bufF))
    {
        //cout << "bufF = " << bufF << endl;
        int nLeftBracket, nRightBracket, nDot;
        nLeftBracket = bufF.find("(");
        nRightBracket = bufF.find(")");
        nDot = bufF.find(",");
        int i = std::stoi(bufF.substr(nLeftBracket + 1, nDot - nLeftBracket - 1));
        int j = std::stoi(bufF.substr(nDot + 1, nRightBracket - nDot - 1));
        string sm = bufF.substr(nRightBracket + 1);
        if (!sm.empty())
        {
            sm.erase(0, sm.find_first_not_of(" "));
            sm.erase(sm.find_last_not_of(" ") + 1);
        }
        double dm = std::stod(sm);
        vF(i,j) = dm;
    }

    infileF.close();

    mK = mK_;

    vDelta = solve(mK, vF);


    cout << "x方向位移(x-direction displacement)：" << endl;
    for (int i = 1; i <= nn; i++)
    {
        if (i % 3 == 1)
        {
            printf("%.8e       ", vDelta.Aij(i, 1));
            cout << endl;
        }
    }

    cout << "y方向位移(y-direction displacement)：" << endl;
    for (int i = 1; i <= nn; i++)
    {
        if (i % 3 == 2)
        {
            printf("%.8e       ", vDelta.Aij(i, 1));
            cout << endl;
        }
    }

    cout << "转角(rotation)：" << endl;
    for (int i = 1; i <= nn; i++)
    {
        if (i % 3 == 0)
        {
            printf("%.8e       ", vDelta.Aij(i, 1));
            cout << endl;
        }
    }

    // cout << vDelta << endl;


    // Example1: 静力问题——线性代数方程组求解 END

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
