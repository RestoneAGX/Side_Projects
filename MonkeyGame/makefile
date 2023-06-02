OS := $(shell uname)
DISTRO := $(shell lsb_release -si)

WIN_CHAIN := $(HOME)/.toolchains/x86_64-w64-mingw32

ARGS := -Wall -O3 -Os

ifeq ( $(OS), windows ) 
	LDFLAGS := -lmingw32 -lSDL2main -lSDL2
	EXTENSION := .exe
	KILL := del
else
	LDFLAGS := -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
	EXTENSION :=
	KILL :=  rm -r

endif

.PHONY: all os test main
all: main

os:
	echo $(OS)

win:
	clang -o Monkey main.c $(ARGS) --target=x86_64-w64-mingw32 --sysroot=$(WIN_CHAIN) -fuse-ld=lld -lSDL2main -lSDL2

	
test: test_
main: monkey_
clean:
	$(KILL) monkey_ test_ Monkey.exe

# platformer: ./example/platformer

%_:
	zig cc -o $@ main.c $(ARGS) $(LDFLAGS)
# 	./$@$(EXTENSION)

# %_:
# 	gcc cc -o $@ main.c $(ARGS) $(LDFLAGS)
# 	./$@$(EXTENSION)
#	$(KILL) $@$(EXTENSION)
