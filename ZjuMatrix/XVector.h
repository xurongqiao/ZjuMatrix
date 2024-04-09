//=======================================================================
// 文件名(File name): XVector.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.03
// ----------------------------------------------------------------------
// 描述：定义一个模板类，用于保存一维数组。
// Description: define a template class for one-dimensional array.
//=======================================================================
#pragma once
#include <iostream>

using namespace std;

namespace ZjuMatrix {

	/// Define a template class for one-dimensional array.
	template <class T> class XVector
	{
	protected:
		int m_nSize;     // 向量的大小(the size of vector)
		T* m_pT;         // 指向向量元素的指针(the pointer to elements)

	public:
		XVector();                 // 缺省的构造函数(default constructor)
		XVector(int nSize);        // 自定义构造函数(customized constructor)
		XVector(int nSize, T* pT); // 自定义构造函数(customized constructor)
		XVector(XVector<T>& v);    // 拷贝构造函数(copy constructor)
		~XVector();                // 析构函数(destructor)

		XVector<T>& operator=(const XVector<T>& v);  // 重载的赋值运算符(overloaded assignment operator)

	public:
		void resetSize(int nSize);           // 重置向量的大小，并初始化为零(reset the size of vector and initialized to zero)
		void ones(int nSize);                // 重置向量的大小，并初始化为1(reset the size of vector and initialized to 1)
		int size() const;                    // 返回向量的大小(return the size of vector)

		// 向量元素位置从1开始(iPos = 1, 2, ..., m_nSize)，而不是从零开始
		// The position of element in the vector count from 1 rather than 0
		void exchange(int iPos, int jPos);   // 交换两个元素(exchange two elements)
		T& operator()(int iPos);             // 返回元素的引用(return the reference of element)
		T Vi(int iPos) const;                // 返回元素的值(return the value of element)
	};


	//using namespace ZjuMatrix;

    //---------------------------------------------------------------------------
    //  函数名(Function name): XVector()
    //  描述: 缺省的构造函数
    /// Description: default constructor
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>::XVector()
	{
		m_nSize = 0;
		m_pT = nullptr;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): XVector(int nSize)
    //  描述: 自定义构造函数
    /// Description: customized constructor
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>::XVector(int nSize)
	{
		m_nSize = nSize;
		m_pT = new T[nSize];
		for (int i = 0; i < nSize; i++)
			m_pT[i] = (T)0;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): XVector(int nSize, T* pT)
    //  描述: 自定义构造函数
    /// Description: customized constructor
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>::XVector(int nSize, T* pT)
	{
		m_nSize = nSize;
		m_pT = new T[nSize];
		for (int i = 0; i < nSize; i++)
			m_pT[i] = pT[i];
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): XVector(XVector<T>& v)
    //  描述: 拷贝构造函数
    /// Description: copy constructor
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>::XVector(XVector<T>& v)
	{
		m_nSize = v.m_nSize;
		m_pT = new T[m_nSize];
		for (int i = 0; i < m_nSize; i++)
			m_pT[i] = v.m_pT[i];
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): ~XVector()
    //  描述: 析构函数
    /// Description: destructor
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>::~XVector()
	{
		if (m_pT)
			delete[] m_pT;
	}

    //---------------------------------------------------------------------------
    //  重载名(Overloading name): =(const XVector<T>& v)
    //  描述: 重载的赋值运算符
    /// Description: overloaded assignment operator
    // -------------------------------------------------------------------------
	template<class T>
	inline XVector<T>& XVector<T>::operator=(const XVector<T>& v)
	{
		this->resetSize(v.m_nSize);
		for (int i = 0; i < m_nSize; i++)
			m_pT[i] = v.m_pT[i];
		return *this;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): resetSize(int nSize)
    //  描述: 重置向量的大小，并初始化为零
    /// Description: Reset the size of vector and initialized to zero.
    // -------------------------------------------------------------------------
	template<class T>
	inline void XVector<T>::resetSize(int nSize)
	{
		if (m_nSize != nSize)
		{
			if (m_pT)
				delete[] m_pT;
			m_nSize = nSize;
			m_pT = new T[nSize];

		}
		for (int i = 0; i < nSize; i++)
			m_pT[i] = (T)0;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): ones(int nSize)
    //  描述: 重置向量的大小，并初始化为1
    /// Description: Reset the size of vector and initialized to 1.
    // -------------------------------------------------------------------------
	template<class T>
	inline void XVector<T>::ones(int nSize)
	{
		if (m_nSize != nSize)
		{
			if (m_pT)
				delete[] m_pT;
			m_nSize = nSize;
			m_pT = new T[nSize];
		}
		for (int i = 0; i < nSize; i++)
			m_pT[i] = (T)1;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): size() const
    //  描述: 返回向量的大小。
    /// Description: Return the size of vector.
    // -------------------------------------------------------------------------
	template<class T>
	inline int XVector<T>::size() const
	{
		return m_nSize;
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): exchange(int iPos, int jPos)
    //  描述: 交换两个元素
    /// Description: Exchange two elements.
    // -------------------------------------------------------------------------
	template<class T>
	inline void XVector<T>::exchange(int iPos, int jPos)
	{
		if (iPos <= 0 || iPos > m_nSize || jPos <= 0 || jPos > m_nSize)
		{
			throw("向量元素指标超出了范围(The index exceed the size!)");
			return;
		}
		T dummy = Vi(iPos);
		operator()(iPos) = Vi(jPos);
		operator()(jPos) = dummy;
	}

    //---------------------------------------------------------------------------
    //  重载名(Overloading name): ()(int iIndex)
    //  描述: 返回元素的引用
    /// Description: Return the reference of element.
    // -------------------------------------------------------------------------
	template<class T>
	inline T& XVector<T>::operator()(int iIndex)
	{
		if (iIndex <= 0 || iIndex > m_nSize)
		{
			throw("向量元素指标超出了范围(The index beyond the scope)!");
			return m_pT[0];
		}
		return m_pT[iIndex - 1];
	}

    //---------------------------------------------------------------------------
    //  函数名(Function name): Vi(int iIndex) const
    //  描述: 返回元素的值
    /// Description: Return the value of element.
    // -------------------------------------------------------------------------
	template<class T>
	inline T XVector<T>::Vi(int iIndex) const
	{
		if (iIndex <= 0 || iIndex > m_nSize)
		{
			throw("向量元素指标超出了范围(The index beyond the scope)!");
			return m_pT[0];
		}
		return m_pT[iIndex - 1];
	}

    //---------------------------------------------------------------------------
    //  重载名(Overloading name): << (ostream& os, XVector<T>& v)
    //  描述: 流输出
    /// Description: stream output
    // -------------------------------------------------------------------------
	template <class T>
	ostream& operator<< (ostream& os, XVector<T>& v)
	{
		os << endl;
		for (int i = 1; i <= v.size(); i++)
			os << v(i) << "  ";
		os << endl;
		return os;
	}

	typedef XVector<int> XIntVector;           // 整形数向量类(a vector class for int)
	typedef XVector<double> XDoubleVector;     // 双精度数向量类(a vector class for double)

	double max(XDoubleVector v);   // 最大值(maximum element)
	double min(XDoubleVector v);   // 最小值(minimum element)
	double sum2(XDoubleVector v);  // 平方和(summation of squares)
}