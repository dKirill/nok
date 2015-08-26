/*--------------------------------------------------------------------------*/
#include <chrono>
/*--------------------------------------------------------------------------*/
#include "Thread.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
void runHelper(Thread* const thread)
{
	thread->run();
}

/***********************************************/
/***********************************************/
Thread::Thread() : _active(false), _shouldRun(false), _thread(runHelper, this)
{

}

/***********************************************/
bool Thread::active() const
{
	return _active.value();
}

/***********************************************/
bool Thread::busy() const
{
	//TODO
	return false;
}

/***********************************************/
void Thread::run()
{
	D("&thread=" << reinterpret_cast<unsigned long long>(this) << " starts");
	_active = true;
	_shouldRun = true;

	while(_shouldRun.value())
	{
		if(busy()) //TODO вместо можно поставить кондишн
		{

		}
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	D("&thread=" << reinterpret_cast<unsigned long long>(this) << " stops");
}

/***********************************************/
void Thread::terminate()
{
	std::lock_guard<std::mutex> guard(_mutex);

	if(!active())
	{
		ERR("&thread=" << reinterpret_cast<unsigned long long>(this) << " isn't running");

		return;
	}
	_shouldRun = false;
	_thread.join();
	_active = false;
	D("&thread=" << reinterpret_cast<unsigned long long>(this) << " terminated");
}
