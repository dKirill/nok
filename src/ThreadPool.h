#ifndef THREADPOOL_H
#define THREADPOOL_H

/*--------------------------------------------------------------------------*/
#include <queue>
#include <vector>
/*--------------------------------------------------------------------------*/
#include "Computer.h"
#include "Thread.h"
/*--------------------------------------------------------------------------*/

class ThreadPool : public ThreadDelegate
{
public:
	ThreadPool();
        virtual ~ThreadPool()/* override*/;

	void add(const NumberInt number);
	void join();
	PrimeToAccNumber nok() const;
	void setThreadNumber(const ThreadInt threadsNumber);
        virtual void threadIsFree(pThread thread)/* override*/;

private:
	Computer _computer;
	PrimeToAccNumber _nok;
	std::mutex _mutex;

	/**
	  @brief _threads пул потоков; указатели, чтобы не копировались в контейнере
	*/
	std::vector<pThread> _threads;
	std::queue<pThread> _freeThreads;
};

#endif // THREADPOOL_H
