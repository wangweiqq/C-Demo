#pragma once
#include <iostream>
/**
访问者模式
*/
template<typename... Types>
struct Visitor;
template<typename T>
struct Visitor<T> {
	virtual void Visit(const T&) = 0;
};
template<typename T, typename... Types>
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

