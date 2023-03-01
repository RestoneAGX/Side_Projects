all:
	gcc -o compressor remix.c -O3
	./compressor test/lamp.obj

dside:
	gcc -o compressor DSide.c -O3
	./compressor test/lamp.obj

bside:
	gcc -o compressor BSide.c -O3
	./compressor test/lamp.obj

clean:
	rm -r output.Robj tempOutput.Robj
