# output executable name
EXEC = client
# source files
CXX = g++
CXXFLAGS = -W -Wall -Iinc/
LDFLAGS = 
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJS)
	
doc: src/*.cpp inc/*.h
	doxygen
