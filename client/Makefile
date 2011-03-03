# output executable name
EXEC = client
# source files
CXX = g++
CXXFLAGS = -W -Wall -Iinc/
LDFLAGS = 
SRCS = $(wildcard src/*.cpp)
INCS = $(wildcard inc/*.h)
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	rm -rf $(OBJS)
	
doc : $(SRCS) $(INCS)
	doxygen
