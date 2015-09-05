/*--------------------------------------------------------------------------*/
#include <chrono>
/*--------------------------------------------------------------------------*/
#include "Thread.h"
/*--------------------------------------------------------------------------*/

#define DL(x) D("thread=" << _thread.get_id() << " " << x);
#define ERRL(x) ERR("thread=" << _thread.get_id() << " " << x);

/***********************************************/
Thread::Thread(const Computer& computer) : _busy(false), _computer(computer), _delegate(0), _number(0), _shouldRun(false), _thread(([this]() { this->run(); }))
{

}

/***********************************************/
void Thread::add(const NumberInt number)
{
	DL("число принято");
	std::lock_guard<decltype(_mutex)> ulock(_mutex);
	DL("блокировка пройдена");

	if(!delegate())
		THROW("Попытка работы с потоком без делегата");

	_number = number;
	_busy = true;
	DL("новое число принято на обработку=" << number);
	_cond.notify_one();
}

/***********************************************/
ThreadDelegate* Thread::delegate() const
{
	return _delegate;
}

/***********************************************/
void Thread::join()
{
	terminate();
	DL("joined");
}

/***********************************************/
bool Thread::joinable() const
{
	return _thread.joinable();
}

/***********************************************/
PrimeToAccNumber Thread::nok() const
{
	return _nok;
}

/***********************************************/
void Thread::run()
{
	DL("starts");
	_shouldRun = true;

	while(_shouldRun.value())
	{
		DL("блокировка в run()");
		std::unique_lock<decltype(_mutex)> ulock(_mutex);
		DL("блокировка в run() пройдена");

		if(!_busy.value())
		{
			_cond.wait(ulock);
			continue;
		}

		_nok = _computer.nok(_nok, _number.value());
		DL("nok для " << _number.value() << " подсчитан");

		_busy = false;
		_delegate->threadIsFree(shared_from_this());
		DL("ожидание сигнала..");
		_cond.wait(ulock);
		DL("сигнал получен..");
	}

	DL("stops");
}

/***********************************************/
void Thread::setDelegate(ThreadDelegate* const delegate)
{
	_delegate = delegate;
	DL("делегат установлен");
	_delegate->threadIsFree(shared_from_this());
}

/***********************************************/
void Thread::terminate()
{
	DL("вызван terminate");
	std::unique_lock<decltype(_mutex)> ulock(_mutex, std::defer_lock);
	DL("terminate лок пройден");

	while(_busy.value())
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); //TODO condition

	_shouldRun = false;
	DL("terminate:lock");
	ulock.lock(); //лок нужен чтобы не кинуть сразу 2 нотифая
	DL("terminate:lock пройден");
	_cond.notify_one();
	DL("сигнал выдан");
	ulock.unlock();
	DL("лок отпущен");
	_thread.join();
	DL("std::thread::join пройден");
	DL("terminated");
}
