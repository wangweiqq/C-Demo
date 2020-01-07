#pragma once
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <iterator>
#include <utility>
#ifdef _DEBUG
#pragma comment(lib,"libboost_regex-vc140-mt-gd-x64-1_72.lib")
#else
#pragma comment(lib,"libboost_regex-vc140-mt-x64-1_72.lib")
#endif // DEBUG
template<typename R>
using iterator_range = boost::iterator_range<decltype(std::begin(std::declval<R>()))>;
template<typename R>
class LinqCpp{
public:
	LinqCpp(R& range) :m_linqrange(range) {}
	auto begin()->decltype(std::begin(std::declval<const R>())) {
		return std::begin(m_linqrange);
	}
	auto end()->decltype(std::end(std::declval<const R>())) {
		return std::end(m_linqrange);
	}
	template<typename F>
	auto select(const F& f)//->LinqCpp<boost::range_detail::transformed_range<F, R>> 
	{
		return LinqCpp<boost::transformed_range<F,R>>(boost::adaptors::transform(m_linqrange, f));
	}
	template<typename F>
	auto where(const F& f)// ->LinqCpp<boost::range_detail::filtered_range<F, R>> 
	{
		return LinqCpp<boost::filtered_range<F,R>>(boost::adaptors::filter(m_linqrange, f));
	}
	auto max() -> typename R::value_type
	{
		return *std::max_element(begin(), end());
	}
	auto reverse() ->LinqCpp<boost::reversed_range<R>> {
		return LinqCpp<boost::reversed_range<R>>(boost::adaptors::reverse(m_linqrange));
	}
private:
	R m_linqrange;
};
template<typename R>
LinqCpp<iterator_range<R>> from(R& range) {
	//return boost::iterator_range<decltype(std::begin(std::declval<std::vector<int>>()))>
	return LinqCpp<iterator_range<R>>(iterator_range<R>(range));
}