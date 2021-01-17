export PKG_CONFIG_PATH=./raylib/lib/pkgconfig
PKGS=raylib
CFLAGS=-Wall -Wextra -ggdb -pedantic -std=c11 `pkg-config --cflags --static $(PKGS)`
LIBS=`pkg-config --libs --static $(PKGS)`

probe: main.c
	$(CC) $(CFLAGS) -o probe main.c $(LIBS)
