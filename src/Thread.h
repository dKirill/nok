#ifndef THREAD_H
#define THREAD_H

/*--------------------------------------------------------------------------*/
#include <map>
#include <memory>
#include <thread>
/*--------------------------------------------------------------------------*/
#include "Global.h"
#include "Guarded.h"
/*--------------------------------------------------------------------------*/

class Thread;
using pThread = std::shared_ptr<Thread>;
using PrimeToAccNumber = std::map<uint16_t, uint32_t>; //ни к чему 8 байтники

class Thread
{
public:
	Thread();

	/**
	   @brief active работает ли поток
	   @return
	 */
	bool active() const;
	void add(const NumberInt number);

	/**
	   @brief busy есть ли у потока задача
	   @return
	 */
	bool busy() const;
	void join();
	void run();

	/**
	   @brief terminate остановка выполнения потока
	 */
	void terminate();

private:
	Guarded<bool> _active;
	mutable std::mutex _mutex;
	Guarded<NumberInt> _number;
	Guarded<bool> _shouldRun;
	std::thread _thread;
};

#endif // THREAD_H
