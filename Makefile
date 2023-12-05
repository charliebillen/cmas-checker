main: src/main.c
	clang -o build/cmas src/*.c

clean:
	rm build/cmas
