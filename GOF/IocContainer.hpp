#pragma once
#include <string>
#include <map>
#include <functional>
#include <exception>
#include <memory>
#include <boost/any.hpp>
//template<typename T>
//class IocContainer
//{
//public:
//
//	IocContainer()
//	{
//	}
//
//	~IocContainer()
//	{
//	}
//	template<typename Drived>
//	void RegisterType(std::string key) {
//		std::function<T*()> func = []() {return new Drived(); };
//		RegisterType(key, func);
//	}
//	T* Resolve(std::string key) {
//		if (m_createMap.find(key) == m_createMap.end()) {
//			return nullptr;
//		}
//		return m_createMap[key]();
//	}
//	std::shared_ptr<T> ResolveShared(std::string key) {
//		return std::shared_ptr<T>(Resolve(key));
//	}
//private:
//	void RegisterType(std::string key, std::function<T*()> func) {
//		if (m_createMap.find(key) != m_createMap.end()) {
//			throw std::invalid_argument("key 已存在");
//		}
//		m_createMap.emplace(key, func);
//	}
//	std::map<std::string, std::function<T*()> > m_createMap;
//};
class IocContainer
{
public:

	IocContainer()
	{
	}

	~IocContainer()
	{
	}
	template<typename T,typename Drived,typename... Args>
	typename std::enable_if<!std::is_base_of<T, Drived>::value>::type RegisterType(const std::string key) {
		std::function<T*(Args...)> func = [](Args... args) {return new T(new Drived(args...)); };
		RegisterType(key, func);
	}
	template<typename T, typename Drived, typename... Args>
	typename std::enable_if<std::is_base_of<T, Drived>::value>::type RegisterType(const std::string key) {
		std::function<T*(Args...)> func = [](Args... args) {return new Drived(args...); };
		RegisterType(key, func);
	}
	template<typename T,typename... Args>
	void RegisterSimple(const std::string key) {
		std::function<T*(Args...)> func = [](Args... args) {return new T(args...); };
		RegisterType(key, func);
	}
	template<typename T,typename... Args>
	T* Resolve(std::string key, Args... args) {
		if (m_createMap.find(key) == m_createMap.end()) {
			return nullptr;
		}
		boost::any resolver = m_createMap[key];
		
		std::function<T*(Args...)> func = boost::any_cast<std::function<T*(Args...)>>(resolver);
		return func(args...);
	}
	template<typename T, typename... Args>
	std::shared_ptr<T> ResolveShared(std::string key, Args... args) {
		return std::shared_ptr<T>(Resolve(key, args));
	}
private:
	void RegisterType(std::string key, boost::any func) {
		if (m_createMap.find(key) != m_createMap.end()) {
			throw std::invalid_argument("key 已存在");
		}
		m_createMap.emplace(key, func);
	}
	std::map<std::string, boost::any> m_createMap;
};

