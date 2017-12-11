CC=g++
CFLAGS=-g -Werror
INCLUDEDIR=-I../
LIBDIR=-L../output/lib -lparser
BINDIR=../output/bin
demo: main.cpp 
	rm -rf $(BINDIR)
	mkdir -p $(BINDIR)
	rm -rf ../output/data
	cp -r ./data ../output
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(INCLUDEDIR) $(LIBDIR)
.PHONY: clean
clean:
	rm -f demo
	rm -rf $(BINDIR)
