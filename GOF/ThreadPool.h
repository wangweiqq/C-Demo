#pragma once
#include <list>
#include <mutex>
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
/**
ͬ������
*/
template<typename T>
class SyncQueue {
public:
	SyncQueue(int maxSize):m_maxSize(maxSize) {}
	~SyncQueue() {}
	/**
	���
	*/
	void Put(const T& x){
		Add(x);
	}
	//void Put(T&& x) {
	//	Add(std::forward<T>(x));
	//}
	/**
	�Ƴ�
	*/
	void Take(T& t){
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this]() {return m_needStop || NotEmpty(); });
		if (m_needStop) {
			return;
		}
		t = m_queue.pop_front();
		m_notFull.notify_one();
	}
	void Take(std::list<T>& list) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this]() {return m_needStop || NotEmpty(); });
		if (m_needStop) {
			return;
		}
		list = std::move(m_queue);
		m_notFull.notify_one();
	}
	void Stop(){
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			m_needStop = true;
		}
		m_notEmpty.notify_all();
		m_notFull.notify_all();
	}
	bool Empty() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return !NotEmpty();
	}
	bool Full() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return !NotFull();
	}
	size_t Size() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}
	int Count() {
		return m_queue.size();
	}
private:
	bool NotFull()const {
		bool full = m_queue.size() == m_maxSize;
		if (full) {
			std::cout << "������������ȴ�.." << std::endl;
		}
		return !full;
	}
	bool NotEmpty()const {
		bool empty = m_queue.size() == 0;
		if (empty) {
			std::cout << "����Ϊ�գ���ȴ�.." << std::endl;
		}
		return !empty;
	}
	template<typename F>
	void Add(F&& t) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notFull.wait(locker, [this]() {return  m_needStop || NotFull(); });
		if (m_needStop) {
			return;
		}
		m_queue.push_back(std::forward<F>(t));
		m_notEmpty.notify_one();
	}
	std::list<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_notEmpty;//��Ϊ��
	std::condition_variable m_notFull;//û����
	bool m_needStop = false;//ֹͣ���
	int m_maxSize;//���������
};
/**
�̳߳�
*/
const int MaxTaskCount = 100;//���������
class ThreadPool
{
	using Task = std::function<void()>;
public:
	ThreadPool(int numThread = std::thread::hardware_concurrency()):m_queue(MaxTaskCount)
	{
		Start(numThread);
	}
	~ThreadPool()
	{
		Stop();
	}
	void Stop() {
		std::call_once(m_flag, [this]() {
			StopThreadGroup();
		});
	}
	void AddTask(const Task& t) {
		m_queue.Put(t);
	}
	//void AddTask(Task&& t) {
	//	m_queue.Put(t);
	//}
private:
	void Start(int numThread) {
		m_running = true;
		for (int i = 0; i < numThread; ++i) {
			m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
		}
	}
	void RunInThread() {
		while (m_running) {
			std::list<Task> list;
			m_queue.Take(list);
			for (auto t : list) {
				if (!m_running) {
					return;
				}
				t();
			}
		}
	}
	void StopThreadGroup() {
		m_queue.Stop();
		m_running = false;
		for (auto t : m_threadgroup) {
			if (t) {
				t->join();
			}
		}
		m_threadgroup.clear();
	}
	std::list<std::shared_ptr<std::thread>> m_threadgroup;
	SyncQueue<Task> m_queue;
	std::atomic_bool m_running = false;//ֹͣ���
	std::once_flag m_flag;//ִֻ��һ��
};

