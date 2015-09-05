/*--------------------------------------------------------------------------*/
#include "Queue.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Queue::Queue() : _thread([this]() { this->run(); })
{

}

/***********************************************/
Queue::~Queue()
{
	if(_thread.joinable())
		join();
}

/***********************************************/
void Queue::add(const NumberInt number)
{
	std::lock_guard<decltype(_mutex)> guard(_mutex);
	_queue.push(number);
	_cond.notify_one();
	D("Число=" << number << " добавлено в очередь");
}

/***********************************************/
void Queue::join()
{
	bool empty;

	while(true) //ждем, пока очередь раздаст все задачи
	{
		std::unique_lock<decltype(_mutex)> ulock(_mutex);

		empty = _queue.empty();

		if(empty)
		{
			_shouldRun = false;
			_cond.notify_one();
			break;
		}
		else
		{
			ulock.unlock();
			D("Очередь ожидает своего опустошения..");
			std::this_thread::sleep_for(std::chrono::milliseconds(50)); //TODO condition
		}
	}

	D("вызов pool.join()");
	_pool.join();
	_thread.join();
}

/***********************************************/
PrimeToAccNumber Queue::result() const
{
	return _pool.nok();
}

/***********************************************/
void Queue::run()
{
	D("Поток очереди запущен");
	_shouldRun = true;

	while(_shouldRun.value())
	{
		NumberInt nextNumber;
		std::unique_lock<decltype(_mutex)> ulock(_mutex);

		if(_queue.empty()) //если очередь пуста, немного спим и проверяем необходимость работы еще раз
		{
			_cond.wait(ulock);
			continue;
		}

		nextNumber = _queue.front();
		_queue.pop();
		_pool.add(nextNumber);
	}

	D("Поток очереди остановлен");
}

/***********************************************/
void Queue::setThreadNumber(const ThreadInt threadsNumber)
{
	_pool.setThreadNumber(threadsNumber);
}
