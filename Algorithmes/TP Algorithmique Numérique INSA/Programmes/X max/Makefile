# Variables dossiers
SRCDIR=src
BINDIR=bin

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-Wall -pedantic -g

# Variables sources et objets
SRC=$(SRCDIR)/xMax.c
OBJ= $(SRC:.c=.o)

# Nom du programme
EXEC=xMax

# Commande par défaut
all: $(BINDIR)/$(EXEC)

# Programme principal
$(BINDIR)/$(EXEC): $(OBJ)
	@$(CC) -o $@ $^

# Éditions de liens
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage
clean:
	@rm $(SRCDIR)/*.o

mrproper: clean
	@rm $(BINDIR)/*
			