#ifndef THREADPOOL_H
#define THREADPOOL_H

/*--------------------------------------------------------------------------*/
#include <vector>
/*--------------------------------------------------------------------------*/
#include "Thread.h"
/*--------------------------------------------------------------------------*/

class ThreadPool
{
public:
	ThreadPool();

	void add(const NumberInt number);
	void join();
	void setThreadNumber(const ThreadInt threadsNumber);

private:
	/**
	   @brief _threads пул потоков; указатели, чтобы не копировались в контейнере
	 */
	std::vector<pThread> _threads;
};

#endif // THREADPOOL_H
