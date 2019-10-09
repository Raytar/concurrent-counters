

# specify all source files here
SRCS = benchmark.c simple_counter.c safe_counter.c approximate_counter.c

# specify target here (name of executable)
TARG = benchmark 

# specify compiler, compile flags, and needed libs
CC   = gcc
OPTS = -Wall -Werror
LIBS = -pthread -lrt

# this translates .c files in src list to .o’s
OBJS = $(SRCS:.c=.o)

# all is not really needed, but is used to generate the target
all: $(TARG)

# debug mode
debug: OPTS += -DDEBUG -g
debug: $(TARG)

# profile mode
profile: OPTS += -DDEBUG -pg
profile: LIBS += -pg
profile: $(TARG)

# this generates the target executable
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

# this is a generic rule for .o files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

# and finally, a clean line
clean:
	rm -f $(OBJS) $(TARG)
