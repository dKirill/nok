/*--------------------------------------------------------------------------*/
#include "ThreadPool.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
ThreadPool::ThreadPool()
{

}

/***********************************************/
void ThreadPool::add(const NumberInt number)
{
	while(true)
	{
		pThread freethread;

		_mutex.lock();

		if(_freeThreads.empty())
		{
			_mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); //операции должны выполняться очень быстро. даже 1мс возможно много
			continue;
		}

		freethread = _freeThreads.front();
		_freeThreads.pop();
		_mutex.unlock();

		freethread->add(number);
	}
	for(auto& pthreadref : _threads)
		pthreadref->busy();
}

/***********************************************/
void ThreadPool::join()
{
	D("Ожидание выполнения всех потоков");
	//TODO ожидание выполнения всех потоков
	for(auto const& thread : _threads)
		thread->join();
	D("Все потоки завершены");
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
		pthreadref = pThread(new Thread);
}
