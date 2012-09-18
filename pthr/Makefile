.PHONY: clean 
CXXFLAGS = $(shell if [ -f /etc/makepkg.conf ]; then cat /etc/makepkg.conf | grep CXXFLAGS | sed 's/"*//g;s/CXXFLAGS=*//g'; fi)
cxx = $(wildcard *.cpp)
obj = $(cxx:.cpp=.o)
lib = $(cxx:.cpp=.so)

$(lib): %.so: %.o
	$(CXX) -ldl -lgmpxx -lgmp -lpthread -shared -o $@ $^

$(obj): %.o: %.cpp
	$(CXX) -fPIC $(CXXFLAGS) -c $^ -o $@

clean:
	$(RM) *.o *.so
