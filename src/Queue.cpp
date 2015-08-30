/*--------------------------------------------------------------------------*/
#include "Queue.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Queue::Queue() : _thread([this]() { this->run(); })
{

}

/***********************************************/
void Queue::add(const NumberInt number)
{
    std::lock_guard<decltype(_mutex)> guard(_mutex);
    _queue.push(number);
    D("Число=" << number << " добавлено в очередь");
}

/***********************************************/
void Queue::join()
{
    bool empty;

    while(true) //ждем, пока очередь раздаст все задачи
    {
        _mutex.lock();
        empty = _queue.empty();
        _mutex.unlock();

        if(empty)
        {
            _shouldRun = false;
            break;
        }
        else
        {
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

        _mutex.lock();

        if(_queue.empty()) //если очередь пуста, немного спим и проверяем необходимость работы еще раз
        {
            _mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        nextNumber = _queue.front();
        _queue.pop();
        _mutex.unlock();

        _pool.add(nextNumber);
    }

    D("Поток очереди остановлен");
}

/***********************************************/
void Queue::setThreadNumber(const ThreadInt threadsNumber)
{
    _pool.setThreadNumber(threadsNumber);
}
