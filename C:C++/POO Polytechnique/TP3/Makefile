CC = g++
CFLAGS = -Wall -std=c++11 
EXEC_NAME = TP3
INCLUDE_DIR = include
INCLUDES = -I $(INCLUDE_DIR)/
LIBS = 
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = obj
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o))) $(OBJ_DIR)/main.o

all : $(EXEC_NAME)

clean :
	rm $(OBJ_FILES)

mr-proper :
	make clean
	rm $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR)/main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<