#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include "ThreadPool.h"
/**
单实例
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
			throw new std::logic_error("没有被初始化");
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
struct A {
	A() {
		std::cout << "A构造" << std::endl;
	}
	//A(std::string str) {
	//	std::cout << "A构造:" << str << std::endl;
	//}
	A(std::string& str) {
		std::cout << "A构造左值:" << str << std::endl;
	}
	A(std::string&& str) {
		std::cout << "A构造右值:" << str << std::endl;
	}
};
/**
观察者模式
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
	//注册观察者,返回Key值
	int Connect(Func&& f) {
		return Assign(f);
	}
	int Connect(const Func& f) {
		return Assign(f);
	}
	//移除观察者
	void Disconnect(int key) {
		m_connections.erase(key);
	}
	//通知所有观察者
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
		m_connections.emplace(key,std::forward<F>(f));
		return key;
	}
	int m_observerId = 0;
	std::map<int, Func> m_connections;
};
struct StA {
	int a, b;
	void print(int a, int b) {
		std::cout << "StA::print:(" << a << "," << b << ")" << std::endl;
	}
};
void print(int a, int b) {
	std::cout << "::print:(" << a << "," << b << ")" << std::endl;
}
/**
访问者模式
*/
template<typename... Types>
struct Visitor;
template<typename T>
struct Visitor<T> {
	virtual void Visit(const T&) = 0;
};
template<typename T,typename... Types>
struct Visitor<T, Types...> :Visitor<Types...> {
	using Visitor<Types...>::Visit;
	virtual void Visit(const T&) = 0;
};
struct stB;
struct stC;
struct Base {
	typedef Visitor<stB, stC> MyVisitor;
	virtual void Accept(MyVisitor&) = 0;
};
struct stB :Base {
	double val;
	void Accept(MyVisitor& v) {
		v.Visit(*this);
	}
};
struct stC :Base {
	int val;
	void Accept(MyVisitor& v) {
		v.Visit(*this);
	}
};
struct PrintVisitor :Base::MyVisitor {
	void Visit(const stB& b) {
		std::cout << "from B:" << b.val << std::endl;
	}
	void Visit(const stC& c) {
		std::cout << "from C:" << c.val << std::endl;
	}
};
/**
命令模式
*/
template<typename Receiver>
class SimpleCommand {
public:
	typedef void (Receiver::* Action)();
	SimpleCommand(Receiver* r, Action a) {
		_receiver = r;
		_action = a;
	}
	virtual void Execute() {
		(_receiver->*_action)();
	}
private:
	Action _action;
	Receiver* _receiver;
};
class MyClass {
public:
	void Func() {
		std::cout << "MyClass::Func" << std::endl;
	}
	int triple0(int a) {
		std::cout << "MyClass::triple0:" << a << std::endl;
		return a;
	}
	int triple1(int a)const {
		std::cout << "MyClass::triple1:" << a << std::endl;
		return a;
	}
};
template<typename R = void>
struct CommCommand {
private:
	std::function<R()> m_f;
public:
	template<typename F,typename... Args, typename = typename std::enable_if<!std::is_member_function_pointer<F>::value >::type >
	void Wrap(F&& f, Args&&... args) {
		m_f = [&]() {return  f(std::forward<Args>(args)...); };
	}
	template<typename C,typename P,typename... Args>
	void Wrap(R(C::*f)(Args...), P&& p, Args&&... args) {
		m_f = [&,f]() {return (p->*f)(args...); };
	}
	template<typename C,typename P,typename...Args>
	void Wrap(R(C::*f)(Args...)const, P&& p, Args&&...args) {
		m_f = [&p,&args...,f]() {return (p->*f)(args...); };
	}
	R Excecute() {
		return m_f();
	}
};
int add_one(int n) {
	std::cout << "add_one:" << n << std::endl;
	return n;
}
int main() {
	int cccc = std::thread::hardware_concurrency();

	ThreadPool pool(2);
	std::thread thr1([&pool]() {
		for (int i = 0; i <  10; ++i) {
			auto thdid = std::this_thread::get_id();
			pool.AddTask([thdid]() {
				std::cout << "同步线程1线程ID：" << thdid << std::endl;
			});
		}
	});
	std::thread thr2([&pool]() {
		for (int i = 0; i <  10; ++i) {
			auto thdid = std::this_thread::get_id();
			pool.AddTask([thdid]() {
				std::cout << "同步线程2线程ID：" << thdid << std::endl;
			});
		}
	});
	std::this_thread::sleep_for(std::chrono::seconds(10));
	thr1.join();
	thr2.join();
	pool.Stop();

	MyClass my;
	CommCommand<int> command;
	//command.Wrap(&MyClass::triple0, &my, 3);
	command.Wrap(&MyClass::triple1, &my, 30);
	//command.Wrap(add_one, 3);
	int r = command.Excecute();

	std::string str = "Hello World";
	Singleton<A>::Instance(str);
	Singleton<A>::DestroyInstance();
	Singleton<A>::Instance(std::move(str));
	Singleton<A>::DestroyInstance();
	Singleton<A>::Instance();
	Singleton<A>::DestroyInstance();

	Event<std::function<void(int,int)>> myevent;
	int key = myevent.Connect(print);
	int lambakey = myevent.Connect([](int a, int b) {
		std::cout << "lamba:(" << a << "," << b << ")" << std::endl;
	});
	StA sa;
	std::function<void(int, int)> f = std::bind(&StA::print, &sa, std::placeholders::_1, std::placeholders::_2);
	int funkey = myevent.Connect(f);
	int a = 1, b = 2;
	myevent.Notify(1, 2);
	myevent.Disconnect(key);
	myevent.Disconnect(lambakey);
	myevent.Disconnect(funkey);


	PrintVisitor vis;
	stB bb;
	bb.val = 8.97;
	stC cc;
	cc.val = 10;
	bb.Accept(vis);
	cc.Accept(vis);
	return 0;
}