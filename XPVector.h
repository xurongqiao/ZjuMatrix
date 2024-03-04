//=============================================================================
// 文件名(File name): XPVector.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.02.23
// ----------------------------------------------------------------------------
// 描述：定义一个模板类，用于保存指针的一维数组。
// Description: define a template class for one-dimensional array of point.
// 注意：向量元素位置从1开始(iPos = 1, 2, ..., m_nSize)，而不是从零开始
// Remark: The position of element in the vector count from 1 rather than 0
//=============================================================================
#pragma once

namespace ZjuMatrix
{
	template <class T>
	class XPVector
	{
	protected:
		int m_nSize;    // 向量大小(size of vector)
		T** m_ppT;      // 指针数组(array of point)

	public:
		XPVector();            // 缺省构造函数(default constructor)
		XPVector(int nSize);   // 指定大小的构造函数(constructor define the size)
		~XPVector();           // 析构函数(destructor)

	public:
		void initialSize(int nSize);    // 初始化大小(initialize the size)
		int size() const;               // 返回大小(return the size)

		// 注意：向量元素位置从1开始(iPos = 1, 2, ..., m_nSize)，而不是从零开始
		// Remark: The position of element in the vector count from 1 rather than 0
		T* operator()(int iPos) const;  // 返回某个元素(return a element)
		void assignAt(int iPos, T* pT); // 给某个元素赋值(assign value to a element)
	};

	template<class T>
	inline XPVector<T>::XPVector()
	{
		m_nSize = 0;
		m_ppT = nullptr;
	}

	template<class T>
	inline XPVector<T>::XPVector(int nSize)
	{
		initialSize(nSize);
	}

	template<class T>
	inline XPVector<T>::~XPVector()
	{
		for (int i = 1; i <= m_nSize; i++)
		{
			if (m_ppT[i - 1])
				delete m_ppT[i - 1];
		}
		if (m_ppT)
			delete m_ppT;
		m_nSize = 0;
	}

	template<class T>
	inline void XPVector<T>::initialSize(int nSize)
	{
		if (nSize > 0)
		{
			m_nSize = nSize;
			m_ppT = new T * [nSize];
			for (int i = 1; i <= nSize; i++)
				m_ppT[i - 1] = nullptr;
		}
		else
			throw("向量大小必须大于零(the size of vector should be a positive integer!)");
	}

	template<class T>
	inline int XPVector<T>::size() const
	{
		return m_nSize;
	}

	template<class T>
	inline T* XPVector<T>::operator()(int iPos) const
	{
		if (iPos < 0 || iPos > m_nSize)
		{
			throw("向量下标超出范围(The index exceed the scope)!");
			return nullptr;
		}
		return m_ppT[iPos - 1];
	}

	template<class T>
	inline void XPVector<T>::assignAt(int iPos, T* pT)
	{
		if (iPos < 0 || iPos > m_nSize)
		{
			throw("向量下标超出范围(The index exceed the scope)!");
			return;
		}
		if (m_ppT[iPos - 1])
			delete m_ppT[iPos - 1];
		m_ppT[iPos - 1] = pT;
	}
}