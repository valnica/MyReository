#pragma once

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

class TaskManager
{
private:
	BaseTask taskList_;

	TaskManager()
	{
		taskList_.next_ = &taskList_;
		taskList_.prev_ = &taskList_;
	}
public:
	static TaskManager* GetInstance()
	{
		static TaskManager* instance = nullptr;

		if (!instance)
			instance = new TaskManager;

		return instance;
	}


	~TaskManager()
	{
		AllTaskKill();
	}

	template <typename T>
	T* Add()
	{
		Task<T>* task = new Task<T>;
		Linktask(task);
		return &task->data_;
	}

private:
	void Linktask(BaseTask* task)
	{
		task->next_ = &taskList_;
		task->prev_ = taskList_.prev_;
		task->next_->prev_ = task;
		task->prev_->next_ = task;
	}

public:
	void Run()
	{
		BaseTask* task = taskList_.next_;
		while (task != &taskList_)
		{
			if (task->Run()) task = task->next_;
			else task = Kill(task);
		}
	}

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
	BaseTask* Kill(BaseTask* task)
	{
		BaseTask* next = task->next_;

		task->next_->prev_ = task->prev_;
		task->prev_->next_ = task->next_;

		delete task;

		return next;
	}

	void AllTaskKill()
	{
		for (BaseTask* task = taskList_.next_; task != &taskList_; task = Kill(task));
	}
};