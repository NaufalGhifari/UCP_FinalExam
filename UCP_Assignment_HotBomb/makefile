CFLAGS=-Wall -g
CC=gcc
OBJ_1=main.o bombFunc.o bombMainMenu.o linkedList.o
OBJ_2=main.o bombFunc_DEBUG.o bombMainMenu.o linkedList.o
EXEC_1=HOT_BOMB_GAME
EXEC_2=HOT_BOMB_DEBUG

all: $(EXEC_1) $(EXEC_2)

$(EXEC_1): $(OBJ_1)
	$(CC) $(OBJ_1) -o $(EXEC_1)

$(EXEC_2): $(OBJ_2)
	$(CC) $(OBJ_2) -o $(EXEC_2)

main.o: main.c bombHeader.h
	$(CC) -c main.c $(CFLAGS)

bombFunc.o: bombFunc.c bombHeader.h
	$(CC) -c bombFunc.c $(CFLAGS)

bombFunc_DEBUG.o: bombFunc.c bombHeader.h
	$(CC) -c bombFunc.c -DDEBUG=1 -o bombFunc_DEBUG.o $(CFLAGS)

bombMainMenu.o: bombMainMenu.c bombHeader.h
	$(CC) -c bombMainMenu.c $(CFLAGS)

linkedList.o: linkedList.c linkedList.h
	$(CC) -c linkedList.c $(CFLAGS)

clean:
	rm -f $(OBJ_1) $(EXEC_1) $(OBJ_2) $(EXEC_2)