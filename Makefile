TARGET=libparser.a
SRCS=parser.cpp
OBJS=$(SRCS:.cpp=.o)
LIBDIR=./output/lib
CC=g++
CFLAGS=-fPIC -Wall -finline-functions -pipe -g -rdynamic -Wno-invalid-offsetof -Werror
.PHONY: all clean output build
all: $(TARGET) $(LIBDIR)
$(TARGET): $(OBJS)
	rm -f $@
	rm -rf output
	mkdir -p output/lib
	ar cr output/lib/$@ $(OBJS)
%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -f *.o
	rm -f *.a
	rm -rf $(LIBDIR)
