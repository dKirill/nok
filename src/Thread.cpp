/*--------------------------------------------------------------------------*/
#include <chrono>
/*--------------------------------------------------------------------------*/
#include "Thread.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Thread::Thread() : _active(false), _shouldRun(false), _thread(runHelper<Thread>, this)
{

}

/***********************************************/
bool Thread::active() const
{
	return _active.value();
}

/***********************************************/
void Thread::add(const NumberInt number)
{
	if(busy())
		THROW("Попытка занять занятый поток");

	_number = number;
}

/***********************************************/
bool Thread::busy() const
{
	//TODO
	return false;
}

/***********************************************/
void Thread::join()
{
	_thread.join();
}

/***********************************************/
void Thread::run()
{
	D("thread=" << _thread.get_id() << " starts");
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

	D("&thread=" << _thread.get_id() << " stops");
}

/***********************************************/
void Thread::terminate()
{
	std::lock_guard<decltype(_mutex)> guard(_mutex);

	if(!active())
	{
		ERR("&thread=" << _thread.get_id() << " isn't running");

		return;
	}
	_shouldRun = false;
	_thread.join();
	_active = false;
	D("&thread=" << _thread.get_id() << " terminated");
}
