.PHONY: clean libs
CXXFLAGS = $(shell if [ -f /etc/makepkg.conf ]; then cat /etc/makepkg.conf | grep CXXFLAGS | sed 's/"*//g;s/CXXFLAGS=*//g'; fi)
cxx = $(wildcard *.cpp)
libs = $(shell ls -d */)
obj = $(cxx:.cpp=.o)
program = factorial

all: $(program) libs

$(program): $(obj)
	$(CXX) -ldl -lgmpxx -lgmp -o $@ $^ 

$(obj): $(cxx)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

libs:
	@-for lib in $(libs); do \
		$(MAKE) -C $$lib; \
	done

clean:
	$(RM) *.o $(program)
	@for lib in $(libs); do \
		$(MAKE) -C $$lib clean; \
	done
