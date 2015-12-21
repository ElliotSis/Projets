# Variables dossiers
SRCDIR=src
BINDIR=bin
INCLUDEDIR=include

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)

# Variables sources et objets
SRC=$(SRCDIR)/main.c $(SRCDIR)/IHM.c $(SRCDIR)/simulation.c
OBJ= $(SRC:.c=.o)

# Nom du programme
EXEC=simulationAutobus


# Commande par défaut
all: $(BINDIR)/$(EXEC)

# Programme principal
$(BINDIR)/$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ -lm

# Éditions de liens
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

# Nettoyage
clean:
	@rm $(SRCDIR)/*.o

mrproper: clean
	@rm $(BINDIR)/*
			