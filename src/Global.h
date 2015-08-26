#ifndef GLOBAL_H
#define GLOBAL_H

/*--------------------------------------------------------------------------*/
#include <cstdint>
#include <exception>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <sstream>
/*--------------------------------------------------------------------------*/

//forward declarations

//aliases
using pAiIndividual = std::shared_ptr<AiIndividual>;

using AttackInt = uint16_t;

using Matches = std::set<pMatch>;
using Players = std::set<pPlayer>;
using Scores = std::vector<pScore>;

//custom exception
class Exception : public std::exception
{
public:
	Exception(const std::string what_) _GLIBCXX_USE_NOEXCEPT : _what(what_) { }
	virtual ~Exception() _GLIBCXX_USE_NOEXCEPT { }

	/** Returns a C-style character string describing the general cause
	 *  of the current error.  */
	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT { return _what.c_str(); }

private:
	std::string _what;
};

//defines
#define THROW(x) { std::stringstream ss; ss << "Error: " << x << "; func: " << __PRETTY_FUNCTION__; throw Exception(ss.str()); }

#endif // GLOBAL_H

