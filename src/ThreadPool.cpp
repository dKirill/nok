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
	if(_threads.empty())
	{
                ERR("Ни один поток не создан");
		return;
	}
int x = 1 + number;
int y = x;
x = y;
	//TODO
}

/***********************************************/
void ThreadPool::join()
{
    //TODO ожидание выполнения всех потоков
}

/***********************************************/
void ThreadPool::setThreadNumber(const ThreadInt threadsNumber)
{
	if(threadsNumber == 0)
	{
                ERR("threadsNumber==0");
		return;
	}

	_threads.resize(threadsNumber);

	for(auto& pthreadref : _threads)
		pthreadref = pThread(new Thread);
}
