/*--------------------------------------------------------------------------*/
#include <limits>
/*--------------------------------------------------------------------------*/
#include "ThreadPool.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
int main(int argc, char* argv[]) //как аргумент можно передать желаемое количество потоков [1, 2^16)
{
	try
	{
		ThreadInt threadNumber;
		ThreadPool pool;
		int64_t number;

		switch(argc)
		{
			case(1):
			{
				threadNumber = std::thread::hardware_concurrency();
				D("Используется дефолтное количество потоков=" << threadNumber);
				break;
			}
			case(2):
			{
				int64_t temp;

				temp = std::stoi(argv[1]);

				if(temp > std::numeric_limits<ThreadInt>::max() || temp < 1)
					THROW("Неправильный аргумент; Допустимые значения [1, " << std::numeric_limits<ThreadInt>::max() << "]\n");

				threadNumber = temp;
				D("Используется количество потоков=" << threadNumber);

				break;
			}
			default:
			{
				THROW("Неправильное количество аргументов");
			}
		}

		pool.setThreadNumber(threadNumber);

		//считывание, пока дают числа
		while(std::cin >> number)
		{
			if(number > maxNumber || number < 0)
				THROW("Неправильное число; Допустимые значения [0, " << maxNumber << "]");

			pool.add(number);
		}

		//ожидание выполнения всех потоков
		pool.join();
		//TODO вывести результаты
	}
	catch(const std::exception& e)
	{
		ERR("Ошибка при выполнении программы: " << e.what());
		return 1;
	}
	catch(...)
	{
		ERR("Неизвестная ошибка при выполнении программы");
		return 2;
	}

    return 0;
}

