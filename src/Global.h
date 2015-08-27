#ifndef GLOBAL_H
#define GLOBAL_H

/*--------------------------------------------------------------------------*/
#include <cstdint>
#include <exception>
#include <iostream>
#include <set>
#include <sstream>
/*--------------------------------------------------------------------------*/

//consts
const uint16_t maxNumber = 10000;

//aliases
using NumberInt = uint16_t; //по заданию макс. значение 10000
using ThreadInt = uint16_t; //макс. кол. потоков 2^16

//custom exception
class Exception : public std::exception
{
public:
	Exception() noexcept { }
	Exception(const std::string what_) noexcept : _what(what_) { }
	virtual ~Exception() override { }

	/** Returns a C-style character string describing the general cause
		 *  of the current error.  */
	virtual const char* what() const noexcept override { return _what.c_str(); }

private:
	std::string _what;
};

//для запуска метода в std::thread
template<typename ThreadType>
void runHelper(ThreadType* const thread)
{
	thread->run();
}

//defines
#ifdef DEBUG
#define D(x) std::cout << x << '\n';
#define ERR(x) std::cerr << x << '\n';
#elif
#define D(x) ;
#define ERR(x) ;
#endif

#define THROW(x) { std::stringstream ss; ss << "Error: " << x << "; func: " << __PRETTY_FUNCTION__; throw Exception(ss.str()); }

#endif // GLOBAL_H

