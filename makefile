csrc = $(wildcard src/*.c)
ccsrc = $(wildcard src/*.cpp)
obj = $(csrc:.c=.o) $(ccsrc:.cpp=.o)

LDFLAGS = 

main: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)