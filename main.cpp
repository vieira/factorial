#include <dlfcn.h>
#include <gmpxx.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

int
main(int argc, char *argv[])
{
  int opt, index;
  std::string library = "iter";
  mpz_class value = -1;

  while ((opt = getopt(argc, argv, "l:v:h")) != EOF) {
    switch(opt) {
      case 'l':
        library = optarg;
        break;
      case 'v':
        value = optarg;
        break;
      case 'h':
        std::cout << "Usage: " << argv[0] << " [-v] number [-l library]" << std::endl;
        std::cout << "Compute the factorial of the given argument using the specified "
                  << "library." << std::endl;
        std::cout << "\t -v \t a positive integer." << std::endl;
        std::cout << "\t -l \t name of a library." << std::endl;
        return 0;
      case '?':
        std::cerr << "Usage: " << argv[0] << " [-v] number [-l library]" << std::endl;
        std::cerr << "Try `" << argv[0] << " -h' for more information." << std::endl;
        return 1;
      default:
        abort();
    }
  }

  for (index = optind; index < argc; ++index) {
    try {
      value = argv[index];
    } catch (std::invalid_argument) {
      std::cerr << argv[0] << ": argument " << argv[1] << " is not a number." << std::endl;
      std::cerr << "Usage: " << argv[0] << " [-v] number [-l library] " << std::endl;
      std::cerr << "Try `" << argv[0] << " -h' for more information." << std::endl;
      return 1;
    }
  }

  if (value < 0 && (!(std::cin >> value) || value < 0)) {
    std::cerr << argv[0] << ": expecting a positive integer." << std::endl;
    return 1;
  }

  library = library + "/" + library + ".so";
  void *handle = dlopen(library.c_str(), RTLD_LAZY);

  if (!handle) {
    std::cerr << "Cannot open library" << std::endl;
    std::cerr << dlerror() << std::endl;
    return 1;
  }

  typedef mpz_class (*mpz_class)(mpz_class);
  mpz_class factorial = (mpz_class) dlsym(handle, "factorial");

  if (!factorial) {
    std::cerr << "Cannot load symbol 'factorial'" << std::endl;
    std::cerr << dlerror() << std::endl;
    dlclose(handle);
    return 1;
  }

  std::cout << factorial(value) << std::endl;

  dlclose(handle);

  return 0;
}
