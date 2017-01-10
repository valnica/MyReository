//////////////////////////////////////////////
// Name : TaskManager
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : BaseTask
//
// Over View : タスクでのデータ管理クラス
//////////////////////////////////////////////
class BaseTask
{
private:
public:
	//次のタスクへのポインタ
	BaseTask* next_;

	//前のタスクへのポインタ
	BaseTask* prev_;

	//コンストラクタ
	BaseTask()
	{
		next_ = nullptr;
		prev_ = nullptr;
	}

	//デストラクタ
	virtual ~BaseTask() {}

	virtual bool Run() { return true; }
	virtual void Draw() { return; }
};

//////////////////////////////////////////////
// Class Name : Task
//
// Over View : Task
//////////////////////////////////////////////
template <typename T>
class Task :public BaseTask
{
private:
public:
	//templateで宣言したクラスのデータを保存
	T data_;

	Task() {}
	~Task() {}

	bool Run() override { return data_.Update(); }
	void Draw() override { data_.Render(); }
};

//////////////////////////////////////////////
// Class Name : TaskManager
//
// Over View : タスクの管理クラス
//////////////////////////////////////////////
class TaskManager:public Singleton<TaskManager>
{
private:
	//空のタスク
	BaseTask taskList_;

	friend class Singleton<TaskManager>;

	TaskManager()
	{
		taskList_.next_ = &taskList_;
		taskList_.prev_ = &taskList_;
	}
public:

	~TaskManager()
	{
		AllTaskKill();
	}

	//////////////////////////////////////////////
	// Name : Add
	//
	// Over View : タスクにデータ追加
	//
	// Argument : 無し
	//
	// Return : データ 
	//////////////////////////////////////////////
	template <typename T>
	T* Add()
	{
		Task<T>* task = new Task<T>;
		Linktask(task);
		return &task->data_;
	}

private:
	//////////////////////////////////////////////
	// Name : LinkTask
	//
	// Over View : タスクを繋げる
	//
	// Argument : タスクのデータ
	//
	// Return : 無し
	//////////////////////////////////////////////
	void Linktask(BaseTask* task)
	{
		task->next_ = &taskList_;
		task->prev_ = taskList_.prev_;
		task->next_->prev_ = task;
		task->prev_->next_ = task;
	}

public:
	//////////////////////////////////////////////
	// Name : Run
	//
	// Over View : タスクを走らせる
	//
	// Argument : 無し
	//
	// Return : 無し 
	//////////////////////////////////////////////
	void Run()
	{
		BaseTask* task = taskList_.next_;
		while (task != &taskList_)
		{
			if (task->Run()) task = task->next_;
			else task = Kill(task);
		}
	}

	//////////////////////////////////////////////
	// Name : Render
	//
	// Over View : 描画
	//
	// Argument : 無し
	//
	// Return : 無し 
	//////////////////////////////////////////////
	void Render()
	{
		BaseTask* task = taskList_.next_;
		while (task != &taskList_)
		{
			task->Draw();
			task = task->next_;
		}
	}

private:
	//////////////////////////////////////////////
	// Name : Kill
	//
	// Over View : タスクを終了させる
	//
	// Argument : 終了させるデータ
	//
	// Return : 次のタスク
	//////////////////////////////////////////////
	BaseTask* Kill(BaseTask* task)
	{
		BaseTask* next = task->next_;

		task->next_->prev_ = task->prev_;
		task->prev_->next_ = task->next_;

		delete task;

		return next;
	}

	//////////////////////////////////////////////
	// Name : TaskAllKill
	//
	// Over View : 全タスクの終了
	//
	// Argument : 無し
	//
	// Return : 無し 
	//////////////////////////////////////////////
	void AllTaskKill()
	{
		for (BaseTask* task = taskList_.next_; task != &taskList_; task = Kill(task));
	}
};