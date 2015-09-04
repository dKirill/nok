#ifndef GLOBAL_H
#define GLOBAL_H

/*--------------------------------------------------------------------------*/
#include <cstdint>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
/*--------------------------------------------------------------------------*/

//consts
const uint16_t defaultThreadNumber = 8;
const uint16_t maxNumber = 10000;
const uint16_t maxThreadNumber = 1024; //смысла столько делать нет, но чтобы не получать "неожиданные" сегфолты приходится ограничивать

//aliases
typedef uint16_t NumberInt; //по заданию макс. значение 10000
typedef std::map<uint16_t, uint32_t> PrimeToAccNumber; //ни к чему 8 байтники
typedef uint16_t ThreadInt;

//custom exception
class Exception : public std::exception
{
public:
	Exception() noexcept { }
	Exception(const std::string what_) noexcept : _what(what_) { }
	virtual ~Exception() noexcept /*override*/ { }

	virtual const char* what() const noexcept /*override*/ { return _what.c_str(); }

private:
	std::string _what;
};

//defines (ошибки пусть выводит и не в дебаге)
#define ERR(x) std::cerr << x << '\n';
#ifdef DEBUG
#define D(x) std::cout << x << '\n';
#else
#define D(x) ;
//#define ERR(x) ;
#endif

#define THROW(x) { std::stringstream ss; ss << "Error: " << x << "; func: " << __PRETTY_FUNCTION__; throw Exception(ss.str()); }

#endif // GLOBAL_H

