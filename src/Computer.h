#ifndef COMPUTER_H
#define COMPUTER_H

/*--------------------------------------------------------------------------*/
#include <set>
/*--------------------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------------------*/

class Computer
{
public:
	Computer();

	PrimeToAccNumber nok(const PrimeToAccNumber& factorized1, const PrimeToAccNumber& factorized2) const;
	PrimeToAccNumber nok(const PrimeToAccNumber& factorized1, const NumberInt number) const;

private:
	PrimeToAccNumber iFactorization(const NumberInt number) const;
	PrimeToAccNumber intersection(const PrimeToAccNumber& map1, const PrimeToAccNumber& map2) const;
	static PrimeToAccNumber merge(const PrimeToAccNumber& map1, const PrimeToAccNumber& map2);
	PrimeToAccNumber substraction(const PrimeToAccNumber& map, const PrimeToAccNumber& subtrahend) const;

	std::set<NumberInt> _primes;
};

#endif // COMPUTER_H
