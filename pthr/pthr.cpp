#include "pthr.h"

struct argument_t {
  mpz_class value;
  mpz_class limit;
  mpz_class result;
};

void*
fact_until(void *operand)
{
  argument_t *a = (argument_t*) operand;
  a->result = a->value > 0 ? a->value : 1;
  a->limit = a->limit < a->value ? a->limit : 0;
  while (--a->value > a->limit) a->result *= a->value;
}

extern "C" mpz_class
factorial(mpz_class value)
{
  unsigned int num_threads = sysconf(_SC_NPROCESSORS_ONLN) > value &&
                              value.fits_uint_p() && value > 0 ?
                              value.get_ui() :
                              sysconf(_SC_NPROCESSORS_ONLN);
  std::vector<pthread_t> threads(num_threads);
  std::vector<argument_t> arg(num_threads);
  mpz_class d = value/num_threads;
  for (unsigned int i = 0; i < arg.size(); ++i) {
    arg[i].result = arg[i].value = value;
    arg[i].limit = value -= d;
    pthread_create(&threads[i], NULL, fact_until, (void*) &arg[i]);
  }

  for (unsigned int i = 0; i < arg.size(); ++i) {
    pthread_join(threads[i], NULL);
    if (i) arg[0].result *= arg[i].result;
  }
  return arg[0].result;
}
