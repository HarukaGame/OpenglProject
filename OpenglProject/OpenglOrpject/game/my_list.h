#pragma once

#ifndef __MY_LIST_H__
#define __MY_LIST_H__


///@brief	�m�[�h�N���X
template<class T>
struct Node {
	T m_value;		//�i�[����l
	Node* m_pPrev = nullptr;//�O�̃m�[�h�|�C���^
	Node* m_pNext = nullptr;//��̃m�[�h�|�C���^

	///@brief	�R���X�g���N�^
	Node() {
		m_pPrev = this;
		m_pNext = this;
	}
	///@brief	�R���X�g���N�^
	///@param[in]	_value	�i�[����l
	///@param[in]	_prev	�O�̃m�[�h�|�C���^
	///@param[in]	_next	��̃m�[�h�|�C���^
	Node(T value, Node* prev, Node* next) {
		m_value = value;
		m_pPrev = prev;
		m_pNext = next;
	}
};


template<class T>
class CList {
public:
class CListIterator;

	///@brief	�R���X�g���N�^
	CList();

	///@brief	�R�s�[�R���X�g���N�^
	///@param[in]	_list	
	CList(const CList& _list);

	///@brief	�f�X�g���N�^
	~CList();
	
	///@brief	������Z�q
	///@param[in]	_list
	///@return		CList
	CList& operator=(const CList& _list);

	///@brief	���X�g���󂩔���
	///@return		bool	true:��
	bool Empty();

	///@brief	��ԑO�ɗv�f������
	///@param[in]	_value
	void PushFront(T _value);

	///@brief	��Ԍ��ɗv�f������
	///@param[in]	_value
	void PushBack(T _value);

	void Insert(T _value, CListIterator _iter);

	///@brief	��ԑO�̗v�f�����o��
	///@return	T
	void PopFront();

	///@brief	��Ԍ��̗v�f�����o��
	///@return	T
	void PopBack();

	void Pop(CListIterator _iter);

	///@brief	���ׂĂ̗v�f���폜����
	void Clear();

	///@brief	�����Ă���v�f����Ԃ�
	///@return	int	�v�f��
	int Length();
private:
	///@brief	�v�f��������
	///@param[in]	_value
	///@param[in]	_node	������ʒu�̒��O�̃m�[�h
	void Add(T _value, Node<T>* _node);

	///@brief	�m�[�h���폜����
	///@param[in]	_node	�폜����m�[�h
	///@return		T	�폜����m�[�h�ɓ����Ă����v�f
	void Remove(Node<T>* node);

	Node<T>* m_root = nullptr;	//�󃊃X�g�̃_�~�[�m�[�h�|�C���^
	int m_length = 0;			//�m�[�h�̐�

public:
	///@brief	�C�e���[�^�[�N���X
	class CListIterator {
	friend class CList;
	public:
		///@brief	�R���X�g���N�^
		///@param[in]	_list	���X�g�N���X	
		///@param[in]	_node	�m�[�h
		CListIterator(CList* _list, Node<T>* _node) {
			m_pList = _list;
			m_pNode = _node;
		}

		///@brief	�Q�Ɖ��Z�q
		///@return	T&		
		T& operator*() { return m_pNode->m_value; }

		///@brief	�A���[���Z�q
		///@return	T*		
		T* operator->() { return &m_pNode->m_value; }

		///@brief	�O�u�C���N�������g
		///@return	CListIterator&
		CListIterator& operator++() {
			m_pNode = m_pNode->m_pNext;
		}

		///@brief	�O�u�f�N�������g
		///@return	CListIterator&
		CListIterator& operator--() {
			m_pNode = m_pNode->m_pPrev;
		}

		///@brief	��u�C���N�������g(�����̓_�~�[)
		///@param[in]	_n	�_�~�[
		///@return	CListIterator&
		CListIterator& operator++(int n) {
			CListIterator iter(*this);
			m_pNode = m_pNode->m_pNext;
			return iter;
		}

		///@brief	��u�f�N�������g(�����̓_�~�[)
		///@param[in]	_n	�_�~�[
		///@return	CListIterator&
		CListIterator& operator--(int n) {
			CListIterator iter(*this);
			m_pNode = m_pNode->m_pPrev;
			return iter;
		}

		///@brief	���Z���
		///@param[in]	_n	���Z��
		///@return	CListIterator&
		CListIterator& operator+=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pNext;
			}
			return *this;
		}

		///@brief	���Z���
		///@param[in]	_n	���Z��
		///@return	CListIterator&
		CListIterator& operator-=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pPrev;
			}
			return *this;
		}

		///@brief	���Z
		///@param[in]	_n
		///@return	CListIterator
		CListIterator operator+(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pNext;
			}
			return CListIterator(m_pList, temp);
		}

		///@brief	���Z
		///@param[in]	_n
		///@return	CListIterator
		CListIterator operator-(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pPrev;
			}
			return CListIterator(m_pList, temp);
		}

		///@brief	��r���Z�q	==
		///@param[in]	_iter
		///@return	T
		bool operator==(const CListIterator& _iter)const {
			return m_pList == _iter.m_pList && m_pNode == _iter.m_pNode;
		}

		///@brief	��r���Z�q	!=
		///@param[in]	_iter
		///@return	T
		bool operator!=(const CListIterator& _iter)const {
			return m_pList != _iter.m_pList || m_pNode != _iter.m_pNode;
		}

	private:
		CList* m_pList = nullptr;	//���X�g�̃|�C���^
		Node<T>* m_pNode = nullptr;	//�m�[�h�̃|�C���^

	};

	///@brief	���߂̃C�e���[�^���擾
	///@return	CListIterator
	CListIterator Begin() {
		return CListIterator(this, m_root->m_pNext);
	}

	///@brief	�Ō�̃C�e���[�^���擾
	///@return	CListIterator
	CListIterator End() {
		return CListIterator(this, m_root);
	}
	typedef CListIterator iterator;

};

template<class T>
CList<T>::CList() {
	m_root = new Node<T>();
}

template<class T>
CList<T>::CList(const CList& _v)
{
	m_root = new Node<T>();
	Node<T>* temp = _v.m_root->m_pNext;
	while (temp != _v.m_root) {
		PushBack(temp->m_value);
		temp = temp->m_pNext;
	}
}

template<class T>
inline CList<T>::~CList()
{
	Clear();
	delete m_root;
}

template<class T>
CList<T>& CList<T>::operator=(const CList& _v)
{
	if (this != &_v) {
		Clear();
		Node<T>* temp = _v.m_root->m_pNext;
		while (temp != _v.m_root) {
			PushBack(temp->m_value);
			temp = temp->m_pNext;
		}
	}
	return *this;
}

template<class T>
bool CList<T>::Empty()
{
	return m_root->m_pNext == m_root;
}

template<class T>
void CList<T>::Add(T _value, Node<T>* _node)
{
	if (_node == nullptr) {
		return;
	}
	Node<T>* newNode = new Node<T>(_value, _node, _node->m_pNext);
	newNode->m_pNext->m_pPrev = newNode;
	newNode->m_pPrev->m_pNext = newNode;
	m_length++;
}

template<class T>
void CList<T>::Remove(Node<T>* node)
{
	if (Empty() == true) {
		return;
	}
	node->m_pPrev->m_pNext = node->m_pNext;
	node->m_pNext->m_pPrev = node->m_pPrev;
	delete node;
	m_length--;
}

template<class T>
void CList<T>::PushFront(T _value) {
	Add(_value, m_root);
}

template<class T>
void CList<T>::PushBack(T _value)
{
	Add(_value, m_root->m_pPrev);
}

template<class T>
inline void CList<T>::Insert(T _value, CListIterator _iter)
{
	Add(_value, _iter.m_pNode);
}

template<class T>
void CList<T>::PopFront() {
	Remove(m_root->m_pNext);
}


template<class T>
void CList<T>::PopBack() {
	Remove(m_root->m_pPrev);
}

template<class T>
void CList<T>::Pop(CListIterator _iter) {
	if (_iter == End()) {
		return;
	}
	Remove(_iter.m_pNode);
}

template<class T>
void CList<T>::Clear()
{
	while (Empty() == false) {
		PopBack();
	}
	m_length = 0;
}

template<class T>
int CList<T>::Length()
{
	return m_length;
}

#endif // !__MY_LIST_H__
