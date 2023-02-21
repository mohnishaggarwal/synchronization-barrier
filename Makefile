CC=g++ -g -Wall -std=c++17

# List of source files for your disk scheduler
SCHEDULER_SOURCES=main.cpp synchronous_buffer.cpp barrier.cpp

# Generate the names of the disk scheduler's object files
SCHEDULER_OBJS=${SCHEDULER_SOURCES:.cpp=.o}

all: scheduler

# Compile the disk scheduler and tag this compilation
app: ${SCHEDULER_OBJS} libthread_macos.o
	${CC} -o $@ $^ -ldl -pthread

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${SCHEDULER_OBJS} scheduler
