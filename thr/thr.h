#ifndef FACTORIAL_THREADED_H_
#define FACTORIAL_THREADED_H_

#include <gmpxx.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

extern "C" mpz_class factorial(mpz_class value);

#endif
