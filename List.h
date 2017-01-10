//////////////////////////////////////////////
// Name : List
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : ListNode
//
// Over View : ���X�g�ł̃f�[�^�ۑ��p�̃N���X
//////////////////////////////////////////////
template <class T>
class ListNode
{
private:
	//Template�ŕۑ�����ϐ�
	T data_;

public:
	//���X�g�̎��̃|�C���^
	ListNode* next_;

	//���X�g�̑O�̃|�C���^
	ListNode* prev_;

	ListNode<T>()
	{
		next_ = nullptr;
		prev_ = nullptr;
	}
	ListNode<T>(T data)
	{
		data_ = data;
	}
	~ListNode<T>() {};

	//�f�[�^�̎擾
	T GetData()
	{
		return data_;
	}

	ListNode<T>& operator=(ListNode<T>& rhs)
	{
		data_ = rhs.data_;
		next_ = rhs.next_;
		prev_ = rhs.prev_;

		return *this;
	}
};

//////////////////////////////////////////////
// Class Name : List
//
// Over View : �o�����A�����X�g
//////////////////////////////////////////////
template <class T>
class List
{
private:
	//�f�[�^�ۑ��p�̕ϐ�
	ListNode<T>* node_;

public:
	List<T>() 
	{
		node_ = nullptr;
	}
	~List<T>(){};

	//////////////////////////////////////////////
	// Name : PushBack
	//
	// Over View : ���X�g�̈�Ԍ��ɒǉ�
	//
	// Argument : �ۑ�����f�[�^
	//
	// Return : ����
	//////////////////////////////////////////////
	void PushBack(T data)
	{
		ListNode<T>* node = new ListNode<T>(data);

		if (!node_)
		{
			node_ = node;
			node_->next_ = node_;
			node_->prev_ = node_;
		}
		else
		{
			node->next_ = node_;
			node->prev_ = node_->prev_;
			node_->prev_->next_ = node;
			node_->prev_ = node;
		}
	}

	//////////////////////////////////////////////
	// Name : Top
	//
	// Over View : �퓬�̃f�[�^�Ǘ��ϐ��̎擾
	//
	// Argument : ����
	//
	// Return : ListNode�̃|�C���^ 
	//////////////////////////////////////////////
	ListNode<T>* Top()
	{
		return node_;
	}

	List<T>& operator=(List<T> rhs)
	{
		node_ = rhs.node_;

		return *this;
	}

	//////////////////////////////////////////////
	// Name : Clear
	//
	// Over View : ���X�g�̏�����
	//
	// Argument : ����
	//
	// Return : ���� 
	//////////////////////////////////////////////
	void Clear()
	{
		node_ = nullptr;
	}

	//////////////////////////////////////////////
	// Name : DataAllDelete
	//
	// Over View : �f�[�^�̑S����
	//
	// Argument : ����
	//
	// Return : ���� 
	//////////////////////////////////////////////
	void DataAllDelete()
	{
		auto node = node_->next_;
		while (node != node_)
		{
			auto delNode = node;
			node = node->next_;
			delete delNode;
		}

		delete node;
	}
};

