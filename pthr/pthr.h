#ifndef FACTORIAL_PTHREADED_H_
#define FACTORIAL_PTHREADED_H_

#include <gmpxx.h>
#include <pthread.h>
#include <vector>

extern "C" mpz_class factorial(mpz_class value);

#endif
