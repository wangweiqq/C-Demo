#pragma once
/**
��ʵ��
*/
template<typename T>
class Singleton {
public:
	template<typename ...Arg>
	static T* Instance(Arg&&... arg) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(std::forward<Arg>(arg)...);
		}
		return m_pInstance;
	}
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			throw new std::logic_error("û�б���ʼ��");
		}
		return m_pInstance;
	}
	static void DestroyInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator =(const Singleton&) = delete;
	static T* m_pInstance;
};
template<typename T> T* Singleton<T>::m_pInstance = nullptr;

