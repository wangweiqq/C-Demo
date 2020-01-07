#pragma once
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
template<typename Clock = boost::posix_time::microsec_clock>
class basic_ptimer {
public:
	basic_ptimer() {
		restart();
	}
	~basic_ptimer() {
		elapsed();
	}
	void restart() {
		_start_time = Clock::local_time();
	}
	void elapsed() {
		std::cout << Clock::local_time() - _start_time << std::endl;
	}
private:
	boost::posix_time::ptime _start_time;
};
typedef basic_ptimer<boost::posix_time::microsec_clock> ptimer;
typedef basic_ptimer<boost::posix_time::second_clock> sptimer;