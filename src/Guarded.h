#ifndef GUARDED
#define GUARDED

/*--------------------------------------------------------------------------*/
#include <mutex>
/*--------------------------------------------------------------------------*/

template<typename Value>
class Guarded
{
public:
	/***********************************************/
	Guarded() { }

	/***********************************************/
	Guarded(const Value& refval) : _value(refval) { }

	/***********************************************/
	Guarded& operator=(const Value& refval)
	{
		std::lock_guard<decltype(_mutex)> guard(_mutex);

		_value = refval;

		return *this;
	}

	/***********************************************/
	Value value() const
	{
		std::lock_guard<decltype(_mutex)> guard(_mutex);

		return _value;
	}

private:
	Value _value;
	mutable std::mutex _mutex;
};

#endif // GUARDED

