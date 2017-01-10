//////////////////////////////////////////////
// Name : TaskManager
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : BaseTask
//
// Over View : �^�X�N�ł̃f�[�^�Ǘ��N���X
//////////////////////////////////////////////
class BaseTask
{
private:
public:
	//���̃^�X�N�ւ̃|�C���^
	BaseTask* next_;

	//�O�̃^�X�N�ւ̃|�C���^
	BaseTask* prev_;

	//�R���X�g���N�^
	BaseTask()
	{
		next_ = nullptr;
		prev_ = nullptr;
	}

	//�f�X�g���N�^
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
	//template�Ő錾�����N���X�̃f�[�^��ۑ�
	T data_;

	Task() {}
	~Task() {}

	bool Run() override { return data_.Update(); }
	void Draw() override { data_.Render(); }
};

//////////////////////////////////////////////
// Class Name : TaskManager
//
// Over View : �^�X�N�̊Ǘ��N���X
//////////////////////////////////////////////
class TaskManager:public Singleton<TaskManager>
{
private:
	//��̃^�X�N
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
	// Over View : �^�X�N�Ƀf�[�^�ǉ�
	//
	// Argument : ����
	//
	// Return : �f�[�^ 
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
	// Over View : �^�X�N���q����
	//
	// Argument : �^�X�N�̃f�[�^
	//
	// Return : ����
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
	// Over View : �^�X�N�𑖂点��
	//
	// Argument : ����
	//
	// Return : ���� 
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
	// Over View : �`��
	//
	// Argument : ����
	//
	// Return : ���� 
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
	// Over View : �^�X�N���I��������
	//
	// Argument : �I��������f�[�^
	//
	// Return : ���̃^�X�N
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
	// Over View : �S�^�X�N�̏I��
	//
	// Argument : ����
	//
	// Return : ���� 
	//////////////////////////////////////////////
	void AllTaskKill()
	{
		for (BaseTask* task = taskList_.next_; task != &taskList_; task = Kill(task));
	}
};