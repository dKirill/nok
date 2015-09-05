/*--------------------------------------------------------------------------*/
#include <limits>
/*--------------------------------------------------------------------------*/
#include "Queue.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
int main(int argc, char* argv[]) //аргументы: количество потоков (необяз.)
{
	try
	{
		Queue queue;
		PrimeToAccNumber result;
		ThreadInt threadNumber;
#ifdef MEASURE
		uint32_t numOfNums = 0;
		decltype(std::chrono::high_resolution_clock::now()) start, end;
#endif

		//разбор арг-ов командной строки
		switch(argc)
		{
			case(1):
			{
				threadNumber = std::thread::hardware_concurrency(); // не выч. основной и "очереди", т.к. они много спят

				if(threadNumber == 0) //в старых библиотеках может быть не реализовано..
					threadNumber = defaultThreadNumber;

				break;
			}
			case(2):
			{
				int64_t temp;

				try
				{
					temp = std::stoi(argv[1]);
				}
				catch(const std::invalid_argument&)
				{
					THROW("Аргумент не число, а должен быть");
				}

				if(temp > std::min(std::numeric_limits<decltype(threadNumber)>::max(), maxThreadNumber) || temp < 1)
					THROW("Неправильный аргумент; Допустимые значения [1, " << std::min(std::numeric_limits<decltype(threadNumber)>::max(), maxThreadNumber) << "]\n");

				threadNumber = temp;

				break;
			}
			default:
			{
				THROW("Неправильное количество аргументов");
			}
		}

		D("Используемое количество потоков=" << threadNumber);
		queue.setThreadNumber(threadNumber);

#ifdef MEASURE
		start = std::chrono::high_resolution_clock::now();
#endif
		D("Начало считывания");
		//считывание, пока дают числа
		for(std::string line; std::getline(std::cin, line); )
		{
			NumberInt number;

			if(line.empty())
			{
				D("Введена пустая строка, интепретируется как завершение ввода");
				break;
			}

			try
			{
				number = std::stoi(line);
			}
			catch(const std::invalid_argument&)
			{
				THROW("В stdin передано не число, так нельзя");
			}

			if(number > maxNumber || number <= 0) //0 нельзя т.к. на него нельзя делить
				THROW("Неправильное число; Допустимы целые числа [1, " << maxNumber << "]");

			queue.add(number);
#ifdef MEASURE
			++numOfNums;
#endif
		}

		D("Считывание окончено");
		//ожидание выполнения всех потоков
		queue.join();
		result = queue.result();

#ifdef MEASURE
		end = std::chrono::high_resolution_clock::now();
#endif
		D("Получен результат:");
		for(auto const& pair : result)
		{
			for(uint32_t i = 0; i < pair.second; ++i)
				std::cout << pair.first << '\n';
		}

#ifdef MEASURE
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
		std::cout << "ВРЕМЯ ВЫПОЛНЕНИЯ АЛГОРИТМА ДЛЯ " << numOfNums << " ЧИСЕЛ И " << threadNumber << " ПОТОКОВ: " << diff.count() << " секунд\n";
#endif
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

