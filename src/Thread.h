#ifndef THREAD_H
#define THREAD_H

/*--------------------------------------------------------------------------*/
#include <condition_variable>
#include <memory>
#include <thread>
/*--------------------------------------------------------------------------*/
#include "Computer.h"
#include "Global.h"
#include "Guarded.h"
/*--------------------------------------------------------------------------*/

class Thread;
//using pThread = std::shared_ptr<Thread>;
typedef std::shared_ptr<Thread> pThread;

class ThreadDelegate
{
public:
	virtual ~ThreadDelegate() { }
	virtual void threadIsFree(pThread thread) = 0;
};

class Thread : public std::enable_shared_from_this<Thread>
{
public:
	Thread(const Computer& computer);

	void add(const NumberInt number);
	ThreadDelegate* delegate() const;
	void join();
	PrimeToAccNumber nok() const;
	void run();
	void setDelegate(ThreadDelegate* const delegate);

	/**
	   @brief terminate остановка выполнения потока
	 */
	void terminate();

private:
	Guarded<bool> _busy;
	const Computer& _computer;
	std::condition_variable _cond;
        ThreadDelegate* _delegate/* = nullptr*/;
	PrimeToAccNumber _nok;
	mutable std::mutex _mutex;
	Guarded<NumberInt> _number;
	Guarded<bool> _shouldRun;
	std::thread _thread;
};

#endif // THREAD_H
