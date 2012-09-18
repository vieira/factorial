#include "thr.h"

void
fact_until(mpz_class limit, mpz_class value, mpz_class &res)
{
  res = value > 0 ? value : 1;
  limit = limit < value ? limit : 0;
  while (--value > limit) res *= value;
}

extern "C" mpz_class
factorial(mpz_class value)
{
  unsigned int num_threads = boost::thread::hardware_concurrency() > value && 
                              value.fits_uint_p() && value > 0 ?
                              value.get_ui() : 
                              boost::thread::hardware_concurrency();
  boost::thread_group factorial;
  std::vector<mpz_class> res(num_threads);
  mpz_class d = value/num_threads;
  for (unsigned int i = 0; i < res.size(); ++i) {
    factorial.create_thread(boost::bind(fact_until, value -= d, value, 
                            boost::ref(res[i])));
  }
  factorial.join_all();

  for (unsigned int i = 1; i < res.size(); ++i) res[0] *= res[i];
  
  return res[0];
}
