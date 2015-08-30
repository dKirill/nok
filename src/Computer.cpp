/*--------------------------------------------------------------------------*/
#include "Computer.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
Computer::Computer()
{
    for(NumberInt num = 2; num <= maxNumber; ++num) //заполняем таблицу простых чисел; 2 - первое простое
    {
        uint16_t numOfDividers = 0;

        for(NumberInt divider = 1; divider <= num; ++divider)
        {
            if(num % divider == 0)
                ++numOfDividers;
        }

        if(numOfDividers == 2)
            _primes.insert(num);
    }
}

/***********************************************/
PrimeToAccNumber Computer::nok(const PrimeToAccNumber& factorized1, const PrimeToAccNumber& factorized2) const
{
    PrimeToAccNumber merged = merge(factorized1, factorized2);
    PrimeToAccNumber isection = intersection(factorized1, factorized2);
    PrimeToAccNumber difference = substraction(merged, isection);

    return difference;
}

/***********************************************/
PrimeToAccNumber Computer::nok(const PrimeToAccNumber& factorized1, const NumberInt number) const
{
    PrimeToAccNumber factorized2 = iFactorization(number);

    return nok(factorized1, factorized2);
}

/***********************************************/
PrimeToAccNumber Computer::iFactorization(NumberInt number) const
{
    PrimeToAccNumber map;
    auto lowestPrimeDivider = std::begin(_primes); //игнорируем возможность maxNumber меньшего 2

    if(number <= 1)
        return map;

    for(auto iter = lowestPrimeDivider; iter != std::end(_primes); )
    {
        if(number % (*iter) == 0)
        {
            map[*iter] += 1;
            lowestPrimeDivider = iter;
            number /= *iter;
        }
        else
            ++iter;
    }

    return map;
}

/***********************************************/
PrimeToAccNumber Computer::intersection(const PrimeToAccNumber& map1, const PrimeToAccNumber& map2) const
{
    PrimeToAccNumber result;

    for(auto const& pair : map1)
    {
        auto foundIter = map2.find(pair.first);

        if(foundIter != std::end(map2))
            result[pair.first] = std::min(pair.second, foundIter->second);
    }

    return result;
}

/***********************************************/
PrimeToAccNumber Computer::merge(const PrimeToAccNumber& map1, const PrimeToAccNumber& map2)
{
    PrimeToAccNumber merged(std::begin(map1), std::end(map1));

    for(auto const& pair : map2)
        merged[pair.first] += pair.second;

    return merged;
}

/***********************************************/
PrimeToAccNumber Computer::substraction(const PrimeToAccNumber& map, const PrimeToAccNumber& subtrahend) const
{
    PrimeToAccNumber result(std::begin(map), std::end(map));

    for(auto const& pair : subtrahend)//все элементы subtrahend должны быть в map
        result[pair.first] -= pair.second;

    return result;
}
