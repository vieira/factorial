#include "iter.h"

extern "C" mpz_class
factorial(mpz_class value)
{
  mpz_class actual_product = value > 0 ? value : 1;
  while (--value > 0) actual_product *= value;
  return actual_product;
}
