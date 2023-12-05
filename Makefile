objs = build/main.o build/server.o build/content.o build/cmas.o

cc = clang -O -Wall -std=c17

build/main: $(objs)
	$(cc) -o build/main $(objs)

build/main.o: src/main.c
	$(cc) -c src/main.c -o build/main.o

build/server.o: src/server.c src/server.h
	$(cc) -c src/server.c -o build/server.o

build/content.o: src/content.c src/content.h
	$(cc) -c src/content.c -o build/content.o

build/cmas.o: src/cmas.c src/cmas.h
	$(cc) -c src/cmas.c -o build/cmas.o

configure:
	mkdir -p build

clean:
	rm -rf build
	mkdir build

start:
	./build/main

curl:
	curl localhost:3000
