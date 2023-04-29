CC=g++
cflags= -std=c++17 -Wall -Wextra -pedantic
objs=obj/my_sdl.o obj/board.o obj/states.o obj/enums.o obj/ai_min_max.o obj/neural_network.o
# dbg=-fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g -DLOCAL
dbg=-g -ggdb
libs=-lSDL2

bin/game.out: main.cpp $(objs)
	$(CC) $(cflags) main.cpp $(objs) -o bin/game.out $(libs)

obj/my_sdl.o: include/my_sdl.h src/my_sdl.cpp
	$(CC) $(cflags) -c src/my_sdl.cpp -o obj/my_sdl.o

obj/board.o: include/board.h src/board.cpp
	$(CC) $(cflags) -c src/board.cpp -o obj/board.o

obj/states.o: include/states.h src/states.cpp
	$(CC) $(cflags) -c src/states.cpp -o obj/states.o

obj/enums.o: include/enums.h src/enums.cpp
	$(CC) $(cflags) -c src/enums.cpp -o obj/enums.o

obj/ai_min_max.o: include/ai_min_max.h src/ai_min_max.cpp
	$(CC) $(cflags) -c src/ai_min_max.cpp -o obj/ai_min_max.o

obj/neural_network.o: include/neural_network.h src/neural_network.cpp
	$(CC) $(cflags) -c src/neural_network.cpp -o obj/neural_network.o

run: bin/game.out
	bin/game.out

debug:
	$(CC) $(dbg) $(cflags) -c src/enums.cpp -o obj/enums.o
	$(CC) $(dbg) $(cflags) -c src/states.cpp -o obj/states.o
	$(CC) $(dbg) $(cflags) -c src/ai_min_max.cpp -o obj/ai_min_max.o
	$(CC) $(dbg) $(cflags) -c src/my_sdl.cpp -o obj/my_sdl.o
	$(CC) $(dbg) $(cflags) -c src/board.cpp -o obj/board.o
	$(CC) $(dbg) $(cflags) main.cpp $(objs) -o bin/game.out $(libs)

prepare:
	mkdir -p bin include src obj

clean:
	rm obj/*.o
	rm bin/*.out
