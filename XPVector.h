//=============================================================================
// �ļ���(File name): XPVector.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.02.23
// ----------------------------------------------------------------------------
// ����������һ��ģ���࣬���ڱ���ָ���һά���顣
// Description: define a template class for one-dimensional array of point.
// ע�⣺����Ԫ��λ�ô�1��ʼ(iPos = 1, 2, ..., m_nSize)�������Ǵ��㿪ʼ
// Remark: The position of element in the vector count from 1 rather than 0
//=============================================================================
#pragma once

namespace ZjuMatrix
{
	template <class T>
	class XPVector
	{
	protected:
		int m_nSize;    // ������С(size of vector)
		T** m_ppT;      // ָ������(array of point)

	public:
		XPVector();            // ȱʡ���캯��(default constructor)
		XPVector(int nSize);   // ָ����С�Ĺ��캯��(constructor define the size)
		~XPVector();           // ��������(destructor)

	public:
		void initialSize(int nSize);    // ��ʼ����С(initialize the size)
		int size() const;               // ���ش�С(return the size)

		// ע�⣺����Ԫ��λ�ô�1��ʼ(iPos = 1, 2, ..., m_nSize)�������Ǵ��㿪ʼ
		// Remark: The position of element in the vector count from 1 rather than 0
		T* operator()(int iPos) const;  // ����ĳ��Ԫ��(return a element)
		void assignAt(int iPos, T* pT); // ��ĳ��Ԫ�ظ�ֵ(assign value to a element)
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
			throw("������С���������(the size of vector should be a positive integer!)");
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
			throw("�����±곬����Χ(The index exceed the scope)!");
			return nullptr;
		}
		return m_ppT[iPos - 1];
	}

	template<class T>
	inline void XPVector<T>::assignAt(int iPos, T* pT)
	{
		if (iPos < 0 || iPos > m_nSize)
		{
			throw("�����±곬����Χ(The index exceed the scope)!");
			return;
		}
		if (m_ppT[iPos - 1])
			delete m_ppT[iPos - 1];
		m_ppT[iPos - 1] = pT;
	}
}