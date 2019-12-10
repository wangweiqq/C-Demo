#pragma once
#include <thread>
#include <mutex>
class PLC_S7
{
public:
	PLC_S7();
	~PLC_S7();
	std::mutex mMutex;
	std::thread* mThread;
	void run();
private:
	bool isStop = false;
};

