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
#include "IocContainer.hpp"
#include "function_traits.h"
#include <sqlite3.h>
#include <codecvt>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/timer.hpp>
//#include <boost/date_time/gregorian/gregorian.hpp>
#include "LinqObject.h"
#include <iterator>
#include <utility>
#include "basic_ptimer.h"
#ifdef _DEBUG
#pragma comment(lib,"libboost_regex-vc140-mt-gd-x64-1_72.lib")
#else
#pragma comment(lib,"libboost_regex-vc140-mt-x64-1_72.lib")
#endif // DEBUG

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
template<typename T>
void PrintT(T& t) {
	std::cout << "左值" << std::endl;
}
template<typename T>
void PrintT(T&& t) {
	std::cout << "右值" << std::endl;
}
template<typename T>
void TestForward(T&& v) {
	PrintT(v);
	PrintT(std::forward<T>(v));
	PrintT(std::move(v));
}
class IHello {
public:
	IHello() {
		std::cout << "IHello()" << std::endl;
	}
	virtual ~IHello() {
		std::cout << "~IHello()" << std::endl;
	}
	virtual void Output(const std::string& str) {
		std::cout << "IHello::Output " << str << std::endl;
	}
};
class Hello :public IHello {
public:
	Hello() {
		std::cout << "Hello()" << std::endl;
	}
	~Hello(){
		std::cout << "~Hello()" << std::endl;
	}
	void Output(const std::string& str)override {
		std::cout << "Hello::Output " << str << std::endl;
	}
};
class HellProxy :public IHello {
public:
	HellProxy(IHello* p) :m_ptr(p) {
		std::cout << "HellProxy()" << std::endl;
	}
	~HellProxy() {
		delete m_ptr;
		m_ptr = nullptr;
		std::cout << "~HellProxy()" << std::endl;
	}
	void Output(const std::string& str)final {
		std::cout << "HellProxy::Output " << std::endl;
		m_ptr->Output(str);
	}
private:
	IHello* m_ptr;
};
struct ICar {
	virtual ~ICar() {};
	virtual void test()const = 0;
};
struct Bus :ICar {
	Bus() {}
	~Bus() {
	
	}
	void test()const {
		std::cout << "Bus::test()" << std::endl;
	}
};
struct Car :ICar {
	Car() {}
	~Car() {
	
	}
	void test()const {
		std::cout << "Car::test()" << std::endl;
	}
};
struct Base2 {
	virtual ~Base2() {}
	virtual void Func() = 0;
};
struct DerivedB :Base2 {
	void Func()override {
		std::cout << "DerivedB::Func" << std::endl;
	}
};
struct DerivedC :Base2 {
	void Func()override {
		std::cout << "DerivedC::Func" << std::endl;
	}
};
struct DerivedD :Base2 {
	void Func()override {
		std::cout << "DerivedD::Func" << std::endl;
	}
};
struct AB {
	AB(Base2* ptr):m_ptr(ptr) {}
	~AB() {
		delete m_ptr;
		m_ptr = nullptr;
	}
	void Func() {
		m_ptr->Func();
	}
private:
	Base2* m_ptr;
};
template<typename T>
void PrintType() {
	std::cout << typeid(T).name() << std::endl;
}
float free_function(const std::string& a, int b) {
	return (float)a.size() / b;
}
int main() {




	return 0;
	ptimer ttttt;
	sptimer ttttt1;
	boost::timer tttttt2;
	std::cout << "C++ : " << __cplusplus << std::endl;
	std::vector<int> v = { 1,2,3,4 };	
	auto rv = from(v).select([](auto i) {return i + 2; }).where([](auto i) {return i > 2; }).max();
	std::cout << rv << std::endl;
	std::cout << boost::gregorian::day_clock::local_day() << std::endl;
	std::cout << boost::gregorian::day_clock::universal_day() << std::endl;
	boost::gregorian::date d1(boost::gregorian::neg_infin);
	boost::gregorian::date d2(boost::gregorian::pos_infin);
	boost::gregorian::date d3(boost::gregorian::not_a_date_time);
	boost::gregorian::date d4(boost::gregorian::max_date_time);
	boost::gregorian::date d5(boost::gregorian::min_date_time);
	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;
	std::cout << d3 << std::endl;
	std::cout << d4 << std::endl;
	std::cout << d5 << std::endl;
	try {
		boost::gregorian::date d6(1399, 12, 1);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	boost::gregorian::date d7(2020, 1, 1);
	boost::gregorian::date d8 = d7.end_of_month();
	std::cout << boost::gregorian::to_iso_extended_string(d8) << std::endl;
	boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();
	boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::universal_time();
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	boost::posix_time::ptime t3(boost::gregorian::date(2020, 1, 10), boost::posix_time::hours(12)+boost::posix_time::minutes(30) + boost::posix_time::seconds(30));
	std::cout << t3 << std::endl;
	std::tm tm1 = boost::posix_time::to_tm(t3);
	std::cout << tttttt2.elapsed() << std::endl;;
	//boost::gregorian::days
	//for (auto it = rv.begin(); it != rv.end(); ++it) {
	//	std::cout << *it << ",";
	//}
	//int intarr[] = { 1,2,3,4 };
	//auto range = boost::make_iterator_range(intarr);
	//for (auto item : range) {
	//	std::cout << item << ",";
	//}
	//std::cout << std::endl;
	//auto rg = boost::adaptors::filter(range, [](auto i) {return i % 2 == 0; });
	//for (auto item : rg) {
	//	std::cout << item << ",";
	//}
	//std::cout << std::endl;
	//auto rg2 = boost::adaptors::transform(range, [](auto i) {return i += 2; });
	//for (auto item : rg2) {
	//	std::cout << item << ",";
	//}
	//std::cout << std::endl;
	return 0;
	sqlite3* conn = nullptr;
	int result = sqlite3_open("D:\\Test\\C-Demo\\test.db", &conn);
	const char* createTableSql = "create table if not exists PersonTable(ID INTEGER NOT NULL,Name Text,Address BLOB);";
	int ret = sqlite3_exec(conn, createTableSql, nullptr, nullptr, nullptr);

	const char* sqlinsert = "insert into PersonTable(ID,Name,Address) values(?,?,?);";
	int id = 2;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring name = L"这是一个宽字符串";
	//std::string name = converter.to_bytes(L"这是一个宽字符串");
	//std::wstring name = converter.from_bytes(www);
	std::wstring city = L"苏州";

	sqlite3_stmt* stmt2 = nullptr;
	sqlite3_prepare_v2(conn, sqlinsert, strlen(sqlinsert), &stmt2, nullptr);

	sqlite3_bind_int(stmt2, 1, id);
	sqlite3_bind_text16(stmt2, 2, name.data(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text16(stmt2, 3, city.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_step(stmt2);
	sqlite3_reset(stmt2);
	//sqlite3_finalize(stmt2);
	//stmt2 = nullptr;
	//const char* sqlselect = "select * from PersonTable where Name=?;";
	const char* sqlselect = "select * from PersonTable;";
	sqlite3_prepare_v2(conn, sqlselect, strlen(sqlselect), &stmt2, nullptr);
	//std::wstring param = L"姓名1";
	//sqlite3_bind_text16(stmt2, 1, param.c_str(), param.length() * sizeof(wchar_t), SQLITE_TRANSIENT);
	int count = sqlite3_column_count(stmt2);
	while (true) {
		int ret = sqlite3_step(stmt2);
		if (ret == SQLITE_DONE || ret != SQLITE_ROW) {
			break;
		}
		for (int c = 0; c < count; ++c) {
			int coltype = sqlite3_column_type(stmt2, c);
			switch (coltype)
			{
			case SQLITE_INTEGER:
			{
				int val = sqlite3_column_int(stmt2, c);
				std::cout << "int : " << val << " ";
			}
				break;
			case SQLITE_FLOAT:
			{
				double val = sqlite3_column_double(stmt2, c);
				std::cout << "float : " << val << " ";
			}
				break;
			case SQLITE_TEXT:
			{
				std::wstring val = (wchar_t*)sqlite3_column_text16(stmt2, c);
				std::wcout.imbue(std::locale("chs"));
				std::wcout << L"text : " << val.c_str() << " ";
				//std::cout << "text : " << val << " ";
			}
				break;
			case SQLITE_BLOB:
			{
				std::wstring val = (wchar_t*)sqlite3_column_text16(stmt2, c);
				std::wcout << L"blob : " << val << " ";
				//std::cout << "blob : ";
			}
				break;
			case SQLITE_NULL:
				std::cout << "null : ";
				break;
			}
		}
		std::cout << std::endl;
	}
	sqlite3_finalize(stmt2);
	sqlite3_close(conn); 



	std::function<int(int)> f111 = [](int a) {return a; };
	PrintType<function_traits<std::function<int(int)>>::function_type>();
	PrintType<function_traits<decltype(f111)>::function_type>();
	PrintType<function_traits<decltype(free_function)>::function_type>();


	IocContainer ioc;
	ioc.RegisterType<Base2, DerivedB>("B");
	ioc.RegisterSimple<DerivedC>("C");
	ioc.RegisterType<AB, DerivedD>("D");
	auto pa = ioc.Resolve<Base2>("B");
	pa->Func();
	auto pa1 = ioc.Resolve<DerivedC>("C");
	pa1->Func();
	auto pa2 = ioc.Resolve<AB>("D");
	pa2->Func();

	std::shared_ptr<HellProxy> hello = std::make_shared<HellProxy>(new Hello());
	hello->Output("It is a Test");
	hello.reset();

	TestForward(1);
	int x = 1;
	TestForward(x);
	TestForward(std::forward<int>(x));


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
	thr1.join();
	thr2.join();
	std::this_thread::sleep_for(std::chrono::seconds(3));
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