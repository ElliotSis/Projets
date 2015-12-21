CC = g++
CFLAGS = -Wall -std=c++11 
INCLUDE_DIR = include
INCLUDES = -I $(INCLUDE_DIR)/ 
LIBS = -lboost_program_options
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = obj
OBJ_FILES = $(OBJ_DIR)/solvers.o $(OBJ_DIR)/main.o

all :
	make vorace
	make dynamique
	make recuitSimule

clean :
	rm $(OBJ_FILES)
	rm $(OBJ_DIR)/vorace.o
	rm $(OBJ_DIR)/dynamique.o
	rm $(OBJ_DIR)/recuitSimule.o

mr-proper :
	make clean
	rm vorace
	rm dynamique
	rm recuitSimule

vorace : $(OBJ_FILES) $(OBJ_DIR)/vorace.o
	$(CC) -o vorace $(OBJ_DIR)/vorace.o  $(OBJ_FILES) $(LIBS)

dynamique : $(OBJ_FILES) $(OBJ_DIR)/dynamique.o
	$(CC) -o dynamique  $(OBJ_DIR)/dynamique.o  $(OBJ_FILES) $(LIBS)

recuitSimule : $(OBJ_FILES) $(OBJ_DIR)/recuitSimule.o
	$(CC) -o recuitSimule  $(OBJ_DIR)/recuitSimule.o $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	