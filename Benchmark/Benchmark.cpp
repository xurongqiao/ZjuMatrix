#include <iostream>
#include<fstream>
#include <chrono>
#include<string>
#include "..\ZjuMatrix\ZjuMatrix.h"
#include<windows.h>
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>


#include <psapi.h>
#pragma comment(lib, "Psapi.lib")
using namespace ZjuMatrix;
using namespace std;
using namespace Eigen;

// Function to get current memory usage in kilobytes
SIZE_T getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounters;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounters, sizeof(memCounters));
    return memCounters.PeakWorkingSetSize / 1024; // Convert bytes to kilobytes
}

// Function to get CPU time used in microseconds
ULONGLONG getCPUUsage() {
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime);

    ULARGE_INTEGER kTime, uTime;
    kTime.LowPart = kernelTime.dwLowDateTime;
    kTime.HighPart = kernelTime.dwHighDateTime;
    uTime.LowPart = userTime.dwLowDateTime;
    uTime.HighPart = userTime.dwHighDateTime;

    return (kTime.QuadPart + uTime.QuadPart) / 10; // Convert to microseconds
}


int main()
{

    // Example2: 子空间迭代法求解广义特征值问题 START
    // 用txt读有限元数据
    int nIteration, nMaxIteration, np, nn;

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
    infileK.open("gK.txt", ios::in);

    if (!infileK.is_open())
    {
        cout << "fail to read file gK.txt" << endl;
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
    infileM.open("gM.txt", ios::in);

    if (!infileM.is_open())
    {
        cout << "fail to read file gM.txt" << endl;
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


    XIntVector viSkylineK(299);
    for (int i = 1; i <= mK_.rowSize(); i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (mK_.Aij(i, j) != 0)
            {
                viSkylineK(i) = i - j + 1;
                break;
            }
        }
    }

    XIntVector viSkylineM(299);
    for (int i = 1; i <= mM_.rowSize(); i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (mM_.Aij(i, j) != 0)
            {
                viSkylineM(i) = i - j + 1;
                break;
            }
        }
    }

    mK.resetSkyline(viSkylineK);
    mM.resetSkyline(viSkylineM);

    for (int i = 1; i <= mK_.size(); i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (mK_.Aij(i, j) != 0)
            {
                mK(i, j) = mK_.Aij(i, j);
            }
        }
    }
    for (int i = 1; i <= mM_.size(); i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (mM_.Aij(i, j) != 0)
            {
                mM(i, j) = mM_.Aij(i, j);
            }
        }
    }

    XDoubleMatrix mX0;
    int nm = 3;
    dTol = 1e-5;
    nMaxIteration = 100;


    // Start time
    auto start = std::chrono::high_resolution_clock::now();

    // Memory and CPU usage before the function call
    SIZE_T memoryBefore = getMemoryUsage();
    ULONGLONG cpuBefore = getCPUUsage();

    nIteration = subspaceIteration(mK, mM, vEigenValue, mEigenVector, dTol, nMaxIteration, nm, nn);

    // Memory and CPU usage after the function call
    SIZE_T memoryAfter = getMemoryUsage();
    ULONGLONG cpuAfter = getCPUUsage();

    // End time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the execution time, memory usage, and CPU usage
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Memory usage: " << (memoryAfter - memoryBefore) << " kilobytes" << std::endl;
    std::cout << "CPU usage: " << (cpuAfter - cpuBefore) << " microseconds" << std::endl;
    

    int size = 299;
    Eigen::MatrixXd Eigen_mK(size, size);
    Eigen::MatrixXd Eigen_mM(size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Eigen_mK(i, j) = mK_.Aij(i + 1, j + 1);
            Eigen_mM(i, j) = mM_.Aij(i + 1, j + 1);
        }
    }

    // 创建求解器
    Eigen::GeneralizedEigenSolver<Eigen::MatrixXd> ges;

    // Start time
    //auto start2 = std::chrono::high_resolution_clock::now();

    // Start time
    auto start2 = std::chrono::high_resolution_clock::now();

    // Memory and CPU usage before the function call
    SIZE_T memoryBefore2 = getMemoryUsage();
    ULONGLONG cpuBefore2 = getCPUUsage();

    // 计算广义特征值
    ges.compute(Eigen_mK, Eigen_mM);

    // Memory and CPU usage after the function call
    SIZE_T memoryAfter2 = getMemoryUsage();
    ULONGLONG cpuAfter2 = getCPUUsage();

    // End time
    auto end2 = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    // Output the execution time, memory usage, and CPU usage
    std::cout << "Execution time: " << duration2.count() << " milliseconds" << std::endl;
    std::cout << "Memory usage: " << (memoryAfter2 - memoryBefore2) << " kilobytes" << std::endl;
    std::cout << "CPU usage: " << (cpuAfter2 - cpuBefore2) << " microseconds" << std::endl;

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
