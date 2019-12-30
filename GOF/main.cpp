#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include "ThreadPool.h"
#include "Singleton.h"
#include "Event.h"
#include "CommCommand.h"
#include "Visitor.h"
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

struct StA {
	int a, b;
	void print(int a, int b) {
		std::cout << "StA::print:(" << a << "," << b << ")" << std::endl;
	}
};
void print(int a, int b) {
	std::cout << "::print:(" << a << "," << b << ")" << std::endl;
}


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