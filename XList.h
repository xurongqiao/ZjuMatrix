//=======================================================================
// 文件名(File name): XList.h
// 作者(Author):      徐荣桥(R.Q.Xu, xurongqiao@zju.edu.cn)
// 日期(Date):        2023.03.06
// ----------------------------------------------------------------------
// 描述：定义一个模板类，用于实现数据结构-链表。
// Description: define a template class for linked list.
//=======================================================================
#pragma once
#include "XVector.h"

namespace ZjuMatrix {

	template <class T> class XListNode    // 链表的节点(node of list)
	{
	public:
		T m_T;                            // 数据(data)
		XListNode<T>* m_pNext;            // 下一个节点的指针(pointer to next node)
	};

	template <class T>	class XList       // 链表(linked list)
	{
	protected:
		XListNode<T>* m_pHead;            // 链表头(head of linked list)

	public:
		XList();
		~XList();

	public:
		void append(T t);                 // 链表尾追加一个节点(append a node at the tail)
		void toVector(XVector<T>& v);     // 把链表转换成向量(convert the list to a vector)
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

	typedef XList<int> XIntList;           // 整形数链表类(a list class for int)
	typedef XList<double> XDoubleList;     // 双精度数链表类(a list class for double)

}

