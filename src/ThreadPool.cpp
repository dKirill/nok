/*--------------------------------------------------------------------------*/
#include "ThreadPool.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
ThreadPool::ThreadPool()
{

}

/***********************************************/
ThreadPool::~ThreadPool()
{

}

/***********************************************/
void ThreadPool::add(const NumberInt number)
{
	D("threadpool: новое число=" << number);
	while(true)
	{
		pThread freethread;
		std::unique_lock<decltype(_mutex)> ulock(_mutex);

		if(_freeThreads.empty())
		{
			_cond.wait(ulock);
			continue;
		}

		freethread = _freeThreads.front();
		_freeThreads.pop();

		D("передача числа потоку..");
		freethread->add(number);
		return;
	}
}

/***********************************************/
void ThreadPool::join()
{
	D("Ожидание выполнения всех потоков");
	for(auto const& thread : _threads)
	{
		if(thread->joinable())
		{
			thread->join();
			_nok = _computer.nok(_nok, thread->nok());
		}
		else
		{
			D("Один из потоков !joinable");
		}
	}
	D("Все потоки завершены");
}

/***********************************************/
PrimeToAccNumber ThreadPool::nok() const
{
	return _nok;
}

/***********************************************/
void ThreadPool::setThreadNumber(const ThreadInt threadsNumber)
{
	if(threadsNumber == 0)
	{
		THROW("threadsNumber==0");
		return;
	}

	_threads.resize(threadsNumber);

	for(auto& pthreadref : _threads)
	{
		pthreadref = pThread(new Thread(_computer));
		pthreadref->setDelegate(this);
	}
}

/***********************************************/
void ThreadPool::threadIsFree(pThread thread)
{
	std::lock_guard<decltype(_mutex)> guard(_mutex);

	D("поток освободился");
	_freeThreads.push(thread);
	_cond.notify_one();
}
