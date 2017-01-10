//////////////////////////////////////////////
// Name : List
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : ListNode
//
// Over View : リストでのデータ保存用のクラス
//////////////////////////////////////////////
template <class T>
class ListNode
{
private:
	//Templateで保存する変数
	T data_;

public:
	//リストの次のポインタ
	ListNode* next_;

	//リストの前のポインタ
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

	//データの取得
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
// Over View : 双方向連結リスト
//////////////////////////////////////////////
template <class T>
class List
{
private:
	//データ保存用の変数
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
	// Over View : リストの一番後ろに追加
	//
	// Argument : 保存するデータ
	//
	// Return : 無し
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
	// Over View : 戦闘のデータ管理変数の取得
	//
	// Argument : 無し
	//
	// Return : ListNodeのポインタ 
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
	// Over View : リストの初期化
	//
	// Argument : 無し
	//
	// Return : 無し 
	//////////////////////////////////////////////
	void Clear()
	{
		node_ = nullptr;
	}

	//////////////////////////////////////////////
	// Name : DataAllDelete
	//
	// Over View : データの全消去
	//
	// Argument : 無し
	//
	// Return : 無し 
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

