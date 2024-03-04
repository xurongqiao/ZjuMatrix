//=======================================================================
// �ļ���(File name): XList.h
// ����(Author):      ������(R.Q.Xu, xurongqiao@zju.edu.cn)
// ����(Date):        2023.03.06
// ----------------------------------------------------------------------
// ����������һ��ģ���࣬����ʵ�����ݽṹ-����
// Description: define a template class for linked list.
//=======================================================================
#pragma once
#include "XVector.h"

namespace ZjuMatrix {

	template <class T> class XListNode    // ����Ľڵ�(node of list)
	{
	public:
		T m_T;                            // ����(data)
		XListNode<T>* m_pNext;            // ��һ���ڵ��ָ��(pointer to next node)
	};

	template <class T>	class XList       // ����(linked list)
	{
	protected:
		XListNode<T>* m_pHead;            // ����ͷ(head of linked list)

	public:
		XList();
		~XList();

	public:
		void append(T t);                 // ����β׷��һ���ڵ�(append a node at the tail)
		void toVector(XVector<T>& v);     // ������ת��������(convert the list to a vector)
	};

	template <class T>
	inline XList<T>::XList()
	{
		m_pHead = nullptr;
	}

	template <class T>
	inline XList<T>::~XList()
	{
		XListNode<T>* pCurrent = m_pHead;
		while (pCurrent)
		{
			XListNode<T>* pNext = pCurrent->m_pNext;
			delete pCurrent;
			pCurrent = pNext;
		}
	}

	template <class T>
	inline void XList<T>::toVector(XVector<T>& v)
	{
		XListNode<T>* pCurrent = m_pHead;
		int nSize = 0;
		while (pCurrent)
		{
			nSize++;
			pCurrent = pCurrent->m_pNext;
		}

		v.resetSize(nSize);
		int iPos = 0;
		pCurrent = m_pHead;
		while (pCurrent)
		{
			iPos++;
			v(iPos) = pCurrent->m_T;
			pCurrent = pCurrent->m_pNext;
		}
	}

	template <class T>
	inline void XList<T>::append(T t)
	{
		if (m_pHead == nullptr)
		{
			m_pHead = new XListNode<T>;
			m_pHead->m_T = t;
			m_pHead->m_pNext = nullptr;
			return;
		}
		XListNode<T>* pCurrent = m_pHead;
		while (pCurrent->m_pNext)
		{
			pCurrent = pCurrent->m_pNext;
		}
		XListNode<T>* pTail = new XListNode<T>;
		pTail->m_pNext = nullptr;
		pTail->m_T = t;
		pCurrent->m_pNext = pTail;
	}

	typedef XList<int> XIntList;           // ������������(a list class for int)
	typedef XList<double> XDoubleList;     // ˫������������(a list class for double)

}

