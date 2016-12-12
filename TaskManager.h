#pragma once

class BaseTask
{
private:
public:
	//���̃^�X�N�ւ̃|�C���^
	BaseTask* m_next;
	//�O�̃^�X�N�ւ̃|�C���^
	BaseTask* m_prev;

	//�R���X�g���N�^
	BaseTask()
	{
		m_next = nullptr;
		m_prev = nullptr;
	}
	//�f�X�g���N�^
	virtual ~BaseTask() {}

	virtual bool Run() { return true; }
	virtual void Draw() { return; }
};

template <typename T>
class Task :public BaseTask
{
private:
public:
	//template�Ő錾�����N���X�̃f�[�^��ۑ�
	T m_data;

	Task() {}
	~Task() {}

	bool Run() override { return m_data.Update(); }
	void Draw() override { m_data.Render(); }
};

class TaskManager
{
private:
	BaseTask m_taskList;

	TaskManager()
	{
		m_taskList.m_next = &m_taskList;
		m_taskList.m_prev = &m_taskList;
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
		return &task->m_data;
	}

private:
	void Linktask(BaseTask* task)
	{
		task->m_next = &m_taskList;
		task->m_prev = m_taskList.m_prev;
		task->m_next->m_prev = task;
		task->m_prev->m_next = task;
	}

public:
	void Run()
	{
		BaseTask* task = m_taskList.m_next;
		while (task != &m_taskList)
		{
			if (task->Run()) task = task->m_next;
			else task = Kill(task);
		}
	}

	void Render()
	{
		BaseTask* task = m_taskList.m_next;
		while (task != &m_taskList)
		{
			task->Draw();
			task = task->m_next;
		}
	}

private:
	BaseTask* Kill(BaseTask* task)
	{
		BaseTask* next = task->m_next;

		task->m_next->m_prev = task->m_prev;
		task->m_prev->m_next = task->m_next;

		delete task;

		return next;
	}

	void AllTaskKill()
	{
		for (BaseTask* task = m_taskList.m_next; task != &m_taskList; task = Kill(task));
	}
};