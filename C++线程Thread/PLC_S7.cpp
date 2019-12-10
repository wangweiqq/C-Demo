#include "PLC_S7.h"



PLC_S7::PLC_S7():mThread()
{
	mThread = new std::thread(&PLC_S7::run, this);
}


PLC_S7::~PLC_S7()
{
	isStop = true;
	mThread->join();
	delete mThread;
}
void PLC_S7::run() {
	while (!this->isStop) {
		std::unique_lock<std::mutex> lock(mMutex,);
	}
}