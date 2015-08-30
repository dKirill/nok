#ifndef QUEUE_H
#define QUEUE_H

/*--------------------------------------------------------------------------*/
#include <mutex>
#include <queue>
#include <thread>
/*--------------------------------------------------------------------------*/
#include "Global.h"
#include "ThreadPool.h"
/*--------------------------------------------------------------------------*/

class Queue
{
public:
	Queue();

	void add(const NumberInt number);
	void join();
	PrimeToAccNumber result() const;
	void run();
	void setThreadNumber(const ThreadInt threadsNumber);

private:

	std::mutex _mutex;
	ThreadPool _pool;
	std::queue<NumberInt> _queue;
	Guarded<bool> _shouldRun;
	std::thread _thread;
};

#endif // QUEUE_H
