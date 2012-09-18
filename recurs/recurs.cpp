#include "recurs.h"

extern "C" mpz_class
factorial(mpz_class value)
{
  if (value == 0) return 1;
  else return factorial(value-1) * value;
}
