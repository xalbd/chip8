src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CXXFLAGS = -std=c++1z

run: $(obj)
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) run