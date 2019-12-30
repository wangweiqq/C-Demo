#pragma once
#include <functional>
/**
ÃüÁîÄ£Ê½
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

template<typename R = void>
struct CommCommand {
private:
	std::function<R()> m_f;
public:
	template<typename F, typename... Args, typename = typename std::enable_if<!std::is_member_function_pointer<F>::value >::type >
	void Wrap(F&& f, Args&&... args) {
		m_f = [&]() {return  f(std::forward<Args>(args)...); };
	}
	template<typename C, typename P, typename... Args>
	void Wrap(R(C::*f)(Args...), P&& p, Args&&... args) {
		m_f = [&, f]() {return (p->*f)(args...); };
	}
	template<typename C, typename P, typename...Args>
	void Wrap(R(C::*f)(Args...)const, P&& p, Args&&...args) {
		m_f = [&p, &args..., f]() {return (p->*f)(args...); };
	}
	R Excecute() {
		return m_f();
	}
};

