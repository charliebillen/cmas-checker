objs = build/main.o build/server.o build/content.o build/cmas.o

build/main: $(objs)
	clang -o build/main $(objs)

build/main.o: src/main.c
	clang -c src/main.c -o build/main.o

build/server.o: src/server.c src/server.h
	clang -c src/server.c -o build/server.o

build/content.o: src/content.c src/content.h
	clang -c src/content.c -o build/content.o

build/cmas.o: src/cmas.c src/cmas.h
	clang -c src/cmas.c -o build/cmas.o

clean:
	rm -rf build
	mkdir build

start:
	./build/main

curl:
	curl localhost:3000
