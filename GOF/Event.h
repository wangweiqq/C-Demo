#pragma once
#include <map>
/**
�۲���ģʽ
*/
class NonCopyable {
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};
template<typename Func>
class Event :NonCopyable {
public:
	Event() {}
	~Event() {}
	//ע��۲���,����Keyֵ
	int Connect(Func&& f) {
		return Assign(f);
	}
	int Connect(const Func& f) {
		return Assign(f);
	}
	//�Ƴ��۲���
	void Disconnect(int key) {
		m_connections.erase(key);
	}
	//֪ͨ���й۲���
	template<typename... Args>
	void Notify(Args&&... args) {
		for (auto& it : m_connections) {
			it.second(std::forward<Args>(args)...);
		}
	}
private:
	template<typename F>
	int Assign(F&& f) {
		int key = m_observerId++;
		m_connections.emplace(key, std::forward<F>(f));
		return key;
	}
	int m_observerId = 0;
	std::map<int, Func> m_connections;
};

