# output executable name
EXEC = test
# source files
CC = g++
CXXFLAGS = 
LDFLAGS = 
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS)
clean:
	rm -rf $(OBJS)
