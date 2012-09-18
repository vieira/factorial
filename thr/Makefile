.PHONY: clean check
CXXFLAGS = $(shell if [ -f /etc/makepkg.conf ]; then cat /etc/makepkg.conf | grep CXXFLAGS | sed 's/"*//g;s/CXXFLAGS=*//g'; fi)
boost = $(shell if [ -f /usr/lib/libboost_thread-mt.so ]; then echo "found"; fi)
cxx = $(wildcard *.cpp)
obj = $(cxx:.cpp=.o)
lib = $(cxx:.cpp=.so)

all: check $(lib)

$(lib): %.so: %.o
	$(CXX) -ldl -lgmpxx -lgmp -lboost_thread-mt -shared -o $@ $^

$(obj): %.o: %.cpp
	$(CXX) -fPIC $(CXXFLAGS) -c $^ -o $@

check:
	$(info Checking for Boost:)
ifneq ($(boost), found)
	$(info >> Error: Not found!)
	@false
else
	$(info >> OK)
endif

clean:
	$(RM) *.o *.so
