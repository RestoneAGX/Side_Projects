.PHONY: all clean
all:
	gcc -o main main.c -O3 -Wall -Wunused

test:
	./run.bash`
clean:
	rm -r main test.txt #test
