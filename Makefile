CC = gcc
CCFLAGS = -g -O2 -Wall
TARGET = a

SRC = src
OBJ = obj
INC = include

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CCFLAGS) -I $(INC) -c $< -o $@ 

clean:
	del /f obj\*.o
	del /f a.exe