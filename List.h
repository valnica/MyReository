#pragma once

template <class T>
class ListNode
{
private:
	T data_;

public:
	ListNode* next_;
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

template <class T>
class List
{
private:
	ListNode<T>* node_;

public:
	List<T>() 
	{
		node_ = nullptr;
	};
	~List<T>() {};

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
	ListNode<T>* Top()
	{
		return node_;
	}

	List<T>& operator=(List<T> rhs)
	{
		node_ = rhs.node_;

		return *this;
	}

	void Clear()
	{
		node_ = nullptr;
	}
};

