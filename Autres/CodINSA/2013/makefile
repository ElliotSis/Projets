SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
TESTDIR=test
DOCDIR=doc
RAPPORTDIR=../rapport
CC=g++ -g
AR=ar
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR) -std=c99
LDFLAGS=-L$(LIBDIR)
LDFLAGSTU=-lcunit
EXEC=codInsa

all : code

code: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o
	$(CC) $(LDFLAGS) -o $@ $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean : 
	rm $(BINDIR)/*
	rm $(SRCDIR)/*.o

mrproper: clean
