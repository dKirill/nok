#ifndef THREAD_H
#define THREAD_H

/*--------------------------------------------------------------------------*/
#include <memory>
#include <thread>
/*--------------------------------------------------------------------------*/
#include "Global.h"
#include "Guarded.h"
/*--------------------------------------------------------------------------*/

class Thread;
using pThread = std::shared_ptr<Thread>;

class Thread
{
public:
	Thread();

	/**
		   @brief active работает ли поток
		   @return
		 */
	bool active() const;
	void add();

	/**
		   @brief busy есть ли у потока задача
		   @return
		 */
	bool busy() const;
	void run();

	/**
		   @brief terminate остановка выполнения потока
		 */
	void terminate();

private:
	Guarded<bool> _active;
	mutable std::mutex _mutex;
	Guarded<bool> _shouldRun;
	std::thread _thread;
};

#endif // THREAD_H
