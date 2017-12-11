CC=g++
CFLAGS=-g -Werror
INCLUDEDIR=-I../
LIBDIR=-L../output/lib -lparser -lgtest -lgtest_main -lpthread
BINDIR=./output/bin
unittest_parser: test_parser.cpp 
	rm -rf $(BINDIR)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(INCLUDEDIR) $(LIBDIR)

.PHONY: clean

clean:
	rm -f unittest_parser 
	rm -rf $(BINDIR)
